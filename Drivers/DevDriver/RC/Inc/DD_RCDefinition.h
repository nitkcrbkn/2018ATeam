#ifndef __DD_RC_DEFINITION_H
#define __DD_RC_DEFINITION_H

/*  * File:   SDBDT ControalerDataFomat.h
 * Author: oishi
 *
 * Created on 2015/05/26, 9:26
 */

/*PS2 controaler 定義データ*/

#define _RC_BAUD 9600


#define __RC_Up  	0x01
#define __RC_Down	0x02
#define __RC_Right	0x04
#define __RC_Left	0x08

#define __RC_Tri	0x10
#define __RC_Cross	0x20
#define __RC_Circle 	0x40
#define __RC_Sq		0x01

#define __RC_L1	0x02
#define __RC_L2	0x04
#define __RC_R1	0x08
#define __RC_R2	0x10

#define __RC_None 0x0
#define __RC_BT1  0x2
#define __RC_BT2  0x1
#define __RC_LY	  0x4
#define __RC_LX	  0x3
#define __RC_RY	  0x6
#define __RC_RX	  0x5
#define __RC_CSM  0x7

#define __RC_Start 0x3
#define __RC_Select 0xC

#define __RC_ISPRESSED_START(x) ((x[__RC_BT1]&__RC_Start)==__RC_Start)
#define __RC_ISPRESSED_SELECT(x) ((x[__RC_BT1]&__RC_Select)==__RC_Select)

//Start,Selectボタン押下中は反応しない(禁止動作)
#define __RC_ISPRESSED_UP(x) ((!__RC_ISPRESSED_START(x))&&(x[__RC_BT1]&__RC_Up))
#define __RC_ISPRESSED_DOWN(x) ((!__RC_ISPRESSED_START(x))&&(x[__RC_BT1]&__RC_Down))
#define __RC_ISPRESSED_RIGHT(x) ((!__RC_ISPRESSED_SELECT(x))&&(x[__RC_BT1]&__RC_Right))
#define __RC_ISPRESSED_LEFT(x) ((!__RC_ISPRESSED_SELECT(x))&&(x[__RC_BT1]&__RC_Left))

#define __RC_ISPRESSED_TRIANGLE(x) (x[__RC_BT1]&__RC_Tri)
#define __RC_ISPRESSED_CROSS(x) (x[__RC_BT1]&__RC_Cross)
#define __RC_ISPRESSED_CIRCLE(x) (x[__RC_BT1]&__RC_Circle)
#define __RC_ISPRESSED_SQARE(x) (x[__RC_BT2]&__RC_Sq)

#define __RC_ISPRESSED_L1(x) (x[__RC_BT2]&__RC_L1)
#define __RC_ISPRESSED_R1(x) (x[__RC_BT2]&__RC_R1)
#define __RC_ISPRESSED_L2(x) (x[__RC_BT2]&__RC_L2)
#define __RC_ISPRESSED_R2(x) (x[__RC_BT2]&__RC_R2)

#define __RC_GET_LX_VAL(x) (x[__RC_LX])
#define __RC_GET_RX_VAL(x) (x[__RC_RX])
#define __RC_GET_LY_VAL(x) (x[__RC_LY])
#define __RC_GET_RY_VAL(x) (x[__RC_RY])

#endif
