#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const int buttonPin = 9; // The pin that the button is attached to

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

void loop() {
 if (digitalRead(buttonPin) == LOW) { // Check if button is pressed
        printFace(happyFace); // Show angry face
        delay(3000); // Wait for 3 seconds
        lcd.clear();
    } else {
    printFace(sleepyFace); // Using sleepyFace array
    delay(500);
    lcd.clear();

    printFace(normalFace);
    delay(5000);
    lcd.clear();
    
    printFace(sleepyFace); // Using sleepyFace array
    delay(200);

    printFace(normalFace); // Using sleepyFace array
    delay(500);
    }
  

}

