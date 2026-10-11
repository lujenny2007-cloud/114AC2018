const int buttonPin = 2;  // the number of the pushbutton pin
const int RledPin = 3;    // the number of the R pin
const int GledPin = 4;    // the number of the G pin
const int BledPin = 5;    // the number of the B pin

// variables will change:
int buttonState = 0;  // variable for reading the pushbutton status
int ledcolor = 0;

void setup() {
  // initialize the LED pins as outputs:
  pinMode(RledPin, OUTPUT);
  pinMode(GledPin, OUTPUT);
  pinMode(BledPin, OUTPUT);

  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
}

void loop() {
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);

  if (buttonState == HIGH) {
    ledcolor = ledcolor + 1;
    delay(100);
  }

  if (ledcolor == 0) {
    digitalWrite(RledPin, HIGH);
    digitalWrite(GledPin, HIGH);
    digitalWrite(BledPin, HIGH);
    delay(1000);
    digitalWrite(RledPin, HIGH);
    digitalWrite(GledPin, HIGH);
    digitalWrite(BledPin, HIGH);
    delay(1000);
  }
  else if (ledcolor == 1) {
    // RED
    digitalWrite(RledPin, LOW);
    digitalWrite(GledPin, HIGH);
    digitalWrite(BledPin, HIGH);
    delay(1000);
    digitalWrite(RledPin, HIGH);
    digitalWrite(GledPin, HIGH);
    digitalWrite(BledPin, HIGH);
    delay(1000);
  }
  else if (ledcolor == 2) {
    // GREEN
    digitalWrite(RledPin, HIGH);
    digitalWrite(GledPin, LOW);
    digitalWrite(BledPin, HIGH);
    delay(1000);
    digitalWrite(RledPin, HIGH);
    digitalWrite(GledPin, HIGH);
    digitalWrite(BledPin, HIGH);
    delay(1000);
  }
  else if (ledcolor == 3) {
    // BLUE
    digitalWrite(RledPin, HIGH);
    digitalWrite(GledPin, HIGH);
    digitalWrite(BledPin, LOW);
    delay(1000);
    digitalWrite(RledPin, HIGH);
    digitalWrite(GledPin, HIGH);
    digitalWrite(BledPin, HIGH);
    delay(1000);
  }
  else if (ledcolor == 4) {
    digitalWrite(RledPin, LOW);
    digitalWrite(GledPin, LOW);
    digitalWrite(BledPin, HIGH);
    delay(1000);
    digitalWrite(RledPin, HIGH);
    digitalWrite(GledPin, HIGH);
    digitalWrite(BledPin, HIGH);
    delay(1000);
  }
  else if (ledcolor == 5) {
    // PURPLE
    digitalWrite(RledPin, LOW);
    digitalWrite(GledPin, HIGH);
    digitalWrite(BledPin, LOW);
    delay(1000);
    digitalWrite(RledPin, HIGH);
    digitalWrite(GledPin, HIGH);
    digitalWrite(BledPin, HIGH);
    delay(1000);
  }
  else if (ledcolor == 6) {
    // CYAN
    digitalWrite(RledPin, HIGH);
    digitalWrite(GledPin, LOW);
    digitalWrite(BledPin, LOW);
    delay(1000);
    digitalWrite(RledPin, HIGH);
    digitalWrite(GledPin, HIGH);
    digitalWrite(BledPin, HIGH);
    delay(1000);
  }
  else if (ledcolor == 7) {
    // WHITE
    digitalWrite(RledPin, LOW);
    digitalWrite(GledPin, LOW);
    digitalWrite(BledPin, LOW);
    delay(1000);
    digitalWrite(RledPin, HIGH);
    digitalWrite(GledPin, HIGH);
    digitalWrite(BledPin, HIGH);
    delay(1000);
  }
  else if (ledcolor == 8) {
    ledcolor = 0;
  }
}