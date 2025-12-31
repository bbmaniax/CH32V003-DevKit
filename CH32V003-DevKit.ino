// CH32V003-DevKit.ino

#include <Arduino.h>

// シリアル通信速度の定義
#define SERIAL_SPEED 115200

// LED と接続するピンの定義
#define LED_PIN PC7

// ボタンと接続するピンの定義
#define BUTTON1_PIN PC5
#define BUTTON2_PIN PC6
#define BUTTON3_PIN PD4

// ブザーと接続するピンの定義
#define BUZZER_PIN PC3

// ボタンと対応する音階の定義
#define TONE_C4 262
#define TONE_D4 294
#define TONE_E4 330

// 音の長さの定義
#define TONE_DURATION_MS 200

// setup はプログラム開始直後に一度だけ実行される関数
void setup() {
  // 起動音
  tone(BUZZER_PIN, 2000, 12);
  delay(150);
  tone(BUZZER_PIN, 1000, 120);
  delay(200);

  // LEDと接続するピンのモードを設定
  pinMode(LED_PIN, OUTPUT);

  // 起動時にLEDを3回点滅させる
  for (int i = 0; i < 3; i++) {
    digitalWrite(LED_PIN, HIGH);
    delay(200);
    digitalWrite(LED_PIN, LOW);
    delay(200);
  }

  // シリアル通信の初期化
  // Serial.begin(SERIAL_SPEED);
  // while (!Serial && millis() < 1000);

  // 起動メッセージを表示
  Serial.println("--");
  Serial.println("DevKit (build " + String(__DATE__) + "." + String(__TIME__) + ")");

  // ボタンと接続するピンのモードを設定
  pinMode(BUTTON1_PIN, INPUT_PULLUP);
  pinMode(BUTTON2_PIN, INPUT_PULLUP);
  pinMode(BUTTON3_PIN, INPUT_PULLUP);

  Serial.println("Setup complete.");
}

// loop は setup 関数が呼び出された後に繰り返し何度も実行される関数
void loop() {
  // ボタン1が押されたらLEDを点灯し、対応する音を鳴らす
  if (digitalRead(BUTTON1_PIN) == LOW) {
    Serial.println("Button 1 pressed");
    digitalWrite(LED_PIN, HIGH);
    tone(BUZZER_PIN, TONE_C4, TONE_DURATION_MS);
    digitalWrite(LED_PIN, LOW);
  }

  // ボタン2が押されたらLEDを点灯し、対応する音を鳴らす
  if (digitalRead(BUTTON2_PIN) == LOW) {
    Serial.println("Button 2 pressed");
    digitalWrite(LED_PIN, HIGH);
    tone(BUZZER_PIN, TONE_D4, TONE_DURATION_MS);
    digitalWrite(LED_PIN, LOW);
  }

  // ボタン3が押されたらLEDを点灯し、対応する音を鳴らす
  if (digitalRead(BUTTON3_PIN) == LOW) {
    Serial.println("Button 3 pressed");
    digitalWrite(LED_PIN, HIGH);
    tone(BUZZER_PIN, TONE_E4, TONE_DURATION_MS);
    digitalWrite(LED_PIN, LOW);
  }

  delay(10);
}

// tone() 関数の実装（CH32V003には標準実装がないため独自実装）
void tone(uint8_t pin, unsigned int frequency, unsigned long duration) {
  uint32_t period_us = 1000000UL / frequency;
  uint32_t half_period_us = period_us / 2;
  uint32_t cycles = duration * 1000UL / period_us;

  pinMode(BUZZER_PIN, OUTPUT);

  for (uint32_t i = 0; i < cycles; i++) {
    digitalWrite(pin, HIGH);
    delayMicroseconds(half_period_us);
    digitalWrite(pin, LOW);
    delayMicroseconds(half_period_us);
  }
}
