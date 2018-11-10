#include <SerialCommand.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <SocketIOClient.h>
#include <SPI.h>
#include <RFID.h>
#include <Servo.h> 

#define SS_PIN 4
#define RST_PIN 5
#define LedPin 16

Servo myservo;
RFID rfid(SS_PIN, RST_PIN); 

//kiểm tra free RAM trên esp8266
extern "C" {
  #include "user_interface.h"
}

unsigned char reading_card[6]; // Mảng đọc mã card
unsigned char master[6] = {146,24,112,254,4}; // Mã Card Huong phù hợp để mở cửa
unsigned char master2[6] = { 26, 26, 85, 11, 94 }; // Mã Card Khoa
unsigned char i, j;
String huong="Xuân Hưởng";
String khoa="Duy Khoa";

bool ledstt= false;

SocketIOClient client;
const char* ssid = "ronaldo";       //Tên mạng Wifi mà Socket server đang kết nối
const char* password = "gianglep3d";  //Pass mạng wifi 
char host[] = "192.168.43.242";  //Địa chỉ IP dịch vụ
int port = 3484;                  //Cổng dịch vụ socket server 
 
//từ khóa extern: dùng để #include các biến toàn cục ở một số thư viện khác. Trong thư viện SocketIOClient có hai biến toàn cục
// RID: Tên sự kiện
// Rfull: Danh sách biến (đóng gói lại thành chuối JSON)
extern String RID;
extern String Rfull;
const byte RX = D4;
const byte TX = D8;
SoftwareSerial mySerial = SoftwareSerial(RX, TX, false, 256); 

void setup()
{
   SPI.begin(); 
   rfid.init();
   pinMode(LedPin,OUTPUT);
    //Bật baudrate để giao tiếp với máy tính qua Serial
    Serial.begin(9600);
    mySerial.begin(9600);
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
  //xu ly quét thẻ từ
if (rfid.isCard()) {
    Serial.println("\nA card try to open the door  ");
        if (rfid.readCardSerial()) {
            for (i = 0; i < 5; i++) {
                reading_card[i] = rfid.serNum[i]; //Lưu mã thẻ đọc được vào mảng reading_card
            }
   
            if (rfid.serNum[0] == master[0]
                && rfid.serNum[1] == master[1]
                && rfid.serNum[2] == master[2]
                && rfid.serNum[3] == master[3]
                && rfid.serNum[4] == master[4]
            ) {
                /* With a new cardnumber, show it. */
                Serial.println(" ");
                Serial.println("OPEN the Door");
                turnLed(huong);
                //guiInfoCard(huong);
                         
                //Serial.println(" ");
                Serial.println("Cardnumber:");
                Serial.print("Dec: ");
                for (i = 0; i < 5; i++) {
                  Serial.print(rfid.serNum[i],DEC);
                  Serial.print(", ");
                }
                        
             }else if (rfid.serNum[0] == master2[0]
                && rfid.serNum[1] == master2[1]
                && rfid.serNum[2] == master2[2]
                && rfid.serNum[3] == master2[3]
                && rfid.serNum[4] == master2[4]
            ) {
                /* With a new cardnumber, show it. */
                Serial.println(" ");
                Serial.println("OPEN the Door");
                turnLed(khoa);
               ///////serial send
               // guiInfoCard(khoa);
               
                //Serial.println(" ");
                Serial.println("Cardnumber:");
                Serial.print("Dec: ");
                for (i = 0; i < 5; i++) {
                  Serial.print(rfid.serNum[i],DEC);
                  Serial.print(", ");
                }
                        
             } else {
               
                Serial.print("ID trying to access : \n");
                Serial.println("Cardnumber:");
                Serial.print("Card : ");
                for (i = 0; i < 5; i++) {
                  Serial.print(rfid.serNum[i],DEC);
                  Serial.print(", ");
                }
             }
          }
    }
    
    rfid.halt();

    if (client.monitor()) {
        Serial.println(RID);
        if(strcmp(RID.c_str(), "SEND_OPEN_DOOR")==0){
          Serial.println(Rfull);
          openDoor();
          turnLed("Phone");
        }
   
}
 //Kết nối lại!
    if (!client.connected()) {
      client.reconnect(host, port);
    }
}

void openDoor() {
  Serial.println("OPEN_THE DOOR");
  
}

void guiInfoCard(String userName) {
  //gửi sự kiện "TIME_OPEN" là một JSON chứa tham số user có nội dung là userName
  client.send("TIME_OPEN", "user", userName);
}
void turnLed(String userName){
  Serial.println("Send Arduino_Start");
  //in ra serial cho Arduino  
  StaticJsonBuffer<200> jsonBuf;
  JsonObject& objLedStt = jsonBuf.createObject();
  objLedStt["JSON_MY_SEND"] = userName;
  objLedStt["LED_STT"] = 1;
 
  mySerial.print("DOOR");
  mySerial.print('\r');
  objLedStt.printTo(mySerial);
  mySerial.print('\r');
  objLedStt.printTo(Serial); //Xuống dòng
  Serial.println("Send Arduino_Done");
  ledstt = !ledstt;
  digitalWrite(LedPin, ledstt);       
}



//#include <ArduinoJson.h>
//#include <ESP8266WiFi.h>
//#include <SocketIOClient.h>
//#include <SerialCommand.h> 
////kiểm tra free RAM trên esp8266
//extern "C" {
//  #include "user_interface.h"
//}
//const byte RX = D4;
//const byte TX = D8;
//SoftwareSerial mySerial = SoftwareSerial(RX, TX, false, 256); 
//
//SocketIOClient client;
//const char* ssid = "ronaldo";       //Tên mạng Wifi mà Socket server đang kết nối
//const char* password = "gianglep3d";  //Pass mạng wifi 
//char host[] = "192.168.43.242";  //Địa chỉ IP dịch vụ
//int port = 3484;                  //Cổng dịch vụ socket server 
// 
////từ khóa extern: dùng để #include các biến toàn cục ở một số thư viện khác. Trong thư viện SocketIOClient có hai biến toàn cục
//// RID: Tên sự kiện
//// Rfull: Danh sách biến (đóng gói lại thành chuối JSON)
//extern String RID;
//extern String Rfull;
//
//void setup()
//{
// 
//  //Bật baudrate ở mức 115200 để giao tiếp với máy tính qua Serial
//    Serial.begin(115200);
//    mySerial.begin(57600); //Bật software serial để giao tiếp với Arduino, nhớ để baudrate trùng với software serial trên mạch arduino
//    delay(10);
// 
//    //kết nối vào mạng Wifi
//    Serial.print("Ket noi vao mang ");
//    Serial.println(ssid);
// 
//    //Kết nối vào mạng Wifi
//    WiFi.begin(ssid, password);
// 
//    //Chờ đến khi đã được kết nối
//    while (WiFi.status() != WL_CONNECTED) { //Thoát ra khỏi vòng 
//        delay(500);
//        Serial.print('.');
//    }
// 
//    Serial.println();
//    Serial.println(F("Da ket noi WiFi"));
//    Serial.println(F("Dia chi IP cua ESP8266 (Socket Client ESP8266): "));
//    Serial.println(WiFi.localIP());
// 
//    if (!client.connect(host, port)) {
//        Serial.println(F("Ket noi den socket server that bai! huhu"));
//        return;
//    }
//    //Khi đã kết nối thành công
//    if (client.connected()) {
//        //Thì gửi sự kiện ("connection") đến Socket server ahihi.
//        client.send("connection_ESP09", "message", " ESP Connected !!!!");
//    }
////   sCmd.addDefaultHandler(defaultCommand); //Lệnh nào đi qua nó cũng bắt hết, rồi chuyển xuống hàm defaultCommand!
//    Serial.println("Da san sang nhan lenh"); 
//}
//void loop()
//{
//    if (client.monitor()) {
//        Serial.println(RID);
//        if(strcmp(RID.c_str(), "SEND_OPEN_DOOR")==0){
//          Serial.println(Rfull);
//          turnLed();
//        }
//}
// //Kết nối lại!
//    if (!client.connected()) {
//      client.reconnect(host, port);
//    }
//}
//void turnLed(){
//  Serial.println("Send Adruino_Start");
//  //in ra serial cho Arduino  
//  StaticJsonBuffer<200> jsonBuf;
//  JsonObject& objLedStt = jsonBuf.createObject();
//  objLedStt["JSON_MY_SEND"] = "ABCD";
//  objLedStt["LED_STT"] = 1;
// 
//  mySerial.print("DOOR");
//  mySerial.print('\r');
//  objLedStt.printTo(mySerial);
//  mySerial.print('\r');
//  objLedStt.printTo(Serial); //Xuống dòng
//  Serial.println("Send Adruino_Done");      
//}

