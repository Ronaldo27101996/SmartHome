package com.xuanhuong.controllight;

import android.app.Fragment;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v7.widget.LinearLayoutManager;
import android.support.v7.widget.RecyclerView;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;


import com.github.nkzawa.emitter.Emitter;
import com.xuanhuong.Adapter.AdapterTime;
import com.xuanhuong.Model.TimeOpen;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.util.ArrayList;
import java.util.List;

/**
 * Created by CR7 on 4/2/2018.
 */

public class History_Fragment extends Fragment {
    public static List<TimeOpen> timeOpenList;
    private RecyclerView rvTime;
    public static AdapterTime adapterTime;


    @Override
    public void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

    }

    @Nullable
    @Override
    public View onCreateView(LayoutInflater inflater, @Nullable ViewGroup container, Bundle savedInstanceState) {
        View view = inflater.inflate(R.layout.history_open, container, false);
        addControls(view);
        addEvents();
        return view;
    }

    private void addEvents() {


    }

    private void addControls(View view) {
        LoginActivity.mSocket.emit("HISTORY", 0);
        LoginActivity.mSocket.on("HISTORY_SEND", onGetHistory);

        timeOpenList = new ArrayList<>();
        rvTime = view.findViewById(R.id.rvTime);
        adapterTime = new AdapterTime(timeOpenList, getActivity());
        RecyclerView.LayoutManager mLayoutManager = new LinearLayoutManager(getActivity());
        rvTime.setLayoutManager(mLayoutManager);
        rvTime.setAdapter(adapterTime);

    }

    private Emitter.Listener onGetHistory = new Emitter.Listener() {
        @Override
        public void call(final Object... args) {
            if (getActivity()!=null) {
                getActivity().runOnUiThread(new Runnable() {
                    @Override
                    public void run() {

                        if (args[0] != null) {
                            JSONArray data = (JSONArray) args[0]; // lay duoc list time
                            for (int i = 0; i < data.length(); i++) {
                                try {
                                    JSONObject obj = (JSONObject) data.get(i);
                                    String username = obj.getString("user");
                                    int id = obj.getInt("id");
                                    String date = obj.getString("date");
                                    String time = obj.getString("time");
                                    TimeOpen timeOpen = new TimeOpen(id, username, date, time);
                                    timeOpenList.add(timeOpen);

                                } catch (JSONException e) {
                                    return;
                                }
                            }
                            adapterTime.notifyDataSetChanged();
                            Log.e("run: ", data.toString());

                        }
                    }
                });
            }
        }


    };
//    @Override
//    public void onDestroyView() {
//        LoginActivity.mSocket.off("newmessage", onGetHistory);
//        super.onDestroyView();
//    }
}
