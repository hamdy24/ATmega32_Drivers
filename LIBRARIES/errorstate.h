/*
 * errorstate.h
 *
 *  Created on: Sep 28, 2021
 *      Author: hamdy
 */

#ifndef ERRORSTATE_H_
#define ERRORSTATE_H_


typedef enum {
	ES_NOK ,
	ES_OK ,
	ES_OUT_OF_RANGE ,
	ES_POINTER_TO_VOID,
	ES_TWI_ERROR,
}ES_t;


#endif /* ERRORSTATE_H_ */
