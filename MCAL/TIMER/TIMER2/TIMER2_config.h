/*
 * TIMER_config.h
 *
 *  Created on: Nov 19, 2021
 *  Author: 	 Hamdy Aouf
 *	Description: File of all needed parameters or configurations would be used to control the Timer2
 */

#ifndef MCAL_TIMER_TIMER_CONFIG_H_
#define MCAL_TIMER_TIMER_CONFIG_H_


/******************************************************************************
 ************************* Timer2 Configuration Types *************************
 ******************************************************************************/


typedef enum{
	//Clock Source Configurations
	Timer2_PRES_Disabled = 0,
	Timer2_PRES_1,
	Timer2_PRES_8,
	Timer2_PRES_32,
	Timer2_PRES_64,
	Timer2_PRES_128,
	Timer2_PRES_256,
	Timer2_PRES_1024,
}Timer2_Pres_t;

typedef enum{
	//Wave Generator Configurations
	Timer2_OVF_Mode = 0,
	Timer2_CTC_Mode,
	Timer2_PWM_Fast,
	Timer2_PWM_Phase,
}Timer2_WGM_t;

typedef enum{
	//Compare Match Output Configurations
	Timer2_OC2_Disabled = 0,
	Timer2_OC2_Toggle,
	Timer2_OC2_Clear,
	Timer2_OC2_Set,
}Timer2_OCM_t;

typedef enum{
	Timer2_OVF_ISR,
	Timer2_COM_ISR
}Timer2_ISRs_t;

/******************************************************************************
 ************************* Configuration DataType ****************************
 ******************************************************************************/

typedef struct{
	Timer2_Pres_t 	ClockSourceSelect  :3;
	Timer2_WGM_t	WaveGenerationMode :2;
	Timer2_OCM_t	OutputCompareMode  :2;
}Timer2_Configs_t;



#endif /* MCAL_TIMER_TIMER_CONFIG_H_ */
