int state = 1;
int currentPosition = 7;
int debounceJoystick = 15;

const int pinA = 4;
const int pinB = 5;
const int pinC = 6;
const int pinD = 7;
const int pinE = 8;
const int pinF = 9;
const int pinG = 10;
const int pinDP = 11;


const int joystickPinSw = 2;  
const int joystickPinX = A0;  
const int joystickPinY = A1;  


const int xMinTreshold = 200;
const int xMaxTreshold = 800;
const int yMinTreshold = 200;
const int yMaxTreshold = 800;
const int highMiddleThreshold = 600;
const int lowMiddleThreshold = 400;

const int segSize = 8;

byte blinkingSegmentState = 0;

int segments[segSize] = {
  pinA, pinB, pinC, pinD, pinE, pinF, pinG, pinDP
};

byte segmentsValues[segSize] = { 0, 0, 0, 0, 0, 0, 0, 0 };  // a  b  c  d  e  f  g dp

const int movementMatrix[segSize][4] = {
  //UP  DOWN  LEFT  RIGHT
  {  0,   6,   5,   1 },  // a
  {  0,   6,   5,   1 },  // b
  {  6,   3,   4,   7 },  // c
  {  6,   3,   4,   2 },  // d
  {  6,   3,   4,   2 },  // e
  {  0,   6,   5,   1 },  // f
  {  0,   3,   6,   6 },  // g
  {  7,   7,   2,   7 },  // dp
};


int up = 0;
int down = 1;
int left = 2;
int right = 3;


byte lastSwReading = 1;
byte swState = LOW;

int xValueJoystick = 0;
int yValueJoystick = 0;
int lastXState = 0;
int lastYState = 0;

const unsigned long debounceTime = 50;
unsigned long lastButtonInputChange = 0;
unsigned long lastBlinkStateChange = 0;
unsigned long timer = 0;
const long blinkInterval = 200;
const int longPressThreshold = 2000;


void setup() {

   pinMode(joystickPinSw, INPUT_PULLUP); 
   for (int i = 0; i < segSize; i++) {
    pinMode(segments[i], OUTPUT);
  }

 
  Serial.begin(9600);
}

void loop() {
  joystickInput();
  blinkSegment();
}



void digitalWriteForCurrPos() {
  digitalWrite(segments[currentPosition], segmentsValues[currentPosition]);
}

void blinkSegment() {
  if (state != 1) {
    return;
  }
  timer = millis();
  if (timer - lastBlinkStateChange >= blinkInterval) {
    lastBlinkStateChange = timer;
    blinkingSegmentState = !blinkingSegmentState;
    digitalWrite(segments[currentPosition], blinkingSegmentState);
  }
}

void reset() {
  for (int i = 0; i < segSize; i++) {
    segmentsValues[i] = 0;
    digitalWrite(segments[i], 0);
    currentPosition = 7;
  }
}

void valuePos(int movement, boolean toggleSeg = false) {
  if (state != 1) {
    if (toggleSeg) {
      segmentsValues[currentPosition] = !segmentsValues[currentPosition];
    }
    digitalWriteForCurrPos();
    return;
  }
  digitalWriteForCurrPos();
  currentPosition = movementMatrix[currentPosition][movement];
}

void xMovement() {
  if (xValueJoystick > xMaxTreshold) {
    if (lastXState != 1) {
      valuePos(right, true);
    }
    lastXState = 1;
    return;
  }
  if (xValueJoystick < xMinTreshold) {
    if (lastXState != -1) {
      valuePos(left, true);
    }
    lastXState = -1;
    return;
  }
  lastXState = 0;
}

void yMovement() {
  if (yValueJoystick > yMaxTreshold) {
    if (lastYState != 1) {
      valuePos(down);
    }
    lastYState = 1;
    return;
  }
  if (yValueJoystick < yMinTreshold) {
    if (lastYState != -1) {
      valuePos(up);
    }
    lastYState = -1;
    return;
  }
  lastYState = 0;
}

void buttonPressed() {
  if (lastSwReading != swState && swState == LOW) {
    lastButtonInputChange = millis();
  }

  if (lastButtonInputChange && lastSwReading != swState && swState == HIGH) {
    if (millis() - lastButtonInputChange < debounceTime) {
      return;
    }
    lastButtonInputChange = 0;
    shortButtonPress();
  }

  if (state == 1 && lastButtonInputChange && millis() - lastButtonInputChange > longPressThreshold) {
    lastButtonInputChange = 0;
    reset();
  }
  lastSwReading = swState;
}


void joystickMovement() {
  if (state != 1) {
    xMovement();
    return;
  }

  if (yValueJoystick < highMiddleThreshold && yValueJoystick > lowMiddleThreshold) {
    xMovement();
  } 
  if(xValueJoystick < highMiddleThreshold && xValueJoystick > lowMiddleThreshold) {
    yMovement();
  }
  if (yMinTreshold + debounceJoystick < yValueJoystick && yValueJoystick < yMaxTreshold - debounceJoystick) {
    lastYState = 0;
  }
  if (xMinTreshold + debounceJoystick < xValueJoystick && xValueJoystick < xMaxTreshold - debounceJoystick) {
    lastXState = 0;
  }
}




void joystickInput() {
  swState = digitalRead(joystickPinSw);
  xValueJoystick = analogRead(joystickPinX);
  yValueJoystick = analogRead(joystickPinY);
  joystickMovement();
  buttonPressed();
}

void shortButtonPress() {
  if (state == 1) {
    state++;
    digitalWriteForCurrPos();
  } 
  else
    state--;
}

