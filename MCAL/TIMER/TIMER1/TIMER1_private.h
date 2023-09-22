/*
 * TIMER_private.h
 *
 *  Created on: Nov 19, 2021
 *  Author: 	 Hamdy Aouf
 *	Description: Here are private macros and declarations related to the TIMER1
 */

#ifndef MCAL_TIMER_TIMER_PRIVATE_H_
#define MCAL_TIMER_TIMER_PRIVATE_H_

#include "../../../LIBRARIES/errorstate.h"
#include "../../../LIBRARIES/stdTypes.h"
#include "../../../LIBRARIES/common.h"


#include "../../AVR_REG.H"
#include "../../interrupt.h"

#include "TIMER1_config.h"

static volatile void (*TIMER1_pfunComA_ISR_fun)(void) = NULL;
static volatile void (*TIMER1_pfunComB_ISR_fun)(void) = NULL;
static volatile void (*TIMER1_pfunOVF_ISR_fun)(void) = NULL;


#define MASK_BIT					1
#define MASK_FIRST_TWO_BITS			3
#define MASK_SECOND_TWO_BITS		12
#define PRES_MSK					~(7<<CS10)

/*** This is used in calculation to limit output value to match with msec calculations ***/
#define CALC_LIMIT_TO_MS			1000ul
#define TIMER1_MAX_COUNTS			(u16)65535


/*
 * Timer1 Bit Macros
 */

#define WGM10				0
#define WGM11				1
#define WGM12				3
#define WGM13				4

#define COM1A1				7
#define COM1A0				6
#define COM1B1				5
#define COM1B0				4

#define CS10				0
#define CS11 				1
#define CS12 				2

#define FOC1A				2
#define FOC1B				3

#define ICES1				6
#define ICNC1				7

#define TICIE1 				5
#define OCIE1A 				4
#define OCIE1B 				3
#define TOIE1				2



#endif /* MCAL_TIMER_TIMER_PRIVATE_H_ */
