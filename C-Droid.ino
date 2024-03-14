#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "pitches.h" 

const int buttonPin = 9; // The pin that the button is attached to
const int buzzerPin = 10; // The pin that the buzzer is attached to

// Set the LCD I2C address
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Define face arrays globally
int sleepyFace[2][16] = {
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,1,1,1,1,0,0,0,0,0,1,1,1,1,0}
};
int happyFace[2][16] = {
  {0,0,0,1,1,0,0,0,0,0,0,0,1,1,0,0},
  {0,0,1,0,0,1,0,0,0,0,0,1,0,0,1,0}
};
int 	angryFace[2][16]={
 {0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0},
 {0,0,0,1,1,1,0,0,0,0,0,1,1,1,0,0}
};
int 	sadFace[2][16]={
 {0,0,0,1,1,1,0,0,0,0,0,1,1,1,0,0},
 {0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0}
};
int 	normalFace[2][16]={
 {0,0,1,1,1,1,0,0,0,0,0,1,1,1,1,0},
 {0,0,1,1,1,1,0,0,0,0,0,1,1,1,1,0}
};
// ... (Define angryFace, sadFace, normalFace here in the same way)

void setup() {
    lcd.init();
    lcd.backlight();
    Serial.begin(9600);
    pinMode(buttonPin, INPUT_PULLUP); // Initialize the button pin as an input with pull-up resistor
    pinMode(buzzerPin, OUTPUT); // Initialize the buzzer pin as an output
}
void printFace(int emo[][16]){
    lcd.clear();
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 16; j++) {
            lcd.setCursor(j, i);
            if (emo[i][j] == 1) {
                lcd.write(255);
            }
        }
    }
}
enum FaceState { NORMAL, SLEEPY, ANGRY };
FaceState currentFace = NORMAL;
unsigned long previousMillis = 0;

int melody[] = {
  NOTE_AS4, NOTE_AS4, NOTE_AS4,
  NOTE_F5, NOTE_C6,
  NOTE_AS5, NOTE_A5, NOTE_G5, NOTE_F6, NOTE_C6,
  NOTE_AS5, NOTE_A5, NOTE_G5, NOTE_F6, NOTE_C6,
  NOTE_AS5, NOTE_A5, NOTE_AS5, NOTE_G5, NOTE_C5, NOTE_C5, NOTE_C5,
  NOTE_F5, NOTE_C6,
  NOTE_AS5, NOTE_A5, NOTE_G5, NOTE_F6, NOTE_C6,

  NOTE_AS5, NOTE_A5, NOTE_G5, NOTE_F6, NOTE_C6,
  NOTE_AS5, NOTE_A5, NOTE_AS5, NOTE_G5, NOTE_C5, NOTE_C5,
  NOTE_D5, NOTE_D5, NOTE_AS5, NOTE_A5, NOTE_G5, NOTE_F5,
  NOTE_F5, NOTE_G5, NOTE_A5, NOTE_G5, NOTE_D5, NOTE_E5, NOTE_C5, NOTE_C5,
  NOTE_D5, NOTE_D5, NOTE_AS5, NOTE_A5, NOTE_G5, NOTE_F5,

  NOTE_C6, NOTE_G5, NOTE_G5, REST, NOTE_C5,
  NOTE_D5, NOTE_D5, NOTE_AS5, NOTE_A5, NOTE_G5, NOTE_F5,
  NOTE_F5, NOTE_G5, NOTE_A5, NOTE_G5, NOTE_D5, NOTE_E5, NOTE_C6, NOTE_C6,
  NOTE_F6, NOTE_DS6, NOTE_CS6, NOTE_C6, NOTE_AS5, NOTE_GS5, NOTE_G5, NOTE_F5,
  NOTE_C6
};

int durations[] = {
  8, 8, 8,
  2, 2,
  8, 8, 8, 2, 4,
  8, 8, 8, 2, 4,
  8, 8, 8, 2, 8, 8, 8,
  2, 2,
  8, 8, 8, 2, 4,

  8, 8, 8, 2, 4,
  8, 8, 8, 2, 8, 16,
  4, 8, 8, 8, 8, 8,
  8, 8, 8, 4, 8, 4, 8, 16,
  4, 8, 8, 8, 8, 8,

  8, 16, 2, 8, 8,
  4, 8, 8, 8, 8, 8,
  8, 8, 8, 4, 8, 4, 8, 16,
  4, 8, 4, 8, 4, 8, 4, 8,
  1
};

void playMelody() {
  int size = sizeof(durations) / sizeof(int);
  for (int note = 0; note < size; note++) {
    int duration = 1000 / durations[note];
    tone(buzzerPin, melody[note], duration);
    int pauseBetweenNotes = duration * 1.30;
    delay(pauseBetweenNotes);
    noTone(buzzerPin);
  }
}

void loop() {
  unsigned long currentMillis = millis();

  if (digitalRead(buttonPin) == LOW) {
    currentFace = ANGRY;
    printFace(angryFace); // Immediately show angry face
    playMelody(); // Play an angry sound
    previousMillis = currentMillis;
  } else {
    if (currentFace == ANGRY && currentMillis - previousMillis >= 3000) {
      lcd.clear();
      currentFace = NORMAL;
      printFace(normalFace);
      previousMillis = currentMillis;
    } else if (currentFace == NORMAL && currentMillis - previousMillis >= 6000) {
      currentFace = SLEEPY;
      printFace(sleepyFace);
      previousMillis = currentMillis;
    } else if (currentFace == SLEEPY && currentMillis - previousMillis >= 300) {
      currentFace = NORMAL;
      printFace(normalFace);
      previousMillis = currentMillis;
    }
  }
}
