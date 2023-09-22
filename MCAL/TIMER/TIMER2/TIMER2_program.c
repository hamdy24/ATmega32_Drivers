/*
 * TIMER_program.c
 *
 *  Created on: Nov 19, 2021
 *  Author: 	 Hamdy Aouf
 *	Description: Here are all the Interfaces definitions of the Timer2
 */

#include "TIMER2_private.h"

/*******************************************************************************************************
 ****************************************** Timer2 Implementations *************************************
 *******************************************************************************************************/

/***************** TCCR2 Watch window ************************
 * FOC2	WGM20 COM21	COM20 WGM21	CS22 CS21 CS20				 *
 *   0	  0	    0 	  0	   0	 1	  0	   0	TCCR2 = 0x13 *
 *************************************************************/

ES_t TIMER2_enuInit(Timer2_Configs_t Copy_strTimer2Configs){
	u8 Local_enuErrorState = ES_NOK;

	TCNT2 = 0;	//Empty
	TCCR2 &= ~(MASK_BIT<<7); //Force output compare match: 0

	/*******************************************/
	/*********** Wave Generation Mode **********/
	/*******************************************/
	switch(Copy_strTimer2Configs.WaveGenerationMode){
	case Timer2_OVF_Mode:
		TCCR2 &= ~(MASK_BIT<<WGM20);
		TCCR2 &= ~(MASK_BIT<<WGM21);

		TIMSK |=  (MASK_BIT<<TOIE2); //Overflow INT Enabled
		TIMSK &= ~(MASK_BIT<<OCIE2);
		break;
	case Timer2_CTC_Mode:
		TCCR2 &= ~(MASK_BIT<<WGM20);
		TCCR2 |=  (MASK_BIT<<WGM21);

		TIMSK &= ~(MASK_BIT<<TOIE2); //Overflow INT Disabled
		TIMSK |=  (MASK_BIT<<OCIE2); //Output Compare Match INT Enabled
		break;
	case Timer2_PWM_Fast:
		TCCR2 |=  (MASK_BIT<<WGM20);
		TCCR2 |=  (MASK_BIT<<WGM21);
		break;
	case Timer2_PWM_Phase:
		TCCR2 |=  (MASK_BIT<<WGM20);
		TCCR2 &= ~(MASK_BIT<<WGM21);
		break;
	default:
		Local_enuErrorState = ES_OUT_OF_RANGE;
		break;
	}
	if(ES_OUT_OF_RANGE != Local_enuErrorState){

		/*******************************************/
		/*********** OUTPUT COMPARE MODE ***********/
		/*******************************************/
		if(Copy_strTimer2Configs.OutputCompareMode >= Timer2_OC2_Disabled
				&& Copy_strTimer2Configs.OutputCompareMode <= Timer2_OC2_Set){

			TCCR2 |= (Copy_strTimer2Configs.OutputCompareMode<<COM20);

			/*******************************************/
			/********** Clock Mode Selection ***********/
			/*******************************************/
			if(Copy_strTimer2Configs.ClockSourceSelect >= Timer2_PRES_Disabled
					&& Copy_strTimer2Configs.ClockSourceSelect <= Timer2_PRES_1024){

				TCCR2 |= (Copy_strTimer2Configs.ClockSourceSelect<<CS20);

				Local_enuErrorState = TIMER2_enuUpdatePrescaler(Copy_strTimer2Configs.ClockSourceSelect);
			}
			else{
				Local_enuErrorState = ES_OUT_OF_RANGE;
			}
		}
		else{
			Local_enuErrorState = ES_OUT_OF_RANGE;
		}
	}
	return Local_enuErrorState;
}
ES_t TIMER2_enuUpdatePrescaler(Timer2_Pres_t Copy_enuTimer2_Pres){
	ES_t Local_enuErrorState = ES_NOK;
	switch(Copy_enuTimer2_Pres){
	case Timer2_PRES_Disabled:
		Timer2_u32PrescalerVal = 0;
		break;
	case Timer2_PRES_1:
		Timer2_u32PrescalerVal = 1;
		break;
	case Timer2_PRES_8:
		Timer2_u32PrescalerVal = 8;
		break;
	case Timer2_PRES_32:
		Timer2_u32PrescalerVal = 32;
		break;
	case Timer2_PRES_64:
		Timer2_u32PrescalerVal = 64;
		break;
	case Timer2_PRES_128:
		Timer2_u32PrescalerVal = 128;
		break;
	case Timer2_PRES_256:
		Timer2_u32PrescalerVal = 256;
		break;
	case Timer2_PRES_1024:
		Timer2_u32PrescalerVal = 1024;
		break;
	default:
		Local_enuErrorState = ES_OUT_OF_RANGE;
		break;
	}
	if(ES_OUT_OF_RANGE != Local_enuErrorState){
		Local_enuErrorState = ES_OK;
	}

	return Local_enuErrorState;
}
ES_t TIMER2_enuSetOutputCompareMode(Timer2_OCM_t Copy_enuTimer2_OCM){
	ES_t Local_enuErrorState = ES_NOK;
	/****** OUTPUT COMPARE MODE ******/

	if(Copy_enuTimer2_OCM >= Timer2_OC2_Disabled
			&& Copy_enuTimer2_OCM <= Timer2_OC2_Set){

		TCCR2 &= ~(Timer2_OC2_Set<<COM20);//mask first
		TCCR2 |= (Copy_enuTimer2_OCM<<COM20);
	}
	if(ES_OUT_OF_RANGE != Local_enuErrorState){
		Local_enuErrorState = ES_OK;
	}

	return Local_enuErrorState;
}
ES_t TIMER2_enuSetWaveGenMode(Timer2_WGM_t Copy_enuTimer2_WGM){
	ES_t Local_enuErrorState = ES_NOK;
	/********* Wave Generation Mode*******/
	switch(Copy_enuTimer2_WGM){
	case Timer2_OVF_Mode:
		TCCR2 &= ~(MASK_BIT<<WGM20);
		TCCR2 &= ~(MASK_BIT<<WGM21);
		break;
	case Timer2_CTC_Mode:
		TCCR2 &= ~(MASK_BIT<<WGM20);
		TCCR2 |=  (MASK_BIT<<WGM21);
		break;
	case Timer2_PWM_Fast:
		TCCR2 |=  (MASK_BIT<<WGM20);
		TCCR2 |=  (MASK_BIT<<WGM21);
		break;
	case Timer2_PWM_Phase:
		TCCR2 |=  (MASK_BIT<<WGM20);
		TCCR2 &= ~(MASK_BIT<<WGM21);
		break;
	default:
		Local_enuErrorState = ES_OUT_OF_RANGE;
		break;
	}
	if(ES_OUT_OF_RANGE != Local_enuErrorState){
		Local_enuErrorState = ES_OK;
	}

	return Local_enuErrorState;
}
ES_t TIMER2_enuSelect_Clock(Timer2_Pres_t Copy_enuTimer2_Pres){
	ES_t Local_enuErrorState = ES_NOK;
	/****** Clock Mode Selection ********/
	if(Copy_enuTimer2_Pres >= Timer2_PRES_Disabled
			&& Copy_enuTimer2_Pres <= Timer2_PRES_1024){
		TCCR2 &= PRES_MSK;
		TCCR2 |= (Copy_enuTimer2_Pres<<CS20);

		Local_enuErrorState = TIMER2_enuUpdatePrescaler(Copy_enuTimer2_Pres);
	}
	else{
		Local_enuErrorState = ES_OUT_OF_RANGE;
	}


	return Local_enuErrorState;
}
ES_t TIMER2_enuDelay_ms_OVF(u32 Copy_u32DesiredTime_ms){
	u8 Local_enuErrorState = ES_NOK;

		u32 Local_u32TotalCounts = (u32)(Copy_u32DesiredTime_ms * (F_CPU /(Timer2_u32PrescalerVal * CALC_LIMIT_TO_MS)) );

		Timer2_u32OVFs_Number = (u32)(Local_u32TotalCounts / FULL_OVF_COUNTS);
		u8 Local_u8FractionCounts = Local_u32TotalCounts % FULL_OVF_COUNTS;

		// this is a polling on the counter that is decremented each time ISR is executed means every ovf occurs
		while (Timer2_u32OVFs_Number > 0);
		while (TCNT2 < Local_u8FractionCounts);

		return Local_enuErrorState;
}
ES_t TIMER2_enuDelay_ms_CTC(u32 Copy_u32DesiredTime_ms){
	u8 Local_enuErrorState = ES_NOK;

/********************************************  OCR2 = desired * freq/pres **************************************************************/
/*
 * We calculate the required OCR value for delay of 1msec each time OCR reached then the input will be the number of counts required directly
 * for prescalers 64..128..256..1024 the value is divided by 1000 to convert to msec
 * But in prescaler of 1 or 8 or 32 the max OCR0 value will generate delay less than 1msec
 * so we divide by 10000 or 100000 to convert calculations from msec to the suitable scale
 */

	if(Timer2_u32PrescalerVal == 8 || Timer2_u32PrescalerVal == 32){
		OCR2 = (u8)( (F_CPU /(Timer2_u32PrescalerVal * 1000ul * 10)));
		Timer2_u32OCFs_Number = Copy_u32DesiredTime_ms * 10;
	}
	else if(Timer2_u32PrescalerVal == 1){
		OCR2 = (u8)( (F_CPU /(Timer2_u32PrescalerVal * 1000ul * 100)) );
		Timer2_u32OCFs_Number = Copy_u32DesiredTime_ms * 100;
	}
	else{
		OCR2 = (u8)(F_CPU /(Timer2_u32PrescalerVal * 1000ul));
		Timer2_u32OCFs_Number = Copy_u32DesiredTime_ms;
	}


	 while ( Timer2_u32OCFs_Number > 0);


	return Local_enuErrorState;
}
ES_t TIMER2_enuSetTCNT2_Value(u8 Copy_u8PreloadValue) {
	u8 Local_enuErrorState = ES_NOK;
	if (Copy_u8PreloadValue >= 0 || Copy_u8PreloadValue <= 255) {
		TCNT2 = Copy_u8PreloadValue;
		Local_enuErrorState = ES_OK;
	} else
		Local_enuErrorState = ES_OUT_OF_RANGE;
	return Local_enuErrorState;
}
ES_t TIMER2_enuSetOCR2_Value(u8 Copy_u8CompareValue) {
	u8 Local_enuErrorState = ES_NOK;
	if (Copy_u8CompareValue >= 0 || Copy_u8CompareValue <= 255) {
		OCR2 = Copy_u8CompareValue;
		Local_enuErrorState = ES_OK;
	}
	return Local_enuErrorState;
}
ES_t TIMER2_enuGetTCNT2_Value(u8* Copy_pu8PreloadValue){
	ES_t Local_enuErrorState = ES_NOK;
	if(NULL != Copy_pu8PreloadValue){
		*Copy_pu8PreloadValue = TCNT2;
		Local_enuErrorState = ES_OK;
	}
	else
	{
		Local_enuErrorState = ES_POINTER_TO_VOID;
	}

	return Local_enuErrorState;
}

ES_t TIMER2_enuGetOCR2_Value(u8* Copy_pu8CompareValue){
	ES_t Local_enuErrorState = ES_NOK;
	if(NULL != Copy_pu8CompareValue){
		*Copy_pu8CompareValue = OCR2;
		Local_enuErrorState = ES_OK;
	}
	else
	{
		Local_enuErrorState = ES_POINTER_TO_VOID;
	}

	return Local_enuErrorState;
}

ES_t TIMER2_enuOVF_Interrupt(bool Copy_enuInterruptEnable) {
	u8 Local_enuErrorState = ES_NOK;
	if (Copy_enuInterruptEnable == false) {
		TIMSK &= ~(MASK_BIT<<TOIE2);
		Local_enuErrorState = ES_OK;
	} else if (Copy_enuInterruptEnable == true) {
		TIMSK |=  (MASK_BIT<<TOIE2);
		Local_enuErrorState = ES_OK;
	} else
		Local_enuErrorState = ES_OUT_OF_RANGE;
	return Local_enuErrorState;
}
ES_t TIMER2_enuCompareMatch_Interrupt(bool Copy_enuInterruptEnable){
	u8 Local_enuErrorState = ES_NOK;
	if (Copy_enuInterruptEnable == false) {
		TIMSK &= ~(MASK_BIT<<OCIE2);
		Local_enuErrorState = ES_OK;
	} else if (Copy_enuInterruptEnable == true) {
		TIMSK |=  (MASK_BIT<<OCIE2);
		Local_enuErrorState = ES_OK;
	} else
		Local_enuErrorState = ES_OUT_OF_RANGE;
	return Local_enuErrorState;
}
ES_t TIMER2_enuSetCallBack(Timer2_ISRs_t Copy_enuSelectedISR, volatile void (*Copy_pfunAppFunction)(void)){
	ES_t Local_enuErrorState = ES_NOK;
	if (Copy_pfunAppFunction != NULL) {
		if (Copy_enuSelectedISR == Timer2_OVF_ISR)
			TIMER2_pfunOVF_ISR_fun = Copy_pfunAppFunction;
		else if (Copy_enuSelectedISR == Timer2_COM_ISR)
			TIMER2_pfunCOM_ISR_fun = Copy_pfunAppFunction;
		Local_enuErrorState = ES_OK;
	} else {
		Local_enuErrorState = ES_POINTER_TO_VOID;
	}
	return Local_enuErrorState;
}

 /******************************************************************************************************
 ****************************************** ISR Implementations ****************************************
 *******************************************************************************************************/

/**** Timer2 ISRs ****/
ISR(VECT_TIMER2_COM){
	if (Timer2_u32OCFs_Number > 0) {
		Timer2_u32OCFs_Number--;
	}
	if (TIMER2_pfunCOM_ISR_fun != NULL) {
		TIMER2_pfunCOM_ISR_fun();
	}
}
ISR(VECT_TIMER2_OVF){
	if (Timer2_u32OVFs_Number > 0) {
		Timer2_u32OVFs_Number--;
	}
	if (TIMER2_pfunOVF_ISR_fun != NULL) {
		TIMER2_pfunOVF_ISR_fun();
	}
}
