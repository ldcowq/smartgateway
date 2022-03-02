package com.hr.smarthome.ui.homeEnvironment;

import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;

import androidx.annotation.NonNull;
import androidx.cardview.widget.CardView;
import androidx.recyclerview.widget.RecyclerView;

import com.hr.smarthome.R;

import java.util.List;

public class homeEnvironmentAdapter extends RecyclerView.Adapter<homeEnvironmentAdapter.ViewHolder> {

    private Context mContext;
    private List<homeEnvironment> mLightList;

    static class ViewHolder extends RecyclerView.ViewHolder {


        TextView tempTextview;
        TextView humiTextview;
        TextView carbonTextview;
        TextView smokeTextview;


        public ViewHolder(@NonNull View view) {
            super(view);
            tempTextview = view.findViewById(R.id.temp_num_textview);
            humiTextview = view.findViewById(R.id.humi_num_textview);
            carbonTextview = view.findViewById(R.id.carbon_num_textview);
            smokeTextview = view.findViewById(R.id.smoke_num_textview);

        }
    }

    public homeEnvironmentAdapter(List<homeEnvironment> lightList) {
        mLightList = lightList;
    }

    @NonNull
    @Override
    public ViewHolder onCreateViewHolder(@NonNull ViewGroup parent, int viewType) {
        if (mContext == null) {
            mContext = parent.getContext();
        }
        View view = LayoutInflater.from(mContext).inflate(R.layout.cardview_home_environment, parent, false);
        final homeEnvironmentAdapter.ViewHolder holder = new homeEnvironmentAdapter.ViewHolder(view);
        return holder;
    }

    @Override
    public void onBindViewHolder(@NonNull ViewHolder holder, int position) {
        homeEnvironment homeEnvironmentJavebean = mLightList.get(position);
        holder.tempTextview.setText(homeEnvironmentJavebean.getTemperature()+"℃");
        holder.humiTextview.setText(homeEnvironmentJavebean.getHumidity()+"%");
        holder.carbonTextview.setText(homeEnvironmentJavebean.getCarbon()+"%");
        holder.smokeTextview.setText(homeEnvironmentJavebean.getSmoke()+"%");
    }


    @Override
    public int getItemCount() {
        return mLightList.size();
    }
}
