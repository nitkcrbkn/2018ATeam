#include <stdlib.h>
#include "SystemTaskManager.h"
#include "DD_MD.h"
#include "trapezoid_ctrl.h"

/*(目標制御値, インデックス,Duty上昇時の変化量, Duty下降の変化量)*/
void trapezoidCtrl(int target_duty, DD_MDHand_t *handle, const tc_const_t *idval){
  int prev_duty;/*直前のDuty*/
  int duty = 0;

  prev_duty = handle->duty;
  if( handle->mode == D_MMOD_FORWARD ){/*直前が正回転なら*/
    if( target_duty > prev_duty ){
      duty = prev_duty + _MIN(idval->inc_con, target_duty - prev_duty);
    } else{
      duty = prev_duty + _MAX(-idval->dec_con, target_duty - prev_duty);
    }
  }else if( handle->mode == D_MMOD_BACKWARD ){/*直前が逆回転なら*/
    if( target_duty < -prev_duty ){
      duty = -prev_duty + _MAX(-idval->inc_con, target_duty - ( -prev_duty ));
    } else{
      duty = -prev_duty + _MIN(idval->dec_con, target_duty - ( -prev_duty ));
    }
  } else {/*直前が0なら*/
    if (target_duty > 0){
      duty = prev_duty + _MIN(idval->inc_con, target_duty - prev_duty);
    } else {
      duty = -prev_duty + _MAX(-idval->inc_con, target_duty - ( -prev_duty ));
    }
  }
  if( duty > 0 ){
    handle->mode = D_MMOD_FORWARD;
  } else if( duty < 0 ){
    handle->mode = D_MMOD_BACKWARD;
  } else{
    handle->mode = D_MMOD_BRAKE;
  }
  handle->duty = abs(duty);
}
