/*
 * TWI_Interface.h
 *
 *  Created on:  Nov 13, 2021
 *  Author: 	 Hamdy Aouf
 *	Description: File of Interfaces used to control the Two Wire Interface of the ATmega32
 */

#ifndef MCAL_TWI_TWI_INTERFACE_H_
#define MCAL_TWI_TWI_INTERFACE_H_

#include "TWI_Config.h"

extern TWI_Cfg_t TWI_Configs;

ES_t TWI_enuInit(TWI_Cfg_t * Copy_pstrTWI_Configs);
ES_t TWI_enuActivateTWI(bool Copy_enuIsEnabled);
ES_t TWI_enuSetSpeed_inKHz(TWI_Pres_t Copy_enuPrescaler,u16 Copy_enuClockSpeed_inKHz);
ES_t TWI_enuSendStartCondition(void);
ES_t TWI_enuSendRepeatedStartCond(void);
ES_t TWI_enuSendStopCondition(void);
ES_t TWI_enuSetSlaveAddress_WithOperation(u8 Copy_u8SlaveAddress,TWI_Operation_t Copy_enuOperation);
ES_t TWI_enuCheckForOwnCall(bool * Copy_penuIsCalled);
ES_t TWI_enuWriteByte(u8 Copy_u8Data);
ES_t TWI_enuReadByte(u8 * Copy_pu8Data);
ES_t TWI_enuACK_EN(bool Copy_enuIsEnabled);
ES_t TWI_enuSetInterrupt_EN(bool Copy_enuIsEnabled);
ES_t TWI_enuSetAppCallBack(CallBackFunc_t Copy_pfunAppFunc);


#endif /* MCAL_TWI_TWI_INTERFACE_H_ */
