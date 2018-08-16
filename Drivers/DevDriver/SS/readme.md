## SS(センサドライバ)

表示形式は
```
SS(Add:hex):[data size],[receive data:hex]*データサイズ分
```
です。

### 用意した型
構造体を一つ用意しました。
上から順に、アドレス、受信データサイズ、受信データ格納配列となります。
```c
typedef struct{
  uint8_t add;       /*I2C アドレス格納変数*/
  uint8_t data_size; /*データサイズ格納変数*/
  uint8_t data[8];   /*データ格納配列*/
}DD_SSHand_t;
```

### 用意した関数
int DD_receive2SS(DD_SSHand_t *dmd);
SSからデータを受信します。

void DD_SSHandPrint(DD_SSHand_t *dmd);
SSのハンドラを表示します。
