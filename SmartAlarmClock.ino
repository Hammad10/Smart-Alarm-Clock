//May 1, 2014 - 5:54 pm
//Stopwatch/Alarmclock with Keypad, speaker and LCD
//LCD SETUP: https://learn.adafruit.com/assets/2364
//KEYPAD SETUP:
/*
KEYPAD PIN      ARDUINO PIN
    1                2
    2                3
    3                4
    4                A4
    5                5
    6                6
    7                13
    8                A5
*/
//SPEAKER SETUP
//resistor --> pin A3
//other wire --> GND


//#include <Scheduler.h>
#include <Keypad.h>
#include <LiquidCrystal.h>
#include "pitches.h"

 
int melody[] = {NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F4, 
                NOTE_G4, NOTE_C7, NOTE_B3, NOTE_C4};
String total;
//String oldKey;
//int countdown;
int count;
int answerCorrect;
String questions [5] = {"5 + 3 = ", "7 x 3 = ", "27 / 3 = ", "(8 x 3)/6 = ", "[(12-1)x4]/2 = "};
String answers [5] = {"8", "21", "9", "4", "22"};

LiquidCrystal lcd(7,8,9,10,11,12);

const byte ROWS = 4; // Four rows
const byte COLS = 4; // Four columns
// Define the Keymap
char keys[ROWS][COLS] = {
{'1','2','3','A'},
{'4','5','6','B'},
{'7','8','9','C'},
{'.','0','#','D'}
};

byte colPins[COLS] = { 2, 3, 4, A4};
byte rowPins[ROWS] = { 5, 6, 13, A5};

// Create the Keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup(){
  //Scheduler.startLoop(loop2);
  //Scheduler.startLoop(loop3);
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.begin(16, 2);
  lcd.print("Set Alarm Clock:");
  lcd.setCursor(0,1);
  count = 0;
  lcd.print("       ");
  lcd.print(count);
  //answerCorrect = 0;
  
}

void speaker(int duration, int length, int mel){
  tone(A3,melody[mel], duration);
  delay(length);
  noTone(A3); 
}

void setTime(char key){
  if(key=='A'){
    lcd.clear();
    lcd.print("Set Alarm Clock:");
    lcd.setCursor(0,1);
    count++;
    lcd.print("       ");
    lcd.print(count);
    speaker(25, 50, 0);
  }
  else if (key=='B'){
    lcd.clear();
    lcd.print("Set Alarm Clock:");
    lcd.setCursor(0,1);
    count--;  
    lcd.print("       ");
    lcd.print(count);
    speaker(25, 50, 0); 
  }
}

void countDown(int count){
  while(count>0){
    lcd.clear();
    lcd.print(count);
    lcd.print(" seconds");
    lcd.setCursor(0,1);
    lcd.print("remaining...");
    delay(1000);
    lcd.clear();
    delay(200);
    speaker(25, 50, 5);
    count--;
  } 
}

void alarmRing(){
  
  int i = 0;
  int a = 0;
  
  while(i<5){
    //while(a==0){
    tone(A3,melody[i]);
    answerCorrect=0;
    total = "";
    lcd.print(questions[i]);
    //speaker(5000,8000,2);
    lcd.setCursor(0,1);
    lcd.print(">");
    
    while(answerCorrect==0){
      char answer = keypad.getKey();
      
      if(answer=='1'||answer=='2'||answer=='3'||answer=='4'||answer=='5'||
      answer=='6'||answer=='7'||answer=='8'||answer=='9'||answer=='0'){
        lcd.print(answer);
        speaker(25, 50, 0);
        tone(A3,melody[i]);
        total = total + String(answer);
      }
      
      else if(answer=='D'){
        answerCorrect=1; 
        speaker(200, 50, 0);
        tone(A3,melody[i]);
      }
    }
        
    if(total == answers[i]){
      //delay(200);
      lcd.clear();  
      lcd.print("GOOD!");
      delay(500);
      i = i+5;
      lcd.clear();
      noTone(A3);
      lcd.print("ALARM OFF");
      delay(1000);
      a=1;
    }  
    else{
      lcd.clear();
      lcd.print("WRONG!");
      i++;
      delay(500);
      lcd.clear();
    }
  //}
  }
}

void loop(){
  char key = keypad.getKey();
  setTime(key);
  if(key=='D'){
    speaker(200, 500, 0);
    countDown(count);
    alarmRing(); 
    lcd.clear();
    noTone(A3); 
  }
}

