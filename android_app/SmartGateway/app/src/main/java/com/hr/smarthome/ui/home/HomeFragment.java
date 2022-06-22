package com.hr.smarthome.ui.home;

import android.annotation.SuppressLint;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.CompoundButton;
import android.widget.Switch;
import android.widget.TextView;
import android.widget.Toast;

import androidx.annotation.NonNull;
import androidx.fragment.app.Fragment;

import com.alibaba.fastjson.JSONObject;
import com.hr.smarthome.MyApplication;
import com.hr.smarthome.R;

import org.eclipse.paho.client.mqttv3.IMqttDeliveryToken;
import org.eclipse.paho.client.mqttv3.IMqttToken;
import org.eclipse.paho.client.mqttv3.MqttAsyncClient;
import org.eclipse.paho.client.mqttv3.MqttCallback;
import org.eclipse.paho.client.mqttv3.MqttClient;
import org.eclipse.paho.client.mqttv3.MqttConnectOptions;
import org.eclipse.paho.client.mqttv3.MqttException;
import org.eclipse.paho.client.mqttv3.MqttMessage;
import org.eclipse.paho.client.mqttv3.persist.MemoryPersistence;

import java.util.concurrent.Executors;
import java.util.concurrent.ScheduledExecutorService;
import java.util.concurrent.TimeUnit;

public class HomeFragment extends Fragment {

    private TextView temp_num_tv;
    private TextView humi_num_tv;
    private TextView smoke_num_tv;
    private TextView carbon_num_tv;

    private int temp;
    private int humi;
    private int carbon;
    private int smoke;

    private String serverURI = "tcp://你的服务器IP:1883";//请填写你自己的服务器IP
    private String topic = "SmartGatewayPub";
    private String userName = "phone";
    private String passWord = "222222";
    private String mqtt_id = "105d51";
    private ScheduledExecutorService scheduler;

    private Switch getdata_swith;
    private MqttClient mqttClient;
    private MqttConnectOptions connectOptions;
    private Handler handler;

    @SuppressLint("HandlerLeak")
    public View onCreateView(@NonNull LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {

        View view = inflater.inflate(R.layout.fragment_home, container, false);//加载布局
        temp_num_tv = view.findViewById(R.id.temp_num_show_tv);
        humi_num_tv = view.findViewById(R.id.humi_num_show_tv);
        smoke_num_tv = view.findViewById(R.id.smoke_num_show_tv);
        carbon_num_tv = view.findViewById(R.id.carbon_num_show_tv);
        getdata_swith = view.findViewById(R.id.getdata_home);
        getdata_swith.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
                if (isChecked) {
                    mqttInit();
                    Mqtt_connect();
                    try {
                        while (!mqttClient.isConnected()) ;//等待连接到mqtt服务器
                        if (mqttClient != null && mqttClient.isConnected()) {
                            mqttClient.subscribe(topic, 0);
                        } else {
                            System.out.println("主题订阅失败！");
                        }
                    } catch (MqttException e) {
                        e.printStackTrace();
                        getdata_swith.setChecked(false);
                    }
                } else {
                    if (mqttClient.isConnected() && mqttClient != null) {
                        try {
                            mqttClient.unsubscribe(topic);
                            disconnect();
                        } catch (MqttException e) {
                            e.printStackTrace();
                        }
                    }
                }
            }
        });

        handler = new Handler() {
            @SuppressLint("SetTextI18n")
            public void handleMessage(Message msg) {
                super.handleMessage(msg);
                switch (msg.what) {
                    case 1: //开机校验更新回传
                        break;
                    case 2:  // 反馈回传
                        break;
                    case 3:  //MQTT 收到消息回传
                        System.out.println("---------------------------"+msg.obj.toString());
                        JSONObject jsonObject = (JSONObject) JSONObject.parse((msg.obj.toString()));
                        String type = jsonObject.getString("type");
                        System.out.println(type);
                        if (type.equals("kitchen"))
                        {
                            carbon = jsonObject.getInteger("Carbon");
                            smoke = jsonObject.getInteger("Smoke");
                            carbon_num_tv.setText(carbon + " %");
                            smoke_num_tv.setText(smoke + " %");
                        }else if(type.equals("living")){
                            temp = jsonObject.getInteger("Temperature");
                            humi = jsonObject.getInteger("Humidity");
                            temp_num_tv.setText(temp + " ℃");
                            humi_num_tv.setText(humi + " %");
                        }
                        break;
                    case 4:  //连接失败
                        Toast.makeText(getActivity(), "连接失败", Toast.LENGTH_SHORT).show();
                        break;
                    case 5:   //连接成功
                        Toast.makeText(getActivity(), "连接成功", Toast.LENGTH_SHORT).show();
                        try {
                            mqttClient.subscribe(topic, 0);
                        } catch (MqttException e) {
                            e.printStackTrace();
                        }
                        break;
                    default:
                        break;
                }
            }
        };
        return view;
    }


    private void mqttInit() {
        try {
            //host为服务器主机名，ClientId_editText获取客户端的id，MemoryPersistence设置客户端id的保存形式，默认为内存保存。
            mqttClient = new MqttClient(serverURI, mqtt_id, new MemoryPersistence());
            //Mqtt的连接配置
            connectOptions = new MqttConnectOptions();
            //设置是否清空session，这里如果设置false，表示服务器会保留客户端的连接记录，设置为true表示每次连接到服务器都以新的身份连接.
            connectOptions.setCleanSession(false);
            //设置连接的用户名
            connectOptions.setUserName(userName);

            //设置连接的密码
            connectOptions.setPassword(passWord.toCharArray());

            //设置超时时间，单位为秒
            connectOptions.setConnectionTimeout(10);

            //设置会话心跳时间,单位为秒,服务器会每隔1.5×20秒的时间向客户端发送一个消息，判断客户端是否在线，但这个方法没有重连的机制.
            connectOptions.setKeepAliveInterval(20);

            //设置回调函数
            mqttClient.setCallback(new MqttCallback() {
                @Override
                public void connectionLost(Throwable cause) {
                    //连接丢失后，一般在这里进行重连.
                    //Toast.makeText(MainActivity.this, "连接已断开！", Toast.LENGTH_SHORT).show();
                    startReconnect();
                    System.out.println("mqtt连接断开");
                }

                @Override
                public void messageArrived(String topicName, MqttMessage message) throws Exception {
                    //订阅后得到的消息会执行到这里
                    System.out.println(message);
                    Message msg = new Message();
                    msg.what = 3;   //收到消息标志位
                    msg.obj = message.toString();
                    handler.sendMessage(msg);    // hander 回传
                }

                @Override
                public void deliveryComplete(IMqttDeliveryToken token) {
                    //推送消息后会执行到这个函数
                }
            });
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private void disconnect() {
        if (mqttClient != null) {
            try {
                Toast.makeText(MyApplication.getContext(), "断开成功！", Toast.LENGTH_SHORT).show();
                mqttClient.disconnect();
                getdata_swith.setChecked(false);
            } catch (MqttException e) {
                e.printStackTrace();
            }
        }
    }

    @Override
    public void onDestroy() {
        super.onDestroy();
        disconnect();
    }

    private void Mqtt_connect() {
        new Thread(new Runnable() {
            @Override
            public void run() {
                try {
                    //mqttClient.disconnect();
                    if (!(mqttClient.isConnected())) {//如果还没有连接
                        mqttClient.connect(connectOptions);
                        Message msg = new Message();
                        msg.what = 5;
                        handler.sendMessage(msg);
                    }
                } catch (Exception e) {
                    e.printStackTrace();
                    Message msg = new Message();
                    msg.what = 4;
                    handler.sendMessage(msg);
                }
            }
        }).start();
    }

    private void startReconnect() {
        scheduler = Executors.newSingleThreadScheduledExecutor();
        scheduler.scheduleAtFixedRate(new Runnable() {
            @Override
            public void run() {
                if (!mqttClient.isConnected()) {
                    Mqtt_connect();
                }
            }
        }, 0 * 1000, 10 * 1000, TimeUnit.MILLISECONDS);
    }

}