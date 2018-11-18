package com.xuanhuong.controllight;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.SeekBar;

import com.github.nkzawa.socketio.client.IO;
import com.github.nkzawa.socketio.client.Socket;
import com.suke.widget.SwitchButton;

import java.net.URISyntaxException;


public class MainActivity extends AppCompatActivity {
//    SwitchButton swtLight1, swtLight2, swtLight3;
//    SeekBar sekLight2, sekLight1, sekLight3;
//    Button openDoor;
//    boolean mLight = true;
//    public String NAME = "Android";
//    private Socket mSocket;
//
//    {
//        try {
//            mSocket = IO.socket("http://192.168.43.242:3484");
//        } catch (URISyntaxException e) {
//        }
//    }
//
//    @Override
//    protected void onCreate(Bundle savedInstanceState) {
//        super.onCreate(savedInstanceState);
//        setContentView(R.layout.activity_main);
//        addControls();
//        addEvents();
//
//
//    }
//
//    private void addEvents() {
//
//        swtLight1.setOnCheckedChangeListener(new SwitchButton.OnCheckedChangeListener() {
//            @Override
//            public void onCheckedChanged(SwitchButton view, boolean light) {
//                mLight = light;
//                if (mLight == false) {
//                    sekLight1.setVisibility(View.GONE);
//                    mSocket.emit("LED1PROG", 0);
//                } else {
//                    sekLight1.setVisibility(View.VISIBLE);
//                    sekLight1.setProgress(100);
//                }
//                mSocket.emit("LED1IO", mLight);
//            }
//        });
//        sekLight1.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
//            @Override
//            public void onProgressChanged(SeekBar seekBar, int progress, boolean b) {
//                Log.e("Change", "onProgressChanged: " + progress + "boolean: " + b);
//                mSocket.emit("LED1PROG", progress);
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
//
//        swtLight2.setOnCheckedChangeListener(new SwitchButton.OnCheckedChangeListener() {
//            @Override
//            public void onCheckedChanged(SwitchButton view, boolean light) {
//                mLight = light;
//                if (mLight == false) {
//                    sekLight2.setVisibility(View.GONE);
//                    mSocket.emit("LED2PROG", 0);
//                } else {
//                    sekLight2.setVisibility(View.VISIBLE);
//                    sekLight2.setProgress(100);
//                }
//                mSocket.emit("LED2IO", mLight);
//            }
//        });
//        sekLight2.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
//            @Override
//            public void onProgressChanged(SeekBar seekBar, int progress, boolean b) {
//                Log.e("LED 2 Change", "onProgressChanged: " + progress + "boolean: " + b);
//                mSocket.emit("LED2PROG", progress);
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
//
//        swtLight3.setOnCheckedChangeListener(new SwitchButton.OnCheckedChangeListener() {
//            @Override
//            public void onCheckedChanged(SwitchButton view, boolean light) {
//                mLight = light;
//                if (mLight == false) {
//                    sekLight3.setVisibility(View.GONE);
//                    mSocket.emit("LED3PROG", 0);
//                } else {
//                    sekLight3.setVisibility(View.VISIBLE);
//                    sekLight3.setProgress(100);
//                }
//                mSocket.emit("LED3IO", mLight);
//            }
//        });
//        sekLight3.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
//            @Override
//            public void onProgressChanged(SeekBar seekBar, int progress, boolean b) {
//                Log.e("LED 3 Change", "onProgressChanged: " + progress + "boolean: " + b);
//                mSocket.emit("LED3PROG", progress);
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
//        openDoor.setOnClickListener(new View.OnClickListener() {
//            @Override
//            public void onClick(View view) {
//                mSocket.emit("OPEN_DOOR", true);
//            }
//        });
//    }
//
//    private void addControls() {
//        mSocket.connect();
//        mSocket.emit("client-gui-username", NAME);
//
//        openDoor= (Button) findViewById(R.id.opendoor);
//        swtLight1 = (SwitchButton) findViewById(R.id.switchLight1);
//        sekLight1 = (SeekBar) findViewById(R.id.sbLight1);
//        swtLight2 = (SwitchButton) findViewById(R.id.switchLight2);
//        sekLight2 = (SeekBar) findViewById(R.id.sbLight2);
//        swtLight3 = (SwitchButton) findViewById(R.id.switchLight3);
//        sekLight3 = (SeekBar) findViewById(R.id.sbLight3);
//        sekLight1.setVisibility(View.GONE);
//        sekLight2.setVisibility(View.GONE);
//        sekLight3.setVisibility(View.GONE);
//
//    }
}
