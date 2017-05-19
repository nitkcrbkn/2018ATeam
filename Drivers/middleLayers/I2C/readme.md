それぞれのI2CのID型である`i2cid_t`はこのように定義される。
```c
typedef enum
  {
    I2C1ID = 0,
    I2C2ID = 1,
  }i2cid_t;
```
I2Cを初期化する。引数としてIDを入れ、成功不成功を返す。
```c
int MW_I2CInit(i2cid_t id);
```
I2Cのクロックスピードを変更する。これは**Initする前に変更すること！**
```c
void MW_SetI2CClockSpeed(i2cid_t id,uint32_t ClockSpeed);
```
I2C1~I2C2の送信関数　送信先、データとそのデータサイズを引数として受け取る。成功不成功を返す。
```c
int32_t MW_I2C1Transmit(uint8_t address,const uint8_t *data,uint16_t size);
int32_t MW_I2C2Transmit(uint8_t address,const uint8_t *data,uint16_t size);
```

I2C1~I2C2の受信関数　受信先、格納データとその受け取るデータサイズを引数として受け取る。成功不成功を返す。
```c
int32_t MW_I2C1Receive(uint8_t address,uint8_t *data,uint16_t size);
int32_t MW_I2C2Receive(uint8_t address,uint8_t *data,uint16_t size);
```
