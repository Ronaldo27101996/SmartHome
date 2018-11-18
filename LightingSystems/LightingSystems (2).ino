#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <SocketIOClient.h>
//kiểm tra free RAM trên esp8266
extern "C" {
  #include "user_interface.h"
}
#define LOA 12     // chọn chân  báo hiệu LED.
#define CB 13         //  chọn ngõ tín hiệu vào cho Cảm biến.
#define LED 15      //  chọn chân cho chuông khi có đột nhập.


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
 int led1 = 5;       
 int led2 = 4;// cổng digital mà LED được nối vào
 int led3 = 2;// cổng digital mà LED được nối vào
int brightness = 0;    // mặc định độ sáng của đèn là 0
void setup()
{

  // Cấu hình các chân điều khiển.
  pinMode(LED, OUTPUT);
  pinMode(CB, INPUT);
  pinMode(LOA, OUTPUT);
  
  
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  pinMode(led3,OUTPUT);
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
  // xu ly cam bien
    if (digitalRead(CB) == HIGH && activeSercurity==1)    // nếu chân nối Cảm biến ở mức cao (có người). và mode security = 1
      {
          digitalWrite(LED, HIGH);        // bật đèn LED.
          analogWrite(LOA, 120);           // phát LOA cảnh báo.
          Serial.println("Co trom co trom:");
          delay(300); 
          digitalWrite(LED, LOW);
          analogWrite(LOA, -1); 
          delay(200); 

          digitalWrite(LED, HIGH);        // bật đèn LED.
          analogWrite(LOA, 120);           // phát LOA cảnh báo.
          Serial.println("Co trom co trom:");
          delay(300); 
          digitalWrite(LED, LOW);
          analogWrite(LOA, -1); 
          delay(200);
                             
      }

             
  
    if (client.monitor()) {
        Serial.println(RID);
        if(strcmp(RID.c_str(), "SEND_ACTIVE_SECURITY")==0){
          Serial.println("Rfull SEND_ACTIVE_SECURITY");
          Serial.println(Rfull);
          changeActiveSecurity();
        }
        if(strcmp(RID.c_str(), "SEDLED1IO")==0){
          Serial.println("Rfull LED1IO");
          Serial.println(Rfull);
          ledAndroid(led1);
        }
        if(strcmp(RID.c_str(), "SENDLED1Prog")==0){
          Serial.println(Rfull);
          ledAndroidProgress(led1);
        }
        if(strcmp(RID.c_str(), "SEDLED2IO")==0){
          Serial.println("Rfull LED2IO");
          Serial.println(Rfull);
          ledAndroid(led2);
        }
        if(strcmp(RID.c_str(), "SENDLED2Prog")==0){
          Serial.println(Rfull);
          ledAndroidProgress(led2);
        }
        if(strcmp(RID.c_str(), "SEDLED3IO")==0){
          Serial.println("Rfull LED3IO");
          Serial.println(Rfull);
          ledAndroid(led3);
        }
        if(strcmp(RID.c_str(), "SENDLED3Prog")==0){
          Serial.println(Rfull);
          ledAndroidProgress(led3);
        }
        
    }
    //Kết nối lại!
    if (!client.connected()) {
      client.reconnect(host, port);
    }
}
void ledAndroid(int sttLed) {
  Serial.println("LED_IO");
  String json = Rfull; //Chỉ cần một dòng này để đọc tham số nhận đươc
  Serial.println(json);
  StaticJsonBuffer<200> jsonBuffer; //tạo Buffer json có khả năng chứa tối đa 200 ký tự
  JsonObject& root = jsonBuffer.parseObject(json);//đặt một biến root mang kiểu json
  int ledStatus = root["led"];
  digitalWrite(sttLed, ledStatus);
}
void ledAndroidProgress(int sttLed) {
  Serial.println("LED PROG");
  String json = Rfull; //đọc tham số nhận đươc
  Serial.println(json);
  StaticJsonBuffer<200> jsonBuffer; //tạo Buffer json có khả năng chứa tối đa 200 ký tự
  JsonObject& root = jsonBuffer.parseObject(json);//đặt một biến root mang kiểu json
 
  int prog = root["prog"];
  prog= prog*255/100;
  //kiểm thử giá trị
  Serial.print(F("prog "));
  Serial.println(prog);
  analogWrite(sttLed, prog); 
}
void changeActiveSecurity() {
  Serial.println("ACTIVE_SECURITY");
  String json = Rfull; //Chỉ cần một dòng này để đọc tham số nhận đươc
  Serial.println(json);
  StaticJsonBuffer<200> jsonBuffer; //tạo Buffer json có khả năng chứa tối đa 200 ký tự
  JsonObject& root = jsonBuffer.parseObject(json);//đặt một biến root mang kiểu json
  activeSercurity = root["active"];
}
