// ===== 腳位設定（依簡報接線圖）=====
const byte BUTTON_PIN = 2;
const byte RED_PIN = 10;
const byte GREEN_PIN = 11;
const byte BLUE_PIN = 9;

// ===== 按鈕設定 =====
const unsigned long LONG_PRESS = 2000;
const unsigned long DEBOUNCE = 35;

bool lastRawState = false;
bool stableState = false;
unsigned long debounceTime = 0;
unsigned long pressStart = 0;

// ===== 燈光模式 =====
// 0 恆亮、1 閃爍、2 呼吸、3 心跳
byte mode = 0;
const byte MODE_COUNT = 4;

// ===== 顏色設定 =====
// 白、紅、綠、藍、黃、紫、青
const byte colors[][3] = {
  {255, 255, 255},
  {255, 0, 0},
  {0, 255, 0},
  {0, 0, 255},
  {255, 255, 0},
  {180, 0, 255},
  {0, 255, 255}
};

const byte COLOR_COUNT = sizeof(colors) / sizeof(colors[0]);
byte colorIndex = 0;

unsigned long effectStart = 0;

// ===== LED 顏色輸出 =====
// 簡報使用共陽極 RGB，數值需要反轉
void setColor(byte r, byte g, byte b) {
  analogWrite(RED_PIN, 255 - r);
  analogWrite(GREEN_PIN, 255 - g);
  analogWrite(BLUE_PIN, 255 - b);
}

// ===== 初始化 =====
void setup() {
  Serial.begin(9600);

  pinMode(BUTTON_PIN, INPUT);
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);

  effectStart = millis();
  setColor(255, 255, 255);
}

// ===== 按鈕偵測 =====
void checkButton(unsigned long now) {
  // 簡報按鈕模組：HIGH 代表按下
  bool rawState = digitalRead(BUTTON_PIN) == HIGH;

  if (rawState != lastRawState) {
    debounceTime = now;
  }

  if (now - debounceTime >= DEBOUNCE) {
    if (rawState != stableState) {
      stableState = rawState;

      if (stableState) {
        pressStart = now;
      } else {
        unsigned long duration = now - pressStart;

        if (duration >= LONG_PRESS) {
          // 長按：切換模式
          mode = (mode + 1) % MODE_COUNT;
          Serial.print("Mode: ");
          Serial.println(mode);
        } else {
          // 短按：切換顏色
          colorIndex = (colorIndex + 1) % COLOR_COUNT;
          Serial.print("Color: ");
          Serial.println(colorIndex);
        }

        effectStart = now;
      }
    }
  }

  lastRawState = rawState;
}

// ===== 控制燈光模式 =====
void updateLED(unsigned long now) {
  unsigned long elapsed = now - effectStart;
  byte brightness = 255;

  switch (mode) {

    case 0:
      // 模式 1：恆亮
      brightness = 255;
      break;

    case 1:
      // 模式 2：閃爍
      // 每 350 毫秒切換亮暗
      brightness = ((elapsed / 350) % 2 == 0)
                     ? 255 : 0;
      break;

    case 2: {
      // 模式 3：呼吸燈
      // 2 秒完成一次呼吸
      unsigned long t = elapsed % 2000UL;

      if (t < 1000) {
        brightness = map(t, 0, 1000, 10, 255);
      } else {
        brightness = map(t, 1000, 2000, 255, 10);
      }
      break;
    }

    case 3: {
      // 模式 4：心跳燈（額外加分）
      // 連續跳動兩次後短暫休息
      unsigned long t = elapsed % 1400UL;

      if (t < 130) {
        brightness = map(t, 0, 130, 0, 255);
      } else if (t < 260) {
        brightness = map(t, 130, 260, 255, 0);
      } else if (t < 390) {
        brightness = map(t, 260, 390, 0, 200);
      } else if (t < 520) {
        brightness = map(t, 390, 520, 200, 0);
      } else {
        brightness = 0;
      }
      break;
    }
  }

  // 套用目前選擇的顏色與亮度
  byte r = (unsigned long)colors[colorIndex][0] * brightness / 255;
  byte g = (unsigned long)colors[colorIndex][1] * brightness / 255;
  byte b = (unsigned long)colors[colorIndex][2] * brightness / 255;

  setColor(r, g, b);
}

// ===== 主迴圈 =====
void loop() {
  unsigned long now = millis();

  checkButton(now);
  updateLED(now);
}