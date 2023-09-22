/*
 * TWI_Program.c
 *
 *  Created on:  Nov 13, 2021
 *  Author: 	 Hamdy Aouf
 *	Description: Here are all the Interfaces definitions of the Two Wire Interface
 */

#include "TWI_Private.h"

/*
 * TWCR Watch Window
 *
 *	TWINT 	TWEA 	TWSTA 	TWSTO 	TWWC 	TWEN 	– 	TWIE
 */
ES_t TWI_enuInit(TWI_Cfg_t * Copy_pstrTWI_Configs){
	ES_t Local_enuErorrState = ES_NOK;
	if(true == Copy_pstrTWI_Configs->IsEnabled){

		// only if it is master mode >> setup the Prescaler and speed
		if(TWI_MasterTransmitter == Copy_pstrTWI_Configs->Mode  || TWI_MasterReciever == Copy_pstrTWI_Configs->Mode ){
			/** Check if PRES is valid then adjust the PRES and The Speed **/
			if(Copy_pstrTWI_Configs->Prescaler >=TWI_Pres_1 && Copy_pstrTWI_Configs->Prescaler <= TWI_Pres_64){
				/** PRES **/
				TWSR &= PRES_BITS_MASK;
				TWSR |= (Copy_pstrTWI_Configs->Prescaler<<TWPS0);
				/** Speed **/
				TWBR = (u8)((u16)(F_CPU-16ul*Copy_pstrTWI_Configs->ClockSpeedKHz*1000)/((u16)2*Copy_pstrTWI_Configs->ClockSpeedKHz*1000*TWI_Prescalers[Copy_pstrTWI_Configs->Prescaler] ));

				TWBR=(u8) (((F_CPU/Copy_pstrTWI_Configs->ClockSpeedKHz*1000)-16ul) / (2ul*TWI_Prescalers[Copy_pstrTWI_Configs->Prescaler]));
			}
			else {
				Local_enuErorrState = ES_OUT_OF_RANGE;
			}
		}
		// in case of being slave and the configured address is not the general call
		// then set the slave node address
		if(0 < Copy_pstrTWI_Configs->NodeAddrress){
			switch(Copy_pstrTWI_Configs->Mode){
			case TWI_SlaveTransmitter:
				TWAR = (Copy_pstrTWI_Configs->NodeAddrress << TWA0) | TWI_Write;
				break;
			case TWI_SlaveReciever:
				TWAR = (Copy_pstrTWI_Configs->NodeAddrress << TWA0) | TWI_Read;
				break;
			}

		}
		// interrupt disabled
		TWCR |=  (MASK_BIT << TWIE);
		// Enable ACK
		TWCR |=  (MASK_BIT << TWEA);
		// TWI enabled
		TWCR |=  (MASK_BIT << TWEN);
	}
	else{
		 TWCR &=  ~(MASK_BIT << TWEN);
	}

	return Local_enuErorrState;
}
ES_t TWI_enuSetSpeed_inKHz(TWI_Pres_t Copy_enuPrescaler,u16 Copy_enuClockSpeed_inKHz){
	ES_t Local_enuErorrState = ES_OK;

	TWSR &= PRES_BITS_MASK;
	TWSR |= (Copy_enuPrescaler<<TWPS0);
	TWBR = ((F_CPU-16ul*Copy_enuClockSpeed_inKHz)/(2ul*Copy_enuClockSpeed_inKHz*TWI_Prescalers[Copy_enuPrescaler] ));

	return Local_enuErorrState;
}
ES_t TWI_enuActivateTWI(bool Copy_enuIsEnabled){
	ES_t Local_enuErorrState = ES_OK;

	if(Copy_enuIsEnabled == true){
		TWCR |=  (MASK_BIT << TWEN);
	}else if(Copy_enuIsEnabled == false){
		TWCR &= ~(MASK_BIT << TWEN);
	}else{
		Local_enuErorrState = ES_OUT_OF_RANGE;
	}

	return Local_enuErorrState;
}
ES_t TWI_enuSendStartCondition(void){
	ES_t Local_enuErorrState = ES_NOK;

	TWCR |= (MASK_BIT<<TWINT);
	TWCR |= (MASK_BIT<<TWSTA);
	TWCR |= (MASK_BIT<<TWEN);
	while(!( (TWCR>>TWINT) & MASK_BIT));
	if(STATUS_CODE_VALUE == Code_StartCondition_Sent){
		Local_enuErorrState = ES_OK;
	}else{
		Local_enuErorrState = ES_TWI_ERROR;
	}
	return Local_enuErorrState;
}
ES_t TWI_enuSendRepeatedStartCond(void){
	ES_t Local_enuErorrState = ES_NOK;

	TWCR |= (MASK_BIT<<TWINT);
	TWCR |= (MASK_BIT<<TWSTA);
	TWCR |= (MASK_BIT<<TWEN);
	while(!( (TWCR>>TWINT) & MASK_BIT));
	if(STATUS_CODE_VALUE == Code_RepeatedStart_Sent){
		Local_enuErorrState = ES_OK;
	}else{
		Local_enuErorrState = ES_TWI_ERROR;
	}
	return Local_enuErorrState;
}
ES_t TWI_enuSendStopCondition(void){
	ES_t Local_enuErorrState = ES_NOK;

	TWCR |= (MASK_BIT<<TWINT);
	TWCR |= (MASK_BIT<<TWSTO);
	TWCR |= (MASK_BIT<<TWEN);
	while(!( (TWCR<<TWINT) & MASK_BIT));
		Local_enuErorrState = ES_OK;

	return Local_enuErorrState;
}
ES_t TWI_enuSetSlaveAddress_WithOperation(u8 Copy_u8SlaveAddress,TWI_Operation_t Copy_enuOperation){
	ES_t Local_enuErorrState = ES_NOK;
	if((Copy_u8SlaveAddress <= 127) && (Copy_enuOperation == TWI_Read || Copy_enuOperation == TWI_Write) ){ //address and operation check

		TWDR = (Copy_u8SlaveAddress<<TWD1) | (Copy_enuOperation);
		TWCR |= (MASK_BIT<<TWINT); // clear the TWI flag
		TWCR |= (MASK_BIT<<TWEN);  // start last operation
		while(!( (TWCR>>TWINT) & MASK_BIT)); //wait till operation is finished
		//check if operation finished successfully or not
		if( (STATUS_CODE_VALUE == Code_Slave_W_WithACK_Sent)  && Copy_enuOperation == TWI_Write ){

			Local_enuErorrState = ES_OK;

		}else if((STATUS_CODE_VALUE == Code_Slave_W_NoACK_Sent) && Copy_enuOperation == TWI_Write){

			Local_enuErorrState = ES_OK;
		}else if((STATUS_CODE_VALUE == Code_Slave_R_WithACK_Sent) && Copy_enuOperation == TWI_Read){

			Local_enuErorrState = ES_OK;
		}
		else{
			Local_enuErorrState = ES_TWI_ERROR;
		}
	}
	else {
		Local_enuErorrState = ES_OUT_OF_RANGE;
	}

	return Local_enuErorrState;
}
ES_t TWI_enuCheckForOwnCall(bool * Copy_penuIsCalled){
	ES_t Local_enuErorrState = ES_NOK;

	//enable acknowledge // clear flag
	TWCR |= (MASK_BIT<<TWEA) | (MASK_BIT<<TWINT) | (MASK_BIT<<TWEN);
	// wait till operation done
	while(!( (TWCR>>TWINT) & MASK_BIT));

	if(STATUS_CODE_VALUE == Code_Own_Slave_R_WithACK_Received){

		Local_enuErorrState = ES_OK;

	}else if(STATUS_CODE_VALUE == Code_Own_Slave_W_WithACK_Received){

		Local_enuErorrState = ES_OK;
	}
	else{
		Local_enuErorrState = ES_TWI_ERROR;
	}
	return Local_enuErorrState;
}
ES_t TWI_enuWriteByte(u8 Copy_u8Data){
	ES_t Local_enuErorrState = ES_NOK;
	TWDR = Copy_u8Data;

	TWCR |= (MASK_BIT<<TWINT); // clear the TWI flag
	TWCR |= (MASK_BIT<<TWEN);  // start last operation
	// wait till operation done
	while(!( (TWCR>>TWINT) & MASK_BIT));

	if(STATUS_CODE_VALUE == Code_Data_WithACK_Sent){
		Local_enuErorrState = ES_OK;

	}else if(STATUS_CODE_VALUE == Code_Data_WithACK_Transmitted){

		Local_enuErorrState = ES_OK;
	}
	else{
		Local_enuErorrState = ES_TWI_ERROR;
	}
	return Local_enuErorrState;
}
ES_t TWI_enuReadByte(u8 * Copy_pu8Data){
	ES_t Local_enuErorrState = ES_NOK;

	// clear flag	// start write operation
	TWCR = (MASK_BIT<<TWINT) | (MASK_BIT<<TWEN);
	// wait till operation done
	while(!( (TWCR>>TWINT) & MASK_BIT));

	if(STATUS_CODE_VALUE == Code_Data_WithACK_Received){

		*Copy_pu8Data = TWDR;
		Local_enuErorrState = ES_OK;
	}
	else{
		Local_enuErorrState = ES_TWI_ERROR;
	}
	return Local_enuErorrState;
}
ES_t TWI_enuACK_EN(bool Copy_enuIsEnabled){
	ES_t Local_enuErorrState = ES_NOK;

	if(Copy_enuIsEnabled == true){
		TWCR |=  (MASK_BIT << TWEA);
	}else if(Copy_enuIsEnabled == false){
		TWCR &= ~(MASK_BIT << TWEA);
	}
	return Local_enuErorrState;
}
ES_t TWI_enuSetInterrupt_EN(bool Copy_enuIsEnabled){
	ES_t Local_enuErorrState = ES_NOK;
	if(Copy_enuIsEnabled == true){
		TWCR |=  (MASK_BIT << TWIE);
	}else if(Copy_enuIsEnabled == false){
		TWCR &= ~(MASK_BIT << TWIE);
	}

	return Local_enuErorrState;
}
ES_t TWI_enuSetAppCallBack(CallBackFunc_t Copy_pfunAppFunc){
	ES_t Local_enuErorrState = ES_NOK;
	if(NULL != Copy_pfunAppFunc){
		TWI_pfunISR_Func = Copy_pfunAppFunc;
	}

	return Local_enuErorrState;
}

ISR(VECT_TWI){
	if(NULL != TWI_pfunISR_Func){
		TWI_pfunISR_Func();
	}
}



