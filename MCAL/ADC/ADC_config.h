/*
 * ADC_config.h
 *
 *  Created on: Nov 15, 2021
 *	Description: File of all needed parameters or configurations would be used to control the ADC
 */

#ifndef MCAL_ADC_ADC_CONFIG_H_
#define MCAL_ADC_ADC_CONFIG_H_

/******************************* ADC Interrupt Sources *****************************************/
typedef enum{
	ADC_FREE_RUNNIG = 0,
	ADC_ANALOG_COMPARATOR,
	ADC_EXTI_INT_0,
	ADC_TIMER_0_COMPARE_MATCH,
	ADC_TIMER_0_OVERFLOW,
	ADC_TIMER_COMPARE_MATCH_B,
	ADC_TIMER_1_OVERFLOW,
	ADC_TIMER_1_CAPTURE_EVENT,
} ADC_INT_Sources_enuType;
/******************************* ADC Channels *****************************************/
typedef enum{
	ADC_CHANNEL_NUM_0,
	ADC_CHANNEL_NUM_1,
	ADC_CHANNEL_NUM_2,
	ADC_CHANNEL_NUM_3,
	ADC_CHANNEL_NUM_4,
	ADC_CHANNEL_NUM_5,
	ADC_CHANNEL_NUM_6,
	ADC_CHANNEL_NUM_7,
	ADC_CHANNEL_NUM_8,
	ADC_CHANNEL_NUM_9,
	ADC_CHANNEL_NUM_10,
	ADC_CHANNEL_NUM_11,
	ADC_CHANNEL_NUM_12,
	ADC_CHANNEL_NUM_13,
	ADC_CHANNEL_NUM_14,
	ADC_CHANNEL_NUM_15,
	ADC_CHANNEL_NUM_16,
	ADC_CHANNEL_NUM_17,
	ADC_CHANNEL_NUM_18,
	ADC_CHANNEL_NUM_19,
	ADC_CHANNEL_NUM_20,
	ADC_CHANNEL_NUM_21,
	ADC_CHANNEL_NUM_22,
	ADC_CHANNEL_NUM_23,
	ADC_CHANNEL_NUM_24,
	ADC_CHANNEL_NUM_25,
	ADC_CHANNEL_NUM_26,
	ADC_CHANNEL_NUM_27,
	ADC_CHANNEL_NUM_28,
	ADC_CHANNEL_NUM_29,
	ADC_CHANNEL_NUM_30,
	ADC_CHANNEL_NUM_31,
} ADC_Channels_enuType;

/******************************* ADC Clock PreScaler *****************************************/
typedef enum {
	ADC_PRES_2, ADC_PRES_4, ADC_PRES_8, ADC_PRES_16, ADC_PRES_32, ADC_PRES_64, ADC_PRES_128,
} ADC_PRES_enuType;

/******************************* ADC Voltage Reference Selector *****************************************/
typedef enum {
	AREF_REF, AVCC_REF, INTERNAL_REF,
} ADC_VREF_enuType;

/******************************* ADC Data Adjustment *****************************************/
typedef enum {
	ADC_LEFT_ADJ, ADC_RIGHT_ADJ
} ADC_ADJ_enuType;

/******************************* ADC Configuration Type *****************************************/
typedef struct {
	ADC_Channels_enuType ChannelNum :6;
	ADC_INT_Sources_enuType INT_Src :3;
	ADC_PRES_enuType PRES :3;
	ADC_VREF_enuType VREF :3;
	ADC_ADJ_enuType ADJ_Direction :1;
} ADC_Cfg_t;

#endif /* MCAL_ADC_ADC_CONFIG_H_ */
