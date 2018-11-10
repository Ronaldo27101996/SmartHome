#include <LiquidCrystal_I2C.h>
#include <Wire.h>
LiquidCrystal_I2C lcd(0x3F,16,2);
#include <Servo.h>
#include <Keypad.h>
//#define SS_PIN 36
//#define RST_PIN 38
//Variables
int cambien = 12;
int Led = 13;
int mot_min = 22;   //min servo angle  (set yours)
int mot_max = 100; //Max servo angle   (set yours)
int character = 0;
int activated =0;

char Str[16] = {' ', ' ', ' ', ' ', ' ', ' ', '-', '*', '*', '*', ' ', ' ', ' ', ' ', ' ', ' '};  

//Pins
Servo myservo;
int buzzer=11;     //pin for the buzzer beep

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
byte rowPins[ROWS] =  {2, 3, 4, 5};//connect to the row pinouts of the keypad
byte colPins[COLS] =  {6, 7, 8, 9};//connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

void setup(){
    pinMode(Led,OUTPUT);
    pinMode(cambien,INPUT);
    myservo.attach(10); //attach the servo to pin D10
    pinMode(buzzer,OUTPUT); 
    Serial.begin (9600);
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
  int value = digitalRead(cambien);
  // Serial.println(value);
  digitalWrite(Led,value);
  delay(50);
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
//    if (character == 4)
//    {
//      Serial.println(customKey);
//      Str[10] = customKey;
//      activated = 1;
//    }
    
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

