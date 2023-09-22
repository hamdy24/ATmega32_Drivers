/*
 * TWI_Config.h
 *
 *  Created on:  Nov 13, 2021
 *  Author: 	 Hamdy Aouf
 *	Description: File of all needed parameters or configurations would be used to control the Two Wire Interface
 */

#ifndef MCAL_TWI_TWI_CONFIG_H_
#define MCAL_TWI_TWI_CONFIG_H_

#include "../../LIBRARIES/errorstate.h"
#include "../../LIBRARIES/stdTypes.h"


typedef enum{
	TWI_MasterTransmitter,
	TWI_MasterReciever,
	TWI_SlaveTransmitter,
	TWI_SlaveReciever,
}TWI_Mode_t;

typedef enum{
	TWI_Pres_1,
	TWI_Pres_4,
	TWI_Pres_16,
	TWI_Pres_64,
}TWI_Pres_t;
typedef enum{
	TWI_Write,
	TWI_Read
}TWI_Operation_t;


typedef struct{
	TWI_Mode_t Mode:2;
	u8 NodeAddrress;// set to zero if no address exists
	TWI_Pres_t Prescaler:2;
	u16 ClockSpeedKHz;
	bool IsEnabled:1;
}TWI_Cfg_t;



#endif /* MCAL_TWI_TWI_CONFIG_H_ */
