// Blink Deluxe

#include <Arduino.h>

// シリアル通信速度の定義
#define SERIAL_SPEED 115200

// LED と接続するピンの定義
#define LED_PIN PC5

// ボタンと接続するピンの定義
#define BUTTON_PIN PC6

// ボタン入力が確定するまでの待機時間の定義（ミリ秒）
#define BUTTON_STABLE_WAIT_MS 50

// LED の点滅間隔の定義（ミリ秒）
const unsigned long ledBlinkIntervals[] = {100, 300, 1000};

// LED の点滅間隔の数の定義
const uint8_t ledBlinkIntervalCount = sizeof(ledBlinkIntervals) / sizeof(ledBlinkIntervals[0]);

// 現在の LED の点滅間隔インデックスを保持する変数
uint8_t ledBlinkIntervalIndex = 0;

// LED の状態を最後に切り替えた時刻（ミリ秒）を保持する変数
unsigned long lastLedStateChangeTime = 0;

// 現在の LED 状態を保持する変数
bool currentLedState = HIGH;

// ボタンの前回の状態を保持する変数
bool lastButtonState = HIGH;

// ボタンの状態が最後に変化した時刻（ミリ秒）を保持する変数
unsigned long lastButtonStateChangeTime = 0;

// ボタンクリックを報告済みかどうかを保持する変数
bool hasReportedClick = false;

// setup() はプログラム開始直後に一度だけ実行される関数
void setup() {
  // NOTE: ch32-riscv core はシリアルの初期化を行うとハングアップするのでコメントアウト
  // シリアル通信の初期化
  // Serial.begin(SERIAL_SPEED);
  // while (!Serial && millis() < 1000);

  // 起動メッセージを表示
  Serial.println("--");
  Serial.println("DevKit (built at " __DATE__ " " __TIME__ ")");

  // LED と接続するピンのモードを設定
  pinMode(LED_PIN, OUTPUT);

  // ボタンと接続するピンのモードを設定
  pinMode(BUTTON_PIN, INPUT_PULLUP);
}

// loop() は setup() 関数が呼び出された後に繰り返し何度も実行される関数
void loop() {
  // ボタンがクリックされたら LED の点滅間隔を変更
  if (isButtonClicked()) {
    changeLedBlinkInterval();
  }

  // LED の点滅処理を実行
  blinkLed();
}

// ボタンクリックを検出する関数
bool isButtonClicked() {
  // 現在のボタン状態を取得
  bool currentButtonState = digitalRead(BUTTON_PIN);

  // ボタン状態が変化した場合はタイマーをリセットして以降の処理をスキップ
  if (currentButtonState != lastButtonState) {
    lastButtonStateChangeTime = millis();
    lastButtonState = currentButtonState;
    hasReportedClick = false;
    return false;
  }

  // ボタンクリックを既に報告済みの場合は以降の処理をスキップ
  if (hasReportedClick) {
    return false;
  }

  // ボタン入力が確定するまでの待機時間経過前は以降の処理をスキップ
  if ((millis() - lastButtonStateChangeTime) <= BUTTON_STABLE_WAIT_MS) {
    return false;
  }

  // ボタンが押されている場合はクリック検出フラグを設定してボタンクリックを報告
  if (currentButtonState == LOW) {
    hasReportedClick = true;
    return true;
  }

  return false;
}

// LED の点滅間隔を変更する関数
void changeLedBlinkInterval() {
  // LED の点滅間隔インデックスを設定
  ledBlinkIntervalIndex = (ledBlinkIntervalIndex + 1) % ledBlinkIntervalCount;

  // 点滅間隔変更メッセージを表示
  Serial.print("Blink Interval Changed: ");
  Serial.print(ledBlinkIntervals[ledBlinkIntervalIndex]);
  Serial.println(" ms");

  // LED の状態を点灯に設定
  currentLedState = HIGH;

  // LED の状態を最後に切り替えた時刻を設定
  lastLedStateChangeTime = millis();

  // LED の状態をピンに反映
  digitalWrite(LED_PIN, currentLedState);
}

// LED の点滅処理を実行する関数
void blinkLed() {
  // 現在時刻（ミリ秒）を取得
  unsigned long currentMillis = millis();

  // 点滅間隔が経過していない場合は以降の処理をスキップ
  if (currentMillis - lastLedStateChangeTime < ledBlinkIntervals[ledBlinkIntervalIndex]) {
    return;
  }

  // LED の状態を最後に切り替えた時刻を設定
  lastLedStateChangeTime = currentMillis;

  // LED の状態を反転（点灯→消灯、または消灯→点灯）
  currentLedState = !currentLedState;

  // LED に状態を反映
  digitalWrite(LED_PIN, currentLedState);
}
