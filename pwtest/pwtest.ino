#include <LiquidCrystal.h> // include the library 
#include "pitches.h"
#include <Servo.h> 

#define TM_pin A0
#define PR_pin A1

const int servoPin = 2; 
const int buzzer = 3; //buzzer to arduino pin 3
const int redPin = 10;
const int greenPin = 11;
const int bluePin = 12;
int noteDurations[] = {4, 8, 8, 4,4,4,4,4 };

int Gnum;
int melody[] = {
NOTE_C4, NOTE_G3,NOTE_G3, NOTE_GS3, NOTE_G3,0, NOTE_B3, NOTE_C4};
// note durations: 4 = quarter note, 8 = eighth note, etc.:
int sound_control = 1;
int rs = 8, en = 9, d4 = 4, d5 = 5, d6 = 6, d7 = 7;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
Servo Servo1;

String str = "";
String data;

bool PWCreate;

void visual(String);
void sound(String);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
   pinMode(buzzer, OUTPUT); 
   lcd.begin(16, 2); // set up the LCD's number of columns and rows:
   Servo1.attach(servoPin); 
   Servo1.write(0);
   PWCreate = false; 
}

void loop() {
  // put your main code here, to run repeatedly:
  if  (Serial.available() > 0) {
    data = Serial.readStringUntil('\n');
    if (data == "1") {
      PWCreate = false;
      Gnum = readIn();
      Serial.println(Gnum);
    }
    else {
        str = data;
        PWCreate = true;
    }
  }
  if (PWCreate) {
     Servo1.write(90);
     visual(str);
     sound(str);
  }
  else {
    Servo1.write(0);
  }
}

int  readIn() {
// read in the value
  int Gnum, TM, PR;
  TM = analogRead(TM_pin);
  PR = analogRead(PR_pin);
  Gnum = TM + PR;
  return Gnum;
}

void visual(String PW) {
  lcd.setCursor(0,0);  //set cursor to the start of the first line
  if (PW !=0){
      // LCD
      lcd.print("PW GEN Success"); // PW genrate success
      lcd.setCursor(0, 1); //move cursor to the start of the second line
      lcd.print(PW);      // print the number 64 since reset:
      
      // RGB RGB DSIPLAY MUTICOLOR 
      analogWrite(redPin, random(0,255));
      analogWrite(greenPin, random(0,255));
      analogWrite(bluePin, random(0,255));
      delay(500);
    }  
  else{
      // LCD
      lcd.print("PW GEN FAIL"); // // PW genrate fail
      // RGB DSIPLAY RED LIGHT
      analogWrite(redPin, 255);
      analogWrite(greenPin, 0);
      analogWrite(bluePin, 0);
  }
}

void sound(String PW){
  
  if(PW !=0 && sound_control == 1){
     for (int thisNote = 0; thisNote < 8; thisNote++) {
      // to calculate the note duration, take one second
      // divided by the note type.
      //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
      int noteDuration = 1000/noteDurations[thisNote];
      tone(3, melody[thisNote],noteDuration);
      //pause for the note's duration plus 30 ms:
      delay(noteDuration +30);
   }
  }
  
  else if (PW == 0 && sound_control == 1){
  tone(buzzer, 5000); // Send 1KHz sound signal...
  delay(1000);        // ...for 1 sec
  noTone(buzzer);     // Stop sound...
  delay(1000);        // ...for 1sec
  }
  
  sound_control++;
}
