# EBSI2025 組込システム I - 7 - 説明・演習

このドキュメントは「EBSI2025 組込システム I」の第7回講義資料「説明・演習」の内容をまとめたものです。主なトピックはイベント検出と電圧比較回路です。

## 1. イベント検出 (Event Detection)

### 入力の検出方法 (Input Detection Methods)
-   **ポーリング (Polling):**
    ソフトウェアが入力装置の状態変化を定期的に読み取り、状態変化を判断する方法。
-   **割り込み (Interrupt):**
    ハードウェアが状態の変化を検知し、プロセッサに割り込みを発生させて登録された処理を実行する方法。

### ポーリング (Polling)
一定時間間隔で入力状態を読み込みます。

```python
import RPi.GPIO as GPIO
import time

GPIO.setmode ( GPIO.BCM )
SW = 21 # GPIO21
GPIO.setup ( SW, GPIO.IN, pull_up_down=GPIO.PUD_UP )
try:
    while True:
        if GPIO.input ( SW ) == 0:
            print ( "SW on” )
        else:
            print ( "SW off” )
        time.sleep(1)
except KeyboardInterrupt:
    pass
GPIO.cleanup() # Added for completeness, though not in original slide snippet
```

### イベント検出 (RPi.GPIO) (Event Detection with RPi.GPIO)
特定のGPIO端子への入力信号の変化（入力エッジ）を検知して、登録した処理を実行します。

#### イベント登録 (Event Registration)
-   どの端子のイベントか
-   どんなイベントか
    -   GPIO端子の入力エッジ（立ち上がり／立ち下がり）
-   どんな処理か
    -   `def`文による関数定義

#### イベント登録・解除関数
-   **イベント登録:** `GPIO.add_event_detect(ch, edge, callback, bouncetime)`
    -   `ch`: イベント登録するGPIO端子番号
    -   `edge`: イベント発生の信号のエッジ
        -   `GPIO.RISING`（立ち上がり）
        -   `GPIO.FALLING`（立ち下がり）
        -   `GPIO.BOTH`（両方）
    -   `callback`: 呼び出す関数
    -   `bouncetime`: 次のイベント検出までの時間（ms）。チャタリング防止用。
-   **イベント解除:** `GPIO.remove_event_detect(ch)`

#### イベント検出の仕組み
GPIO端子の状態変化でcallback関数が実行されます。

```python
import RPi.GPIO as GPIO
import time

GPIO.setmode ( GPIO.BCM )
SW = 21 # GPIO21
GPIO.setup ( SW, GPIO.IN, pull_up_down=GPIO.PUD_UP )
s = 0
def checkSW ( pin ): # pin はイベントが発生したGPIOピン番号
    global s # グローバル変数 s を使用
    s = 1
GPIO.add_event_detect ( SW, GPIO.FALLING, callback=checkSW, bouncetime=200 )
try:
    while True:
        if s==1:
            print('SW on')
            s = 0
        else:
            print('SW off')
        time.sleep(1)
except KeyboardInterrupt:
    pass
finally: # Ensure cleanup happens
    GPIO.remove_event_detect ( SW )
    GPIO.cleanup( )
```

### チャタリング (Chattering)
スイッチ変化時の連続的なON/OFFによる繰り返しのイベント発生を回避するために`bouncetime`を使用します。
-   スイッチが物理的に接触する際に、微細な振動により短時間にON/OFFが繰り返される現象。

### 演習（1）
SW入力をイベントを利用して検出します。
-   GPIO 21番ピンを使用。
-   立ち下がりエッジでイベントを検出し、`checkSW`関数を呼び出す。
-   `bouncetime`は200ms。
-   メインループではフラグ`s`を監視し、スイッチの状態を表示。

```python
# (演習(1)のコードは上記のイベント検出の仕組みのコードと同じです)
import RPi.GPIO as GPIO
import time

GPIO.setmode ( GPIO.BCM )
SW = 21
GPIO.setup ( SW, GPIO.IN, pull_up_down=GPIO.PUD_UP )
s = 0
def checkSW ( pin ):
    global s
    s = 1
GPIO.add_event_detect ( SW, GPIO.FALLING, callback=checkSW, bouncetime=200 )
try:
    while True:
        if s==1:
            print('SW on')
            s = 0
        else:
            print('SW off')
        time.sleep(1)
except KeyboardInterrupt:
    pass
finally:
    GPIO.remove_event_detect(SW)
    GPIO.cleanup()
```

## 2. 電圧比較回路 (Voltage Comparison Circuit)

### オペアンプ (Operational Amplifier / 演算増幅器)
-   2入力差動増幅器（2つの信号の差を増幅）。
-   応用例:
    -   増幅回路
    -   フィルタ
    -   比較回路

### 比較回路 (LM339は電圧比較用IC)
-   V2 - V1 > 0  => 出力 V<sub>CC</sub>（High）
-   V2 - V1 < 0  => 出力 V<sub>EE</sub>（Low）
-   **注意:** LM339はオープンコレクタタイプのため、プルアップ抵抗が必須です。

### 電圧比較回路（LM339）
LM339は4回路入りの電圧比較器です。
ピン配置例:
-   IN2-, IN2+, IN1-, IN1+
-   OUT2, OUT1

### 演習（2）
以下の回路を作製し、可変抵抗を調整して、cds素子への光を遮った時と遮らない時とでLEDの点滅状態が変わるようにします。
-   **回路構成要素:** LM339, 3.3V電源, GND, cds素子, 6.8kΩ抵抗, 10kΩ可変抵抗, 1kΩ抵抗, LED。
-   LM339のIN+にcds素子と6.8kΩ抵抗の分圧回路からの電圧を入力。
-   LM339のIN-に10kΩ可変抵抗からの電圧を入力。
-   LM339の出力を1kΩ抵抗経由でLEDに接続。

### 演習（3）
LEDを比較回路から切り離し、GPIOの出力に繋ぎ、比較回路の出力をGPIOの入力に繋ぎます。
cds素子により暗くなったことを検知した時にLEDを点灯し、SWを押すことでLEDを消灯するシステム（プログラム）を設計、製作します。cds素子（比較回路出力）、SWの変化の検知にはイベント検出を用います。

-   **ヒント:**
    -   回路は演習（1）（2）を参考に。
    -   比較器出力はオープンコレクタである。
    -   比較器出力はエッジに気をつけてSWと同様に扱う。

## 3. 問い (Question)

-   オープンコレクタとはどの様なものか。
    -   (解答は資料には含まれていませんが、一般的にトランジスタのコレクタが出力端子となっており、負荷抵抗（プルアップ抵抗）を介して電源に接続する必要がある出力形式です。LowレベルはトランジスタがONになることでGNDに接続され、HighレベルはトランジスタがOFFになることでプルアップ抵抗を介して電源電圧になります。)

## 4. 課題 (Assignment)

演習（1）（3）について全体が把握できる様に詳細にまとめること。最低限、以下の項目は含むこと。（課題〜考察で1200字以上）
-   **表紙:** 授業名、学籍番号・氏名、提出日
-   **本文:**
    -   課題
    -   使用部品
    -   回路の説明（RaspberryPiの端子を明記）
    -   アルゴリズムの説明
    -   結果（説明を工夫すること）
    -   考察
    -   問いの解答
    -   参考文献（任意）
-   **図表:**
    -   回路図と回路の写真は必須

## 5. レポート作成上の注意 (Notes on Report Creation)

-   **締め切り:** 6月5日（厳守）
-   **提出物:**
    -   レポート (学籍番号.pdf)
    -   演習（1）（3）ソースファイル（＊＊＊.py）
-   **注意:**
    -   実体配線図は回路図として認めない。
    -   授業資料のコピペ、流用は認めない。
    -   レポートはA4版としてPDFファイルで提出する。
    -   印刷して適切なレポートであること。
    -   キャプチャ画像等の文字は読めるものであること。
    -   PDFファイルに変換後、必ず、確認すること。

## 6. 次回 (Next Time)

-   LED ダイナミック点灯
