/* ===Kisarazu RBKN Library===
 *
 * autor          : Idutsu
 * version        : v0.10
 * last update    : 20180501
 *
 * **overview***
 * SDの通信プロトコルを定める。
 *
 * ・I2Cのみのサポート
 */

#ifndef __SS_H
#define __SS_H
#include <stdint.h>

typedef struct{
  uint8_t add;       /*I2C アドレス格納変数*/
  uint8_t data_size; /*データサイズ格納変数*/
  uint8_t data[8];   /*データ格納配列*/
}DD_SSHand_t;

/*
 * 指定バイト受信。
 * [data[7:0](7:0)]*指定バイト分
 *
 */
int DD_receive2SS(DD_SSHand_t *dmd);

/*
 *SD handlerを表示。
 *
 *SD(Add:hex):[データサイズ],[受信データ]*データサイズ分
 */
void DD_SSHandPrint(DD_SSHand_t *dmd);

#endif
