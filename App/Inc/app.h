#ifndef __APP_H
#define __APP_H

/*NO Device mode*/
#define _NO_DEVICE 0

int appTask(void);
int appInit(void);

#define DD_NUM_OF_MD 5
#define DD_NUM_OF_AB 1

#define DD_NUM_OF_SS 1
#define DD_USE_ENCODER1 0
#define DD_USE_ENCODER2 0
#define DD_NUM_OF_SV 0


//右側のリミットスイッチが押されているか
#define _SW_RIGHT_LIMIT_GPIOxID GPIOCID
#define _SW_RIGHT_LIMIT_GPIOPIN GPIO_PIN_1
#define _IS_PRESSED_RIGHT_LIMITSW() ((MW_GPIORead(_SW_RIGHT_LIMIT_GPIOxID,_SW_RIGHT_LIMIT_GPIOPIN)))

//左側のリミットスイッチが押されているか
#define _SW_DELIVERY_LIMIT_GPIOxID GPIOBID
#define _SW_DELIVERY_LIMIT_GPIOPIN GPIO_PIN_15
#define _IS_PRESSED_DELIVERY_LIMITSW() ((MW_GPIORead(_SW_DELIVERY_LIMIT_GPIOxID,_SW_DELIVERY_LIMIT_GPIOPIN)))

/*//
#define _SW_CENTER_LIMIT_GPIOxID
#define _SW_CENTER_LIMIT_GPIOPIN
#define _IS_PRESSED_CENTER_LIMIYSW()*/

#include "DD_RC.h"
#include "DD_MD.h"
#include "DD_SV.h"

#define MECHA1_MD0 0 //駆動右前側のモータ
#define MECHA1_MD1 1 //駆動右後側のモータ
#define MECHA1_MD2 2 //駆動左後側のモータ
#define MECHA1_MD3 3 //駆動左前側のモータ
#define MECHA1_MD4 4 //受け渡し機構のモータ 
#define CENTRAL_THRESHOLD 4


#define ON_AB0 (1<<0) //0x01
#define ON_AB1 (1<<1) //0x02
#define ON_AB2 (1<<2) //0x04
#define ON_AB3 (1<<3) //0x08
#define ON_AB4 (1<<4) //0x10
#define ON_AB5 (1<<5) //0x20

#define NO_BLOW 1000

#define MD_GAIN ( DD_MD_MAX_DUTY / DD_RC_ANALOG_MAX )

#endif
