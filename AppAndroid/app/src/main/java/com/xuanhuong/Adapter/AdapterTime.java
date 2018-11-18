package com.xuanhuong.Adapter;

import android.content.Context;
import android.support.v7.widget.RecyclerView;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;
import android.widget.TextView;

import com.xuanhuong.Model.TimeOpen;
import com.xuanhuong.controllight.R;

import java.util.List;

/**
 * Created by CR7 on 3/12/2018.
 */

public class AdapterTime extends RecyclerView.Adapter<AdapterTime.ExpertViewHolder> {
    private List<TimeOpen> listTimeOpen;
    private Context context;

    public AdapterTime(List<TimeOpen> listTimeOpen, Context context) {
        this.listTimeOpen = listTimeOpen;
        this.context = context;
    }

    @Override
    public AdapterTime.ExpertViewHolder onCreateViewHolder(ViewGroup parent, int viewType) {
        View view = LayoutInflater.from(context).inflate(R.layout.item_history, parent, false);
        return new ExpertViewHolder(view);
    }

    @Override
    public void onBindViewHolder(AdapterTime.ExpertViewHolder holder, int position) {
        TimeOpen timeOpen = listTimeOpen.get(position);
        holder.txtName.setText(timeOpen.getUser());
        holder.txtDate.setText(timeOpen.getDate());
        holder.txtTime.setText(timeOpen.getTime());
        if(timeOpen.getUser().equals("Xuân Hưởng")==true){
            holder.imgAvatar.setImageDrawable(context.getResources().getDrawable(R.drawable.ronaldo));
        } else if(timeOpen.getUser().equals("Duy Khoa")==true) {
            holder.imgAvatar.setImageDrawable(context.getResources().getDrawable(R.drawable.kaka));
        }

    }

    @Override
    public int getItemCount() {
        return listTimeOpen.size();
    }

    public class ExpertViewHolder extends RecyclerView.ViewHolder {
        private TextView txtName, txtDate, txtTime;
        private ImageView imgAvatar;

        public ExpertViewHolder(View itemView) {
            super(itemView);
            txtName = itemView.findViewById(R.id.txtName);
            txtDate = itemView.findViewById(R.id.txtDate);
            txtTime = itemView.findViewById(R.id.txtTime);
            imgAvatar = itemView.findViewById(R.id.imgAvatar);


        }


    }

}

