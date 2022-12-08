#include <LiquidCrystal.h>
#include "LedControl.h"

// LCD variables
const byte RS = 9;
const byte enable = 8;
const byte d4 = 7;
const byte d5 = 6;
const byte d6 = 5;
const byte d7 = 4;
LiquidCrystal lcd(RS,enable,d4,d5,d6,d7);

// joystick variables
const int pinSW = 2;  
const int pinX = A1;  
const int pinY = A0;  

byte swState = LOW;
int xValue = 0;
int yValue = 0;

const int lowerThreshold = 200;
const int upperThreshold = 800;
bool joyMoved = 0;

const int debounceDelay = 50;
unsigned long int lastDebounce = 0;

byte lastReading = LOW;
byte reading = LOW;

// matrix variables
const byte dinPin = 12;
const byte clockPin = 11;
const byte loadPin = 10;
const byte matrixSize = 8;
LedControl lc = LedControl(dinPin, clockPin, loadPin,1);  //DIN, CLK, LOAD, No.


// auxiliary matrix variables
byte matrixBrightness = 2;
byte xPos = 0;
byte yPos = 0;
byte xLastPos = 0;
byte yLastPos = 0;
const byte moveInterval = 100;
unsigned long long lastMoved = 0;
bool matrixChanged = true;
byte currentPos = 0;
byte lastPos = 0;

byte matrix[matrixSize][matrixSize] = {
  {0,0,0,0,0,0,0,1},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0}
};


const long delayPeriod = 2000;

String mainMenu[5] = {
  "Start",
  "High scores",
  "Settings",
  "About",
  "How to play"  
};

String settingsMenu[6] = {
  "Player name",
  "Difficulty",
  "LCD contrast",
  "LCD brightness",
  "Matrix brightness",
  "Audio"
};


int state = 0;
int lastState = 0;
// current menu pos
int menuPos = 0;
//settings menu pos
int setPos = 0;




void setup() {
  pinMode(pinSW, INPUT_PULLUP);  // activate pull-up resistor on the push-button pin
    // the zero refers to the MAX7219 number, it iszero for 1 chip
  lc.shutdown(0, false);  // turn off power saving,enables display
  lc.setIntensity(0, matrixBrightness);  // sets brightness(0~15 possiblevalues)
  lc.clearDisplay(0);  // clear screen
  matrix[xPos][yPos] = 1;

  Serial.begin(9600);

  lcd.begin(16, 2);
  lcd.print("WELCOME!");
  lcd.setCursor(4, 1);
  lcd.print("Have fun!");

  delay(delayPeriod);
  lcd.clear();
}


void loop() {
  xValue = analogRead(pinX);
  yValue = analogRead(pinY);
  reading = digitalRead(pinSW);

  
  if (state == 0) {
    printMenu();
  } else if(state == 1){
    matrixGame();
    gamerMenu();
  } else if(state == 2){
    scoresSection();
  }
  else if(state == 3){
    settingsSection();
    
  }

  
}

void printMenu() {
  joystickYMovement();
  joystickButton();
  lcd.setCursor(0, 0);
  lcd.print(">");
  lcd.print(mainMenu[menuPos]);

}


void gamerMenu() {
  lcd.setCursor(0, 0);
  lcd.print(" Game started");
  lcd.setCursor(0, 1);
  lcd.print("Points: ");
  joystickButton();
}
void matrixGame() {

  // TODO: update positions in an interval

  if(millis() - lastMoved > moveInterval) {
    updatePositions(); // calculare stare
  }

  if(matrixChanged == true) {
    updateMatrix();
    matrixChanged = false;
  }
  // TODO: update matrix when broadcasted that it changed
} 
// theoretical example
void generateFood() {
  // lastFoodPos = currentPos;
  // newFoodPos = random(ceva);
  // matrix[lastFoodPos] = 0;
  // matrix[newFoodPos] = 1;
  matrixChanged = true;
}

void updateMatrix() {
 // TODO: update matrix using byte matrix (refresh function)
   for(int i = 0; i<matrixSize; i++) {
     for (int j = 0; j<matrixSize; j++) {
       lc.setLed(0,i,j,matrix[i][j]);
     }
   }
}

void updatePositions() {
 // TODO: joystick control
 int xValue = analogRead(pinX);
 int yValue = analogRead(pinY);
 
 xLastPos = xPos;
 yLastPos = yPos;
 if (xValue < lowerThreshold) {
    xPos--;
    if (xPos < 0) {
      xPos = 7;
    }
 }

 if (xValue > upperThreshold) {
   xPos++;
   if (xPos > 7) {
     xPos = 0;
   }
 }


  if (yValue > upperThreshold) {
    if (yPos < matrixSize - 1) {
      yPos++;
    } 
    else {
      yPos = 0;
    }
  }

  if (yValue < lowerThreshold) {
    if (yPos > 0) {
      yPos--;
    }
    else {
      yPos = matrixSize - 1;
    }
  }

if (xLastPos != xPos || yLastPos != yPos) {
  matrix[xLastPos][yLastPos] = 0;
  matrix[xPos][yPos]=1;
  matrixChanged = true;
  lastMoved = millis();
}
}

void scoresSection() {
  lcd.clear();

   lcd.setCursor(0, 0);
   lcd.print("Uknown: 2330");
   joystickButton();
  
}
void settingsSection () {
  if (yValue > upperThreshold  && joyMoved == 0) { 
    if (setPos != 0) {
      setPos--;
    } 
    else setPos = 5;

    joyMoved++;
    lcd.clear();
    lcd.print(settingsMenu[setPos]);

  } else if (yValue < lowerThreshold && joyMoved == 0) { 
    if (setPos != 5) {
      setPos++;
    } 
    else setPos = 0;
    
    joyMoved++;
    lcd.clear();
     lcd.print(settingsMenu[setPos]);

  } else if (yValue < upperThreshold && yValue > lowerThreshold) {
      joyMoved = 0;
    }
    
  joystickButton();    


}


void joystickYMovement() {

  if (yValue > upperThreshold  && joyMoved == 0) { 
    if (menuPos != 0) {
      menuPos--;
    } 
    else menuPos = 4;

    joyMoved++;
    lcd.clear();

  } else if (yValue < lowerThreshold && joyMoved == 0) { 
    if (menuPos != 4) {
      menuPos++;
    } 
    else menuPos = 0;
    
    joyMoved++;
    lcd.clear();

  } else if (yValue < upperThreshold && yValue > lowerThreshold) {
      joyMoved = 0;
    }
}



void joystickButton() {
  if (lastReading != reading) {
      lastDebounce = millis();
    }
  if ((millis() - lastDebounce) >= debounceDelay) {
    if (swState != reading) {
      swState = reading;

      if (!swState) {
          switch(menuPos) {
            case 0:
              if (state == 0) {
                state = 1;
                lcd.clear();
              } else {
                state = 0;
                lcd.clear();
              }
              break;
            case 1:
              if (state == 0) {
                state = 2;
                lcd.clear();
              } else {
                state = 0;
                lcd.clear();
              }
              break;
            case 2:
               if (state == 0) {
                state = 3;
                lcd.clear();
              } else {
                state = 0;
                lcd.clear();
              }
              break;
            case 3:
              //to do about section
              break;
            case 4:
              // to do how to play section
              break;
          }
        }
        }
      }

  lastReading = reading;
}





