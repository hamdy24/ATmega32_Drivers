/*
 * EEPROM_Interface.h
 *
 *  Created on:  Sep 20, 2022
 *  Author: 	 Hamdy Aouf
 *	Description: File of Interfaces used to control the Internal EEPROM of the ATmega32
 */

#ifndef MCAL_EEPROM_EEPROM_INTERFACE_H_
#define MCAL_EEPROM_EEPROM_INTERFACE_H_

#include "../../LIBRARIES/errorstate.h"
#include "../../LIBRARIES/stdTypes.h"

ES_t EEPROM_enuWriteByte(u16 Copy_u16DesiredLocation , u8 Copy_u8Data);
ES_t EEPROM_enuWriteBlock(u16 Copy_u16DesiredLocation , u8 * Copy_pu8ArrayOfData , u8 Copy_u8BlockSize);

ES_t EEPROM_enuReadByte(u16 Copy_u16DesiredLocation , u8 * Copy_pu8Data);
ES_t EEPROM_enuReadBlock(u16 Copy_u16DesiredLocation , u8 * Copy_pu8ArrayOfDataReturned , u8 Copy_u8ReadingSize);

ES_t EEPROM_enuSetInterrupt_EN(bool Copy_enuIsEnabled);
ES_t EEPROM_enuSetAppCallBack(CallBackFunc_t Copy_pfunAppFunc);

#endif /* MCAL_EEPROM_EEPROM_INTERFACE_H_ */
