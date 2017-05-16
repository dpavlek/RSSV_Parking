#include <Ultrasonic.h>
#include "pitches.h"
#include <SoftwareSerial.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// notes to play, corresponding to the 3 sensors:
int notes[] = {
  NOTE_A4, NOTE_B4, NOTE_C3
};

SoftwareSerial WIFIserial(2,3); //RX, TX

Ultrasonic ultrasonic(11,12); //trig,echo
int sensorValueF;
Adafruit_SSD1306 display(4);
String ssidName = "iPhone";
String ssidPass = "a0sasmsuc9cy";

void connectWifi(){
  WIFIserial.begin(115200);
  String ssid="AT+CWJAP=\"";
  ssid+=ssidName;
  ssid+="\",\"";
  ssid+=ssidPass;
  ssid+="\"";
  WIFIserial.println("AT+RST");
  delay(5000);
  WIFIserial.println("AT+CWMODE=1");
  delay(5000);
  WIFIserial.println(ssid);
  delay(7000);
}

void sendEmail()
{
  Serial.println("Sending e-mail");
  /*display.clearDisplay();
  display.setCursor(0,0);
  display.setTextSize(2);
  display.println("Sending e-mail");
  display.display();
  display.setTextSize(3);*/
  
  String message="Car has been damaged";

  WIFIserial.begin(115200);
  delay(1000);  
  WIFIserial.println("AT+CIPMUX=1");
  delay(10);
  WIFIserial.println("AT+CIPSERVER=1,80");
  delay(10);
  WIFIserial.println("AT+CIPSTART=4,\"TCP\",\"43.228.184.6\",2525");
  delay(3000);
  WIFIserial.println("AT+CIPSEND=4,20");
  delay(10);
  WIFIserial.println("EHLO 192.168.1.123");
  delay(500);
  WIFIserial.println("AT+CIPSEND=4,12");
  delay(10);
  WIFIserial.println("AUTH LOGIN");
  delay(500);
  WIFIserial.println("AT+CIPSEND=4,38");
  delay(10);
  WIFIserial.println("ZGFuaWVsLnBhdmxla292aWNAZ21haWwuY29t");     //base64 encoded username
  delay(500);
  WIFIserial.println("AT+CIPSEND=4,18");
  delay(10);
  WIFIserial.println("SGNWcmh2aTd2dVNT");                    //base64 encoded password
  delay(500);
  WIFIserial.println("AT+CIPSEND=4,41");
  delay(10);
  WIFIserial.println("MAIL FROM:<daniel.pavlekovic@gmail.com>");  // use your email address
  delay(500);  
  WIFIserial.println("AT+CIPSEND=4,39");
  delay(10);
  WIFIserial.println("RCPT To:<daniel.pavlekovic@gmail.com>");
  delay(500);
  WIFIserial.println("AT+CIPSEND=4,6");
  delay(10);
  WIFIserial.println("DATA");
  delay(500);
  WIFIserial.println("AT+CIPSEND=4,10");
  delay(10);
  WIFIserial.println("To: User");
  delay(500);
  WIFIserial.println("AT+CIPSEND=4,15");
  delay(10);
  WIFIserial.println("From: Arduino");
  delay(500);
  WIFIserial.println("AT+CIPSEND=4,19");
  delay(10);
  WIFIserial.println("Subject: Warning!");
  delay(500);
  WIFIserial.println("AT+CIPSEND=4,22");
  delay(10);
  WIFIserial.println(message);
  delay(500);
  WIFIserial.println("AT+CIPSEND=4,3");
  delay(10);
  WIFIserial.println(".");
  delay(500);
  WIFIserial.println("AT+CIPSEND=4,6");
  delay(10);
  WIFIserial.println("QUIT");
  delay(500);
  
  Serial.println("Email Sent!");
  /*display.clearDisplay();
  display.setCursor(0,0);
      display.setTextSize(2);
      display.println("E-Mail Sent!");
      display.display();
      display.clearDisplay();
      delay(5000);
      display.setTextSize(3);*/
}

void drawCar(){
  display.drawRoundRect(26,9,76,15,3,WHITE);
  display.drawRoundRect(45,11,45,11,3,WHITE);
}

void drawLineF4(){
  display.drawLine(10,0,0,10,WHITE);
  display.drawLine(0,10,0,21,WHITE);
  display.drawLine(0,21,10,31,WHITE);
}

void drawLineF3(){
  display.drawLine(14,2,5,11,WHITE);
  display.drawLine(5,11,5,20,WHITE);
  display.drawLine(5,20,14,29,WHITE);
}

void drawLineF2(){
  display.drawLine(18,4,10,12,WHITE);
  display.drawLine(10,12,10,19,WHITE);
  display.drawLine(10,19,18,27,WHITE);
}

void drawLineF1(){
  display.drawLine(22,6,15,13,WHITE);
  display.drawLine(15,13,15,18,WHITE);
  display.drawLine(15,18,22,25,WHITE);
}

void drawLineB4(){
  display.drawLine(117,0,127,10,WHITE);
  display.drawLine(127,10,127,21,WHITE);
  display.drawLine(127,21,117,31,WHITE);
}

void drawLineB3(){
  display.drawLine(113,2,122,11,WHITE);
  display.drawLine(122,11,122,20,WHITE);
  display.drawLine(122,20,113,29,WHITE);
}

void drawLineB2(){
  display.drawLine(109,4,117,12,WHITE);
  display.drawLine(117,12,117,19,WHITE);
  display.drawLine(117,19,109,27,WHITE);
}

void drawLineB1(){
  display.drawLine(105,6,112,13,WHITE);
  display.drawLine(112,13,112,18,WHITE);
  display.drawLine(112,18,105,25,WHITE);
}

void setup() {
Serial.begin(9600);
display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
connectWifi();
display.clearDisplay();
display.setCursor(0,0);
drawCar();
display.display();
display.clearDisplay();
}

void setupDisplay(){
      display.display();
      display.clearDisplay();
      drawCar();
}

void loop() {
    display.clearDisplay();
    drawCar();
    display.display();
    sensorValueF = ultrasonic.distanceRead();
    Serial.println(sensorValueF);

    if(sensorValueF < 3 || sensorValueF > 800){
      sendEmail();
    }
    
    if (sensorValueF >= 100 && sensorValueF < 150) {
      drawLineF4();
      setupDisplay();
      tone(8, notes[0], 50);
      delay(1000);
      display.display();
      noTone(8);
    }
    else if (sensorValueF >= 75 && sensorValueF < 100) {
      drawLineF4();
      setupDisplay();
      tone(8, notes[0], 50);
      delay(800);
      display.display();
      noTone(8);
    }
    else if (sensorValueF >= 50 && sensorValueF < 75) {
      // play the note corresponding to this sensor:
      drawLineF4();
      drawLineF3();
      setupDisplay();
      tone(8, notes[0], 50);
      delay(400);
      display.display();
      noTone(8);
    }
    else if (sensorValueF >= 25 && sensorValueF < 50) {
      drawLineF4();
      drawLineF3();
      setupDisplay();
      tone(8, notes[0], 50);
      delay(200);
      display.display();
      noTone(8);
    }
    else if (sensorValueF >= 10 && sensorValueF < 25) {
      drawLineF4();
      drawLineF3();
      drawLineF2();
      setupDisplay();
      tone(8, notes[0], 50);
      delay(100);
      display.display();
      noTone(8);
    }
    else if (sensorValueF < 10) {
      drawLineF4();
      drawLineF3();
      drawLineF2();
      drawLineF1();
      setupDisplay();
      tone(8, notes[0], 50);
      delay(50);
      display.display();
      noTone(8);
    }
}
