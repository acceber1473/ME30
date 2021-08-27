// Rebecca Shen November 2nd, 2020 
// ME30 Project 3 Code 

// Simon Says inspired game with LEDs and button notes! 
/* Game format: 5 notes correspond to 5 pushbuttons. Arduino generates array of notes with random
   length and random order. Player mimics pattern and code will compare input with generate melody*/
   
// References: Winningtone melody is the Super Mario Brothers complete level theme
// pitches.h list of frequency tones format taken from https://gist.github.com/mikeputnam/2820675 

#include "pitches.h"
#include <Servo.h>

// PINS //

const int button1 = 0;   // declaring buttons as pin numbers
const int button2 = 2;   // even pins if you can consider 0 as an even number
const int button3 = 4;
const int button4 = 6;
const int button5 = 8;

const int led1 = 1;      // declaring leds that correspond to buttons as pin numbers
const int led2 = 3;      // odd pins
const int led3 = 5;
const int led4 = 7;
const int led5 = 12;

const int speaker = 10;  // speaker will be pin 6

// ARRAYS //

int buttons[] = {button1, button2, button3, button4, button5};  // creating an array of buttons

int notes[] = {NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F4, NOTE_G4};  // creating an array of notes where index matches pin

int leds[] = {led1, led2, led3, led4, led5};   // creating an array of leds that correspond to the rest indices

int melody[10]; // creating an array of size 10 that will fit the melody

int answer[10]; // creating array of size 10 that will fit the answer

int ledOne[10];

// OTHER VARIABLES //

int buttonState;       // variable to store button state through digitalWrite

int press = 0;

int pinNumber = 0;

int randomLength;

int angle = 135;

//int count = 0;

Servo myservo;  // create servo object

///// SET UP /////

void setup() {

  for (int i = 0; i < 5; i++) {    // setting buttons as pin inputs
    pinMode(buttons[i], INPUT);
  }

  for (int j = 0; j < 5; j++) {    // setting leds as pin outputs
    pinMode(leds[j], OUTPUT);
  }

  pinMode(speaker, OUTPUT);       // setting speaker as pin output

  myservo.attach(9);              // attaches the servo on pin 9

  Serial.begin(9600);             // beginning serial monitor connection

/// START OF GAME ///

  delay(9000);    // delay 9 seconds bc the serial monitor is very slow on the online IDE
  
  while (digitalRead(button1) == HIGH && digitalRead(button2) == HIGH && digitalRead(button3) == HIGH && digitalRead(button4) == HIGH && digitalRead(button5) == HIGH) {
  }              // wait until any button press to start game 

  preGame();     // call preGame function


}

/// PREGAME ///

void preGame() {

  Serial.println("Hello!!!"); 
  delay(1000);
  Serial.println("When you're ready, press any button to start the game!");
  Serial.println("");   // empty print line used for serial print formatting

  // wait for button press 
  while (digitalRead(button1) == HIGH && digitalRead(button2) == HIGH && digitalRead(button3) == HIGH && digitalRead(button4) == HIGH && digitalRead(button5) == HIGH) {
    ledPreGame();
  }
}

/// BEFORE GAME LED AND TONE STUFF///

  // helps users familiarize themselves with the buttons and the corresponding tones

void ledPreGame() {

  for (int i = 0; i < 5; i++) {         // turns LEDs on and play corresponding tune one by one
    digitalWrite(leds[i], LOW);
    delay(50);
    digitalWrite(leds[i], HIGH);
    delay(50);
    tone(speaker, notes[i]);
    delay(200);
    noTone(speaker);
    delay(50);
  }

  digitalWrite(leds[4], LOW);

  for (int i = 3; i >= 1; i--) {       // turns LEDs off and play corresponding tune one by one
    digitalWrite(leds[i], HIGH);
    delay(50);
    digitalWrite(leds[i], LOW);
    delay(50);
    tone(speaker, notes[i]);
    delay(200);
    noTone(speaker);
    delay(50);
  }
}

/// REPEAT ///

  // offers choice to repeat or quit came 

void repeat() {
  Serial.println("Press button 1 to continue or button 2 to quit the game");
  Serial.println("");

  while (digitalRead(button1) == HIGH && digitalRead(button2) == HIGH && digitalRead(button3) == HIGH && digitalRead(button4) == HIGH && digitalRead(button5) == HIGH) {

    digitalWrite(leds[0], HIGH);    // flashing LEDs to correspond to buttons 1 and 2
    delay(100);
    digitalWrite(leds[1], HIGH);
    delay(100);
    digitalWrite(leds[0], LOW);
    delay(100);
    digitalWrite(leds[1], LOW);
    delay(100);

  }
  if (digitalRead(button1) == LOW) {

    digitalWrite(leds[1], LOW);    
    digitalWrite(leds[0], HIGH);    // turn on button 1 and turn off button 2

    Serial.println("You chose to repeat the game!!");
    delay(100);
    digitalWrite(leds[0], LOW);  
  }
  else if (digitalRead(button2) == LOW) {

    digitalWrite(leds[0], LOW);
    digitalWrite(leds[1], HIGH);   // turn on button 2 and turn off button 1

    Serial.println("You chose to quit the game-bye!");
    resetServo(90);
    noTone(speaker);
    delay(100);
    digitalWrite(leds[1], LOW);
    exit(0);
  }
}

/// READ NOTE ///

  // function that reads user input note by note and returns to the main loop

int readNote() {

  while (press == 0) {
    for (int n = 0; n < 5; n++) {
      buttonState = digitalRead(buttons[n]);
      if (buttonState == LOW) {
        digitalWrite(leds[n], HIGH);
        Serial.println("button has been pressed");
        tone(speaker, notes[n]);
        press = 1;
        digitalWrite(leds[n], LOW);
        return n;

      }
    }
  }
}

/// RANDOM MELODY ///

  // function that take randomLength (randomly generated number) and 
  // sets that as the randomly generated melody array length
  // then randomly generates melody
  

void randomMel(int randomLength) {

  while (digitalRead(button1) == HIGH && digitalRead(button2) == HIGH && digitalRead(button3) == HIGH && digitalRead(button4) == HIGH && digitalRead(button5) == HIGH) {
  }

  delay(200);
  countdown();   // calls countdown function to countdown using LEDs and serial prints to inform user


  for (int i = 0; i < randomLength; i++) {     // this for loop runs through melody and assigns it to random
    int randomNum = random(1, 5);    // notes using the random function
    melody[i] = notes[randomNum];    // randomizes pins and assigns them to melody 
    ledOne[i] = leds[randomNum];     // and corresponding led pin arrays 
    delay(100);                      // basically uses pin number as main "currency" vs note integers
  }

  for (int k = 0; k < randomLength; k++) {  // relays the chosen pins to buzzer and leds
    tone(speaker, melody[k]);
    digitalWrite(ledOne[k], HIGH);     
    delay(500);
    noTone(speaker);
    digitalWrite(ledOne[k], LOW);
    delay(50);
  }

}

/// COUNT DOWN ///

  // countdown to let user know when the melody will be played using LEDs and serial output

void countdown() {

  delay(100);
  Serial.println("3...");

  digitalWrite(leds[0], HIGH);

  digitalWrite(leds[1], HIGH);

  digitalWrite(leds[2], HIGH);

  digitalWrite(leds[3], HIGH);

  digitalWrite(leds[4], HIGH);

  delay(1000);

  Serial.println("2...");

  digitalWrite(leds[0], LOW);
  delay(100);
  digitalWrite(leds[4], LOW);

  delay(1000);

  Serial.println("1...");

  digitalWrite(leds[1], LOW);
  delay(100);
  digitalWrite(leds[3], LOW);

  delay(1000);

  Serial.println("Here comes the melody!");

  digitalWrite(leds[2], LOW);

  delay(200);

}

/// WINNER ///
  // function called when level is won

void winner() { 
  
  Serial.println("");
  Serial.println("CORRECT!!");    // prints out correct and plays winning tone 
  delay(100);
  winningTone();
  delay(50);

}


/// SERVO FUNCTIONS ///

void servoWheel(int angle) {       // function used to move servo a set angle when won
  myservo.write(angle);
  delay(500);

}

void resetServo(int a) {          // function used to reset servo when lost a level
  myservo.write(a);
  delay(100);
}

/// LOSER ///

  // function called when player gets note wrong 

void loser() {
  losingTone();
  Serial.println("YOU LOST");     // prints out you lost and plays losing turn and resets servo
  delay(100);
  Serial.println("YOU LOST");
  delay(100);
  Serial.println("YOU LOST");
  delay(100);
  resetServo(90);

}

/// WINNING TONE ///

  // note by note transcribing the Super Mario Brothers level complete theme 

void winningTone() {
  tone(speaker, NOTE_G3);  // triplets 
  delay(125);              // delay times based on whether or not note is triplet, eigth, quarter, etc.
  tone(speaker, NOTE_C4);
  delay(125);
  tone(speaker, NOTE_E4);
  delay(125);

  tone(speaker, NOTE_G4);
  delay(125);
  tone(speaker, NOTE_C5);
  delay(125);
  tone(speaker, NOTE_E5);
  delay(125);

  tone(speaker, NOTE_G6); // quarter note
  delay(375);
  tone(speaker, NOTE_E5);  // eighth note
  delay(188);

  noTone(speaker);
  delay(188);   // eighth note rest

  tone(speaker, NOTE_GS3);  // triplets
  delay(125);
  tone(speaker, NOTE_C4);
  delay(125);
  tone(speaker, NOTE_DS4);
  delay(125);

  tone(speaker, NOTE_GS4);
  delay(125);
  tone(speaker, NOTE_C5);
  delay(125);
  tone(speaker, NOTE_DS5);
  delay(125);

  tone(speaker, NOTE_GS6);  // quarter note
  delay(375);
  tone(speaker, NOTE_E5);  // eighth note
  delay(188);

  noTone(speaker);
  delay(188);   // eighth note rest

  tone(speaker, NOTE_AS3);  // triplets
  delay(125);
  tone(speaker, NOTE_D4);
  delay(125);
  tone(speaker, NOTE_F4);
  delay(125);

  tone(speaker, NOTE_AS4);
  delay(125);
  tone(speaker, NOTE_D5);
  delay(125);
  tone(speaker, NOTE_F5);
  delay(125);

  tone(speaker, NOTE_AS6);  // quarter note
  delay(375);

  tone(speaker, NOTE_AS6);  // triplets
  delay(125);
  noTone(speaker);
  delay(25);
  tone(speaker, NOTE_AS6);
  delay(125);
  noTone(speaker);
  delay(25);
  tone(speaker, NOTE_AS6);
  delay(125);
  noTone(speaker);
  delay(25);

  tone(speaker, NOTE_C7); // whole note
  delay(1400);
  noTone(speaker);

}

/// LOSING TONE ///
  // losing tone function just makes an unpleasant tone

void losingTone() {
  tone(speaker, 1000);  

}

///// MAIN CODE LOOP /////

  // main loop here!

void loop() {

  randomLength = random(3, 10);    // generates random length of melody array 

  Serial.println("Game is about to start...");  // this will print after a button has been pressed and can incorporate some sort of count down or something idk

  delay(1000);

  Serial.println("Press any button to hear the melody");
  Serial.println("");

  delay(100);

  randomMel(randomLength);     // calls the random melody generation function with randomLength as input

  Serial.println("Now it's time for you to repeat it!");
  Serial.println("");

  for (int i = 0; i < randomLength; i++) {

    press = 0;
    pinNumber = readNote();
    answer[i] = notes[pinNumber];

    // compare user input with melody note by note here!

    if (answer[i] == melody[i]) {           // if current note in answer index = note in melody index play the note

      delay(500);
      tone(speaker, notes[pinNumber], 500);
      delay(50);
      noTone(speaker);
      press = 0;

    }

    else {
      loser();                              // if current note doesn't match then call loser
      delay(1000);                          // reset servo to 90 degrees 
      noTone(speaker);                      // break out of loop 
      angle = 90;
      break;
     
    }

  }

  int count = 0;

  for (int j = 0; j < randomLength; j++) {       // since both losing and winning situations will end
    if (answer[j] == melody[j]) {                // up here, needed an extra thing to weed out the 
      count++;                                   // winning scenario
    }
    if (count == randomLength) {                 // basically double checks that the answer array 
      winner();                                  // DOES equal the generated melody array and if so,
      servoWheel(angle);                         // calls winner function and moves servo accordingly
      angle = angle + 45;
    }

  }

  repeat(); // can choose to repeat or quit the game     // both win or lose will end up here with 
  Serial.println("");                                    // the option to continue or quit
} 


/// END OF CODE ////







