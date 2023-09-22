/*
 * PWM_program.c
 *
 *  Created on: Nov 19, 2021
 *  Author: 	 Hamdy Aouf
 *	Description: Here are all the Interfaces definitions of the PWM
 */

#include "PWM_private.h"


/*
 * Fast PWM : 5,6,7 & 14,15
 *
 * Phase Correct PWM : 1,2,3 & 10,11
 *
 * Phase and frequency Correct PWM : 8,9
 *
 * non-PWM: 0,4,12
 */
/********************** TCCR1A Watch window ************************
 * COM1A1 	COM1A0 	COM1B1 	COM1B0 	FOC1A 	FOC1B 	WGM11 	WGM10  *
 *	 0		  0		  0	  	  0		 0		  0		  0		  0	   *
 ********************** TCCR1B Watch window ************************
 * ICNC1 	ICES1 	  – 	WGM13 	WGM12 	CS12 	CS11 	CS10   *
 *   0		  0		  d		  0		  0		  0		  0		  0	   *
 *******************************************************************/

ES_t PWM_enuInit(PWM1_t Copy_strPWM_Config){
	ES_t Local_enuErrorState = ES_NOK;

	PWM_Type = Copy_strPWM_Config.PWM_Type;
	PWM_OC_Mode = Copy_strPWM_Config.PWM_Mode;

	if(Copy_strPWM_Config.PWM_EnableState == true){
		/*** Interrupts Initialization ***/
		TIMSK |=  (MASK_BIT<<OCIE1A); /** Output Compare A Match Interrupt Enabled **/
		TIMSK |=  (MASK_BIT<<OCIE1B); /** Output Compare B Match Interrupt Enabled **/

		/*** Force Output Compare Disabled ***/
		TCCR1A =0;
		TCCR1B =0;

		/*******************************/
		/*** PWM Mode Initialization ***/
		/*******************************/
		if(Copy_strPWM_Config.PWM_Type >= PWM1_PhaseCorrect_8bit
				&& Copy_strPWM_Config.PWM_Type <= PWM1_Fast_OCR1A){

			// Apply get bit mechanism to extract each bit mapped to the WGM bits to apply the change
			TCCR1A |= (((Copy_strPWM_Config.PWM_Type>>GET_BIT0)&MASK_BIT)<<WGM10); // 14=> 11 10 & 0001 = 0
			TCCR1A |= (((Copy_strPWM_Config.PWM_Type>>GET_BIT1)&MASK_BIT)<<WGM11); // 14=> 11 10 & 0010 = 1
			TCCR1B |= (((Copy_strPWM_Config.PWM_Type>>GET_BIT2)&MASK_BIT)<<WGM12); // 14=> 11 10 & 0100 = 1
			TCCR1B |= (((Copy_strPWM_Config.PWM_Type>>GET_BIT3)&MASK_BIT)<<WGM13); // 14=> 11 10 & 1000 = 1

			/*******************************************/
			/*********** OUTPUT COMPARE MODE ***********/
			/*******************************************/
			// Case Fast PWM
			if((Copy_strPWM_Config.PWM_Type >= PWM1_Fast_8bit
					&& Copy_strPWM_Config.PWM_Type <= PWM1_Fast_10bit)
					|| Copy_strPWM_Config.PWM_Type == PWM1_Fast_ICR1
					|| Copy_strPWM_Config.PWM_Type == PWM1_Fast_OCR1A ){

				if(Copy_strPWM_Config.PWM_Mode == OC_InvertingMode){  // Clear on OCR
					if(Copy_strPWM_Config.PWM_Channel == PWM1_OC_ChannelA_B){
						TCCR1A |= (INVERTING<<COM1A0);
						TCCR1A |= (INVERTING<<COM1B0);
					}
					else if(Copy_strPWM_Config.PWM_Channel  == PWM1_OC_ChannelA){
						TCCR1A |= (INVERTING<<COM1A0);
					}
					else{
						TCCR1A |= (INVERTING<<COM1B0);
					}
				}
				else if(Copy_strPWM_Config.PWM_Mode == OC_Non_InvertingMode){ // Set on OCR
					if(Copy_strPWM_Config.PWM_Channel == PWM1_OC_ChannelA_B){
						TCCR1A |= (NON_INVERTING<<COM1A0);
						TCCR1A |= (NON_INVERTING<<COM1B0);
					}
					else if(Copy_strPWM_Config.PWM_Channel  == PWM1_OC_ChannelA){
						TCCR1A |= (NON_INVERTING<<COM1A0);
					}
					else{
						TCCR1A |= (NON_INVERTING<<COM1B0);
					}
				}
			}
			// Case Phase or Phase and frequency Correct PWM
			else if((Copy_strPWM_Config.PWM_Type >= PWM1_PhaseCorrect_8bit
					&& Copy_strPWM_Config.PWM_Type <= PWM1_PhaseCorrect_10bit)
					|| Copy_strPWM_Config.PWM_Type == PWM1_PhaseFrequencyCorrect_ICR1
					|| Copy_strPWM_Config.PWM_Type == PWM1_PhaseCorrect_OCR1A ){

				if(Copy_strPWM_Config.PWM_Mode == OC_InvertingMode){  // Set up counting
					if(Copy_strPWM_Config.PWM_Channel == PWM1_OC_ChannelA_B){
						TCCR1A |= (NON_INVERTING<<COM1A0);
						TCCR1A |= (NON_INVERTING<<COM1B0);
					}
					else if(Copy_strPWM_Config.PWM_Channel  == PWM1_OC_ChannelA){
						TCCR1A |= (NON_INVERTING<<COM1A0);
					}
					else{
						TCCR1A |= (NON_INVERTING<<COM1B0);
					}
				}
				else if(Copy_strPWM_Config.PWM_Mode == OC_Non_InvertingMode){ // Clear up counting
			//		if(Copy_strPWM_Config.PWM_Mode == OC_InvertingMode){  // Clear on OCR
						if(Copy_strPWM_Config.PWM_Channel == PWM1_OC_ChannelA_B){
							TCCR1A |= (INVERTING<<COM1A0);
							TCCR1A |= (INVERTING<<COM1B0);
						}
						else if(Copy_strPWM_Config.PWM_Channel  == PWM1_OC_ChannelA){
							TCCR1A |= (INVERTING<<COM1A0);
						}
						else{
							TCCR1A |= (INVERTING<<COM1B0);
						}
				}
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

ES_t PWM_enuSetFrequency(u16 Copy_u16Frequency){
	ES_t Local_enuErrorState = ES_NOK;
/*
 * if limited PWM type is used we set clock source to closest one to required
 * if PWM = 8,9,10,11,14,15 we can control the TOP value so we adjust frequency more accurately
 */
/*
 * in accuracy types there are two cases....fast or phase
 */
	// 14,15 are types with FAST PWM mode
		// set clock
		TCCR1B |= (PWM_Pres<<CS10);
	if( PWM_Type == PWM1_Fast_ICR1){
		// set ICR to the required frequency
		u16 ICR_Val = (u16)(F_CPU/(Copy_u16Frequency * PWM_Prescalers[PWM_Pres]) );
		ICR_Val--;
		ICR1 = ICR_Val;
	}
	else if(PWM_Type == PWM1_Fast_OCR1A){
		u16 OCR_Value = (u16)(F_CPU/(Copy_u16Frequency * PWM_Prescalers[PWM_Pres]) );
		OCR_Value--;
		OCR1A = OCR_Value;
	}
	freq = Copy_u16Frequency;

	return Local_enuErrorState;
}

ES_t PWM_enuSetDutyCycle(f32 Copy_f32DutyCycle){
	ES_t Local_enuErrorState = ES_NOK;

	u16 Local_u16OCR_Val;

	if( PWM_Type == PWM1_Fast_ICR1){
		Local_u16OCR_Val = (F_CPU*Copy_f32DutyCycle/(freq *  PWM_Prescalers[PWM_Pres])/100 );
		Local_u16OCR_Val--;
		OCR1A =Local_u16OCR_Val;
	}
	else if(PWM_Type == PWM1_Fast_OCR1A){

	}
	return Local_enuErrorState;
}
/*
 * Following are all solid configuration and approximate calculations as Timer 1 is the best choice for Wave generation
 * but they are implemented in case you will generate two waves for example
 */
ES_t PWM_enuInitLowAccuracy(PWM_Weak_t * Copy_pAstrPWM_Config ,PWM_Weak_Channels_t Copy_enuSelectedChannel)
{
	ES_t Local_enuErrorState = ES_NOK;

	if(Copy_enuSelectedChannel == PWM_Timer0){
		if(Copy_pAstrPWM_Config->PWM_EnableState == true)
		{
			if (Copy_pAstrPWM_Config->PWM_WaveType == PWM_Fast)
			{
				TCCR0 |=  (MASK_BIT<<WGM00);
				TCCR0 |=  (MASK_BIT<<WGM01);
				if (Copy_pAstrPWM_Config->PWM_Mode == OC_Non_InvertingModeWeak)
				{
					TCCR0 |= (MASK_BIT<<COM01);
					TCCR0 &= PRES_MSK;

				}
			}
			else if(Copy_pAstrPWM_Config->PWM_WaveType == PWM_PhaseCorrect)
			{

			}
		}

	}else if(Copy_enuSelectedChannel == PWM_Timer2){
		if(Copy_pAstrPWM_Config->PWM_EnableState == true)
		{
			if (Copy_pAstrPWM_Config->PWM_WaveType == PWM_Fast)
			{
				TCCR2 |=  (MASK_BIT<<WGM00);
				TCCR2 |=  (MASK_BIT<<WGM01);
				if (Copy_pAstrPWM_Config->PWM_Mode == OC_Non_InvertingModeWeak)
				{
					TCCR2 |= (MASK_BIT<<COM01);
					TCCR2 &= PRES_MSK;

				}
			}
			else if(Copy_pAstrPWM_Config->PWM_WaveType == PWM_PhaseCorrect)
			{

			}
		}

	}else{
		Local_enuErrorState = ES_OUT_OF_RANGE;
	}

	return Local_enuErrorState;
}

ES_t PWM_enuSet_FrequencyLowAccuracy(u16 Copy_u16Frequency , PWM_Weak_t * Copy_pstrPWM_Config,PWM_Weak_Channels_t Copy_enuSelectedChannel)
{
	ES_t Local_enuErrorState = ES_NOK;

	u16 Local_Au16FreqFast0 []={62500,7812,976,245,61};// this for pwm0
	u16 Local_Au16FreqFast2 []={62500,7812,1953,976,488,245,61};// this for pwm2

	u8 flag=0;

	if (Copy_enuSelectedChannel == PWM_Timer0)
	{
		if (Copy_pstrPWM_Config->PWM_WaveType == PWM_Fast)
		{
			for (u8 i=0 ; i<5 ; i++)
			{
				if (Copy_u16Frequency == Local_Au16FreqFast0[i])
				{
					TCCR0 &=~(7<<0);
					TCCR0 |= (i+1);
					flag=1;
					break;
				}
			}
			if(flag==0)
			{
				for (u8 i=0; i<5 ; i++)
				{
					if (Copy_u16Frequency > Local_Au16FreqFast0[i])
					{
						TCCR0 &=~(7<<0);
						TCCR0 |= (i+1);
						flag=1;
						break;
					}
				}
				if (flag==0)
				{
					TCCR0 &=~(7<<0);
					TCCR0 |= (5);
				}
			}
		}
	}else if (Copy_enuSelectedChannel == PWM_Timer2)
	{
		if (Copy_pstrPWM_Config->PWM_WaveType == PWM_Fast)
		{
			for (u8 i=0 ; i<7 ; i++)
			{
				if (Copy_u16Frequency == Local_Au16FreqFast2[i])
				{
					TCCR2 &=~(7<<0);
					TCCR2 |= (i+1);
					flag=1;
					break;
				}
			}
			if(flag==0)
			{
				for (u8 i=0; i<7 ; i++)
				{
					if (Copy_u16Frequency > Local_Au16FreqFast2[i])
					{
						TCCR2 &=~(7<<0);
						TCCR2 |= (i+1);
						flag=1;
						break;
					}
				}
				if (flag==0)
				{
					TCCR2 &=~(7<<0);
					TCCR2 |= (5);
				}
			}

		}
	}

	return Local_enuErrorState;
}

ES_t PWM_enuSet_DutyCycleLowAccuracy(u8 Copy_u16DutyCycle , PWM_Weak_t * Copy_pstrPWM_Config ,PWM_Weak_Channels_t Copy_enuSelectedChannel)
{
	ES_t Local_enuErrorState = ES_NOK;
	if (Copy_enuSelectedChannel == PWM_Timer0)
	{
		if (Copy_u16DutyCycle <=100)
		{
			if (Copy_pstrPWM_Config->PWM_EnableState == true)
			{
				if (Copy_pstrPWM_Config->PWM_WaveType == PWM_Fast)
				{
					if (Copy_pstrPWM_Config->PWM_Mode == OC_Non_InvertingModeWeak)
					{
						u8 OCR_Value = (u8)( (Copy_u16DutyCycle * 256ul)/100ul );
						OCR0 = OCR_Value;
					}
				}
			}
		}

	}else if (Copy_enuSelectedChannel == PWM_Timer2)
	{
		if (Copy_u16DutyCycle <=100)
		{
			if (Copy_pstrPWM_Config->PWM_EnableState == true)
			{
				if (Copy_pstrPWM_Config->PWM_WaveType == PWM_Fast)
				{
					if (Copy_pstrPWM_Config->PWM_Mode == OC_Non_InvertingModeWeak)
					{
						u8 OCR_Value = (u8)( (Copy_u16DutyCycle * 256ul)/100ul );
						OCR2 = OCR_Value;
					}
				}
			}
		}

	}

	return Local_enuErrorState;
}

