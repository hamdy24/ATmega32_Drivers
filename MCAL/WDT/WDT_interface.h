/*
 * WDT_interface.h
 *
 *  Created on:  Sep 12, 2022
 *  Author: 	 Hamdy Aouf
 *	Description: File of Interfaces used to control the Watch Dog Timer of the ATmega32
 */

#ifndef MCAL_WDT_WDT_INTERFACE_H_
#define MCAL_WDT_WDT_INTERFACE_H_

#include "WDT_Config.h"


ES_t WDT_enuStartWatching(WDT_Prescaler Copy_enuPrescaler);
ES_t WDT_enuStopWatching(void);

#endif /* MCAL_WDT_WDT_INTERFACE_H_ */
