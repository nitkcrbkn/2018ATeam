#include "DD_RC.h"
#include "DD_RCDefinition.h"
#include <stdlib.h>
#include <stdint.h>
#include "message.h"
#include "SystemTaskManager.h"
#include "MW_USART.h"
#include "constManager.h"

static volatile int is_not_avaiable = 8+1;
static volatile uint8_t correct[RC_DATA_NUM];

#define _RELANGE(x) (x<DD_RC_ANALOG_MAX?(x>-DD_RC_ANALOG_MAX?x:-DD_RC_ANALOG_MAX):DD_RC_ANALOG_MAX)

int DD_RCInit(uint8_t rc_data[RC_DATA_NUM], uint32_t timeout){
  uint32_t remaining;
  int ret;

  MW_USARTSetBaudRate(USART3ID, _RC_BAUD);
  ret = MW_USARTInit(USART3ID);
  if( ret ){
    return ret;
  }

  remaining = g_SY_system_counter + timeout;

  MW_USART3ReceiveMult(RC_DATA_NUM, rc_data);
  while( remaining > g_SY_system_counter && is_not_avaiable ){
    MW_printf("$0");
    flush();
  }

  if( is_not_avaiable ){
    return EXIT_FAILURE;
  }

  for(int i=0;i<3;i++){
    rc_data[i]=0;
  }for(int i=3;i<7;i++){
    rc_data[i]=0x40;
  }

  return EXIT_SUCCESS;
}

static int ip;
static uint8_t rcv_data[RC_DATA_NUM];
rc_error_t DD_RC_element(uint8_t rc_data_el,uint8_t outdata[RC_DATA_NUM]){
  if(rc_data_el==0x80){
    ip=0;
  }else if(ip<7){
    rcv_data[ip]=rc_data_el;
  }else{
    uint8_t check_sum = 0;
    for(int i=1;i<7;i++){
      check_sum += rcv_data[i];
    }
    if((check_sum&0x7F)==(rc_data_el&0x7F)){
      for(int i=0;i<8;i++){
	outdata[i] = rcv_data[i];
      }
    }else{
      return DD_RC_CHECKSUM_ERR;
    }
  }
  if(ip>8){
    return DD_RC_INVAILD_DATA;
  }
  ip++;
  return DD_RC_OK;
}

rc_error_t DD_RCTask(uint8_t rc_data[RC_DATA_NUM], uint8_t out_data[RC_DATA_NUM]){
  int i;
  rc_error_t ret;
  
  if( is_not_avaiable > 0){
    is_not_avaiable--;
    MW_USART3ReceiveMult(8, rc_data);
    return DD_RC_OK;
  }
  for( i = 0; i < RC_DATA_NUM; i++ ){
    ret = DD_RC_element(rc_data[i], out_data);
    if(ret!=DD_RC_OK)break;
  }
  MW_USART3ReceiveMult(8, rc_data);

  return ret;
}

int DD_RCGetLX(volatile uint8_t data[RC_DATA_NUM]){
  return _RELANGE((int)data[__RC_LX] - DD_RC_CENTRAL);
}

int DD_RCGetLY(volatile uint8_t data[RC_DATA_NUM]){
  return _RELANGE((int)data[__RC_LY] - DD_RC_CENTRAL);
}

int DD_RCGetRX(volatile uint8_t data[RC_DATA_NUM]){
  return _RELANGE((int)data[__RC_RX] - DD_RC_CENTRAL);
}

int DD_RCGetRY(volatile uint8_t data[RC_DATA_NUM]){
  return _RELANGE((int)data[__RC_RY] - DD_RC_CENTRAL);
}

int DD_RCPrint(volatile uint8_t data[RC_DATA_NUM]){
  int bp;

  bp=__RC_ISPRESSED_UP(data);
  if(bp){
    MW_printf("\033[1;33m\033[40m");
  }
  MW_printf("↑  ");
  if(bp){
    MW_printf("\033[0;39m\033[49m");
  }
  
  bp=__RC_ISPRESSED_DOWN(data);
  if(bp){
    MW_printf("\033[1;33m\033[40m");
  }
  MW_printf("↓  ");
  if(bp){
    MW_printf("\033[0;39m\033[49m");
  }

  bp=__RC_ISPRESSED_RIGHT(data);
  if(bp){
    MW_printf("\033[1;33m\033[40m");
  }
  MW_printf("→  ");
  if(bp){
    MW_printf("\033[0;39m\033[49m");
  }
  
  bp=__RC_ISPRESSED_LEFT(data);
  if(bp){
    MW_printf("\033[1;33m\033[40m");
  }
  MW_printf("←  ");
  if(bp){
    MW_printf("\033[0;39m\033[49m");
  }

  bp=__RC_ISPRESSED_SQARE(data);
  if(bp){
    MW_printf("\033[1;33m\033[40m");
  }
  MW_printf("□  ");
  if(bp){
    MW_printf("\033[0;39m\033[49m");
  }
  
  bp=__RC_ISPRESSED_CROSS(data);
  if(bp){
    MW_printf("\033[1;33m\033[40m");
  }
  MW_printf("X  ");
  if(bp){
    MW_printf("\033[0;39m\033[49m");
  }  

  bp=__RC_ISPRESSED_CIRCLE(data);
  if(bp){
    MW_printf("\033[1;33m\033[40m");
  }
  MW_printf("○  ");
  if(bp){
    MW_printf("\033[0;39m\033[49m");
  }  

  bp=__RC_ISPRESSED_TRIANGLE(data);
  if(bp){
    MW_printf("\033[1;33m\033[40m");
  }
  MW_printf("△  ");
  if(bp){
    MW_printf("\033[0;39m\033[49m");
  }  

  bp=__RC_ISPRESSED_L1(data);
  if(bp){
    MW_printf("\033[1;33m\033[40m");
  }
  MW_printf("L1  ");
  if(bp){
    MW_printf("\033[0;39m\033[49m");
  }  

  bp=__RC_ISPRESSED_L2(data);
  if(bp){
    MW_printf("\033[1;33m\033[40m");
  }
  MW_printf("L2  ");
  if(bp){
    MW_printf("\033[0;39m\033[49m");
  }  

  bp=__RC_ISPRESSED_R1(data);
  if(bp){
    MW_printf("\033[1;33m\033[40m");
  }
  MW_printf("R1  ");
  if(bp){
    MW_printf("\033[0;39m\033[49m");
  }
  
  bp=__RC_ISPRESSED_R2(data);
  if(bp){
    MW_printf("\033[1;33m\033[40m");
  }
  MW_printf("R2  ");
  if(bp){
    MW_printf("\033[0;39m\033[49m");
  }  
  MW_printf("\n");
  
  MW_printf("(%3d,%3d),(%3d,%3d)\n",
	    DD_RCGetLX(data),
	    DD_RCGetLY(data),
	    DD_RCGetRX(data),
	    DD_RCGetRY(data)
	    );
  
  return EXIT_SUCCESS;
}
