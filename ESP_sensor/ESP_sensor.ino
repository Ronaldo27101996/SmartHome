#include <SoftwareSerial.h>
#include <SerialCommand.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <SocketIOClient.h>

#define LedPin 13

//kiểm tra free RAM trên esp8266
extern "C" {
  #include "user_interface.h"
}

bool ledstt= false;

SocketIOClient client;
const char* ssid = "ronaldo";       //Tên mạng Wifi mà Socket server đang kết nối
const char* password = "gianglep3d";  //Pass mạng wifi 
char host[] = "192.168.43.242";  //Địa chỉ IP dịch vụ
int port = 3484;                  //Cổng dịch vụ socket server 

int activeSecurity = 0;

//từ khóa extern: dùng để #include các biến toàn cục ở một số thư viện khác. Trong thư viện SocketIOClient có hai biến toàn cục
// RID: Tên sự kiện
// Rfull: Danh sách biến (đóng gói lại thành chuối JSON)
extern String RID;
extern String Rfull;
const byte RX = D1;
const byte TX = D2;

SoftwareSerial mySerial = SoftwareSerial(RX, TX, false, 256); 
SerialCommand sCmd(mySerial); // Khai báo biến sử dụng thư viện Serial Command

void setup()
{
    pinMode(LedPin,OUTPUT);
    //Bật baudrate để giao tiếp với máy tính qua Serial
    Serial.begin(115200);
    mySerial.begin(9600);
    sCmd.addCommand("GAS", gas);
    sCmd.addCommand("SECURITY", security);
    sCmd.addCommand("RAIN", rain);
    sCmd.addCommand("GRAPH", graph);
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
        if(strcmp(RID.c_str(), "SEND_ACTIVE_SECURITY")==0){
          Serial.println("Rfull SEND_ACTIVE_SECURITY");
          Serial.println(Rfull);
          changeActiveSecurity();
          RID="";
        }
        if(strcmp(RID.c_str(), "SEND_STOP_ALERT")==0){
          Serial.println("Rfull SEND_STOP_ALERT");
          Serial.println(Rfull);
          sendSttToUno("STOP_ALERT",1);
          RID="";
        }
    }
    //Kết nối lại!
    if (!client.connected()) {
      client.reconnect(host, port);
    }
}

void changeActiveSecurity() {
  Serial.println("ACTIVE_SECURITY");
  String json = Rfull; //Chỉ cần một dòng này để đọc tham số nhận đươc
  Serial.println(json);
  StaticJsonBuffer<200> jsonBuffer; //tạo Buffer json có khả năng chứa tối đa 200 ký tự
  JsonObject& root = jsonBuffer.parseObject(json);//đặt một biến root mang kiểu json
  activeSecurity = root["active"];
  Serial.println(activeSecurity);
  sendSttToUno("ACTIVE_SECURITY",activeSecurity);
}

void sendSttToUno(String command, int stt){
  Serial.println("Send Arduino_Start");
  //in ra serial cho Arduino  
  StaticJsonBuffer<200> jsonBuf;
  JsonObject& objStt = jsonBuf.createObject();
  objStt["ACTIVE_STT"] = stt;
 
  mySerial.print(command);
  mySerial.print('\r');
  objStt.printTo(mySerial);
  mySerial.print('\r');
  objStt.printTo(Serial); //Xuống dòng
  Serial.println("Send Arduino_Done");
  ledstt = !ledstt;
  digitalWrite(LedPin, ledstt);       
}
void gas(){
  
}
void security(){
  
}
void rain(){
  
}
void graph(){
}

