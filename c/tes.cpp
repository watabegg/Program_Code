#include <DHT.h>
#include <DHT_U.h>
#include <DHT.h>
#include <DHT_U.h>
#include <DHT.h>
#include <DHT_U.h>
// 転送スピード
#define SERIAL_SPEED 115200
// 赤外線受信モジュールを接続するピン
const int modulePin = 2;
// 待ち時間
const int waitMicros = 1000000;
// 起動から現在の経過時間
unsigned long now;
// 1 つ前の経過時間を保持
unsigned long lastMicros;
// 待ち開始時間
unsigned long waitStartMicros;
// 赤外線受信モジュールの状態
// 0 : LOW, 1 : HIGH
int moduleStatus;
// 待ち時間の状態
int waitStatus;
void setup()
{
    // パソコンとのシリアル通信のポートを開ける
    Serial.begin(SERIAL_SPEED);
    // デジタル入力として設定
    pinMode(modulePin, INPUT);
    // 初期値を設定
    now = micros();
    lastMicros = micros();
    moduleStatus = 1;
}
void loop()
{
    // 赤外線受信モジュールが LOW ならば
    if (moduleStatus == 0)
    {
        // LOW の間待つ処理
        waitStatus = waitLow();
        // 1 秒以上 LOW から切り替わらなかったら
        if (waitStatus == 1)
        {
            // シリアルモニターを改行
            Serial.println();
            return;
        }
    }
    else
    {
        // HIGH の間待つ処理
        waitStatus = waitHigh();
        // 1 秒以上 HIGH から切り替わらなかったら
        if (waitStatus == 1)
        {
            // シリアルモニターを改行
            Serial.println();
            return;
        }
    }
    // 起動からの現在の経過時間を取得
    now = micros();
    // 赤外線モジュールの状態が変化するまでにかかった時間を表示
    Serial.print((now - lastMicros) / 10, DEC);
    Serial.print(",");
    // 現在の経過時間を保持
    lastMicros = now;
    // モジュールの状態を反転
    // LOW なら HIGH へ、HIGH なら LOW へ
    moduleStatus = !moduleStatus;
}
/*
赤外線情報が LOW のとき待つ処理です
*/
int waitLow()
{
    waitStartMicros = micros();
    // LOW の間処理を繰り返す
    while (digitalRead(modulePin) == LOW)
    {
        // 待ち始めて 1 秒以上経過したら
        if (micros() - waitStartMicros > waitMicros)
        {
            return 1;
        }
    }
    return 0;
}
/*
赤外線情報が HIGH のとき待つ処理です
*/
int waitHigh()
{
    waitStartMicros = micros();
    // HIGH の間処理を繰り返す
    while (digitalRead(modulePin) == HIGH)
    {
        // 待ち始めて 1 秒以上経過したら
        if (micros() - waitStartMicros > waitMicros)
        {
            return 1;
        }
    }
    return 0;
}