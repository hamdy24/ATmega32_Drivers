/*
 * TWI_Private.h
 *
 *  Created on:  Nov 13, 2021
 *  Author: 	 Hamdy Aouf
 *	Description: Here are private macros and declarations related to the TWI
 */


#ifndef MCAL_TWI_TWI_PRIVATE_H_
#define MCAL_TWI_TWI_PRIVATE_H_

#include "../../LIBRARIES/errorstate.h"
#include "../../LIBRARIES/stdTypes.h"
#include "../../LIBRARIES/common.h"


#include "../AVR_REG.H"
#include "../interrupt.h"

#include "TWI_Config.h"

static CallBackFunc_t TWI_pfunISR_Func = NULL;

static u8 TWI_Prescalers[] = {1,4,16,64};
// INT flag cleared >> Start bit set >> TWI enable set
#define START_CONDITION			(MASK_BIT<<TWINT) | (MASK_BIT<<TWSTA) | (MASK_BIT<<TWEN)
#define STOP_CONDITION			(MASK_BIT<<TWINT) | (MASK_BIT<<TWSTO) | (MASK_BIT<<TWEN)
//
#define STATUS_BITS_MASK		0xF8
//
#define STATUS_CODE_VALUE		(TWSR & STATUS_BITS_MASK)
//
#define PRES_BITS_MASK			~(3<<TWPS0)

typedef enum{
// Master Transmitter
	Code_StartCondition_Sent 									= 0x08,
	Code_RepeatedStart_Sent 									= 0x10,
	Code_Slave_W_WithACK_Sent 									= 0x18,
	Code_Slave_W_NoACK_Sent 									= 0x20,
	Code_Data_WithACK_Sent 										= 0x28,	//send
	Code_Data_WithNoACK_Sent 									= 0x30,
	Code_Arbitration_Lost 										= 0x38, // in SLA_W or Data ////////// SLA_R or No ACK
// Master Receiver with some of previous states too
	Code_Slave_R_WithACK_Sent 									= 0x40,
	Code_Slave_R_NoACK_Sent 									= 0x48,
	Code_Data_WithACK_Received 									= 0x50,//
	Code_Data_WithNoACK_Received 								= 0x58,//
// Slave Receiver
	Code_Own_Slave_W_WithACK_Received 							= 0x60,
	Code_MasterArbitration_LostOR_Own_Slave_W_WithACK_Received 	= 0x68,
	Code_GeneralCall_WithACK_Received 							= 0x70,
	Code_MasterArbitration_LostOR_GeneralCall_Received 			= 0x78,
	Code_PreAddrWithOwn_Slave_W_OR_Data_WithACK_Received  		= 0x80,//
	Code_PreAddrWithOwn_Slave_W_OR_Data_WithNoACK_Received		= 0x88,
	Code_PreAddrWithGeneralCall_OR_Data_WithACK_Received 		= 0x90,
	Code_PreAddrWithGeneralCall_OR_Data_WithNoACK_Received 		= 0x98,
	Code_StartOrStopCondition_WhileSlave 						= 0xA0,
// Slave Transmitter
	Code_Own_Slave_R_WithACK_Received 							= 0xA8,
	Code_MasterArbitration_LostOR_Own_Slave_R_WithACK_Received 	= 0xB0,
	Code_Data_WithACK_Transmitted 								= 0xB8,		//send
	Code_Data_WithNoACK_Transmitted 							= 0xC0,
	Code_LastData_WithACK_Transmitted 							= 0xC8,

	Code_NoStateInfo											= 0xF8,
	Code_BusError 												= 0x00,
}TWI_MT_StatusCodes_t;

/*
 * TWCR >> TWI Control Register
 */

// interrupt Flag >> Must be CLEARED by writing one to it each time to start the operation of TWI
// NOTICE: Setup everything else before clearing the flag
#define TWINT 					7
// TWI Enable Acknowledge Bit
#define TWEA 					6
// TWI START Condition Bit >> it requests the device to be a master and waits till bus is free then generate start condition
#define TWSTA 					5
//  TWI Write Collision Flag
#define TWSTO 					4
//  TWI Write Collision Bit
#define TWWC 					3
//  TWI Enable Bit >> it switches the TWI on/off >> if TWI off the pin is in normal port operation
#define TWEN 					2
// TWI Interrupt Enable >> this makes a interrupt request activated as long as the Interrupt flag is raised TWINT
#define TWIE					0

/*
 * TWSR >> TWI Status Register
 */
// this contains the current status code of the TWI
#define TWS3 					3
// Prescalers >>> 1 >>> 4 >>> 16 >>> 64
#define TWPS1 					1
#define TWPS0					0

/*
 * TWAR >> TWI Slave Address Register
 */
// General Call Bit
#define TWGCE					0

#define TWAR_RW					0
// Start of slave address bits
#define TWA0					1

#define TWD1					1


#endif /* MCAL_TWI_TWI_PRIVATE_H_ */
