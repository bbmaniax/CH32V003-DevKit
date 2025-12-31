# Arduino: DevKit

CH32V003 開発ボードを入門用のプロジェクトです。

## 部材

| 種別 | 型番など | 数量 |
|:-----|:---------|:-----|
| ブレッドボード | 400H | 1個 |
| ジャンパーワイヤ | - | 適量 |
| タクトスイッチ | 2P 6x6mm | 1個 |
| マイコン | CH32V003 開発ボード | 1個 |
| LED | 3mm または 5mm | 1個 |
| 抵抗 | 220Ω | 1個 |

## 配線

- **LED**: PC5（220Ω抵抗経由でGND）
- **ボタン**: PC6（INPUT_PULLUP）

## プログラム開発環境

### 統合開発環境

**インストール**:
1. 公式サイト [https://www.arduino.cc/en/software/#ide](https://www.arduino.cc/en/software/#ide) からダウンロード・インストール

### ボードマネージャ

**インストール**:
1. Arduino IDE の「ファイル」→「環境設定」→「追加のボードマネージャのURL」に以下を追加:
   ```
   https://raw.githubusercontent.com/ch32-riscv-ug/arduino_core_ch32_riscv_arduino/main/package_ch32-riscv-arduino.json
   ```
2. ボードマネージャーで「CH32 RISC-V Arduino」を検索し、「インストール」ボタンをクリック

## ビルド・書き込み手順

1. Arduino IDE で `CH32V003-BlinkPlus.ino` を開く
2. 「ツール」→「ボード」→「CH32 RISC-V Arduino」→「CH32V003」を選択
3. 「ツール」→「ポート」でWCH-LinkEが接続されているポートを選択
4. 画面上部の右向き矢印ボタン（アップロード）をクリック

## スケッチの動作

### 起動時

- LED が点滅を開始します

### ボタン操作

ボタンを押すたびに、LED の点滅間隔が切り替わります。

## ライセンス

このプロジェクトは [MIT ライセンス](./LICENSE) の下で公開されています。
自由に使用、改変、再配布していただけます。
