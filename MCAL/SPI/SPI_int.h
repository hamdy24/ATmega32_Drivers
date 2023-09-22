/*
 * SPI_int.h
 *
 *  Created on: Oct 30, 2021
 *  Author: 	 Hamdy Aouf
 *	Description: File of Interfaces used to control the SPI of the ATmega32
 */

#ifndef SPI_INT_H_
#define SPI_INT_H_

#include "SPI_config.h"

extern SPI_Cfg_t SPI_Configs;

ES_t SPI_enuInit(SPI_Cfg_t * Copy_pstrSPI_Config);
ES_t SPI_enuTranscieve(u8 Copy_u8DataSent, u8 * Copy_pu8DataRecieved,bool Copy_enuIsBlocking);
ES_t SPI_enuSetSPI_Mode(SPI_Mode_enuType Copy_enuOperatingMode);
ES_t SPI_enuSetClockRate(SPI_PRES_enuType Copy_enuClockRate);
ES_t SPI_enuSetDataTransferOrder(SPI_DataOrder_enuType Copy_enuDataOrder);
ES_t SPI_enuSetPhasePolarityMode(SPI_PolarityPhase_enuType	Copy_enuPhasePolarityCfg);
ES_t SPI_enuSetInterrupt_Enable(bool Copy_enuIsEnabled);
ES_t SPI_enuSetSPI_Enable(bool Copy_enuIsEnabled);
ES_t SPI_enuCallBack(CallBackFunc_t Copy_pfun_AppFun);

#endif /* SPI_INT_H_ */
