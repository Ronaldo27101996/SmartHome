package com.xuanhuong.controllight;

import android.app.FragmentManager;
import android.app.FragmentTransaction;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.ImageView;

import com.github.nkzawa.socketio.client.IO;
import com.github.nkzawa.socketio.client.Socket;

import java.net.URISyntaxException;


public class ContainerActivity extends AppCompatActivity {
    ImageView imgHistory;
    ImageView imgAvatar;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_container);
        getSupportActionBar().hide();
        addControls();
        addEvents();
    }

    private void addEvents() {
        imgHistory.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                FragmentManager fragmentManager = getFragmentManager();
                FragmentTransaction fragmentTransaction = fragmentManager.beginTransaction();
                History_Fragment history_fragment = new History_Fragment();
                fragmentTransaction.replace(R.id.layout_container,history_fragment,"history_fragment");
                fragmentTransaction.addToBackStack("history_fragment");
                fragmentTransaction.commit();
            }
        });
    }

    private void addControls() {

        imgAvatar = (ImageView) findViewById(R.id.imgAvatar);
        imgHistory = (ImageView) findViewById(R.id.imgHistory);

        FragmentManager fragmentManager = getFragmentManager();
        FragmentTransaction fragmentTransaction = fragmentManager.beginTransaction();
        Frag_Control frag_control = new Frag_Control();
        fragmentTransaction.replace(R.id.layout_container,frag_control,"frag_control");
        fragmentTransaction.addToBackStack("frag_control");
        fragmentTransaction.commit();

    }

    @Override
    public void onBackPressed() {
        if(getFragmentManager().getBackStackEntryCount()>1){
            getFragmentManager().popBackStack("frag_control",0);
        }else {
            finish();
        }


    }
//    @Override
//    public void onDestroy() {
//        super.onDestroy();
//        mSocket.disconnect();
//    }

}
