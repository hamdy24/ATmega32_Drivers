/*
 * ADC_interface.h
 *
 *  Created on: Nov 15, 2021
 *  Author: 	 Hamdy Aouf
 *	Description: File of Interfaces used to control the ADC of the ATmega32
 */

#ifndef MCAL_ADC_ADC_INTERFACE_H_
#define MCAL_ADC_ADC_INTERFACE_H_

#include "ADC_config.h"
#include "../../LIBRARIES/stdTypes.h"
#include "../../LIBRARIES/errorstate.h"

/** Use it To Configure The ADC **/
extern ADC_Cfg_t ADC_Configs;

/*************************************************************************
 * This function Initializes the ADC
 ************************************************************************/
ES_t  ADC_enuInit(ADC_Cfg_t * Copy_pstrADC_Configs);

/*************************************************************************
 * This function Sets the bit that start the conversion
 ************************************************************************/
ES_t  ADC_enuStart_Conversion(void);

/*************************************************************************
 * This function only reads the high 8 bits no matter the adjustment
 ************************************************************************/
ES_t  ADC_enuRead_HighADC_Register(u8 * Copy_pu8Higher_Value);

/*************************************************************************
 * This function reads all 10 bits no matter the adjustment
 ************************************************************************/
ES_t  ADC_enuFully_ReadADC_Register(u16 * Copy_pu16Full_Value);


/*************************************************************************
 * This function enables/disables auto triggering and handles the bits for the desired INT Source
 ************************************************************************/
ES_t  ADC_enuSetAutoTriggering_EN(ADC_INT_Sources_enuType Copy_u8INT_Source, bool Copy_IsEnabled);


/*************************************************************************
 * This function selects which channel to use from ADC MUX and activate it
 ************************************************************************/
ES_t  ADC_enuSelect_Channel(ADC_Channels_enuType Copy_u8Channel_ID);


/*************************************************************************
 * This function enables/disables ADC itself
 ************************************************************************/
ES_t  ADC_enuSetADC_Enable(bool Copy_strBooleanValue);

/*************************************************************************
 * This function enables/disables ADC Interrupt
 ************************************************************************/
ES_t  ADC_enuSetADC_INT_EN(bool Copy_strBooleanValue);


/*************************************************************************
 * This function Starts Conversion with polling technique
 ************************************************************************/
ES_t  ADC_enuStartPolling(void);


/*************************************************************************
 * This function for APP CallBacks
 ************************************************************************/
ES_t  ADC_enuCall_Back(CallBackFunc_t Copy_pfun_AppFun);




#endif /* MCAL_ADC_ADC_INTERFACE_H_ */
