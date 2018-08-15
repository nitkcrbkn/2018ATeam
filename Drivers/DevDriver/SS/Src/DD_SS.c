/* ===Kisarazu RBKN Library===
 *
 * autor          : Idutsu
 * version        : v0.10
 * last update    : 20180501
 *
 * **overview***
 * SSの通信プロトコルを定める。
 *
 * ・I2Cのみのサポート
 */
#include <stdint.h>
#include "message.h"
#include "DD_SS.h"
#include "DD_Gene.h"
/*
 *2018年第31回ロボコンでの自動ロボット自立制御の為追加
 *deviceDefinition.cで使用するセンサドライバの数、初期設定を行い
 *使用する
 */

/*SystemTaskManagerにより繰り返し実行される*/
int DD_receive2SS(DD_SSHand_t *dmd){
  /*I2Cのアドレス、受信データを格納する配列とそのサイズを
   *受信用の関数に引数として渡し、返り値として成功か否かを 
   *返す
   *引数として渡した配列に受信データが格納される
   *引数として渡す配列は、アドレスを渡す
   */
  return DD_I2C2Receive(dmd->add, dmd->data, dmd->data_size);
}


/*
 * *SS handlerを表示。
 *
 * SS(Add:hex):[データサイズ],[受信データ]*データサイズ分
 */

void DD_SSHandPrint(DD_SSHand_t *dmd){
  MW_printf("SS(%02x):[%d]", dmd->add,dmd->data_size);
  for(int i=0;i<dmd->data_size;i++){
    MW_printf("[%02x]",dmd->data[i]);
  }
  MW_printf("\n");
}

