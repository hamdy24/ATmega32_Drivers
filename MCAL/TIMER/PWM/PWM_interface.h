/*
 * PWM_interface.h
 *
 *  Created on: Nov 19, 2021
 *  Author: 	 Hamdy Aouf
 *	Description: File of Interfaces used to control the PWM of the ATmega32
 */
#ifndef MCAL_PWM_PWM_INTERFACE_H_
#define MCAL_PWM_PWM_INTERFACE_H_

#include "PWM_config.h"

extern PWM1_t PWM_strPWM1_Config;
extern PWM_Weak_t PWM_strWeakPWM_Config ;

ES_t PWM_enuInit(PWM1_t * Copy_pstrPWM_Config);

ES_t PWM_enuSetFrequency(u16 Copy_u16Frequency);

ES_t PWM_enuSetDutyCycle(f32 Copy_f32DutyCycle);
/*
 * Following are all solid configuration and approximate calculations as Timer 1 is the best choice for Wave generation
 * but they are implemented in case you will generate two waves for example
 */
ES_t PWM_enuInitLowAccuracy(PWM_Weak_t * Copy_pAstrPWM_Config,PWM_Weak_Channels_t Copy_enuSelectedChannel);

ES_t PWM_enuSet_FrequencyLowAccuracy(u16 Copy_u16Frequency , PWM_Weak_t * Copy_pstrPWM_Config,PWM_Weak_Channels_t Copy_enuSelectedChannel);

ES_t PWM_enuSet_DutyCycleLowAccuracy(u8 Copy_u16DutyCycle , PWM_Weak_t * Copy_pstrPWM_Config ,PWM_Weak_Channels_t Copy_enuSelectedChannel);

#endif /* MCAL_PWM_PWM_INTERFACE_H_ */
