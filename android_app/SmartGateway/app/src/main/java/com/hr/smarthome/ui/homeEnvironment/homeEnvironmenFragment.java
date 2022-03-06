package com.hr.smarthome.ui.homeEnvironment;


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

import org.jetbrains.annotations.NotNull;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

import okhttp3.Call;
import okhttp3.Callback;
import okhttp3.Response;

public class homeEnvironmenFragment extends Fragment {

    private HomeEnvironmenViewModel mViewModel;
    private List<homeEnvironment> mSensorDataList = new ArrayList<>();
    private homeEnvironmentAdapter adapter;
    private SwipeRefreshLayout swipeRefresh;


    @Override
    public View onCreateView(@NonNull LayoutInflater inflater, @Nullable ViewGroup container, @Nullable Bundle savedInstanceState) {
        View view = inflater.inflate(R.layout.home_environmen_fragment, container, false);
        RecyclerView recyclerView = view.findViewById(R.id.homeEnvironment_recyclerview);
        GridLayoutManager gridLayoutManager = new GridLayoutManager(getContext(), 1);
        recyclerView.setLayoutManager(gridLayoutManager);
        adapter = new homeEnvironmentAdapter(mSensorDataList);
        recyclerView.setAdapter(adapter);
        swipeRefresh = view.findViewById(R.id.homeEnvironment_swipe_refresh);
        swipeRefresh.setColorScheme(R.color.colorPrimary);
        swipeRefresh.setOnRefreshListener(new SwipeRefreshLayout.OnRefreshListener() {
            @Override
            public void onRefresh() {
                refresh();
                swipeRefresh.setRefreshing(false);
            }
        });

        refresh();
        return view;
    }

    private void refresh() {
        if (isAdded()) {
            getActivity().runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    OkHttpUtil.sendHttpRequest("http://106.13.7.2:8080/smarthome/QuerySensor?pageNo=1&&pageSize=20", new Callback() {
                        @Override
                        public void onResponse(@NotNull Call call, @NotNull Response response) throws IOException {
                            String responseData = response.body().string();
                            System.out.println(responseData);
                            Gson gson = new Gson();
                            List<homeEnvironment> homeEnvironmentJavaBeans = gson.fromJson(responseData, new TypeToken<List<homeEnvironment>>() {
                            }.getType());
                            for (homeEnvironment h : homeEnvironmentJavaBeans) {
                                mSensorDataList.add(new homeEnvironment(h.getTemperature(), h.getHumidity(), h.getCarbon(), h.getSmoke()));
                            }
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
    public void onActivityCreated(@Nullable Bundle savedInstanceState) {
        super.onActivityCreated(savedInstanceState);

    }

}