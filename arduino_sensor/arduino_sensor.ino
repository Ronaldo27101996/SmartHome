#include <ArduinoJson.h>
#include <SoftwareSerial.h>
#include <SerialCommand.h>
#include <Wire.h>
#include "DHT.h"            
const byte RX = 3;          // Chân 3 được dùng làm chân RX
const byte TX = 2;          // Chân 2 được dùng làm chân TX
SoftwareSerial mySerial = SoftwareSerial(RX, TX); 
//Variables
SerialCommand sCmd(mySerial); // Khai báo biến sử dụng thư viện Serial Command

const int DHTPIN = 9;       //Đọc dữ liệu từ DHT11 ở chân 9 trên mạch Arduino
const int DHTTYPE = DHT11;  //Khai báo loại cảm biến, có 2 loại là DHT11 và DHT22
int isWarning = 1;
DHT dht(DHTPIN, DHTTYPE);

int LED = 13;        // chọn chân 13 báo hiệu LED
int LED_pir = 12;
int pirSensor = 7;       // chọn ngõ tín hiệu vào cho PIR
//int pirState = LOW;     // Bắt đầu với không có báo động
int val = 0;
int pinSpeaker = 10; //chọn chân cho chuông khi có đột nhập
int LOA = 5;            // loa,den ket noi Pin 5
//int gas_din=9;                  // Dout ket noi Pin 9
int gas_ain = A5;                   // Aout ket noi Pin A5
int ad_value;  // bien luu gia tri adc
int rainSensor = 6; // Chân tín hiệu cảm biến mưa ở chân digital 6 (arduino)     
int gasThres = 400;
int flagrain=0;
int flagGas=0;
int activeSercurity = 0;
//int activeArlertGas = 1;
int stop_alert = 0;
// hay them tinh nang tat bao dong vao speech android. No se gui 1 message LOW all Loa.

int state = LOW;             // by default, no motion detected
void setup()
{
  pinMode(LED, OUTPUT);
  pinMode(LED_pir, OUTPUT);
  pinMode(pirSensor, INPUT);
  pinMode(pinSpeaker, OUTPUT);
  pinMode(rainSensor,INPUT);
  //pinMode(gas_din,INPUT);            // set Input  
  pinMode(gas_ain,INPUT);            // set Input 
  pinMode(LOA,OUTPUT);        // set Output 
  Serial.begin(9600);
  mySerial.begin(9600);
  sCmd.addCommand("ACTIVE_SECURITY", changeSecurityStt); //Khi có lệnh thì sẽ thực thi hàm   
  sCmd.addCommand("STOP_ALERT", stopAlertStt); //Khi có lệnh thì sẽ thực thi hàm   
  Serial.println("Da san sang nhan lenh");
  flagrain = 0;
  dht.begin(); 
}
 
void loop(){
  sCmd.readSerial();
  float hum = dht.readHumidity();    //Đọc độ ẩm
  float tem = dht.readTemperature(); //Đọc nhiệt độ
 
  Serial.print("Nhiet do: ");
  Serial.println(tem);               //Xuất nhiệt độ
  Serial.print("Do am: ");
  Serial.println(hum);               //Xuất độ ẩm
  
  Serial.println();                //Xuống hàng
  delay(1000);                     //Đợi 1 giây

  
  int value = digitalRead(rainSensor);//Đọc tín hiệu cảm biến mưa
  if (value == HIGH ) { // Cảm biến đang không mưa
    
    flagrain = 0;       //flag rain de khoi dong gửi notification
    stop_alert = 0; // khi het mua, khoi dong lai chế độ cảnh báo cho cơm mưa tiếp theo.
    Serial.println("Dang khong mua");
    
  } else if(value == LOW ){ // Co mưa
      //  bao dong
      if(stop_alert == 0){
        warning("Co mua!!!");
      }
      if(flagrain == 0){
        // tạo notificaton & send here
        flagrain =1;
      }
  }

    
    val = digitalRead(pirSensor);   // read sensor value
    Serial.println("PIR:");
    Serial.println(val); 
    if (val == HIGH) {           // check if the sensor is HIGH
//      digitalWrite(LED_pir, HIGH);   // turn LED ON
      warning("Co Trom!!!");
      delay(100);                // delay 100 milliseconds 
      
      if (state == LOW) {
        Serial.println("Motion detected!"); 
        state = HIGH;       // update variable state to HIGH
      }
    } 
    else {
        digitalWrite(LED_pir, LOW); // turn LED OFF
        delay(200);             // delay 200 milliseconds 
        
        if (state == HIGH){
          Serial.println("Motion stopped!");
          state = LOW;       // update variable state to LOW
      }
    }
//  
  ad_value = analogRead(gas_ain);          // doc gia tri adc
  Serial.println(ad_value);

if (ad_value < gasThres) { // không rò rỉ gas
    
    flagGas = 0;       //flag gas de khoi dong gửi notification  
  } else if(ad_value > gasThres){ // Co gas
      //  bao dong
      warning("Co GAS!!!");
      if( flagGas == 0 ){
        // tạo notificaton & send here
        flagrain =1;
      }
  }
}

void warning(String notification){
  
          digitalWrite(LED, HIGH);        // bật đèn LED.
          analogWrite(LOA, 120);           // phát LOA cảnh báo.
          Serial.println(notification);
          delay(300); 
          digitalWrite(LED, LOW);
          analogWrite(LOA, -1); 
          delay(200); 

          digitalWrite(LED, HIGH);        // bật đèn LED.
          analogWrite(LOA, 120);           // phát LOA cảnh báo.
          Serial.println(notification);
          delay(300); 
          digitalWrite(LED, LOW);
          analogWrite(LOA, -1); 
          delay(200);
          Serial.println(notification);
}
void changeSecurityStt() {
  Serial.println("ACTIVE_SECURITY");
  char *json = sCmd.next(); //Chỉ cần một dòng này để đọc tham số nhận đươc
  Serial.println(json);
  StaticJsonBuffer<200> jsonBuffer; //tạo Buffer json có khả năng chứa tối đa 200 ký tự
  JsonObject& root = jsonBuffer.parseObject(json);//đặt một biến root mang kiểu json
  int stt = root["ACTIVE_STT"];
  activeSercurity=stt;
  Serial.println(activeSercurity);
  
}
void stopAlertStt() {
  Serial.println("STOP_ALERT");
  char *json = sCmd.next(); //Chỉ cần một dòng này để đọc tham số nhận đươc
  Serial.println(json);
  StaticJsonBuffer<200> jsonBuffer; //tạo Buffer json có khả năng chứa tối đa 200 ký tự
  JsonObject& root = jsonBuffer.parseObject(json);//đặt một biến root mang kiểu json
  int stt = root["ACTIVE_STT"];
  stop_alert=stt;
  Serial.println(activeSercurity);
}
void sendToESP(String command, int stt){
      StaticJsonBuffer<200> jsonBuffer;
      JsonObject& root = jsonBuffer.createObject();
      root["stt"] = stt;
      mySerial.print(command);   //gửi tên lệnh
      mySerial.print('\r');           // gửi \r
      root.printTo(mySerial); //gửi chuỗi JSON
      mySerial.print('\r');           // gửi \r
  
}
void sendGraphData(int hum, int temp){
      StaticJsonBuffer<200> jsonBuffer;
      JsonObject& root = jsonBuffer.createObject();
      root["hum"] = hum;
      root["temp"] = temp;
      mySerial.print("GRAPH");   //gửi tên lệnh
      mySerial.print('\r');           // gửi \r
      root.printTo(mySerial); //gửi chuỗi JSON
      mySerial.print('\r');           // gửi \r
  
}
//void playTone(long duration, int freq)
//{
//  duration *= 1000;
//  int period = (1.0 / freq) * 1000000;
//  long elapsed_time = 0;
//  while (elapsed_time < duration)
//  {
//    digitalWrite(pinSpeaker,HIGH);
//    delayMicroseconds(period / 2);
//    digitalWrite(pinSpeaker, LOW);
//    delayMicroseconds(period / 2);
//    elapsed_time += (period);
//  }
//}

