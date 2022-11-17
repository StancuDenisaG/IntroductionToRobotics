const long blinkInterval = 300;
const int longPress = 2000;
int state = 1;
int currentDisplay = 3;
int byteEncodings[16] = {
  //A B C D E F G DP
  B11111100,  // 0
  B01100000,  // 1
  B11011010,  // 2
  B11110010,  // 3
  B01100110,  // 4
  B10110110,  // 5
  B10111110,  // 6
  B11100000,  // 7
  B11111110,  // 8
  B11110110,  // 9
  B11101110,  // A
  B00111110,  // b
  B10011100,  // C
  B01111010,  // d
  B10011110,  // E
  B10001110   // F
};

const int numberOfDisplays = 4;
const int segD1 = 7;
const int segD2 = 6;
const int segD3 = 5;
const int segD4 = 4;
byte blinkingDpState = 0;
const byte regSize = 8;  

int displayDigits[numberOfDisplays] = {
  segD1, segD2, segD3, segD4
};

int displayValues[numberOfDisplays] = {
  0, 0, 0, 0
};


const int joystickPinSw = 2;  
const int joystickPinX = A0;  
const int joystickPinY = A1;  
const int upperLimit = 800;
const int lowerLimit = 300;

const int left = 0;
const int right = 1;
const int up = 2;
const int down = 3;

byte previousSwReading = 1;
byte swState = LOW;

int xValueJoystick = 0;
int yValueJoystick = 0;
int lastXState = 0;
int lastYState = 0;

const int latchPin = 11; 
const int clockPin = 10;  
const int dataPin = 12;   

const unsigned long debounceTime = 50;
unsigned long lastButtonInputChange = 0;
unsigned long lastBlinkStateChange = 0;
unsigned long timer = 0;

void setup() {
  pinMode(joystickPinSw, INPUT_PULLUP);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  for (int i = 0; i < numberOfDisplays; i++) {
    pinMode(displayDigits[i], OUTPUT);
    digitalWrite(displayDigits[i], LOW);
  }
  Serial.begin(9600);
}

void loop() {
  refreshDisplay();
  joystickInput();
  blinkSegment();
}

void blinkSegment() {
  if (state != 1) {
    return;
  }
  timer = millis();
  if (timer - lastBlinkStateChange >= blinkInterval) {
    lastBlinkStateChange = timer;
    blinkingDpState = !blinkingDpState;
  }
}


void writeReg(int encoding, int displayIndex) {
  digitalWrite(latchPin, LOW);
  byte msb = B0;
  for (int i = 0; i < regSize - 1; i++) {
    msb = bitRead(encoding, regSize - i - 1);
    insertBitIntoShiftReg(msb);
  }
  if (displayIndex == currentDisplay) {
    insertBitIntoShiftReg(blinkingDpState);
  } else {
    insertBitIntoShiftReg(0);
  }
  digitalWrite(latchPin, HIGH);
}

void insertBitIntoShiftReg(byte bit) {
  digitalWrite(clockPin, LOW);
  digitalWrite(dataPin, bit);
  digitalWrite(clockPin, HIGH);
}

void refreshDisplay() {
  for (int i = 0; i < numberOfDisplays; i++) {
    for (int i = 0; i < numberOfDisplays; i++) {
    digitalWrite(displayDigits[i], HIGH);
  }
    writeReg(byteEncodings[displayValues[i]], i);
    digitalWrite(displayDigits[numberOfDisplays - i - 1], LOW);
    delay(5);
  }
}

void movement(int move) {
  switch (move) {
    case up:
      {
        if (state == 1) {
          return;
        }
        displayValues[currentDisplay]++;
        if (displayValues[currentDisplay] > 15) {
          displayValues[currentDisplay] = 0;
        }
        return;
      }
    case down:
      {
        if (state == 1) {
          return;
        }
        displayValues[currentDisplay]--;
        if (displayValues[currentDisplay] < 0) {
          displayValues[currentDisplay] = 15;
        }
        return;
      }
          case right:
      {
        currentDisplay++;
        if (currentDisplay > 3) {
          currentDisplay = 0;
        }
        return;
      }
    case left:
      {
        currentDisplay--;
        if (currentDisplay < 0) {
          currentDisplay = 3;
        }
        return;
      }
  }
}

void xMovement() {
  if (xValueJoystick > upperLimit) {
    if (lastXState != 1) {
      movement(right);
    }
    lastXState = 1;
    return;
  }
  if (xValueJoystick < lowerLimit) {
    if (lastXState != -1) {
      movement(left);
    }
    lastXState = -1;
    return;
  }
  lastXState = 0;
}

void yMovement() {
  if (yValueJoystick > upperLimit) {
    if (lastYState != 1) {
      movement(down);
    }
    lastYState = 1;
    return;
  }
  if (yValueJoystick < lowerLimit) {
    if (lastYState != -1) {
      movement(up);
    }
    lastYState = -1;
    return;
  }
  lastYState = 0;
}

void implementButtonPress() {
  if (previousSwReading != swState && swState == LOW) {
    lastButtonInputChange = millis();
  }

  if (lastButtonInputChange && previousSwReading != swState && swState == HIGH) {
    if (millis() - lastButtonInputChange < debounceTime) {
      return;
    }
    lastButtonInputChange = 0;
    shortButtonPress();
  }

  if (lastButtonInputChange && millis() - lastButtonInputChange > longPress) {
    lastButtonInputChange = 0;
    if (state == 1)
        currentDisplay = 3;
        for (int i = 0; i < numberOfDisplays; i++) {
          displayValues[i] = 0;
               }
  }

  previousSwReading = swState;
}

void takeInputBasedOnState() {
  if (state == 1) {
    xMovement();
    return;
  } 
  else {
    yMovement();
    return;
  }
}

void joystickInput() {
  swState = digitalRead(joystickPinSw);
  xValueJoystick = analogRead(joystickPinX);
  yValueJoystick = analogRead(joystickPinY);
  takeInputBasedOnState();
  implementButtonPress();
}

void shortButtonPress() {
  if (state == 1) {
    state++;
    blinkingDpState = 1;
  } else
    state--;
}

