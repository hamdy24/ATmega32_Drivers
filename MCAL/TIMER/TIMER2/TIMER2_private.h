/*
 * TIMER_private.h
 *
 *  Created on: Nov 19, 2021
 *  Author: 	 Hamdy Aouf
 *	Description: Here are private macros and declarations related to the Timer2
 */

#ifndef MCAL_TIMER_TIMER_PRIVATE_H_
#define MCAL_TIMER_TIMER_PRIVATE_H_

#include "../../../LIBRARIES/errorstate.h"
#include "../../../LIBRARIES/stdTypes.h"
#include "../../../LIBRARIES/common.h"


#include "../../AVR_REG.H"
#include "../../interrupt.h"

#include "TIMER2_config.h"

static ES_t TIMER2_enuUpdatePrescaler(Timer2_Pres_t Copy_enuTimer2_Pres);

static u32 Timer2_u32PrescalerVal = 1; //changed when clock source is initialized or changed so it can be used later in delay calculations

volatile u32 Timer2_u32OVFs_Number = 0;
volatile u32 Timer2_u32OCFs_Number = 0;

static volatile void (*TIMER2_pfunOVF_ISR_fun)(void) = NULL;
static volatile void (*TIMER2_pfunCOM_ISR_fun)(void) = NULL;




#define MASK_BIT					1
#define MASK_FIRST_TWO_BITS			3
#define MASK_SECOND_TWO_BITS		12
#define FULL_OVF_COUNTS				256
#define PRES_MSK					~(7<<CS20)

/*** This is used in calculation to limit output value to match with msec calculations ***/
#define CALC_LIMIT_TO_MS			1000ul
#define TIMER1_MAX_COUNTS			(u16)65535

/*
 * Timer 2
 */
#define WGM20				6
#define WGM21				3

#define COM20				4
#define COM21				5

#define CS20				0
#define CS21				1
#define CS22				2

#define TOIE2				6
#define OCIE2				7

#define FOC2				7


#endif /* MCAL_TIMER_TIMER_PRIVATE_H_ */
