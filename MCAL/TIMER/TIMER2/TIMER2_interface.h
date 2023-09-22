/*
 * TIMER_interface.h
 *
 *  Created on: Nov 19, 2021
 *  Author: 	 Hamdy Aouf
 *	Description: File of Interfaces used to control the Timer2 of the ATmega32
 */

#ifndef MCAL_TIMER_TIMER_INTERFACE_H_
#define MCAL_TIMER_TIMER_INTERFACE_H_

#include "TIMER2_config.h"
/*
 * Here you can do whatever you want with timer2 and there is interfaces to use delay with OVF,CTC modes
 * but if you want to generate waves go to PWM driver which is more specified for that purpose using Timer1
 * also there is interfaces there for wave generating with timer0 but it is annotated with 'LowAccuracy'
 */

/*
 * Used for Initialization functions
 */

extern Timer2_Configs_t Timer2_Configs;

/***********************************************************************************************************************/
/*********************************************** TIMER2 **********************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

ES_t TIMER2_enuInit(Timer2_Configs_t Copy_strTimer2Configs);
ES_t TIMER2_enuSetOutputCompareMode(Timer2_OCM_t Copy_enuTimer2_OCM);
ES_t TIMER2_enuSetWaveGenMode(Timer2_WGM_t Copy_enuTimer2_WGM);
ES_t TIMER2_enuSelect_Clock(Timer2_Pres_t Copy_enuTimer2_Pres);
ES_t TIMER2_enuDelay_ms_OVF(u32 Copy_u32DesiredTime_ms);
ES_t TIMER2_enuDelay_ms_CTC(u32 Copy_u32DesiredTime_ms);
ES_t TIMER2_enuSetTCNT2_Value(u8 Copy_u8PreloadValue);
ES_t TIMER2_enuSetOCR2_Value(u8 Copy_u8CompareValue);
ES_t TIMER2_enuGetTCNT2_Value(u8* Copy_pu8PreloadValue);
ES_t TIMER2_enuGetOCR2_Value(u8* Copy_pu8CompareValue);
ES_t TIMER2_enuOVF_Interrupt(bool Copy_enuInterruptEnable);
ES_t TIMER2_enuCompareMatch_Interrupt(bool Copy_enuInterruptEnable);
ES_t TIMER2_enuSetCallBack(Timer2_ISRs_t Copy_enuSelectedISR, volatile void (*Copy_pfunAppFunction)(void));



#endif /* MCAL_TIMER_TIMER_INTERFACE_H_ */
