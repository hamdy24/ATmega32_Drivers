/*
 * TIMER_config.h
 *
 *  Created on: Nov 19, 2021
 *  Author: 	 Hamdy Aouf
 *	Description: File of all needed parameters or configurations would be used to control the Timer1
 */

#ifndef MCAL_TIMER_TIMER_CONFIG_H_
#define MCAL_TIMER_TIMER_CONFIG_H_

/******************************************************************************
 ************************* Timer1 Configuration Types *************************
 ******************************************************************************/

typedef enum{
	//Clock Source Configurations
	Timer1_PRES_Disabled = 0,
	Timer1_PRES_1,
	Timer1_PRES_8,
	Timer1_PRES_64,
	Timer1_PRES_256,
	Timer1_PRES_1024,
	Timer1_T1_Falling,
	Timer1_T1_Rising,
}Timer1_Pres_t;

typedef enum{
	//Wave Generator Configurations
	Timer1_OVF_Mode = 0,
	Timer1_PWM_PhaseCorrect_8bit,
	Timer1_PWM_PhaseCorrect_9bit,
	Timer1_PWM_PhaseCorrect_10bit,
	Timer1_CTC_OCR1A_TopMode,
	Timer1_PWM_Fast_8bit,
	Timer1_PWM_Fast_9bit,
	Timer1_PWM_Fast_10bit,
	Timer1_PWM_PhaseFrequencyCorrect_ICR1,
	Timer1_PWM_PhaseFrequencyCorrect_OCR1A,
	Timer1_PWM_PhaseCorrect_ICR1,
	Timer1_PWM_PhaseCorrect_OCR1A,
	Timer1_CTC_ICR1_TopMode,
	Timer1_PWM_Fast_ICR1 = 14,
	Timer1_PWM_Fast_OCR1A = 15,
}Timer1_WGM_t;

typedef enum{
	//Compare Match Output Configurations
	/*****Remember they depend on WGM Configuration****/
	Timer1_OC1A_B_Disabled = 0,
	Timer1_OC1A_B_Toggle,
	Timer1_OC1A_B_Clear,
	Timer1_OC1A_B_Set,
}Timer1_OCM_t;

typedef enum{
	Timer1_Capture_ISR,
	Timer1_OCR1A_ISR,
	Timer1_OCR1B_ISR,
	Timer1_OVF_ISR,
}Timer1_ISRs_t;

/******************************************************************************
 ************************* Configuration DataTypes ****************************
 ******************************************************************************/

typedef struct{
	Timer1_Pres_t 	ClockSourceSelect  :3;
	Timer1_WGM_t	WaveGenerationMode :4;
	Timer1_OCM_t	OutputCompareMode  :2;
}Timer1_Configs_t;


#endif /* MCAL_TIMER_TIMER_CONFIG_H_ */
