/*
 * SPI_priv.h
 *
 *  Created on: Oct 30, 2021
 *  Author: 	 Hamdy Aouf
 *	Description: File of all needed parameters or configurations would be used to control the SPI
 */

#ifndef SPI_PRIV_H_
#define SPI_PRIV_H_

#include "../../LIBRARIES/errorstate.h"
#include "../../LIBRARIES/stdTypes.h"
#include "../../LIBRARIES/common.h"

#include "../interrupt.h"
#include "../AVR_REG.H"

#include "SPI_config.h"

static CallBackFunc_t SPI_pfunISR_Func = NULL;

//SPCR
#define	SPIE				7
#define SPE					6
#define	DORD				5
#define MSTR				4
#define	CPOL				3
#define CPHA				2
#define SPR1				1
#define	SPR0				0
//SPSR
#define SPIF				7
#define WCOL				6
#define SPI2X				0


#ifndef MCAL_AVR_REG_H_
#define SPDR	*((volatile u8*) 0x2f)
#define SPSR	*((volatile u8*) 0x2e)
#define SPCR	*((volatile u8*) 0x2d)
#endif

#endif /* SPI_PRIV_H_ */
