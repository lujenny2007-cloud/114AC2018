const int buttonPin = 2;
const int RledPin = 3;
const int GledPin = 5;
const int BledPin = 4;

// Variables
int buttonState = 0;
bool ButtonPressed = false;

int mood = 10;

unsigned long previousMillis = 0;
unsigned long currentMillis = 0;

const long interval = 5000;
const long decreaseInterval = 1000;

unsigned long lastDecrease = 0;

// Setup
void setup() {
  pinMode(RledPin, OUTPUT);
  pinMode(GledPin, OUTPUT);
  pinMode(BledPin, OUTPUT);

  pinMode(buttonPin, INPUT);

  Serial.begin(9600);

  previousMillis = millis();
  lastDecrease = millis();

  updateMood();

  Serial.println("Game Start!");
  Serial.println("Mood: 10");
}

// Main Loop
void loop() {

  currentMillis = millis();

  buttonState = digitalRead(buttonPin);

  // Button Pressed
  if (buttonState == HIGH && !ButtonPressed) {

    ButtonPressed = true;

    // Increase mood
    if (mood < 20) {
      mood = mood + 1;
    }

    previousMillis = currentMillis;
    lastDecrease = currentMillis;

    updateMood();

    Serial.print("Mood: ");
    Serial.println(mood);

    delay(30);
  }

  // Button Released
  if (buttonState == LOW && ButtonPressed) {
    ButtonPressed = false;
    delay(30);
  }

  // No touch for 5 seconds
  if (currentMillis - previousMillis >= interval) {

    // Decrease mood every second
    if (currentMillis - lastDecrease >= decreaseInterval) {

      lastDecrease = currentMillis;

      if (mood > 0) {
        mood = mood - 1;
      }

      updateMood();

      Serial.print("Mood: ");
      Serial.println(mood);
    }
  }
}

// RGB LED Mood Color
void updateMood() {

  int red = 0;
  int green = 0;
  int blue = 0;

  // Mood 0~10: Red to Green
  if (mood <= 10) {

    red = map(mood, 0, 10, 255, 0);
    green = map(mood, 0, 10, 0, 255);
    blue = 0;

  }

  // Mood 10~20: Green to Blue
  else {

    red = 0;
    green = map(mood, 10, 20, 255, 0);
    blue = map(mood, 10, 20, 0, 255);

  }

  // Common Anode RGB LED
  analogWrite(RledPin, 255 - red);
  analogWrite(GledPin, 255 - green);
  analogWrite(BledPin, 255 - blue);
}