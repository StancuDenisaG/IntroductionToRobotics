// pedestrians lights 
const int greenLightPedestrians = 7;
byte greenLightPedestriansState = LOW;
const int greenLightDuration = 8000;
const int resetDelay = 12000;
const int redLightPedestrians = 8; 
byte redLightPedestriansState = HIGH;

// cars lights 
const int greenLightCars = 11;
byte greenLightCarsState = HIGH;
const int yellowLightCars = 12;
byte yellowLightCarsState = LOW;
const int yellowLightDuration = 3000;
const int redLightCars = 13; 
byte redLightCarsState = LOW;

//button
const int buttonPin = 2;
byte buttonState;
const int buttonPressDelay = 8000; 
byte lastButtonState = LOW;

//buzzer
const int buzzerPin = 3;
const int buzzerTone = 400;
const int buzzerFasterTone = 600;
unsigned long buzzerTimer = 0;
const int buzzerBlinkDelay = 500;
const int buzzerBlinkFaster = 300;


unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;


int state = 1;
unsigned long timer = 0;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(greenLightPedestrians, OUTPUT);
  pinMode(redLightPedestrians, OUTPUT);
  pinMode(greenLightCars, OUTPUT);
  pinMode(yellowLightCars, OUTPUT);
  pinMode(redLightCars, OUTPUT);

  Serial.begin(9600);

}


void firstState() {
  // red for pedestrians
  greenLightPedestriansState = LOW;
  redLightPedestriansState = HIGH;
  // green for cars
  greenLightCarsState = HIGH;
  yellowLightCarsState = LOW;
  redLightCarsState = LOW;

  state = 1;
  buzzerTimer = 0;
  timer = 0;

}

void secondState() {
  // red for pedestrians, yellow for cars
  greenLightCarsState = LOW;
  yellowLightCarsState = HIGH;
 
  state = 3;
  timer = millis();
}


void thirdState() {
  //red for cars
  redLightCarsState = HIGH;
  yellowLightCarsState = LOW;
  greenLightCarsState = LOW;
  //green for pedestrians
  greenLightPedestriansState = HIGH;
  redLightPedestriansState = LOW;
  
  state = 4;
  timer = millis();
}
// buzzer beeping
void beepingBuzzer() {
  if ((millis() - buzzerTimer) > buzzerBlinkDelay) {
    tone(buzzerPin, buzzerTone, buzzerBlinkFaster);
    buzzerTimer = millis();
  }
}


void fourthState() {
  // blinking green for pedestrians, red for cars, buzzer beeping faster
  if ((millis() - buzzerTimer) > buzzerBlinkFaster) {
  tone(buzzerPin, buzzerFasterTone, buzzerBlinkFaster);
  greenLightPedestriansState = !greenLightPedestriansState;
  buzzerTimer = millis();
  }
}

void loop() {

  digitalWrite(greenLightPedestrians, greenLightPedestriansState);
  digitalWrite(redLightPedestrians, redLightPedestriansState);
  digitalWrite(greenLightCars, greenLightCarsState);
  digitalWrite(yellowLightCars, yellowLightCarsState);
  digitalWrite(redLightCars, redLightCarsState);

  byte reading = digitalRead(buttonPin);
  
  if (reading != lastButtonState && state == 1) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;

      if (!buttonState && state == 1) {
        timer = millis();
        state = 2;
      }
    }
  }

  if ((millis() - timer) >= buttonPressDelay && state == 2) {
    secondState();
  }

  if ((millis() - timer) >= yellowLightDuration && state == 3) {
    thirdState();
  }

  if ((millis() - timer) < greenLightDuration && state == 4) {
    beepingBuzzer();
  }

  if ((millis() - timer) >= greenLightDuration && state == 4 && (millis() - timer) < resetDelay) {
    fourthState();
  }

  if ((millis() - timer) >= resetDelay && state == 4) {
    firstState();
  }

  lastButtonState = reading;
}