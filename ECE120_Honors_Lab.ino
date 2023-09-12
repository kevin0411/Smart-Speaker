// First direction set up:

int pirPin1 = 2;                 // PIR Out pin 
int pirStat1 = 0;                // PIR status
int trigPin1 = 1;
int echoPin1 = 3;
long duration1; // variable for the duration of sound wave travel
int distance1; // variable for the distance measurement

// Second direction set up:

int pirPin2 = 6;                 // PIR Out pin 
int pirStat2 = 0;                // PIR status
int trigPin2 = 4;
int echoPin2 = 5;
long duration2; // variable for the duration of sound wave travel
int distance2; // variable for the distance measurement

#include "pitches.h"

// notes in the melody:
int melody[] = {

  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};

int buzzer = 9;
int volume = 0;

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {

  4, 8, 8, 4, 4, 4, 4, 4
};

void setup() {     
  pinMode(pirPin1, INPUT);  
  pinMode(trigPin1, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin1, INPUT); // Sets the echoPin as an INPUT
   
  pinMode(pirPin2, INPUT);  
  pinMode(trigPin2, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin2, INPUT); // Sets the echoPin as an INPUT
  
  Serial.begin(9600); // // Serial Communication is starting with 9600 of baudrate speed
}
void loop(){
  // Clears the trigPin condition
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration1 = pulseIn(echoPin1, HIGH);
  // Calculating the distance
  distance1 = duration1 * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  
  // Displays the distance on the Serial Monitor
  
  Serial.print("Distance1: ");
  Serial.print(distance1);
  Serial.println(" cm");

  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration2 = pulseIn(echoPin2, HIGH);
  // Calculating the distance
  distance2 = duration2 * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)

  Serial.print("Distance2: ");
  Serial.print(distance2);
  Serial.println(" cm");
 
  analogWrite(buzzer, volume);

  for (int thisNote = 0; thisNote < 8; thisNote++) {
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(buzzer, melody[thisNote], noteDuration);
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    noTone(8);
  }
 
  pirStat1 = digitalRead(pirPin1); 
  pirStat2 = digitalRead(pirPin2); 

  Serial.print("PIR1: ");
  Serial.println(pirStat1);

  Serial.print("PIR2: ");
  Serial.println(pirStat2);

  if(pirStat1 ==0 && pirStat2 ==0){
    volume = 0;
  }
  else if(pirStat1 == 1 && pirStat2 ==1){
    if(distance1<distance2){
      volume = distance2;
    }
    else{
      volume = distance1;
    }
  }
  else if(pirStat1 == 1){
    volume = distance1;
  }
  else{
    volume = distance2;
  }

  Serial.print("Volume: ");
  Serial.println(volume);

  
} 
