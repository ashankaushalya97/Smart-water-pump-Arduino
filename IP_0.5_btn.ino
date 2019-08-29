#include <LCD.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7,3,POSITIVE);

bool motor;
int relay=7;
int buzzer=8;

byte LowLevel[8] = {
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b11111
};

byte Level0[8] = {
        0b00000,
 0b00000,
 0b00000,
 0b00000,
 0b00000,
 0b00000,
 0b11111,
 0b11111
};
byte Level1[8] = {
        0b00000,
 0b00000,
 0b00000,
 0b00000,
 0b11111,
 0b11111,
 0b11111,
 0b11111
};
byte Level2[8] = {
        0b00000,
 0b00000,
 0b11111,
 0b11111,
 0b11111,
 0b11111,
 0b11111,
 0b11111
};
byte Level3[8] = {
        0b11111,
 0b11111,
 0b11111,
 0b11111,
 0b11111,
 0b11111,
 0b11111,
 0b11111
};
byte NoLevel[8] = {
        0b00000,
 0b00000,
 0b00000,
 0b00000,
 0b00000,
 0b00000,
 0b00000,
 0b00000
};


void setup() {

  Serial.begin(38400);
  pinMode(relay,OUTPUT);
  pinMode(buzzer,OUTPUT);
  pinMode(3,OUTPUT);

  lcd.begin(16,2);
    
    lcd.createChar(0,Level0);
    lcd.createChar(1,Level1);
    lcd.createChar(2,Level2);
    lcd.createChar(3,Level3);
    lcd.createChar(4,NoLevel);
    lcd.createChar(5,LowLevel);

    lcd.clear();
    lcd.setCursor(4,0);
    lcd.print("Welcome!");
       

}

int x=0;
int y,cm;

void loop() {

    int sw=digitalRead(2);
    if(sw==1) {
        
      
      getHeight();
   

    
    }else if(sw==0) {
        digitalWrite(3,LOW);
      }

  

  //Get distance from serial read
  if(Serial.available()) {
        cm = Serial.parseInt();
        Serial.println(cm);
        //delay(100);
        
        } 

    if(x!=0) {


             
   //checking the water level
    if(cm<=(x*0.2)) {
         motor=0;
        lcd.setCursor(11,0);
        lcd.write(byte(5));
        lcd.setCursor(12,0);
        lcd.write(byte(0));
        lcd.setCursor(13,0);
        lcd.write(byte(1));
        lcd.setCursor(14,0);
        lcd.write(byte(2));
        lcd.setCursor(15,0);
        lcd.write(byte(3));
        
    }else if(x*0.2<cm && cm<x*0.4) {
      
        lcd.setCursor(11,0);
        lcd.write(byte(5));
        lcd.setCursor(12,0);
        lcd.write(byte(0));
        lcd.setCursor(13,0);
        lcd.write(byte(1));
        lcd.setCursor(14,0);
        lcd.write(byte(2));
        lcd.setCursor(15,0);
        lcd.write(byte(4));
        
         
    }else if(x*0.4<cm && cm<x*0.6) {

        lcd.setCursor(11,0);
        lcd.write(byte(5));
        lcd.setCursor(12,0);
        lcd.write(byte(0));
        lcd.setCursor(13,0);
        lcd.write(byte(1));
        lcd.setCursor(14,0);
        lcd.write(byte(4));
        lcd.setCursor(15,0);
        lcd.write(byte(4));
         
    }else if(x*0.6<cm && cm<x*0.8) {
        lcd.setCursor(11,0);
        lcd.write(byte(5));
        lcd.setCursor(12,0);
        lcd.write(byte(0));
        lcd.setCursor(13,0);
        lcd.write(byte(4));
        lcd.setCursor(14,0);
        lcd.write(byte(4));
        lcd.setCursor(15,0);
        lcd.write(byte(4));

    }else if(cm>x*0.8) {
        
        lcd.setCursor(11,0);
        lcd.write(byte(5));
        lcd.setCursor(12,0);
        lcd.write(byte(4));
        lcd.setCursor(13,0);
        lcd.write(byte(4));
        lcd.setCursor(14,0);
        lcd.write(byte(4));
        lcd.setCursor(15,0);
        lcd.write(byte(4));

        motor=1;
        
    }
    //checking the motor

    if(motor==1) {

        //LCD
        lcd.setCursor(9,1);
        lcd.write("ON");
        lcd.write(byte(4));

        //relay
        digitalWrite(relay,HIGH);

        //buzzer
        digitalWrite(buzzer,HIGH);
        delay(500);
        digitalWrite(buzzer,LOW);
        delay(500);
        
      }else {
        lcd.setCursor(9,1);
        lcd.write("OFF");

        //relay
        digitalWrite(relay,LOW);

        //buzzer
        digitalWrite(buzzer,LOW);
        
        }
      }else
        {
            getHeight();
          }
   

}

void getHeight() {

    if(Serial.available()) {

        digitalWrite(3,HIGH);
        
        int newH= Serial.parseInt();

        lcd.clear();
        lcd.setCursor(3,0);
        lcd.print("Scanning..");

        //buzzer
        digitalWrite(buzzer,HIGH);
        delay(500);
        digitalWrite(buzzer,LOW);
        delay(500);
        
        delay(4000);
        
        lcd.clear();
        lcd.setCursor(1,0);
        lcd.write("New Tank height");
        lcd.setCursor(6,1);
        lcd.print(newH);
        lcd.setCursor(9,1);
        lcd.print("cm");
        
        delay(5000);
        x=newH;

        digitalWrite(3,LOW);

        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Water Level");
        lcd.setCursor(4,1);
        lcd.write("Pump");
      }
    
  }
