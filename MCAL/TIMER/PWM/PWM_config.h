/*
 * PWM_config.h
 *
 *  Created on: Nov 19, 2021
 *	Description: File of all needed parameters or configurations would be used to control the PWM
 */

#ifndef MCAL_PWM_PWM_CONFIG_H_
#define MCAL_PWM_PWM_CONFIG_H_

typedef enum{
	//Wave Generator Configurations

	PWM1_PhaseCorrect_8bit = 1,
	PWM1_PhaseCorrect_9bit,
	PWM1_PhaseCorrect_10bit,

	PWM1_Fast_8bit = 5,
	PWM1_Fast_9bit,
	PWM1_Fast_10bit,
	PWM1_PhaseFrequencyCorrect_ICR1,
	PWM1_PhaseFrequencyCorrect_OCR1A,
	PWM1_PhaseCorrect_ICR1,
	PWM1_PhaseCorrect_OCR1A,

	PWM1_Fast_ICR1 = 14,
	PWM1_Fast_OCR1A = 15,
}PWM1_WGM_t;

typedef enum{
	//Compare Match Output Configurations
	OC_InvertingMode,
	OC_Non_InvertingMode
}PWM1_Mode_t;

typedef enum{
	/*****Remember they depend on WGM Configuration****/
	PWM1_OC_ChannelA_B,
	PWM1_OC_ChannelA,
	PWM1_OC_ChannelB,
}PWM1_Channel_t;

typedef struct
{
	bool PWM_EnableState:1;
	PWM1_WGM_t 	PWM_Type:4;
	PWM1_Mode_t PWM_Mode:1;
	PWM1_Channel_t PWM_Channel:2;
}PWM1_t;

/**
 *****************************************************************************
 **/


typedef enum{
	OC_InvertingModeWeak,
	OC_Non_InvertingModeWeak
}PWM_Weak_Mode_t;

typedef enum{
	PWM_Fast,
	PWM_PhaseCorrect
}PWM_Weak_WGM_t;

typedef enum{
	PWM_Timer0,
	PWM_Timer2
}PWM_Weak_Channels_t;


typedef struct
{
	bool PWM_EnableState:1;
	PWM_Weak_WGM_t PWM_WaveType:1;
	PWM_Weak_Mode_t PWM_Mode:1;
}PWM_Weak_t;

#endif /* MCAL_PWM_PWM_CONFIG_H_ */
