/*
 * ADC_program.c
 *
 *  Created on: Nov 15, 2021
 *  Author: 	 Hamdy Aouf
 *	Description: Here are all the Interfaces definitions of the ADC
 */
#include "ADC_private.h"


ES_t ADC_enuInit(ADC_Cfg_t * Copy_pstrADC_Configs) {
	ES_t Local_enuErrorState = ES_NOK;
	/***************************************************************************
	 ************************ ADC PreScaler Initialization *********************
	 **************************************************************************/

	switch (Copy_pstrADC_Configs->PRES) {
	case ADC_PRES_2:
		ADCSRA = PRES2_DIVISION_FACTOR_SET;
		break;
	case ADC_PRES_4:
		ADCSRA = PRES4_DIVISION_FACTOR_SET;
		break;
	case ADC_PRES_8:
		ADCSRA = PRES8_DIVISION_FACTOR_SET;

		break;
	case ADC_PRES_16:
		ADCSRA = PRES16_DIVISION_FACTOR_SET;
		break;
	case ADC_PRES_32:
		ADCSRA = PRES32_DIVISION_FACTOR_SET;

		break;
	case ADC_PRES_64:
		ADCSRA = PRES64_DIVISION_FACTOR_SET;
		break;
	case ADC_PRES_128:
		ADCSRA = PRES128_DIVISION_FACTOR_SET;
		break;
	default:
		Local_enuErrorState = ES_OUT_OF_RANGE;
		break;
	}

	if (ES_OUT_OF_RANGE != Local_enuErrorState) {
		/*******************************************************
		 ********* Voltage Reference Initialization ************
		 *******************************************************/

		switch (Copy_pstrADC_Configs->VREF) {
		case AREF_REF:
			/* REFS1_BIT_6 -> bit7   REFS0_BIT_6 -> bit6 */
			ADMUX &= ~(MASK_BIT << REFS0_SEL_BIT_6);
			ADMUX &= ~(MASK_BIT << REFS1_SEL_BIT_7);
			break;
		case AVCC_REF:
			/* REFS1 -> bit7   REFS0 -> bit6 */
			ADMUX |= (MASK_BIT << REFS0_SEL_BIT_6);
			ADMUX &= ~(MASK_BIT << REFS1_SEL_BIT_7);
			break;
		case INTERNAL_REF:
			/* REFS1 -> bit7   REFS0 -> bit6 */
			ADMUX |= (MASK_BIT << REFS0_SEL_BIT_6);
			ADMUX |= (MASK_BIT << REFS1_SEL_BIT_7);
			break;
		default:
			Local_enuErrorState = ES_OUT_OF_RANGE;
			break;
		}
		/***********************************************************************
		 ************** Data Adjust Direction Initialization *******************
		 **********************************************************************/

		if (ES_OUT_OF_RANGE != Local_enuErrorState) {
			if (Copy_pstrADC_Configs->ADJ_Direction == ADC_LEFT_ADJ) {
				ADC_DataADJ_Direction = ADC_LEFT_ADJ;
				/******* ADLAR is Bit 5 of ADMUX ******/
				ADMUX |= (MASK_BIT << ADLAR_BIT_5);
			} else if (Copy_pstrADC_Configs->ADJ_Direction == ADC_RIGHT_ADJ) {
				ADC_DataADJ_Direction = ADC_RIGHT_ADJ;
				/******* ADLAR is Bit 5 of ADMUX ******/
				ADMUX &= ~(MASK_BIT << ADLAR_BIT_5);
			} else {
				Local_enuErrorState = ES_OUT_OF_RANGE;
			}
		}
		/**********************************************************************************
		 ************ ADC INT source and channel select Initialization ********************
		 **********************************************************************************/

		if (ES_OUT_OF_RANGE != Local_enuErrorState) {
			if (Copy_pstrADC_Configs->INT_Src <= ADC_TIMER_1_CAPTURE_EVENT) {
				// we disable it first till we adjust SFIOR Bits first then enable it again as
				// if it was enabled previously from previous call of the function and i called it again
				// the following masking process will force the ADC to free running mode as its bits will be 000

				ADCSRA &= ~(MASK_BIT << ADC_AUTO_TRIGGER_BIT_5);

				SFIOR &= SFIOR_MASK_VALUE; //0x0001 1111
				SFIOR |= (Copy_pstrADC_Configs->INT_Src << ADC_TRIGGER_SELECT_BIT_5); // here we set the ADTS

				ADCSRA |= (MASK_BIT << ADC_AUTO_TRIGGER_BIT_5); // without this one set...selecting interrupt source has no effect

				if(Copy_pstrADC_Configs->INT_Src == ADC_FREE_RUNNIG){
					// if it is free running mode we start conversion for the first time only
					ADCSRA |= (MASK_BIT << ADC_START_CONVERSION_BIT);
				}

				if (Copy_pstrADC_Configs->ChannelNum <= ADC_MAX_CHANNEL_NUM) {
					// in single ended channel the channel number is same with pin number
					ADMUX &= ~ADMUX_CHANNELS_MASK_VALUE;  //0xddd0 0000 at ADMUX
					ADMUX |= Copy_pstrADC_Configs->ChannelNum;

					Local_enuErrorState = ES_OK;
				} else {
					Local_enuErrorState = ES_OUT_OF_RANGE;
				}
			} else {
				Local_enuErrorState = ES_OUT_OF_RANGE;
			}
		}

	}

	ADCSRA |= (MASK_BIT << ADC_INT_ENABLE_BIT_3);//enable ADC Interrupt
	ADCSRA |= (MASK_BIT << ADC_ENABLE_BIT_7);	// enable ADC Module



	return Local_enuErrorState;
}

ES_t ADC_enuStart_Conversion(void) {
	ES_t Local_enuErrorState = ES_NOK;

	ADCSRA |= (MASK_BIT << ADC_START_CONVERSION_BIT);

	Local_enuErrorState = ES_OK;

	return Local_enuErrorState;
}
/*************************************************************************
 * This function only reads the high 8 bits no matter the adjustment
 * in LEFT ADJ it reads ADCH
 * in RIGHT ADJ it reads 2bits from ADCH and 6bits from ADCL
 ************************************************************************/
ES_t ADC_enuRead_HighADC_Registers(u8 * Copy_pu8HighReg_Value) {
	ES_t Local_enuErrorState = ES_NOK;

	if(ADC_DataADJ_Direction == ADC_LEFT_ADJ){
		/*
		 * ADCH		BIT_9....2
		 * ADCL		Ignored
		 */
		*Copy_pu8HighReg_Value = ADCH;

		Local_enuErrorState = ES_OK;
	}
	else{
		/*
		 * ADCH		BIT_9,8
		 * ADCL		BIT_7...0
		 */
		*Copy_pu8HighReg_Value = (ADCL >> 2);  //shifts 2 bit to GET the 6 MSBs
		*Copy_pu8HighReg_Value |= (ADCH << 6);//shifts the 2LSBs of ADCH to be in front of the 6 bits of ADCL

		Local_enuErrorState = ES_OK;
	}

	return Local_enuErrorState;
}
/*************************************************************************
 * This function reads all 10 bits no matter the adjustment
 ************************************************************************/
ES_t ADC_enuFully_ReadADC_Register(u16 * Copy_pu16Full_Value) {
	ES_t Local_enuErrorState = ES_NOK;

	if(ADC_DataADJ_Direction == ADC_LEFT_ADJ){
		/*
		 * ADCH		BIT_9....2
		 * ADCL		BIT_1,0
		 */
		(*Copy_pu16Full_Value) = (ADCL >> 6); //shifts 6 bit to GET the 2 MSBs
		(*Copy_pu16Full_Value) |= ((u16) ADCH << 2);

		Local_enuErrorState = ES_OK;
	}
	else if(ADC_DataADJ_Direction == ADC_RIGHT_ADJ){
		(*Copy_pu16Full_Value) = ADCL;
		(*Copy_pu16Full_Value) |= ((u16)ADCH << 8);

		Local_enuErrorState = ES_OK;
	}

	return Local_enuErrorState;
}

/*************************************************************************
 * This function enables auto triggering and sets the bits for the desired INT Source
 ************************************************************************/
ES_t  ADC_enuSetAutoTriggering_EN(ADC_INT_Sources_enuType Copy_u8INT_Source, bool Copy_IsEnabled){
	ES_t Local_enuErrorState = ES_NOK;

	if(Copy_IsEnabled == true){
		if (Copy_u8INT_Source <= ADC_TIMER_1_CAPTURE_EVENT
				&& Copy_u8INT_Source >= ADC_FREE_RUNNIG) {
	// we disable it first till we adjust SFIOR Bits first then enable it again as
	// if it was enabled previously from previous call of the function and i called it again
	// the following masking process will force the ADC to free running mode as its bits will be 000

			ADCSRA &= ~(MASK_BIT << ADC_AUTO_TRIGGER_BIT_5);

			SFIOR &= SFIOR_MASK_VALUE; //0x0001 1111
			SFIOR |= (Copy_u8INT_Source << ADC_TRIGGER_SELECT_BIT_5); // here we set the ADTS

			ADCSRA |= (MASK_BIT << ADC_AUTO_TRIGGER_BIT_5); // without this one set...selecting interrupt source has no effect

			if(Copy_u8INT_Source == ADC_FREE_RUNNIG){
				// if it is free running mode we start conversion for the first time only
				ADCSRA |= (MASK_BIT << ADC_START_CONVERSION_BIT);
			}
			Local_enuErrorState = ES_OK;
		} else {
			Local_enuErrorState = ES_OUT_OF_RANGE;
		}
	}
	else if(Copy_IsEnabled == false){
		ADCSRA &= ~(MASK_BIT << ADC_AUTO_TRIGGER_BIT_5);
	}


	return Local_enuErrorState;
}

/*************************************************************************
 * This function selects which channel to use from ADC MUX and activate it
 ************************************************************************/
ES_t ADC_enuSelect_Channel(u8 Copy_u8Channel_ID) {
	ES_t Local_enuErrorState = ES_NOK;

	if (Copy_u8Channel_ID <= ADC_MAX_CHANNEL_NUM) {
// in single ended channel the channel number is same with pin number
		ADMUX &= ~ADMUX_CHANNELS_MASK_VALUE;  //0xddd0 0000 at ADMUX
		ADMUX |= Copy_u8Channel_ID;

		Local_enuErrorState = ES_OK;
	} else {
		Local_enuErrorState = ES_OUT_OF_RANGE;
	}
	return Local_enuErrorState;
}

ES_t  ADC_enuSetADC_Enable(bool Copy_enuBooleanValue){
	ES_t Local_enuErrorState = ES_NOK;

	if(Copy_enuBooleanValue == true){
		ADCSRA |= (MASK_BIT << ADC_ENABLE_BIT_7);

		Local_enuErrorState = ES_OK;
	}
	else if(Copy_enuBooleanValue == false){
		ADCSRA &= ~(MASK_BIT << ADC_ENABLE_BIT_7);

		Local_enuErrorState = ES_OK;
	}


	return Local_enuErrorState;
}

ES_t  ADC_enuSetADC_INT_EN(bool Copy_enuBooleanValue){
	ES_t Local_enuErrorState = ES_NOK;

	if(Copy_enuBooleanValue == true){
		ADCSRA |= (MASK_BIT << ADC_INT_ENABLE_BIT_3);

		Local_enuErrorState = ES_OK;
	}
	else if(Copy_enuBooleanValue == false){
		ADCSRA &= ~(MASK_BIT << ADC_INT_ENABLE_BIT_3);

		Local_enuErrorState = ES_OK;

	}


	return Local_enuErrorState;
}

/*
 * Start waiting till the conversion is complete
 */
ES_t ADC_enuStartPolling(void) {
	ES_t Local_enuErrorState = ES_NOK;
	/*
	 * ADIF is cleared by hardware when executing the corresponding interrupt handling vector so we wait till it is zero then proceed
	 */
	while (!(ADCSRA << ADC_INT_FLAG_BIT_4) & LOGIC_ONE)
		;
	ADCSRA |= (MASK_BIT << ADC_INT_FLAG_BIT_4); // clear mechanism of this flag is to set it with logic one

	Local_enuErrorState = ES_OK;

	return Local_enuErrorState;
}

ES_t ADC_enuCall_Back(CallBackFunc_t Copy_pfun_AppFun) {
	ES_t Local_enuErrorState = ES_NOK;
	if (Copy_pfun_AppFun != NULL) {
		ADC_pfunISR_Fun = Copy_pfun_AppFun;
		Local_enuErrorState = ES_OK;
	} else
		Local_enuErrorState = ES_POINTER_TO_VOID;

	return Local_enuErrorState;
}

ISR(VECT_ADC) {

	if (ADC_pfunISR_Fun != NULL) {
		ADC_pfunISR_Fun();
	}
    // Unlock the ADC register
    ADCSRA |= (1 << ADC_INT_FLAG_BIT_4);
}

