/*
 * PWM_private.h
 *
 *  Created on: Nov 19, 2021
 *  Author: 	 Hamdy Aouf
 *	Description: Here are private macros and declarations related to the PWM
 */

#ifndef MCAL_PWM_PWM_PRIVATE_H_
#define MCAL_PWM_PWM_PRIVATE_H_

#include "../../../LIBRARIES/errorstate.h"
#include "../../../LIBRARIES/stdTypes.h"
#include "../../../LIBRARIES/common.h"

#include "../../AVR_REG.H"
#include "PWM_config.h"

typedef enum{
	//Clock Source Configurations
	PWM1_PRES_Disabled = 0,
	PWM1_PRES_1,
	PWM1_PRES_8,
	PWM1_PRES_64,
	PWM1_PRES_256,
	PWM1_PRES_1024,
	PWM1_T1_Falling,
	PWM1_T1_Rising,
}PWM1_Pres_t;

static PWM1_Mode_t PWM_OC_Mode = OC_InvertingMode  ;
static PWM1_WGM_t  PWM_Type    = PWM1_Fast_ICR1;
static PWM1_Pres_t PWM_Pres    = PWM1_PRES_8;
static u16 PWM_Prescalers[] = {0,1,8,64,256,1024};
static u8 freq;


#define GET_BIT0     0
#define GET_BIT1     1
#define GET_BIT2     2
#define GET_BIT3     3

#define INVERTING				2
#define NON_INVERTING			3

#define MASK_FIRST_TWO_BITS		3
#define MASK_SECOND_TWO_BITS 	12
#define PRES_MSK				~(7<<CS00)

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



#define WGM00				6
#define WGM01				3

#define COM00				4
#define COM01				5

#define CS00				0
#define CS01				1
#define CS02				2
#endif /* MCAL_PWM_PWM_PRIVATE_H_ */
