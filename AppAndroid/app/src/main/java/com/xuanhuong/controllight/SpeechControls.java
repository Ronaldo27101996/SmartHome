package com.xuanhuong.controllight;

import android.content.ActivityNotFoundException;
import android.content.Intent;
import android.speech.RecognizerIntent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.Menu;
import android.view.View;
import android.widget.ImageButton;
import android.widget.TextView;
import android.widget.Toast;

import java.util.ArrayList;
import java.util.Locale;

public class SpeechControls extends AppCompatActivity {
    private TextView txtSpeechInput;
    private ImageButton btnSpeak;
    private final int REQ_CODE_SPEECH_INPUT = 100;
    public ArrayList<String> arrCommand=new ArrayList<>();
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_speech_controls);
        txtSpeechInput = (TextView) findViewById(R.id.txtSpeechInput);
        btnSpeak = (ImageButton) findViewById(R.id.btnSpeak);

        // hide the action bar
        getSupportActionBar().hide();
        arrCommand.add("system stop"); //0

        arrCommand.add(1,"turn the light on"); // 1
        arrCommand.add(2,"Turn on the light"); // 2
        arrCommand.add(3,"all the light on");  // 3

        arrCommand.add(4,"Turn off the light"); //4
        arrCommand.add(5,"turn the light off"); //5
        arrCommand.add(6,"all the light off");  //6

        arrCommand.add(7,"open the door");      //7

        arrCommand.add(8,"turn on the fan");    //8

        arrCommand.add(9,"turn off the fan");   //9

        arrCommand.add(10,"bright down");        //10

        arrCommand.add(11,"bright up");          //11

        arrCommand.add(12,"water begin");        //12

        arrCommand.add(13,"water stop");         //13

        arrCommand.add(14,"Active security system");         //14

        arrCommand.add(15,"security system stop");    //15

        arrCommand.add(16,"Bật toàn bộ đèn");  // 16
        arrCommand.add(17,"Bật Đèn");  // 17

        arrCommand.add(18,"Tắt toàn bộ đèn");  // 18
        arrCommand.add(19,"Tắt Đèn");  // 19

        arrCommand.add(20,"Bật quạt");    //20

        arrCommand.add(21,"Tắt quạt");    //21

        arrCommand.add(22,"Giảm ánh sáng xuống");        //22

        arrCommand.add(23,"Tăng ánh sáng lên");        //23

        arrCommand.add(24,"Tưới cây");        //24

        arrCommand.add(25,"Dừng tưới cây");         //25

        arrCommand.add(26,"Khởi động hệ thống an ninh");         //26

        arrCommand.add(27,"Tắt hệ thống an ninh");    //27


        arrCommand.add(28,"Bật Đèn Giúp Tôi");
        arrCommand.add(29,"Tắt Đèn Giúp Tôi");
        arrCommand.add(30,"Bật Quạt Giúp Tôi");
        arrCommand.add(31,"Tắt Quạt Giúp Tôi");
        arrCommand.add(32,"Tăng độ sáng Giúp Tôi");
        arrCommand.add(33,"Thêm Ánh Sáng Giúp Tôi");
        arrCommand.add(34,"Tưới Cây Giúp Tôi");
        arrCommand.add(35,"Khóa Nước Giúp Tôi");
        arrCommand.add(36,"Giúp tôi khởi động hệ thống an ninh");
        arrCommand.add(37,"Giúp tôi dừng hệ thống an ninh");
        arrCommand.add(38,"Giảm độ sáng Giúp Tôi");
        arrCommand.add(39,"Mở Cửa giúp tôi");

        btnSpeak.setOnClickListener(new View.OnClickListener() {

            @Override
            public void onClick(View v) {
                promptSpeechInput();
            }
        });
    }
    /**
     * Showing google speech input dialog
     * */
    private void promptSpeechInput() {
        Intent intent = new Intent(RecognizerIntent.ACTION_RECOGNIZE_SPEECH);
        intent.putExtra(RecognizerIntent.EXTRA_LANGUAGE_MODEL,
                RecognizerIntent.LANGUAGE_MODEL_FREE_FORM);
        intent.putExtra(RecognizerIntent.EXTRA_LANGUAGE, Locale.getDefault());
        intent.putExtra(RecognizerIntent.EXTRA_PROMPT,
                getString(R.string.speech_prompt));
        try {
            startActivityForResult(intent, REQ_CODE_SPEECH_INPUT);
        } catch (ActivityNotFoundException a) {
            Toast.makeText(getApplicationContext(),
                    getString(R.string.speech_not_supported),
                    Toast.LENGTH_SHORT).show();
        }
    }

    /**
     * Receiving speech input
     * */
    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);

        switch (requestCode) {
            case REQ_CODE_SPEECH_INPUT: {
                if (resultCode == RESULT_OK && null != data) {

                    ArrayList<String> result = data
                            .getStringArrayListExtra(RecognizerIntent.EXTRA_RESULTS);
                    for (int i= 0; i < arrCommand.size(); i++){
                        Log.e( "onActivityResult: ", arrCommand.get(i));
                        if(result.get(0).compareToIgnoreCase(arrCommand.get(i))==0){
                            txtSpeechInput.setText("Of course, "+ result.get(0));
                            if (i == 1 || i == 2 || i == 3 || i== 16 || i == 17|| i== 28){
                                for(int j = 1;j<=6;j++){
                                    String event = "ANDROID_LIGHT"+j+"_IO";
                                    LoginActivity.mSocket.emit(event, 1);
                                }
                                LoginActivity.mSocket.emit("ANDROID_LAMP_IO", 1);

                            }else if(i == 4 || i == 5 || i == 6 || i== 18 || i == 19 || i==29){
                                for(int j = 1;j<=6;j++){
                                    String event = "ANDROID_LIGHT"+j+"_IO";
                                    LoginActivity.mSocket.emit(event, 0);
                                }
                                LoginActivity.mSocket.emit("ANDROID_LAMP_IO", 0);
                            }else if(i == 7|| i== 39){
                                LoginActivity.mSocket.emit("OPEN_DOOR", LoginActivity.user.getName());
                            }else if(i == 8 || i == 20 || i== 30){
                                LoginActivity.mSocket.emit("ANDROID_FAN_IO", 1);
                            }else if(i == 9 || i == 21 || i==31){
                                LoginActivity.mSocket.emit("ANDROID_FAN_IO", 0);
                            }else if(i == 10 || i == 22 ||i==38 ){
                                LoginActivity.mSocket.emit("LAMP_PROG_BRIGHT", 0);
                            }else if(i == 11|| i == 23 || i==32 || i== 33){
                                LoginActivity.mSocket.emit("LAMP_PROG_BRIGHT", 1);
                            }else if(i == 12|| i == 24|| i== 34){
                                LoginActivity.mSocket.emit("ANDROID_PUMP_IO", 1);
                            }else if(i == 13|| i == 25 || i== 35){
                                LoginActivity.mSocket.emit("ANDROID_PUMP_IO", 0);
                            }else if(i == 14|| i == 26 || i== 36){
                                LoginActivity.mSocket.emit("ACTIVE_SECURITY", 1);
                            }else if(i == 15|| i == 27 || i==37){
                                LoginActivity.mSocket.emit("ACTIVE_SECURITY", 0);
                            }

                            return;
                        }
                    }
                    txtSpeechInput.setText(result.get(0)+ "\n Can't find it at list command");
                }
                break;
            }

        }
    }


}


