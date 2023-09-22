/*
 * common.h
 *
 *      Created on: Oct 13, 2021
 *      Author: hamdy
 */

#ifndef LIBRARIES_COMMON_H_
#define LIBRARIES_COMMON_H_


#ifndef F_CPU
#define F_CPU					16000000
#endif


#define MAP_X_TO_Y(VAL,OLD_MIN,OLD_MAX,NEW_MIN,NEW_MAX)	((f32)((OLD_MIN-NEW_MAX*VAL)+(f32)((f32)(VAL-OLD_MAX)*NEW_MIN))/(OLD_MIN-OLD_MAX))

/***************************************************************************************************
                                Macros for Bit Manipulation
 ****************************************************************************************************/

#define MASK_BIT			  			1

#define GET_BIT_MSK(BIT)          		(MASK_BIT<<(BIT))
#define SET_BIT(REG,BIT)          		((REG) |=  GET_BIT_MSK(BIT))
#define CLR_BIT(REG,BIT)          		((REG) &= ~GET_BIT_MSK(BIT))
#define TOG_BIT(REG,BIT)         		((REG) ^=  GET_BIT_MSK(BIT))


#define IS_BIT_SET(REG,BIT)          	(((REG)&(GET_BIT_MSK(BIT)))!=0u)
#define IS_BIT_CLEARED(REG,BIT)      	(((REG)&(GET_BIT_MSK(BIT)))==0u)

/**************************************************************************************************/


#endif /* LIBRARIES_COMMON_H_ */
