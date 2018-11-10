#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <SocketIOClient.h>
//kiểm tra free RAM trên esp8266
extern "C" {
  #include "user_interface.h"
}

int Light1 = 16;       
int Light2 = 5;
int Light3 = 4;
int Light4 = 0;
int pump = 2;
int Fan = 14;
int In4 = 12;
int brightness = 0;    // mặc định độ sáng của đèn là 0
SocketIOClient client;
const char* ssid = "ronaldo";       //Tên mạng Wifi mà Socket server đang kết nối
const char* password = "gianglep3d";  //Pass mạng wifi 
char host[] = "192.168.43.242";  //Địa chỉ IP dịch vụ
int port = 3484;                  //Cổng dịch vụ socket server 

int activeSercurity=0;

//từ khóa extern: dùng để #include các biến toàn cục ở một số thư viện khác. Trong thư viện SocketIOClient có hai biến toàn cục
// RID: Tên sự kiện
// Rfull: Danh sách biến (đóng gói lại thành chuối JSON)
extern String RID;
extern String Rfull;
 
void setup()
{

  // Cấu hình các chân điều khiển.
  pinMode(Light1, OUTPUT);
  pinMode(Light2, OUTPUT);
  pinMode(Light3, OUTPUT);
  pinMode(Light4,OUTPUT);
  pinMode(pump,OUTPUT);
  pinMode(Fan,OUTPUT);
    //Bật baudrate ở mức 115200 để giao tiếp với máy tính qua Serial
    Serial.begin(115200);
    delay(10);
 
    //kết nối vào mạng Wifi
    Serial.print("Ket noi vao mang ");
    Serial.println(ssid);
 
    //Kết nối vào mạng Wifi
    WiFi.begin(ssid, password);
 
    //Chờ đến khi đã được kết nối
    while (WiFi.status() != WL_CONNECTED) { //Thoát ra khỏi vòng 
        delay(500);
        Serial.print('.');
    }
 
    Serial.println();
    Serial.println(F("Da ket noi WiFi"));
    Serial.println(F("Dia chi IP cua ESP8266 (Socket Client ESP8266): "));
    Serial.println(WiFi.localIP());
 
    if (!client.connect(host, port)) {
        Serial.println(F("Ket noi den socket server that bai! huhu"));
        return;
    }
 
    //Khi đã kết nối thành công
    if (client.connected()) {
        //Thì gửi sự kiện ("connection") đến Socket server ahihi.
        client.send("connection", "message", " ESP Connected !!!!");
    }
}
void loop()
{
    if (client.monitor()) {
        Serial.println(RID);
        
        if(strcmp(RID.c_str(), "SEND_LIGHT1_IO")==0){
          Serial.println("Rfull SEND_LIGHT1_IO");
          Serial.println(Rfull);
          AndroidIO(Light1);
        }
        
        if(strcmp(RID.c_str(), "SEND_LIGHT2_IO")==0){
          Serial.println("Rfull SEND_LIGHT2_IO");
          Serial.println(Rfull);
          AndroidIO(Light2);
        }
       
        if(strcmp(RID.c_str(), "SEND_LIGHT3_IO")==0){
          Serial.println("Rfull SEND_LIGHT3_IO");
          Serial.println(Rfull);
          AndroidIO(Light3);
        }
      if(strcmp(RID.c_str(), "SEND_LIGHT4_IO")==0){
          Serial.println("Rfull SEND_LIGHT4_IO");
          Serial.println(Rfull);
          AndroidIO(Light4);
        }
        if(strcmp(RID.c_str(), "SEND_FAN_IO")==0){
          Serial.println("Rfull SEND_FAN_IOD3IO");
          Serial.println(Rfull);
          AndroidIO(Fan);
        }
        if(strcmp(RID.c_str(), "SEND_PUMP_IO")==0){
          Serial.println("Rfull SEND_PUMP_IO");
          Serial.println(Rfull);
          AndroidIO(pump);
        }
    }
    //Kết nối lại!
    if (!client.connected()) {
      client.reconnect(host, port);
    }
}
void AndroidIO(int stt) {
  Serial.println("ANDROID_IO");
  String json = Rfull; //Chỉ cần một dòng này để đọc tham số nhận đươc
  Serial.println(json);
  StaticJsonBuffer<200> jsonBuffer; //tạo Buffer json có khả năng chứa tối đa 200 ký tự
  JsonObject& root = jsonBuffer.parseObject(json);//đặt một biến root mang kiểu json
  int stt_IO = root["io_data"];
  if(stt_IO==0){
    stt_IO=1;
  }else{
    stt_IO=0;
  }
  digitalWrite(stt, stt_IO);
}
