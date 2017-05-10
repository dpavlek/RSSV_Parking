/*
  keyboard

 Plays a pitch that changes based on a changing analog input

 circuit:
 * 3 force-sensing resistors from +5V to analog in 0 through 5
 * 3 10K resistors from analog in 0 through 5 to ground
 * 8-ohm speaker on digital pin 8

 created 21 Jan 2010
 modified 9 Apr 2012
 by Tom Igoe

This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/Tone3

 */
#include <Ultrasonic.h>
#include "pitches.h"

// notes to play, corresponding to the 3 sensors:
int notes[] = {
  NOTE_A4, NOTE_B4, NOTE_C3
};

Ultrasonic ultrasonic(11,12); //trig,echo
int sensorValue;

void setup() {
Serial.begin(9600);
}

void loop() {
    sensorValue = ultrasonic.distanceRead();
    Serial.println(sensorValue);
    if(sensorValue<200){
    tone(8,notes[0],50);
    delay(sensorValue*4);
    noTone(8);
    }
    else{
    delay(2000);
    }
    /*if (sensorValue > 200 && sensorValue < 250) {
      // play the note corresponding to this sensor:
      tone(8, notes[0], 50);
      delay(1000);
      noTone(8);
    }
    else if (sensorValue > 150 && sensorValue < 200) {
      // play the note corresponding to this sensor:
      tone(8, notes[0], 50);
      delay(800);
      noTone(8);
    }
    else if (sensorValue > 100 && sensorValue < 150) {
      // play the note corresponding to this sensor:
      tone(8, notes[0], 50);
      delay(600);
      noTone(8);
    }
    else if (sensorValue > 50 && sensorValue < 100) {
      // play the note corresponding to this sensor:
      tone(8, notes[0], 50);
      delay(400);
      noTone(8);
    }
    else if (sensorValue > 10 && sensorValue < 50) {
      // play the note corresponding to this sensor:
      tone(8, notes[0], 50);
      delay(200);
      noTone(8);
    }
    else if (sensorValue < 10) {
      // play the note corresponding to this sensor:
      tone(8, notes[0], 50);
      delay(50);
      noTone(8);
    }*/
}
