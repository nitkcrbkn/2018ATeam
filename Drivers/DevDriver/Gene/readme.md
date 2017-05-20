# デバイス制御
デバイス全体の制御系。リモコンの動作はここでは定義しない。

# 公開関数
デバイスに対するタスクを実行する。成功不成功を返す。
たとえばMDに対して送信を行ったり、Encoderに対して更新を行ったりする。
```c
int DD_doTasks(void)
```

デバイスのハンドラ(送信データ)を表示する。ハンドラの中身を順に表示する。
```c
void DD_print(void)
```

デバイスの初期化を行う。実際はSVのドライバの初期化や、エンコーダの初期化を行う。
```c
int DD_initialize(void)
```


## Private 関数
I2Cの送受信関数。addressとデータと大きさを引数に指定する。成功不成功を返す。
```c
static
int DD_I2CSend(uint8_t add, const uint8_t *data, uint8_t size)
int DD_I2CRecieve(uint8_t add, const uint8_t *data, uint8_t size)
```
