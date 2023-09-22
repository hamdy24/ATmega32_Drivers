/*
 * ICU_Private.h
 *
 *  Created on:  Sep 19, 2022
 *  Author: 	 Hamdy Aouf
 *	Description: Private Macros and declarations
 */

#ifndef MCAL_ICU_HW_ICU_PRIVATE_H_
#define MCAL_ICU_HW_ICU_PRIVATE_H_

#include "../../../LIBRARIES/errorstate.h"
#include "../../../LIBRARIES/stdTypes.h"
#include "../../../LIBRARIES/common.h"


#include "ICU_Config.h"

#include "../../AVR_REG.H"
#include "../../interrupt.h"

volatile void (*ICU_pfunAppCallBack)(void) = NULL;


static volatile f32 ICU_Frequency = 0;
static volatile u16 ICU_DutyCycle = 0;
static volatile u16 ICU_HighTime = 0;
static volatile u16 ICU_Period = 0;

static volatile u8 ICU_State = 0;

static volatile u16 ICU_CapturedValue = 0;

static volatile u16 ICU_u16Time1 = 0;
static volatile u16 ICU_u16Time2 = 0;
static volatile u16 ICU_u16Time3 = 0;



static u16 ICU_Prescalers[] = {0,1,8,64,256,1024,100,200};
static u16 ICU_Pres = 0;


#define ICU_PRES_MASKING		~(7<<CS10)


#define ICNC1					7
#define ICES1					6

#define TICIE1					5

#define CS10					0
#define CS11					1
#define CS12					2

#define ICF1					5

#define TOV1					2

#endif /* MCAL_ICU_HW_ICU_PRIVATE_H_ */
