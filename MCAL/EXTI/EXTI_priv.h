/*
 * EXTI_priv.h
 *
 *  Created on: Oct 30, 2021
 *  Author: 	 Hamdy Aouf
 *	Description: Here are private macros and declarations related to the EXTI
 */

#ifndef MCAL_EXTI_EXTI_PRIV_H_
#define MCAL_EXTI_EXTI_PRIV_H_

#include "../../LIBRARIES/errorstate.h"
#include "../../LIBRARIES/stdTypes.h"
#include "../../LIBRARIES/common.h"


#include "EXTI_config.h"

#include "../AVR_REG.H"
#include "../interrupt.h"


static CallBackFunc_t EXTI_pfunISR_fun[INTERRUPT_NUM] = {NULL , NULL , NULL};


#define INT2_EN					5
#define INT0_EN					6
#define INT1_EN					7

#define INT0_SENSE_BIT0			0
#define INT0_SENSE_BIT1			1

#define INT1_SENSE_BIT2			2
#define INT1_SENSE_BIT3			3

#define INT2_SENSE_BIT6			6

#define TWO_BIT_MSK(BIT)		~(3<<BIT)

#ifndef MCAL_AVR_REG_H_
#define MCUCR		*((volatile u8*)0x55)	//Control Register for interrupt sense control
/*** Bit 2,3 controls INT1 ********* Bits 0,1 controls INT0 *********/
////////////////////////////////////////////////////////////////////////////////////////////////

#define MCUCSR		*((volatile u8*)0x54)   //Status regester ->>
/*** Bit 6 controls INT2 Sense Level -> 0 for falling edge & 1 for rising edge  **/
//////////////////////////////////////////////////////////////////////////////////////////////

#define GICR		*((volatile u8*)0x5B)	//works as PIE for EXTI
/****  BIT 5 => INT2	BIT 6 => INT0	BIT 7 => INT1 ****/
//////////////////////////////////////////////////////////////////////////////////////////////

#define GIFR		*((volatile u8*)0x5A)	//works as PIF for EXTI
/****  BIT 5 => INT2	BIT 6 => INT0	BIT 7 => INT1 ****/
//////////////////////////////////////////////////////////////////////////////////////////////
#endif


#endif /* MCAL_EXTI_EXTI_PRIV_H_ */
