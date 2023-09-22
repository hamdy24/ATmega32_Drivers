/*
 * TIMER_private.h
 *
 *  Created on: Nov 19, 2021
 *  Author: 	 Hamdy Aouf
 *	Description: Here are private macros and declarations related to the TIMER0
 */

#ifndef MCAL_TIMER_TIMER_PRIVATE_H_
#define MCAL_TIMER_TIMER_PRIVATE_H_

#include "../../../LIBRARIES/errorstate.h"
#include "../../../LIBRARIES/stdTypes.h"
#include "../../../LIBRARIES/common.h"


#include "../../AVR_REG.H"
#include "../../interrupt.h"

#include "TIMER0_config.h"

static ES_t TIMER0_enuUpdatePrescaler(Timer0_Pres_t Copy_enuTimer0_Pres);

static u32 Timer0_u32PrescalerVal = 1; //changed when clock source is initialized or changed so it can be used later in delay calculations

volatile u32 Timer0_u32OVFs_Number = 0;
volatile u32 Timer0_u32OCFs_Number = 0;

static volatile void (*TIMER0_pfunOVF_ISR_fun)(void) = NULL;
static volatile void (*TIMER0_pfunCOM_ISR_fun)(void) = NULL;



#define MASK_BIT					1
#define MASK_FIRST_TWO_BITS			3
#define MASK_SECOND_TWO_BITS		12
#define PRES_MSK					~(7<<CS00)
#define FULL_OVF_COUNTS				256
/*** This is used in calculation to limit output value to match with msec calculations ***/
#define CALC_LIMIT_TO_MS			1000ul

/*
 * Timer 0
 */
#define WGM00				6
#define WGM01				3

#define COM00				4
#define COM01				5

#define CS00				0
#define CS01				1
#define CS02				2

#define TOIE0				0
#define OCIE0				1

#define FOC0				7

#define OVF0				0
#define OCF0				1

#endif /* MCAL_TIMER_TIMER_PRIVATE_H_ */
