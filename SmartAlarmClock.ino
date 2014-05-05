//May 5, 2014 - 7:05 pm
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

// Necessary Libraries
#include <Keypad.h>
#include <LiquidCrystal.h>
#include "pitches.h"

// Initialize variables
int melody[] = {NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F4, 
                NOTE_G4, NOTE_C7, NOTE_B3, NOTE_C4};
String total;
int count;
int answerCorrect;
String questions [5] = {"5 + 3 = ", "7 x 3 = ", "27 / 3 = ", "(8 x 3)/6 = ", "[(12-1)x4]/2 = "};
String answers [5] = {"8", "21", "9", "4", "22"};

// Initialize LCD display
LiquidCrystal lcd(7,8,9,10,11,12);

// Initialize keypad
const byte ROWS = 4; // 4 rows on keypad
const byte COLS = 4; // 4 columns on keypad

// Define the Keymap
char keys[ROWS][COLS] = {
{'1','2','3','A'},
{'4','5','6','B'},
{'7','8','9','C'},
{'.','0','#','D'}
};

// Identify which pins on arduino are associated with the keypad
byte colPins[COLS] = { 2, 3, 4, A4};
byte rowPins[ROWS] = { 5, 6, 13, A5};

// Create the Keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

// Setup
void setup(){
  lcd.begin(16, 2);
  lcd.begin(16, 2);
  lcd.print("Set Alarm Clock:");
  lcd.setCursor(0,1);
  count = 0;
  lcd.print("       ");
  lcd.print(count);
}

// Functions below are called by the loop function

// Plays a specific melody for a determined length and duration
void speaker(int duration, int length, int mel){
  tone(A3,melody[mel], duration);
  delay(length);
  noTone(A3); 
}

// Allows the user to set the timer on their alarm clock
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

// Displays a countdown on the LCD based on the user's timer setting
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

// Rings the initial alarm and increasingly louder alarms if the user fails 
// to answer the question correctly
void alarmRing(){
  
  int i = 0;
  int a = 0;
  
  while(i<5){
    tone(A3,melody[i]);
    answerCorrect=0;
    total = "";
    lcd.print(questions[i]);
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
  }
}

// Function loops until a question is answered correctly
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

