/*
 * ADC_private.h
 *
 *  Created on: Nov 15, 2021
 *  Author: 	 Hamdy Aouf
 *	Description: Here are private macros and declarations related to the ADC
 */

#ifndef MCAL_ADC_ADC_PRIVATE_H_
#define MCAL_ADC_ADC_PRIVATE_H_


#include "../../LIBRARIES/stdTypes.h"
#include "../../LIBRARIES/errorstate.h"
#include "../../LIBRARIES/common.h"


#include "../AVR_REG.H"
#include "../interrupt.h"

#include "ADC_config.h"

static volatile void (*ADC_pfunISR_Fun)(void) = NULL;
static u8 ADC_DataADJ_Direction;

#define LOGIC_ONE							1

/************************** ADMUX Register Bits **********************************/
// 	Reference Selection Bit 6 of ADMUX from: AREF...AVCC...INTERNAL
#define REFS1_SEL_BIT_7						7
//	Reference Selection Bit 6 of ADMUX from: AREF...AVCC...INTERNAL
#define REFS0_SEL_BIT_6						6
//	ADC Left Adjust Result Bit 5 of ADMUX that controls which mode to read the bit..left or right
#define ADLAR_BIT_5							5
/// MUX4...0

/************************** ADCSRA Register Bits"Control and Status" **********************************/
#define ADC_ENABLE_BIT_7					7
/** in single running mode it must be SET each time we use ADC but in free running mode need to be SET only once**/
#define ADC_START_CONVERSION_BIT			6
/** '1' to enable auto  triggering and trigger source is selected from SFIOR Register '0' for single running mode*/
#define ADC_AUTO_TRIGGER_BIT_5				5
#define ADC_INT_FLAG_BIT_4					4
#define ADC_INT_ENABLE_BIT_3				3

// 2..0 are ADC Prescaler Select


/************************** SFIOR Register Bits"Special function IO" **********************************/
// will be used to put the desired value starting from bit 5 to change in ADTS_2,1,0
#define ADC_TRIGGER_SELECT_BIT_5			5
#define SFIOR_MASK_VALUE					0x1F
#define ADMUX_CHANNELS_MASK_VALUE			0x1F

#define PRES2_DIVISION_FACTOR_SET			0x01
#define PRES4_DIVISION_FACTOR_SET			0x02
#define PRES8_DIVISION_FACTOR_SET			0x03
#define PRES16_DIVISION_FACTOR_SET			0x04
#define PRES32_DIVISION_FACTOR_SET			0x05
#define PRES64_DIVISION_FACTOR_SET			0x06
#define PRES128_DIVISION_FACTOR_SET			0x07

#define ADC_MAX_CHANNEL_NUM					31

///Guard in case AVR Register file is already included
#ifndef MCAL_AVR_REG_H_
// auto trigger mode select register
#define SFIOR 								*((volatile u8*) 0x50)
/**** INTERRUPT REGISTERS ****/

#define MCUCR 								*((volatile u8*) 0x55)
#define MCUCSR								*((volatile u8*) 0x54)
#define GICR 								*((volatile u8*) 0x5b)
#define SREG  								*((volatile u8*) 0x5f)
#define GIFR  								*((volatile u8*) 0x5a)

/**** ADC REGISTERS *****/
/* ADC Multiplexer Register*/
#define ADMUX								*((volatile u8*) 0x27)
/* ADC Control and Status Register:*/
#define ADCSRA								*((volatile u8*) 0x26)
#define ADCH								*((volatile u8*) 0x25)
#define ADCL								*((volatile u8*) 0x24)

#endif /* MCAL_AVR_REG_H_ */


#endif /* MCAL_ADC_ADC_PRIVATE_H_ */
