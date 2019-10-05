// Author: Shelby Ferrier
// Created: May 2018

// The below code reads input (BPM) from a serial connection and sets off four lights alternating in
// fun patterns

// Initializing pin locations 
const int purple = 13;
const int blue = 11;
const int green = 9;
const int yellow = 7;

int bpm = 0;
int bpmDelay = 300;
int numberRead = 11;

void setup() {
  Serial.begin(9600);
  pinMode (purple, OUTPUT);
  pinMode (blue, OUTPUT);
  pinMode (green, OUTPUT);
  pinMode (yellow, OUTPUT);
}

void loop() {

  // note Serial.available > 0 if there are characters waiting to be read and = 0 if there are no 
  // characters left to be read
  if (Serial.available() > 0) {
    bpm = 0;

    // When characters are sent they're converted to indexes on the ASCII table
    while (Serial.available() > 0) {
      numberRead = char(Serial.read()) - 48;
      bpm = bpm * 10 + numberRead;
      delay (300);
      
    }
    bpmDelay = (60000 / bpm);

  }

  // Will run only if numberRead has been changed and there's nothing left to read on serial
  if (Serial.available() == 0 and numberRead != 11) {
    
    // bouncing back and forth
    for (int a = 0; a < 4; a++) {
      digitalWrite(blue, LOW);
      digitalWrite(purple, HIGH);
      delay (bpmDelay / 6);
      digitalWrite(purple, LOW);
      digitalWrite(blue, HIGH);
      delay (bpmDelay / 6);
      digitalWrite(blue, LOW);
      digitalWrite(green, HIGH);
      delay (bpmDelay / 6);
      digitalWrite(green, LOW);
      digitalWrite(yellow, HIGH);
      delay (bpmDelay / 6);
      digitalWrite(yellow, LOW);
      digitalWrite(green, HIGH);
      delay (bpmDelay / 6);
      digitalWrite(green, LOW);
      digitalWrite(blue, HIGH);
      delay (bpmDelay / 6);
    }
    
    //streaming through
    for (int b = 0; b < 8; b++) {
      digitalWrite(yellow, LOW);
      digitalWrite(purple, HIGH);
      delay (bpmDelay / 8);
      digitalWrite(purple, LOW);
      digitalWrite(blue, HIGH);
      delay (bpmDelay / 8);
      digitalWrite(blue, LOW);
      digitalWrite(green, HIGH);
      delay (bpmDelay / 8);
      digitalWrite(green, LOW);
      digitalWrite(yellow, HIGH);
      delay (bpmDelay / 8);

    }
    
    //straight flashing
    for (int c = 0; c < 4; c++) {
      digitalWrite (purple, HIGH);
      digitalWrite (blue, HIGH);
      digitalWrite (green, HIGH);
      digitalWrite (yellow, HIGH);
      delay (bpmDelay / 2);
      digitalWrite (purple, LOW);
      digitalWrite (blue, LOW);
      digitalWrite (green, LOW);
      digitalWrite (yellow, LOW);
      delay (bpmDelay / 2);

    }
    
    //straight flashing but twice as fast
    for (int d = 0; d < 8; d++) {
      digitalWrite (purple, HIGH);
      digitalWrite (blue, HIGH);
      digitalWrite (green, HIGH);
      digitalWrite (yellow, HIGH);
      delay (bpmDelay / 4);
      digitalWrite (purple, LOW);
      digitalWrite (blue, LOW);
      digitalWrite (green, LOW);
      digitalWrite (yellow, LOW);
      delay (bpmDelay / 4);
    }
  }
}
