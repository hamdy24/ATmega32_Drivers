/*
 * TIMER_interface.h
 *
 *  Created on: Nov 19, 2021
 *  Author: 	 Hamdy Aouf
 *	Description: File of Interfaces used to control the Timer0 of the ATmega32
 */

#ifndef MCAL_TIMER_TIMER_INTERFACE_H_
#define MCAL_TIMER_TIMER_INTERFACE_H_

#include "TIMER0_config.h"
/*
 * Here you can do whatever you want with timer0 and there is interfaces for delay with OVF,CTC modes
 * but if you want to generate waves go to PWM driver which is more specified for that purpose using Timer1
 * also there is interfaces there for wave generating with timer0 but it is annotated with 'LowAccuracy'
 */

/*
 * Used for Initialization functions
 */
extern Timer0_Configs_t Timer0_Configs;

/***********************************************************************************************************************/
/************************************************** TIMER0 *************************************************************/
/***********************************************************************************************************************/

ES_t TIMER0_enuInit(Timer0_Configs_t * Copy_pstrTimer0Configs);
ES_t TIMER0_enuSetOutputCompareMode(Timer0_OCM_t Copy_enuTimer0_OCM);
ES_t TIMER0_enuSetWaveGenMode(Timer0_WGM_t Copy_enuTimer0_WGM);
ES_t TIMER0_enuSelect_Clock(Timer0_Pres_t Copy_enuTimer0_Pres);
ES_t TIMER0_enuDelay_ms_OVF(u32 Copy_u32DesiredTime_ms);
ES_t TIMER0_enuDelay_ms_CTC(u32 Copy_u32DesiredTime_ms);
ES_t TIMER0_enuSetTCNT0_Value(u8 Copy_u8PreloadValue);
ES_t TIMER0_enuSetOCR0_Value(u8 Copy_u8CompareValue);
ES_t TIMER0_enuGetTCNT0_Value(u8* Copy_pu8PreloadValue);
ES_t TIMER0_enuGetOCR0_Value(u8* pCopy_u8CompareValue);
ES_t TIMER0_enuOVF_Interrupt(bool Copy_enuInterruptEnable);
ES_t TIMER0_enuCompareMatch_Interrupt(bool Copy_enuInterruptEnable);
ES_t TIMER0_enuSetCallBack(Timer0_ISRs_t Copy_enuSelectedISR, volatile void (*Copy_pfunAppFunction)(void));


#endif /* MCAL_TIMER_TIMER_INTERFACE_H_ */
