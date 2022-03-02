package com.hr.smarthome.ui.mq2;


import android.os.Bundle;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.fragment.app.Fragment;
import androidx.recyclerview.widget.GridLayoutManager;
import androidx.recyclerview.widget.RecyclerView;
import androidx.swiperefreshlayout.widget.SwipeRefreshLayout;

import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

import com.google.gson.Gson;
import com.google.gson.reflect.TypeToken;
import com.hr.smarthome.R;
import com.hr.smarthome.okhttp.OkHttpUtil;
import com.hr.smarthome.ui.temphumi.TempHumiJavaBean;

import org.jetbrains.annotations.NotNull;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

import okhttp3.Call;
import okhttp3.Callback;
import okhttp3.Response;

public class Mq2Fragment extends Fragment {
    private List<Mq2JavaBean> mMq2dataList = new ArrayList<Mq2JavaBean>();
    private Mq2ViewModel mViewModel;
    private Mq2Adapter adapter;
    private SwipeRefreshLayout swipeRefresh;

    @Override
    public View onCreateView(@NonNull LayoutInflater inflater, @Nullable ViewGroup container,
                             @Nullable Bundle savedInstanceState) {
        View view = inflater.inflate(R.layout.fragment_mq2, container, false);
        RecyclerView recyclerView = view.findViewById(R.id.mq2_recyclerview);
        GridLayoutManager gridLayoutManager = new GridLayoutManager(getContext(), 1);
        recyclerView.setLayoutManager(gridLayoutManager);
        adapter = new Mq2Adapter(mMq2dataList);
        recyclerView.setAdapter(adapter);
        swipeRefresh = view.findViewById(R.id.mq2_swipe_refresh);
        swipeRefresh.setColorScheme(R.color.colorPrimary);
        swipeRefresh.setOnRefreshListener(new SwipeRefreshLayout.OnRefreshListener() {
            @Override
            public void onRefresh() {
                //从数据库获取最新的温湿度数据
                refresh();
                swipeRefresh.setRefreshing(false);
            }
        });
        System.out.println("oncreateview()________");
        //refresh();
        return view;
    }

    private void refresh() {
        if (isAdded()) {
            getActivity().runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    OkHttpUtil.sendHttpRequest("http://106.13.7.2:8080/smarthome/QuerySensor?pageNo=1&&pageSize=15", new Callback() {
                        @Override
                        public void onResponse(@NotNull Call call, @NotNull Response response) throws IOException {
                            String responseData = response.body().string();
                            System.out.println(responseData);
//                                    Gson gson = new Gson();
//                                    List<Mq2JavaBean> mq2JavaBeans = gson.fromJson(responseData, new TypeToken<List<Mq2JavaBean>>() {
//                                    }.getType());
//                                    for (Mq2JavaBean t : mq2JavaBeans) {
//                                        mMq2dataList.add(new Mq2JavaBean(t.getMq2()));
//                                    }
                            mMq2dataList.add(new Mq2JavaBean("15"));

                        }

                        @Override
                        public void onFailure(@NotNull Call call, @NotNull IOException e) {
                            e.printStackTrace();
                        }
                    });
                    adapter.notifyDataSetChanged();
                }
            });
        }
    }

    @Override
    public void onStart() {
        super.onStart();
        System.out.println("MQ:  start()________");
    }

    @Override
    public void onResume() {
        super.onResume();
        System.out.println("MQ:  onresume()________");
    }


    @Override
    public void onPause() {
        super.onPause();
        System.out.println("MQ:  onpause()________");
    }

    @Override
    public void onStop() {
        super.onStop();
        System.out.println("MQ:  onstop()________");
    }

    @Override
    public void onDestroy() {
        super.onDestroy();
        System.out.println("MQ:  ondestroy()________");
    }

    @Override
    public void onActivityCreated(@Nullable Bundle savedInstanceState) {
        super.onActivityCreated(savedInstanceState);

    }

}