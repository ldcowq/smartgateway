package com.hr.smarthome.ui.control;

import android.os.Bundle;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.fragment.app.Fragment;

import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.CompoundButton;
import android.widget.ImageView;
import android.widget.Switch;
import android.widget.Toast;

import com.hr.smarthome.MyApplication;
import com.hr.smarthome.R;

import org.eclipse.paho.client.mqttv3.IMqttDeliveryToken;
import org.eclipse.paho.client.mqttv3.IMqttToken;
import org.eclipse.paho.client.mqttv3.MqttAsyncClient;
import org.eclipse.paho.client.mqttv3.MqttCallback;
import org.eclipse.paho.client.mqttv3.MqttConnectOptions;
import org.eclipse.paho.client.mqttv3.MqttException;
import org.eclipse.paho.client.mqttv3.MqttMessage;
import org.eclipse.paho.client.mqttv3.persist.MemoryPersistence;

public class ControlFragment extends Fragment {

    private MqttAsyncClient mqttClient;
    private MqttConnectOptions connectOptions;

    String topic = "SmartHomeSub";

    private ImageView livingroom_light_img;
    private ImageView livingroom_beep_img;

    private ImageView kitchen_light_img;
    private ImageView kitchen_fan_img;

    private Switch livingroom_light_switch;
    private Switch livingroom_beep_switch;

    private Switch kitchen_light_switch;
    private Switch kitchen_fan_switch;



    @Override
    public View onCreateView(@NonNull LayoutInflater inflater, @Nullable ViewGroup container,
                             @Nullable Bundle savedInstanceState) {
        View view = inflater.inflate(R.layout.fragment_control, container, false);

        livingroom_light_img = view.findViewById(R.id.control_livingroom_light_img);
        livingroom_beep_img = view.findViewById(R.id.control_livingroom_fan_img);
        kitchen_light_img = view.findViewById(R.id.control_kitchen_light_img);
        kitchen_fan_img = view.findViewById(R.id.control_kitchen_fan_img);

        livingroom_light_switch = view.findViewById(R.id.livingroom_light_switch);
        livingroom_beep_switch = view.findViewById(R.id.livingroom_fan_switch);
        kitchen_light_switch = view.findViewById(R.id.kitchen_light_switch);
        kitchen_fan_switch = view.findViewById(R.id.kitchen_fan_switch);

        mqttInit();
        Mqtt_connect();
        return view;

    }

    @Override
    public void onStart() {
        super.onStart();
        livingroom_light_switch.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
                if (isChecked) {
                    while (!mqttClient.isConnected()) ;
                    if (mqttClient != null && mqttClient.isConnected()) {
                        try {
                            String payload = "111";
                            MqttMessage mqttMessage = new MqttMessage(payload.getBytes());
                            mqttClient.publish(topic, mqttMessage);
                            livingroom_light_img.setImageResource(R.drawable.livingroom_light_open);
                        } catch (MqttException e) {
                            e.printStackTrace();
                        }
                    } else {
                        livingroom_light_switch.setChecked(false);
                        livingroom_light_img.setImageResource(R.drawable.livingroom_light_close);
                    }
                } else {
                    try {
                        String payload = "110";
                        MqttMessage mqttMessage = new MqttMessage(payload.getBytes());
                        mqttClient.publish(topic, mqttMessage);
                        livingroom_light_img.setImageResource(R.drawable.livingroom_light_close);
                    } catch (MqttException e) {
                        e.printStackTrace();
                    }
                }
            }
        });


        livingroom_beep_switch.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
                if (isChecked) {
                    while (!mqttClient.isConnected()) ;
                    if (mqttClient != null && mqttClient.isConnected()) {
                        try {
                            String payload = "121";
                            MqttMessage mqttMessage = new MqttMessage(payload.getBytes());
                            mqttClient.publish(topic, mqttMessage);
                            livingroom_beep_img.setImageResource(R.drawable.livingroom_beep_open);
                        } catch (MqttException e) {
                            e.printStackTrace();
                        }
                    } else {
                        livingroom_beep_switch.setChecked(false);
                        livingroom_beep_img.setImageResource(R.drawable.livingroom_beep_close);
                    }
                } else {
                    try {
                        String payload = "120";
                        MqttMessage mqttMessage = new MqttMessage(payload.getBytes());
                        mqttClient.publish(topic, mqttMessage);
                        livingroom_beep_img.setImageResource(R.drawable.livingroom_beep_close);
                    } catch (MqttException e) {
                        e.printStackTrace();
                    }
                }
            }
        });


        kitchen_light_switch.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
                if (isChecked) {
                    while (!mqttClient.isConnected()) ;
                    if (mqttClient != null && mqttClient.isConnected()) {
                        try {
                            String payload = "211";
                            MqttMessage mqttMessage = new MqttMessage(payload.getBytes());
                            mqttClient.publish(topic, mqttMessage);
                            kitchen_light_img.setImageResource(R.drawable.kitchen_light_open);
                        } catch (MqttException e) {
                            e.printStackTrace();
                        }
                    } else {
                        kitchen_light_switch.setChecked(false);
                        kitchen_light_img.setImageResource(R.drawable.kitchen_light_close);
                    }
                } else {
                    try {
                        String payload = "210";
                        MqttMessage mqttMessage = new MqttMessage(payload.getBytes());
                        mqttClient.publish(topic, mqttMessage);
                        kitchen_light_img.setImageResource(R.drawable.kitchen_light_close);
                    } catch (MqttException e) {
                        e.printStackTrace();
                    }
                }
            }
        });


        kitchen_fan_switch.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
                if (isChecked) {

                    while (!mqttClient.isConnected()) ;
                    if (mqttClient != null && mqttClient.isConnected()) {
                        try {
                            String payload = "221";
                            MqttMessage mqttMessage = new MqttMessage(payload.getBytes());
                            mqttClient.publish(topic, mqttMessage);
                            kitchen_fan_img.setImageResource(R.drawable.kitchen_fan_open);
                        } catch (MqttException e) {
                            e.printStackTrace();
                        }
                    } else {
                        kitchen_fan_switch.setChecked(false);
                        kitchen_fan_img.setImageResource(R.drawable.kitchen_fan_close);
                    }
                } else {
                    try {
                        String payload = "220";
                        MqttMessage mqttMessage = new MqttMessage(payload.getBytes());
                        mqttClient.publish(topic, mqttMessage);
                        kitchen_fan_img.setImageResource(R.drawable.kitchen_fan_close);
                    } catch (MqttException e) {
                        e.printStackTrace();
                    }
                }
            }
        });

    }


    private void mqttInit() {
        try {
            //host为服务器主机名，ClientId_editText获取客户端的id，MemoryPersistence设置客户端id的保存形式，默认为内存保存
            String serverURI = "tcp://你的服务器IP:1883";//请填写你自己的服务器IP
            //Toast.makeText(MyApplication.getContext(), serverURI, Toast.LENGTH_SHORT).show();

            mqttClient = new MqttAsyncClient(serverURI, "hostPhone_control", new MemoryPersistence());
            //Mqtt的连接配置
            connectOptions = new MqttConnectOptions();
            //设置是否清空session，这里如果设置force，表示服务器会保留客户端的连接记录，设置为true表示每次连接到服务器都以新的身份连接.
            connectOptions.setCleanSession(false);
            //设置连接的用户名
            connectOptions.setUserName("control");

            //设置连接的密码
            connectOptions.setPassword("root".toCharArray());

            //设置超时时间，单位为秒
            connectOptions.setConnectionTimeout(10);

            //设置会话心跳时间,单位为秒,服务器会每隔1.5×20秒的时间向客户端发送一个消息，判断客户端是否在线，但这个方法没有重连的机制.
            connectOptions.setKeepAliveInterval(20);

            //设置回调函数
            mqttClient.setCallback(new MqttCallback() {
                @Override
                public void connectionLost(Throwable cause) {
                    //连接丢失后，一般在这里进行重连.
                    Mqtt_connect();
                    cause.printStackTrace();
                }

                @Override
                public void messageArrived(String topicName, MqttMessage message) throws Exception {

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
                mqttClient.disconnect();
            } catch (MqttException e) {
                e.printStackTrace();
            }
        }
    }


    private void Mqtt_connect() {
        new Thread(new Runnable() {
            @Override
            public void run() {
                try {
                    if (!(mqttClient.isConnected())) {//如果还没有连接
                        IMqttToken token = mqttClient.connect(connectOptions);
                        token.waitForCompletion();
                        System.out.println("连接成功");
                    } else {
                        System.out.println("连接失败！");
                    }
                } catch (Exception e) {
                    e.printStackTrace();
                }
            }
        }).start();
    }

    @Override
    public void onDestroy() {
        super.onDestroy();
        disconnect();
    }

    @Override
    public void onActivityCreated(@Nullable Bundle savedInstanceState) {
        super.onActivityCreated(savedInstanceState);

    }

}