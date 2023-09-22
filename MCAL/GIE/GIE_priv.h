/*
 * GIE_priv.h
 *
 *  Created on: Oct 30, 2021
 *  Author: 	 Hamdy Aouf
 *	Description: Here are private macros and declarations related to the GIE
 */

#ifndef MCAL_GIE_GIE_PRIV_H_
#define MCAL_GIE_GIE_PRIV_H_

#include "../../LIBRARIES/stdTypes.h"
#include "../../LIBRARIES/errorstate.h"
#include "../../LIBRARIES/common.h"


#include "../AVR_REG.H"

#define	GIE_BIT_EN		7


#ifndef	MCAL_AVR_REG_H_
#define SREG	*((volatile u8*)(0x5F))
#endif

#endif /* MCAL_GIE_GIE_PRIV_H_ */
