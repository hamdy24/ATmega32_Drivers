/*
 * EEPROM_Private.h
 *
 *  Created on:  Sep 20, 2022
 *  Author: 	 Hamdy Aouf
 *	Description: Here are private macros and declarations related to the Internal EEPROM
 */

#ifndef MCAL_EEPROM_EEPROM_PRIVATE_H_
#define MCAL_EEPROM_EEPROM_PRIVATE_H_

#include "../../LIBRARIES/errorstate.h"
#include "../../LIBRARIES/stdTypes.h"
#include "../../LIBRARIES/common.h"


#include "../AVR_REG.H"
#include "../interrupt.h"

CallBackFunc_t EEPROM_pfunISR_FUNC = NULL;


#define MAX_ADDRESS_SIZE	1023
#define MIN_ADDRESS_SIZE	0



/*
 * EECR > Control register bits
 */
//ready interrupt
#define EERIE				3
// Master Write
#define EEMWE				2
//
#define EEWE				1
//
#define EERE				0


#endif /* MCAL_EEPROM_EEPROM_PRIVATE_H_ */
