#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <Servo.h>
#include <Keypad.h>
#include <ArduinoJson.h>
#include <SoftwareSerial.h>
#include <SerialCommand.h>
#include <SPI.h>
#include <RFID.h>

const byte RX = 10;          // Chân 3 được dùng làm chân RX
const byte TX = 11;          // Chân 2 được dùng làm chân TX
bool ledstt = false;
#define SS_PIN 53
#define RST_PIN 49
RFID rfid(SS_PIN, RST_PIN);
SoftwareSerial mySerial = SoftwareSerial(RX, TX); 
LiquidCrystal_I2C lcd(0x3F,16,2);

unsigned char reading_card[6]; // Mảng đọc mã card
unsigned char master[6] = {146,24,112,254,4}; // Mã Card Huong phù hợp để mở cửa
unsigned char master2[6] = { 26, 26, 85, 11, 94 }; // Mã Card Khoa
unsigned char i, j;
String huong="Xuan Huong";
String khoa="Duy Khoa";

//Variables
SerialCommand sCmd(mySerial); // Khai báo biến sử dụng thư viện Serial Command

int red = 32, blue = 34; 
int cambien = 12;
int Led = 13;
int mot_min = 22;   //min servo angle  
int mot_max = 100; //Max servo angle   
int character = 0;
int activated =0;

char Str[16] = {' ', ' ', ' ', ' ', ' ', ' ', '-', '*', '*', '*', ' ', ' ', ' ', ' ', ' ', ' '};  

//Pins
Servo myservo;
int buzzer = 7;     //pin for the buzzer beep

//Keypad config
const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'},
};
byte rowPins[ROWS] =  {36, 37, 38, 39};//connect to the row pinouts of the keypad
byte colPins[COLS] =  {40, 41, 42, 43};//connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

void setup(){
    SPI.begin(); 
    rfid.init();
    
    pinMode(Led,OUTPUT);
    pinMode(cambien,INPUT);
    myservo.attach(6); //attach the servo to pin D10
    pinMode(buzzer,OUTPUT); 
    Serial.begin (9600);
    mySerial.begin(9600);
    
    pinMode(red,OUTPUT);
    pinMode(blue,OUTPUT);
    sCmd.addCommand("DOOR", doorphone); //Khi có lệnh DOOR thì sẽ thực thi hàm doorphone  
    Serial.println("Da san sang nhan lenh");
    //Init the screen and print the first text
    lcd.begin();
    //  lcd.backlight();
    lcd.clear();
    lcd.print("    PASSWORD");
    lcd.setCursor(0,1);
    lcd.print("      ****     ");
    //put the servo in the close position first
    myservo.write(mot_min);  
//    character = 0;
//    Str = {' ', ' ', ' ', ' ', ' ', ' ', '-', '*', '*', '*', ' ', ' ', ' ', ' ', ' ', ' '};
}
  
void loop(){
  sCmd.readSerial();
  int value = digitalRead(cambien);
  // Serial.println(value);
  digitalWrite(Led,value);
  delay(50);

  //xu ly quét thẻ từ
  if (rfid.isCard()) {
    Serial.println("\nA card try to open the door  ");
        if (rfid.readCardSerial()) {
            for (i = 0; i < 5; i++) {
                reading_card[i] = rfid.serNum[i]; //Lưu mã thẻ đọc được vào mảng reading_card
            }
   
            if (rfid.serNum[0] == master[0]&& rfid.serNum[1] == master[1]&& rfid.serNum[2] == master[2]&& rfid.serNum[3] == master[3]&& rfid.serNum[4] == master[4])
            {
                /* With a new cardnumber, show it. */
                Serial.println(" ");
                Serial.println("OPEN the Door");
                openDoorRFID(huong);
//                turnLed(huong);
                //guiInfoCard(huong);
                         
                //Serial.println(" ");
                Serial.println("Cardnumber:");
                Serial.print("Dec: ");
                for (i = 0; i < 5; i++) {
                  Serial.print(rfid.serNum[i],DEC);
                  Serial.print(", ");
                }
                        
             }else if (rfid.serNum[0] == master2[0]&& rfid.serNum[1] == master2[1]&& rfid.serNum[2] == master2[2]&& rfid.serNum[3] == master2[3]&& rfid.serNum[4] == master2[4]) {
                /* With a new cardnumber, show it. */
                Serial.println(" ");
                Serial.println("OPEN the Door");
                openDoorRFID(khoa);
//                turnLed(khoa);
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
    
  ///////////////EMERGENCY OPEN/CLOSE/////////
  ///////////////KEYPAD OPEN/CLOSE////////////  
  char customKey = customKeypad.getKey(); //this function reads the presed key
  if (customKey){
    character = character+1;
    Serial.println("\ncharacter: ");
    Serial.println(character);
    if (character == 1)
    {
      Serial.println(customKey);
      Str[6] = customKey;   
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("    PASSWORD");    
      lcd.setCursor(0,1);
      lcd.print(Str);
    }
    if (character == 2)
    {
      Serial.println(customKey);
      Str[7]= customKey;   
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("    PASSWORD");    
      lcd.setCursor(0,1);
      lcd.print(Str);
    }
    if (character == 3)
    {
      Serial.println(customKey);
      Str[8] = customKey;   
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("    PASSWORD");    
      lcd.setCursor(0,1);
      lcd.print(Str);
    }
    if (character == 4)
    {
      Serial.println(customKey);
      Str[9] = customKey;   
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("    PASSWORD");    
      lcd.setCursor(0,1);
      lcd.print(Str);
      activated = 1;
    }
    
  }
  if (activated == 1)
    {
      Serial.println("Active: 1");
      Serial.println(Str);
//     Serial.println(customKey);
    /*Change your password below!!! 
    Change each of Str[6], Str[7], Str[8], Str[9]*/
    if(Str[6]=='1' && Str[7]=='2' && Str[8]=='3' && Str[9]=='4' )
    {
      myservo.write(mot_max);
      lcd.clear();
      lcd.setCursor(4,0);
      lcd.print("ACCEPTED");
      activated = 2;
      analogWrite(buzzer,240);
      delay(250);
      analogWrite(buzzer,200);
      delay(250);
      analogWrite(buzzer,180);
      delay(250);
      analogWrite(buzzer,250);
      delay(250);
      analogWrite(buzzer,LOW);
      delay(500);
      
      lcd.clear();    
      lcd.setCursor(4,0);
      lcd.print("WELLCOME");
      delay(500);
      lcd.setCursor(2,1);
      lcd.print("Smart home");
      delay(500);

      lcd.clear();    
      lcd.setCursor(3,0);
      lcd.print("DOOR  OPEN");
      lcd.setCursor(2,1);
      lcd.print("Smart home");
      
    }
    else
    {
      Serial.println("Wrong pass ");
      lcd.clear();    
      lcd.setCursor(1,0);
      lcd.print("PASSWORD ERROR");
      lcd.setCursor(3,1);
      lcd.print("TRY  AGAIN");
      analogWrite(buzzer,150);
      delay(3000);
      analogWrite(buzzer,LOW);
      character=0;
      Str[6]= '-';
      Str[7]= '*'; 
      Str[8]= '*'; 
      Str[9]= '*';
      Str[10]= ' ';
      activated = 0;
      lcd.clear();    
      lcd.setCursor(4,0);
      lcd.print("PASSWORD");
      lcd.setCursor(0,1);
      lcd.print(Str);   
    }
  }
  if (activated == 2)
    {
      if(customKey == 'C' )
      {
        myservo.write(mot_min);
        activated = 0;
        character=0;
        Str[6]= '-';
        Str[7]= '*'; 
        Str[8]= '*'; 
        Str[9]= '*';
        Str[10]= ' ';   
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("    PASSWORD");    
        lcd.setCursor(0,1);
        lcd.print(Str);
      }
  }  
}
void doorphone() {
  Serial.println("PHONE_OPEN_DOOR");
  char *json = sCmd.next(); //Chỉ cần một dòng này để đọc tham số nhận đươc
  Serial.println(json);
  StaticJsonBuffer<200> jsonBuffer; //tạo Buffer json có khả năng chứa tối đa 200 ký tự
  JsonObject& root = jsonBuffer.parseObject(json);//đặt một biến root mang kiểu json
 
  int redStatus = root["LED_STT"];//json -> tham số root --> phần tử thứ 0. Đừng lo lắng nếu bạn không có phần tử này, không có bị lỗi đâu!
  int blueStatus = root["LED_STT"];//json -> tham số root --> phần tử thứ 0. Đừng lo lắng nếu bạn không có phần tử này, không có bị lỗi đâu!
  String xname = root["NAME"];
  Serial.println(xname);
  ledstt = !ledstt;
  //xuất ra màn hình
  digitalWrite(red, ledstt);
  digitalWrite(blue, ledstt);
  openDoorRFID(xname);
  Serial.println("DONE");
}
void openDoorRFID(String xname){

      myservo.write(mot_max);
      lcd.clear();
      lcd.setCursor(4,0);
      lcd.print("ACCEPTED");
      activated = 2;
      analogWrite(buzzer,240);
      delay(250);
      analogWrite(buzzer,200);
      delay(250);
      analogWrite(buzzer,180);
      delay(250);
      analogWrite(buzzer,250);
      delay(250);
      analogWrite(buzzer,LOW);
      delay(500);
      
      lcd.clear();    
      lcd.setCursor(3,0);
      lcd.print("DOOR  OPEN");
      lcd.setCursor(2,1);
      lcd.print("Smart home");

      lcd.clear();    
      lcd.setCursor(4,0);
      lcd.print("WELLCOME");
      delay(500);
      lcd.setCursor(3,1);
      lcd.print(xname);
      delay(500);
      
      //in ra cổng software serial để ESP8266 nhận
      StaticJsonBuffer<200> jsonBuffer;
      JsonObject& root = jsonBuffer.createObject();
      root["name"] = xname;
      mySerial.print("INFORCARD");   //gửi tên lệnh
      mySerial.print('\r');           // gửi \r
      root.printTo(mySerial); //gửi chuỗi JSON
      mySerial.print('\r');           // gửi \r
}

