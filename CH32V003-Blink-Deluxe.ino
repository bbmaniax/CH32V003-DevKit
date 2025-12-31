// Blink Deluxe

#include <Arduino.h>

// シリアル通信速度の定義
#define SERIAL_SPEED 115200

// LED と接続するピンの定義
#define LED1_PIN PC4
#define LED2_PIN PC3
#define LED3_PIN PC2

// ボタンと接続するピンの定義
#define BUTTON1_PIN PC5
#define BUTTON2_PIN PC6
#define BUTTON3_PIN PC7

// ブザーと接続するピンの定義
#define BUZZER_PIN PC1

// LED の点滅間隔の定義（ミリ秒）
#define BLINK_INTERVAL_MS 1000

// LED と対応する音階の定義
#define TONE_C4 262
#define TONE_D4 294
#define TONE_E4 330

// 音の長さの定義（ミリ秒）
#define TONE_DURATION_MS 200

// LED と対応するピンの配列
const uint8_t ledPins[] = {LED1_PIN, LED2_PIN, LED3_PIN};

// LED と対応する音階の配列
const int ledTones[] = {TONE_C4, TONE_D4, TONE_E4};

// setup はプログラム開始直後に一度だけ実行される関数
void setup() {
  // NOTE: ch32-riscv コアは Serial の初期化を行うとハングアップするのでコメントアウト
  // シリアル通信の初期化
  // Serial.begin(SERIAL_SPEED);
  // while (!Serial && millis() < 1000);

  // 起動メッセージを表示
  Serial.println("--");
  Serial.println("Blink Deluxe (built at " + String(__DATE__) + " " + String(__TIME__) + ")");

  // LED と接続するピンのモードを設定
  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
  pinMode(LED3_PIN, OUTPUT);

  // ボタンと接続するピンのモードを設定
  pinMode(BUTTON1_PIN, INPUT_PULLUP);
  pinMode(BUTTON2_PIN, INPUT_PULLUP);
  pinMode(BUTTON3_PIN, INPUT_PULLUP);

  // ブザーと接続するピンのモードを設定
  pinMode(BUZZER_PIN, OUTPUT);

  // 起動音
  tone(BUZZER_PIN, 2000, 12);
  delay(150);
  tone(BUZZER_PIN, 1000, 120);
  delay(200);

  Serial.println("Setup complete.");
}

// loop は setup 関数が呼び出された後に繰り返し何度も実行される関数
void loop() {
  // LED点滅モードと点滅状態を管理する変数
  static unsigned long lastMillis = 0;
  static uint8_t  currentLedIndex = 0;
  static bool currentLedState = HIGH;

  // ボタン押下を検出
  int8_t buttonIndex = -1;
  if (digitalRead(BUTTON1_PIN) == LOW) {
    buttonIndex = 0;
  } else if (digitalRead(BUTTON2_PIN) == LOW) {
    buttonIndex = 1;
  } else if (digitalRead(BUTTON3_PIN) == LOW) {
    buttonIndex = 2;
  }

  // ボタンが押されたら対応するLEDを点灯し、音を鳴らす
  if (buttonIndex >= 0) {
    currentLedIndex = buttonIndex;
    currentLedState = HIGH;
    lastMillis = millis();
    digitalWrite(LED1_PIN, LOW);
    digitalWrite(LED2_PIN, LOW);
    digitalWrite(LED3_PIN, LOW);
    digitalWrite(ledPins[currentLedIndex], currentLedState);
    tone(BUZZER_PIN, ledTones[currentLedIndex], TONE_DURATION_MS);
  }

  // LED の点灯・消灯を切り替える
  unsigned long currentMillis = millis();
  if (currentMillis - lastMillis >= BLINK_INTERVAL_MS) {
    lastMillis = currentMillis;
    currentLedState = !currentLedState;
    digitalWrite(ledPins[currentLedIndex], currentLedState);
  }
}

// Arduino 標準 tone() 関数の代替実装（ch32-riscv コアには tone() 関数が無いため）
void tone(uint8_t pin, unsigned int frequency, unsigned long duration) {
  uint32_t period_us = 1000000UL / frequency;
  uint32_t half_period_us = period_us / 2;
  uint32_t cycles = duration * 1000UL / period_us;

  for (uint32_t i = 0; i < cycles; i++) {
    digitalWrite(pin, HIGH);
    delayMicroseconds(half_period_us);
    digitalWrite(pin, LOW);
    delayMicroseconds(half_period_us);
  }
}
