package com.xuanhuong.controllight;

import android.app.ProgressDialog;
import android.content.Intent;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.CheckBox;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.TextView;
import android.widget.Toast;

import com.github.nkzawa.emitter.Emitter;
import com.github.nkzawa.socketio.client.IO;
import com.github.nkzawa.socketio.client.Socket;
import com.xuanhuong.Model.SharePref;
import com.xuanhuong.Model.TimeOpen;
import com.xuanhuong.Model.User;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.net.URISyntaxException;
import java.util.List;

import butterknife.ButterKnife;


public class LoginActivity extends AppCompatActivity {
    public static User user = new User();
    public String NAME = "Android";
    EditText txtID;

    EditText txtPass;

    CheckBox ckbRemember;

    Button btnLogin;

    TextView txtSignUp;

    LinearLayout linearWrapper;

    ImageView imgLogo;

    ProgressDialog mProgressDialog;
//    public static int isExpert = 0;
//    public static User user = null;
//    public static String USER_ID = "";


    public static Socket mSocket;

    {
        try {
            mSocket = IO.socket("http://192.168.43.242:3484");
        } catch (URISyntaxException e) {
        }
    }
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_login);
        addControls();
        getSupportActionBar().hide();
        SharePref.getInstance(getApplicationContext());
        mProgressDialog = new ProgressDialog(this);
        mProgressDialog.setIndeterminate(true);
        mProgressDialog.setMessage("Loading...");
        addEvents();
    }

    private void addControls() {
        LoginActivity.mSocket.connect();
        LoginActivity.mSocket.emit("android_connect", NAME);

        txtID = (EditText) findViewById(R.id.txtId);

         txtPass= (EditText) findViewById(R.id.txtPass);;

         ckbRemember= (CheckBox) findViewById(R.id.ckbRemember);

         btnLogin = (Button) findViewById(R.id.btnLogin);

//         txtSignUp;
    }

    @Override
    protected void onResume() {
        super.onResume();
        Boolean b = SharePref.readBoolean(SharePref.ISCHECK, false);
        if (b == true) {
            txtID.setText(SharePref.readString(SharePref.EMAIL, ""));
            txtPass.setText(SharePref.readString(SharePref.PASS, ""));
            ckbRemember.setChecked(b);
        } else {
            txtID.setText("");
            txtPass.setText("");
            ckbRemember.setChecked(false);
        }
    }

    @Override
    protected void onPause() {
        super.onPause();
        SharePref.writeString(SharePref.EMAIL, txtID.getText().toString().trim());
        SharePref.writeString(SharePref.PASS, txtPass.getText().toString().trim());
        SharePref.writeBoolean(SharePref.ISCHECK, ckbRemember.isChecked());
    }

    private void addEvents() {
        btnLogin.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                clickLogin();
            }
        });

    }

    private void clickLogin() {
        Log.e("Username+ Pass", txtID.getText().toString().trim() + "__" + txtPass.getText().toString());
        if (txtID.getText().toString().equals("")) {
            txtID.requestFocus();
            Toast.makeText(this, "Mời nhập Email ", Toast.LENGTH_SHORT).show();
            return;
        } else if (txtPass.getText().toString().equals("")) {
            txtPass.requestFocus();
            Toast.makeText(this, "Mời nhập Pass ", Toast.LENGTH_SHORT).show();
        } else {
            loginProcess();
        }

    }
    private Emitter.Listener onGetLogin = new Emitter.Listener() {
        @Override
        public void call(final Object... args) {
            LoginActivity.this.runOnUiThread(new Runnable() {
                @Override
                public void run() {

                    if (args[0] != null) {
                        JSONArray data = (JSONArray) args[0]; // lay duoc list time
                        if (data.length()==0){
                            Toast.makeText(LoginActivity.this, "Login Fail", Toast.LENGTH_SHORT).show();
                        }else{
                            try {
                                JSONObject obj = (JSONObject) data.get(0);
                                int id = obj.getInt("id");
                                String username = obj.getString("username");
                                String name = obj.getString("name");
                                String card = obj.getString("card");
                                String password = obj.getString("password");
                                user.setIdUser(id);
                                user.setIdCard(card);
                                user.setName(name);
                                user.setUsername(username);
                                user.setPassword(password);

                            } catch (JSONException e) {
                                return;
                            }
                            Log.e("run: ", user.toString());
                            Toast.makeText(LoginActivity.this, "Welcome "+user.getName(), Toast.LENGTH_SHORT).show();
                            Intent intent = new Intent(LoginActivity.this,ContainerActivity.class);
                            intent.putExtra("user",user);
                            startActivity(intent);
                        }

                    } else{
                        Toast.makeText(LoginActivity.this, "Login fail !!!", Toast.LENGTH_SHORT).show();
                    }
                }
            });
        }


    };
    private void loginProcess() {
        JSONObject obj = new JSONObject();

        try {
            obj.put("username", txtID.getText().toString().trim());
            obj.put("pass", txtPass.getText().toString());
        } catch (JSONException e) {
            e.printStackTrace();
        }
        Log.e("Login", txtID.getText().toString().trim() + "__" + txtPass.getText().toString());
        mSocket.emit("LOGIN", obj);
        mSocket.on("LOGIN_SEND", onGetLogin);
    }

//
//    public void showDialog() {
//
//        if (mProgressDialog != null && !mProgressDialog.isShowing())
//            mProgressDialog.show();
//    }
//
//    public void hideDialog() {
//        if (mProgressDialog != null && mProgressDialog.isShowing())
//            mProgressDialog.dismiss();
//    }

    public void AppExit()
    {
        this.finish();
        Intent intent= new Intent(Intent.ACTION_MAIN);
        intent.addCategory(Intent.CATEGORY_HOME);
        intent.setFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP);
        startActivity(intent);
        finish();
        System.exit(0);
    }

    @Override
    public void onBackPressed() {
        AppExit();
    }
}
