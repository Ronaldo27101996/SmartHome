package com.xuanhuong.controllight;

import android.app.Fragment;
import android.content.Intent;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.ImageButton;
import android.widget.SeekBar;

import com.github.nkzawa.socketio.client.IO;
import com.github.nkzawa.socketio.client.Socket;
import com.suke.widget.SwitchButton;

import java.net.URISyntaxException;
import java.util.ArrayList;

/**
 * Created by CR7 on 4/17/2018.
 */

public class Frag_Control extends Fragment {
    SwitchButton swtLight1, swtLight2, swtLight3, swtLight4,swtFAN,swtPUMP, swtSecurity, swtLamp;
    SeekBar sekLed;
    private ImageButton btnSpeak;
    Button openDoor;
    boolean mLight = true;
    boolean active = false;
    private final int REQ_CODE_SPEECH_INPUT = 100;
    public ArrayList<String> arrCommand=new ArrayList<>();
    @Nullable
    @Override
    public View onCreateView(LayoutInflater inflater, @Nullable ViewGroup container, Bundle savedInstanceState) {
        View view = inflater.inflate(R.layout.activity_main,container,false);
        addControls(view);
        addEvents();
        return view;
    }
    private void addEvents() {

        swtLight1.setOnCheckedChangeListener(new SwitchButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(SwitchButton view, boolean light) {
                mLight = light;
                if (mLight == false) {
//                    sekLight1.setVisibility(View.GONE);
                    LoginActivity.mSocket.emit("LED1PROG", 0);
                } else {
//                    sekLight1.setVisibility(View.VISIBLE);
//                    sekLight1.setProgress(100);
                }
                LoginActivity.mSocket.emit("ANDROID_LIGHT1_IO", mLight);
            }
        });
//        sekLight1.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
//            @Override
//            public void onProgressChanged(SeekBar seekBar, int progress, boolean b) {
//                Log.e("Change", "onProgressChanged: " + progress + "boolean: " + b);
//                LoginActivity.mSocket.emit("LED1PROG", progress);
//            }
//
//            @Override
//            public void onStartTrackingTouch(SeekBar seekBar) {
//
//            }
//
//            @Override
//            public void onStopTrackingTouch(SeekBar seekBar) {
//
//            }
//        });

        swtLight2.setOnCheckedChangeListener(new SwitchButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(SwitchButton view, boolean io) {
                mLight = io;
                if (mLight == false) {
//                    sekLight2.setVisibility(View.GONE);
                    LoginActivity.mSocket.emit("LED2PROG", 0);
                } else {
//                    sekLight2.setVisibility(View.VISIBLE);
//                    sekLight2.setProgress(100);
                }
                LoginActivity.mSocket.emit("ANDROID_LIGHT2_IO", mLight);
            }
        });


        swtLight3.setOnCheckedChangeListener(new SwitchButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(SwitchButton view, boolean light) {
                mLight = light;
                if (mLight == false) {
//                    sekLight3.setVisibility(View.GONE);
                    LoginActivity.mSocket.emit("LED3PROG", 0);
                } else {
//                    sekLight3.setVisibility(View.VISIBLE);
//                    sekLight3.setProgress(100);
                }
                LoginActivity.mSocket.emit("ANDROID_LIGHT3_IO", mLight);
            }
        });

        swtLight4.setOnCheckedChangeListener(new SwitchButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(SwitchButton view, boolean light) {
                mLight = light;
                if (mLight == false) {
//                    sekLight3.setVisibility(View.GONE);
                    LoginActivity.mSocket.emit("LED4PROG", 0);
                } else {
//                    sekLight3.setVisibility(View.VISIBLE);
//                    sekLight3.setProgress(100);
                }
                LoginActivity.mSocket.emit("ANDROID_LIGHT4_IO", mLight);
            }
        });

        swtFAN.setOnCheckedChangeListener(new SwitchButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(SwitchButton view, boolean light) {
                mLight = light;
                LoginActivity.mSocket.emit("ANDROID_FAN_IO", mLight);
            }
        });

        swtPUMP.setOnCheckedChangeListener(new SwitchButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(SwitchButton view, boolean light) {
                mLight = light;

                LoginActivity.mSocket.emit("ANDROID_PUMP_IO", mLight);
            }
        });

        swtLamp.setOnCheckedChangeListener(new SwitchButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(SwitchButton view, boolean light) {
                mLight = light;
                if (mLight == false) {
                    sekLed.setVisibility(View.GONE);
                    LoginActivity.mSocket.emit("LAMPPROG", 0);
                } else {
                    sekLed.setVisibility(View.VISIBLE);
                    sekLed.setProgress(100);
                }
                LoginActivity.mSocket.emit("ANDROID_LAMP_IO", mLight);
            }
        });
        sekLed.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int progress, boolean b) {
                Log.e("Change", "onProgressChanged: " + progress + "boolean: " + b);
                LoginActivity.mSocket.emit("LAMPPROG", progress);
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {

            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {

            }
        });
        swtSecurity.setOnCheckedChangeListener(new SwitchButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(SwitchButton view, boolean isActive) {
                active = isActive;
                LoginActivity.mSocket.emit("ACTIVE_SECURITY", active);
            }
        });



        openDoor.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                //mSocket.emit("OPEN_DOOR", true);
                openTheDoor();
            }
        });
        btnSpeak.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                speakControls();
            }
        });
    }

    private void speakControls() {
        Intent intent = new Intent(getActivity(),SpeechControls.class);
        startActivity(intent);
    }

    private void openTheDoor() {
        Intent intent = new Intent(getActivity(),LockActivity.class);
        startActivity(intent);
    }

    private void addControls(View view) {
        arrCommand.add("system start");
        arrCommand.add("system stop");
        arrCommand.add("turn on the light");
        arrCommand.add("turn off the light");
        arrCommand.add("the fan start");
        arrCommand.add("turn off the fan");
        arrCommand.add("all the light start");
//        ContainerActivity.mSocket.emit("LED1PROG", 0);
//        ContainerActivity.mSocket.emit("LED2PROG", 0);
//        ContainerActivity.mSocket.emit("LED3PROG", 0);
        openDoor= (Button) view.findViewById(R.id.opendoor);
        swtSecurity = (SwitchButton) view.findViewById(R.id.switchSecurity);
        swtLight1 = (SwitchButton) view.findViewById(R.id.switchLight1);
//        sekLight1 = (SeekBar) view.findViewById(R.id.sbLight1);
        swtLight2 = (SwitchButton) view.findViewById(R.id.switchLight2);
//        sekLight2 = (SeekBar) view.findViewById(R.id.sbLight2);
        swtLight3 = (SwitchButton) view.findViewById(R.id.switchLight3);
//        sekLight3 = (SeekBar) view.findViewById(R.id.sbLight3);
        swtLight4 = (SwitchButton) view.findViewById(R.id.switchLight4);
        swtFAN = (SwitchButton) view.findViewById(R.id.switchFAN);
        swtPUMP = (SwitchButton) view.findViewById(R.id.switchPUMP);
//        sekLight1.setVisibility(View.GONE);
//        sekLight2.setVisibility(View.GONE);
//        sekLight3.setVisibility(View.GONE);
        swtLamp = (SwitchButton) view.findViewById(R.id.switchLamp);
        sekLed = view.findViewById(R.id.sbLed);
        sekLed.setVisibility(View.GONE);
        btnSpeak = view.findViewById(R.id.btnSpeak);


    }


}
