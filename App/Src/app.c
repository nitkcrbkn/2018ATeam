#include "app.h"
#include "DD_Gene.h"
#include "DD_RCDefinition.h"
#include "SystemTaskManager.h"
#include <stdlib.h>
#include "MW_GPIO.h"
#include "MW_IWDG.h"
#include "message.h"
#include "MW_flash.h"
#include "constManager.h"
#include <trapezoid_ctrl.h>
#define time 100 //電磁弁が開く時間を設定する　例:100で1秒

static
int suspensionSystem(void); //足回り
static
int ThrowSystem_1(void); //左側の発射機構
static
int ThrowSystem_2(void); //真ん中の発射機構
static
int ThrowSystem_3(void); //右側の発射機構
static
int DeliverySystem(void); //受け渡し機構

/*メモ
 *g_ab_h...ABのハンドラ
 *g_md_h...MDのハンドラ
 *
 *g_rc_data...RCのデータ
 */

int appInit(void){

  ad_init();

  /*GPIO の設定などでMW,GPIOではHALを叩く*/
  return EXIT_SUCCESS;
}

/*application tasks*/
int appTask(void){
  int ret=0;


  /*それぞれの機構ごとに処理をする*/
  /*途中必ず定数回で終了すること。*/
  
  ret = suspensionSystem();
  if(ret){
    return ret;
  }
  
  ret = ThrowSystem_1();
  if(ret){
    return ret;
  }

  ret = ThrowSystem_2();
  if(ret){
    return ret;
  }  

  ret = ThrowSystem_3();
  if(ret){
    return ret;
  }
  
  ret = DeliverySystem();
  if(ret){
    return ret;
    }

  return EXIT_SUCCESS;
}



static
int suspensionSystem(void){
  const int num_of_motor = 4;/*モータの個数*/
  //  int rc_analogdata;/*アナログデータ*/
  unsigned int idx=0;/*インデックス*/
  int i,x,y,w;
  int m=0;
  int adjust;

 const tc_const_t tc ={
    .inc_con = 200,
    .dec_con = 225,
  };

  x = DD_RCGetLY(g_rc_data);
  y = DD_RCGetLX(g_rc_data);
  w = DD_RCGetRX(g_rc_data);
  /* if(__RC_ISPRESSED_R2(g_rc_data)){
     w = 60;
     }else if(__RC_ISPRESSED_L2(g_rc_data)){
     w = -60;
     } else {
     w = 0;
     }*/


  /*for each motor*/
  for(i=0;i<num_of_motor;i++){
    /*それぞれの差分*/
    switch(i){
    case 0:
      idx = MECHA1_MD0; //駆動左前用モータ
      m =  x + y + w;
      m *= 75;
      if(abs(m) <= 3200) {//dutyが低かったら引き上げ
	m *= 2;
      } else if(abs(m) >= 6500) {//dutyが6500を超えたら6500以下になるよう調整
	adjust = abs(m) - 6500;
	if(m > 0) {
	  m -= adjust;
	} else if(m < 0) {
	  m += adjust;
	}
      }
      break;
      
    case 1:
      idx = MECHA1_MD1; //駆動左後用モータ
      m =  x - y + w;
      m *= 75;
      if(abs(m) <= 3200) {//dutyが低かったら引き上げ
	m *= 2;
      } else if(abs(m) >= 6500) {//dutyが6500を超えたら6500以下になるよう調整
	adjust = abs(m) - 6500;
	if(m > 0) {
	  m -= adjust;
	} else if(m < 0) {
	  m += adjust;
	}
      }
      break;
      
    case 2:
      idx = MECHA1_MD2; //駆動右後用モータ
      m = - x - y + w;
      m *= 75;
      if(abs(m) <= 3200) {//dutyが低かったら引き上げ
	m *= 2;
      } else if(abs(m) >= 6500) {//dutyが6500を超えたら6500以下になるよう調整
	adjust = abs(m) - 6500;
	if(m > 0) {
	  m -= adjust;
	} else if(m < 0) {
	  m += adjust;
	}
      }
      break;
      
    case 3:
      idx = MECHA1_MD3; //駆動右前用モータ
      m = - x + y + w;
      m *= 75;
      if(abs(m) <= 3200) {//dutyが低かったら引き上げ
	m *= 2;
      } else if(abs(m) >= 6500) {//dutyが6500を超えたら6500以下になるよう調整
	adjust = abs(m) - 6500;
	if(m > 0) {
	  m -= adjust;
	} else if(m < 0) {
	  m += adjust;
	}
      }
      break;
      
      return EXIT_FAILURE;
    }
    trapezoidCtrl(m,&g_md_h[idx],&tc);
  }

  return EXIT_SUCCESS;
}

static
int ThrowSystem_1(void){

  static int count = 0;
  static int check = 0;

  if(__RC_ISPRESSED_LEFT(g_rc_data)){
    check = 1;
  }
  if(check == 1 && count < time){ //左の投射機構
      g_ab_h[0].dat |= ON_AB0;
      //g_ab_h[0].dat |= ON_AB3;
      count++;
    } else {
      g_ab_h[0].dat &= ~ON_AB0;
      //g_ab_h[0].dat &= ~ON_AB3;
      count = 0;
      check = 0;
    }
  
  return EXIT_SUCCESS;
}

static
int ThrowSystem_2(void){

  static int count = 0;
  static int check = 0;
  
  if(__RC_ISPRESSED_UP(g_rc_data)){
    check = 1;
  }
     if(check == 1 && count < time){ //左の投射機構
      g_ab_h[0].dat |= ON_AB1;
      //g_ab_h[0].dat |= ON_AB4;
      count++;
    } else {
      g_ab_h[0].dat &= ~ON_AB1;
      //g_ab_h[0].dat &= ~ON_AB4;
      count = 0;
      check = 0;
     }
  
  return EXIT_SUCCESS;
}

static
int ThrowSystem_3(void){

  static int count = 0;
  static int check = 0;
  
    if(__RC_ISPRESSED_RIGHT(g_rc_data)){
      check = 1;
    }
     if(check == 1 && count < time){ //左の投射機構
      g_ab_h[0].dat |= ON_AB2;
      //g_ab_h[0].dat |= ON_AB5;
      count++;
    } else {
      g_ab_h[0].dat &= ~ON_AB2;
      //g_ab_h[0].dat &= ~ON_AB5;
      count = 0;
      check = 0;
    }
  
  return EXIT_SUCCESS;
}

static
int DeliverySystem(void){
  const tc_const_t load_tcon = {
    .inc_con = 250,
    .dec_con = 250,
  };

  /* 装填機構のduty */
  int loading = 0;
  const int forword_duty = -9500;
  const int end_duty = 9500;
  
  /* ボタンやリミットスイッチが押されているかどうかの判定 */
    if(__RC_ISPRESSED_CIRCLE(g_rc_data) &&_IS_PRESSED_DELIVERY_LIMITSW() == 1){
    loading = forword_duty;
    trapezoidCtrl(loading,&g_md_h[MECHA1_MD4],&load_tcon);
    }else if(__RC_ISPRESSED_CROSS(g_rc_data)){
    loading = end_duty;
    trapezoidCtrl(loading,&g_md_h[MECHA1_MD4],&load_tcon);
  }else{
    loading = 0;
    trapezoidCtrl(loading,&g_md_h[MECHA1_MD4],&load_tcon);
  }
    MW_printf("SW1[%d]",_IS_PRESSED_DELIVERY_LIMITSW());
  
  return EXIT_SUCCESS;
}
                                                                                                                                                                                  
