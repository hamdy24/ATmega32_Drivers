/*
 * TIMER_interface.h
 *
 *  Created on: Nov 19, 2021
 *  Author: 	 Hamdy Aouf
 *	Description: File of Interfaces used to control the Timer1 of the ATmega32
 */
#ifndef MCAL_TIMER_TIMER_INTERFACE_H_
#define MCAL_TIMER_TIMER_INTERFACE_H_

#include "TIMER1_config.h"
/*
 * Here you can do whatever you want with timer1 and there is no interfaces to use  delay with OVF,CTC modes
 * timer 1 is better for other uses so didn't make a delay interface for it you can build it with other interfaces i provided
 * but if you want to generate waves go to PWM driver which is more specified for that purpose using Timer1
 */

/*
 * Used for Initialization functions
 */
extern Timer1_Configs_t Timer1_Configs;


/***********************************************************************************************************************/
/************************************************ TIMER1 *************************************************************/
/***********************************************************************************************************************/
/***********************************************************************************************************************/

ES_t TIMER1_enuInit(Timer1_Configs_t Copy_strTimer1Configs);
ES_t TIMER1_enuSelectWaveGenMode(Timer1_WGM_t Copy_enuTimer1_WGM);
ES_t TIMER1_enuSelectOutputCompareMode(Timer1_OCM_t Copy_enuTimer1_OCM);
ES_t TIMER1_enuSelectClockSource(Timer1_Pres_t Copy_enuTimer1_Pres);
ES_t TIMER1_enuSetTCNT1(u16 Copy_u16TCNT1_Value);
ES_t TIMER1_enuSet_OCR1A(u16 Copy_u16OCR1A_Value);
ES_t TIMER1_enuSet_OCR1B(u16 Copy_u16OCR1B_Value);
ES_t TIMER1_enuSet_ICR1(u16 Copy_u16ICR1B_Value);
ES_t TIMER1_enuGetTCNT1(u16* Copy_pu16TCNT1_Value);
ES_t TIMER1_enuGet_OCR1A(u16* Copy_pu16OCR1A_Value);
ES_t TIMER1_enuGet_OCR1B(u16* Copy_pu16OCR1B_Value);
ES_t TIMER1_enuGet_ICR1(u16* Copy_pu16ICR1B_Value);
ES_t TIMER1_enuEnable_InputCapture_INT(bool Copy_enuInterruptEnable);
ES_t TIMER1_enuEnable_OVF_INT(bool Copy_enuInterruptEnable);
ES_t TIMER1_enuEnable_OCRA_INT(bool Copy_enuInterruptEnable);
ES_t TIMER1_enuEnable_OCRB_INT(bool Copy_enuInterruptEnable);
ES_t TIMER1_enuSetCallBack(Timer1_WGM_t Copy_enuTimer1_WGM , volatile void (*Copy_pfunAppCallBack)(void) );


#endif /* MCAL_TIMER_TIMER_INTERFACE_H_ */
