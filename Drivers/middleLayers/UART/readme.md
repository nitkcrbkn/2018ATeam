ボーレート設定関数
	引数はUARTのid,ボーレート設定値
	初期化前に実行のこと。
```c
void MW_USARTSetBaudRate(usartid_t id, uint32_t BaudRate)
```

初期化関数
	USARTの初期化を行う。引数はUARTのidで成功不成功を返す。
```c
int MW_USARTInit(usartid_t id)
```

UART1送信関数
	引数は送信データとそのデータのバイト数で、成功不成功を返す。
	ポーリングで送信する。送信が完了してから帰る。
```c
int32_t MW_USART1Transmit(const uint8_t *str, uint16_t datanum)
```


UART1受信関数
	1バイト受信で成功したらその文字を返し、失敗したら-1を返す。
```c
int32_t MW_USART1Receive(void)
```

UART2送信関数
	引数は送信データとそのデータのバイト数で、成功不成功を返す。
	DMAで送信する。そのため送信完了を待たずに正常終了する。
```c
int32_t MW_USART2Transmit(const uint8_t *str, uint16_t datanum)
```

UART2受信関数
	1バイト受信で成功したらその文字を返し、失敗したら-1を返す。
```c
int32_t MW_USART2Receive(void)
```

UART3送信関数
	引数は送信データとそのデータのバイト数で、成功不成功を返す。
	ポーリングで送信する。送信が完了してから帰る。
```c
int32_t MW_USART3Transmit(const uint8_t *str, uint16_t datanum)
```

UART3受信関数(Polling)
	1バイト受信で成功したらその文字を返し、失敗したら-1を返す。
```c
int32_t MW_USART3Receive(void)
```

UART3受信関数(DMA)
	引数は受信サイズとデータ格納先、マルチバイト受信をする。
	DMAなので送信が完了しない中でも正常終了を返す。
```c
int32_t MW_USART3ReceiveMult(int size, const uint8_t *data)
```
