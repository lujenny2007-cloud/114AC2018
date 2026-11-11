const int buttonPin = 2;
const int ledPin = 3;

const int LED_ON = HIGH;
const int LED_OFF = LOW;

int mode = 0; // 0恆亮 1慢閃 2中閃 3快閃

bool lastReading = LOW;
bool buttonState = LOW;

unsigned long debounceTime = 0;
unsigned long blinkStart = 0;

const unsigned long debounceDelay = 30;

void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);

  digitalWrite(ledPin, LED_ON);
  Serial.begin(9600);
}

void loop() {
  unsigned long now = millis();

  // 按鈕去彈跳，確保按一次只切換一次
  bool reading = digitalRead(buttonPin);

  if (reading != lastReading) {
    debounceTime = now;
  }

  if (now - debounceTime > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;

      if (buttonState == HIGH) {
        mode = (mode + 1) % 4;
        blinkStart = now;

        Serial.print("Mode: ");
        Serial.println(mode);
      }
    }
  }

  lastReading = reading;

  // 根據模式決定閃爍速度
  unsigned long interval = 0;

  if (mode == 0) {
    digitalWrite(ledPin, LED_ON);
    return;
  }
  else if (mode == 1) {
    interval = 1000; // 慢閃
  }
  else if (mode == 2) {
    interval = 500;  // 中閃
  }
  else if (mode == 3) {
    interval = 150;  // 快閃
  }

  // 不使用 delay，按鈕可以隨時切換
  if (((now - blinkStart) / interval) % 2 == 0) {
    digitalWrite(ledPin, LED_ON);
  } else {
    digitalWrite(ledPin, LED_OFF);
  }
}
