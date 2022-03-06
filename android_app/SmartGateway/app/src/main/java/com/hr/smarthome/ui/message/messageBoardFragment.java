package com.hr.smarthome.ui.message;

import androidx.lifecycle.ViewModelProvider;

import android.os.Bundle;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.fragment.app.Fragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;

import android.widget.EditText;
import android.widget.Toast;

import com.hr.smarthome.R;

import org.eclipse.paho.client.mqttv3.IMqttDeliveryToken;
import org.eclipse.paho.client.mqttv3.IMqttToken;
import org.eclipse.paho.client.mqttv3.MqttAsyncClient;
import org.eclipse.paho.client.mqttv3.MqttCallback;
import org.eclipse.paho.client.mqttv3.MqttConnectOptions;
import org.eclipse.paho.client.mqttv3.MqttException;
import org.eclipse.paho.client.mqttv3.MqttMessage;
import org.eclipse.paho.client.mqttv3.persist.MemoryPersistence;

public class messageBoardFragment extends Fragment {

    private MqttAsyncClient mqttClient;
    private MqttConnectOptions connectOptions;

    String topic = "SmartHomeSub";

    private MessageBoardViewModel mViewModel;
    private EditText messageEditText;
    private Button sendMessageBtn;
    private Button clearMessageBtn;

    @Override
    public View onCreateView(@NonNull LayoutInflater inflater, @Nullable ViewGroup container, @Nullable Bundle savedInstanceState) {
        View view = inflater.inflate(R.layout.message_board_fragment, container, false);
        messageEditText = view.findViewById(R.id.message_inPut_MultiLine);
        sendMessageBtn = view.findViewById(R.id.sendMessage_btn);
        clearMessageBtn = view.findViewById(R.id.clearMessage_btn);
        mqttInit();
        Mqtt_connect();
        return view;
    }

    @Override
    public void onStart() {
        super.onStart();
        sendMessageBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if (v.getId() == R.id.sendMessage_btn) {
                    while (!mqttClient.isConnected()) ;
                    if (mqttClient != null && mqttClient.isConnected()) {
                        try {
                            String payload = messageEditText.getText().toString();
                            MqttMessage mqttMessage = new MqttMessage(payload.getBytes());
                            mqttClient.publish(topic, mqttMessage);
                            Toast.makeText(getContext(), "留言成功", Toast.LENGTH_SHORT).show();
                        } catch (MqttException e) {
                            e.printStackTrace();
                        }
                    }
                }
            }
        });

        clearMessageBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if (v.getId() == R.id.clearMessage_btn) {
                    messageEditText.setText("");
                }
            }
        });
    }

    private void mqttInit() {
        try {
            //host为服务器主机名，ClientId_editText获取客户端的id，MemoryPersistence设置客户端id的保存形式，默认为内存保存
            String serverURI = "tcp://106.13.7.2:1883";
            //Toast.makeText(MyApplication.getContext(), serverURI, Toast.LENGTH_SHORT).show();

            mqttClient = new MqttAsyncClient(serverURI, "hostPhone_message", new MemoryPersistence());
            //Mqtt的连接配置
            connectOptions = new MqttConnectOptions();
            //设置是否清空session，这里如果设置force，表示服务器会保留客户端的连接记录，设置为true表示每次连接到服务器都以新的身份连接.
            connectOptions.setCleanSession(false);
            //设置连接的用户名
            connectOptions.setUserName("message");

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
        mViewModel = new ViewModelProvider(this).get(MessageBoardViewModel.class);
        // TODO: Use the ViewModel
    }

}