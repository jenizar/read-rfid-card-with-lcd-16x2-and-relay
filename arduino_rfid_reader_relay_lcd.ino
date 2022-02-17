#include <SPI.h>
#include <Wire.h> 
#include <MFRC522.h>
#include <LiquidCrystal_I2C.h> 
#include "DS3231.h"

LiquidCrystal_I2C lcd(0x27,16,2); // Initialize LCD Display at address 0x27 / 0X3F

#define RST_PIN  9     // Configurable, see typical pin layout above
#define SS_PIN  10     // Configurable, see typical pin layout above

const int lred=3;
const int lgreen=4;
const int buzer=5;
const int relay1=6;
const int relay2=7;

RTClib RTC;

MFRC522 rfid(SS_PIN, RST_PIN); // Instance of the class
MFRC522::MIFARE_Key key;

String tag;
char dateBuffer[12];

void setup() {
  Serial.begin(9600);
  pinMode(buzer,OUTPUT);
  pinMode(relay1,OUTPUT);
  pinMode(relay2,OUTPUT);
  digitalWrite(relay1, LOW);
  digitalWrite(relay2, LOW);
   Wire.begin();
    lcd.init();
    lcd.backlight();
  SPI.begin(); // Init SPI bus
  rfid.PCD_Init(); // Init MFRC522

  Serial.println("Welcome, Tap your ID");
  lcd.setCursor(0, 0);
    lcd.print("Welcome");
  lcd.setCursor(0, 1);
    lcd.print("Tap your ID");
}

void loop() {
  if ( ! rfid.PICC_IsNewCardPresent())
    return;
  
  if (rfid.PICC_ReadCardSerial()) {
    for (byte i = 0; i < 4; i++) {
      tag += rfid.uid.uidByte[i];
    }
        Serial.println(tag);
    digitalWrite(buzer, HIGH);
    delay(300);
    digitalWrite(buzer, LOW);
    
    lcd.clear();
    lcd.setCursor (0, 0);
    if(tag=="18013759150") {
      lcd.print("Access Denied");        
      digitalWrite(lred, HIGH);
      digitalWrite(relay1, HIGH);
       delay(1200);
      digitalWrite(lred, LOW);   
      digitalWrite(relay1, LOW);    
    }    
    else if(tag=="53193164172") {
      lcd.print("Access Denied");  
      digitalWrite(lred, HIGH);
      digitalWrite(relay1, HIGH);
       delay(1200);
      digitalWrite(lred, LOW);   
      digitalWrite(relay1, LOW);        
    }
    else if(tag=="81710826") {
      lcd.print("Access Denied"); 
      digitalWrite(lred, HIGH);
      digitalWrite(relay1, HIGH);
       delay(1200);
      digitalWrite(lred, LOW);   
      digitalWrite(relay1, LOW);       
    }
    else if(tag=="971889556") {
      lcd.print("Access Denied"); 
      digitalWrite(lred, HIGH);
      digitalWrite(relay1, HIGH);
       delay(1200);
      digitalWrite(lred, LOW);   
      digitalWrite(relay1, LOW);        
    }
    else {
     lcd.print(tag);
      digitalWrite(lgreen, HIGH);
      digitalWrite(relay2, HIGH);
       delay(1200);
      digitalWrite(lgreen, LOW);   
      digitalWrite(relay2, LOW); 
    }
  lcd.setCursor(0,1);

    DateTime now = RTC.now();
   sprintf(dateBuffer,"%02u/%02u/%04u ",now.day(),now.month(),now.year());
   lcd.print(dateBuffer);
   
  lcd.setCursor(11, 1);

  sprintf(dateBuffer,"%02u:%02u ",now.hour(),now.minute());
  lcd.print(dateBuffer);
  
    tag = "";
    rfid.PICC_HaltA();
    rfid.PCD_StopCrypto1();   

    delay(4000);     

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Welcome");
    lcd.setCursor(0,1);
    lcd.print("Tap your ID");     
  }
}
