const int redPotPin = A0;
const int greenPotPin = A1;
const int bluePotPin = A2;

const int redLedPin = 9;
const int greenLedPin = 10;
const int blueLedPin = 11;

const int maxAnalogValue = 1023;
const int maxDiodeValue = 255;

int redPotValue, greenPotValue, bluePotValue, redLedValue, greenLedValue, blueLedValue;

void setup() {
  pinMode(redPotPin, INPUT);
  pinMode(greenPotPin, INPUT);
  pinMode(bluePotPin, INPUT);

  pinMode(redLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);
  pinMode(blueLedPin, OUTPUT);

}

void loop() {
  redPotValue = analogRead(redPotPin);
  greenPotValue = analogRead(greenPotPin);
  bluePotValue = analogRead(bluePotPin);

  redLedValue = map(redPotValue, 0, maxAnalogValue, 0, maxDiodeValue);
  greenLedValue = map(greenPotValue, 0, maxAnalogValue, 0, maxDiodeValue);
  blueLedValue = map(bluePotValue, 0, maxAnalogValue, 0, maxDiodeValue);

  analogWrite(redLedPin, redLedValue);
  analogWrite(greenLedPin, greenLedValue);
  analogWrite(blueLedPin, blueLedValue);

}
