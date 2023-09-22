/*
 * WDT_Private.h
 *
 *  Created on:  Sep 12, 2022
 *  Author: 	 Hamdy Aouf
 *	Description: Here are private macros and declarations related to the WDT
 */

#ifndef MCAL_WDT_WDT_PRIVATE_H_
#define MCAL_WDT_WDT_PRIVATE_H_

#include "../../LIBRARIES/errorstate.h"
#include "../../LIBRARIES/stdTypes.h"

#include "../../LIBRARIES/common.h"

#include "../AVR_REG.H"

#include "WDT_Config.h"

#define WDP0      		0
#define WDP1      		1
#define WDP2      		2
#define WDE       		3
#define WDTOE     		4

#define WDT_PRES_MASK	~(7<<WDP0)

#define WDT_OFF			0x00

#endif /* MCAL_WDT_WDT_PRIVATE_H_ */
