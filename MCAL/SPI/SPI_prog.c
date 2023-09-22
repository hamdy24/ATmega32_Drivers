/*
 * SPI_prog.c
 *
 *  Created on: Oct 30, 2021
 *  Author: 	 Hamdy Aouf
 *	Description: Here are all the Interfaces definitions of SPI
 */

#include "SPI_priv.h"

/*	SPCR
 * SPIE		SPE		DORD		MSTR		CPOL			CPHA		SPR1	SPR0
 *	INT		EN	  Data Order	SPI Mode   Clk polarity		Clk Phase	  Clk Rate
 *	SPSR
 *	Double speed by SPI2X Bit
 */
ES_t SPI_enuInit(SPI_Cfg_t * Copy_pstrSPI_Config)
{
	ES_t Local_enuErorrState = ES_NOK;

	switch(Copy_pstrSPI_Config->OperatingMode){
	case SPI_Master:
		SPCR |=  (MASK_BIT<<MSTR);
		break;
	case SPI_Slave:
		SPCR &= ~(MASK_BIT<<MSTR);
		break;
	default:
		Local_enuErorrState = ES_OUT_OF_RANGE;
	}
	if(ES_OUT_OF_RANGE != Local_enuErorrState){

		switch(Copy_pstrSPI_Config->ClockRate){
		case SPI_NormalSpeedPRES_4:
			SPSR &= ~(MASK_BIT<<SPI2X);// for the normal speed operation

			SPCR &= ~(MASK_BIT<<SPR0); // to select the clock rate
			SPCR &= ~(MASK_BIT<<SPR1);
			break;
		case SPI_NormalSpeedPRES_16:
			SPSR &= ~(MASK_BIT<<SPI2X);

			SPCR |=  (MASK_BIT<<SPR0);
			SPCR &= ~(MASK_BIT<<SPR1);
			break;
		case SPI_NormalSpeedPRES_64:
			SPSR &= ~(MASK_BIT<<SPI2X);

			SPCR &= ~(MASK_BIT<<SPR0);
			SPCR |=  (MASK_BIT<<SPR1);
			break;
		case SPI_NormalSpeedPRES_128:
			SPSR &= ~(MASK_BIT<<SPI2X);

			SPCR |=  (MASK_BIT<<SPR0);
			SPCR |=  (MASK_BIT<<SPR1);
			break;
		case SPI_DoubleSpeedPRES_2:
			SPSR |=  (MASK_BIT<<SPI2X);

			SPCR &= ~(MASK_BIT<<SPR0);
			SPCR &= ~(MASK_BIT<<SPR1);
		break;
		case SPI_DoubleSpeedPRES_8:
			SPSR |=  (MASK_BIT<<SPI2X);

			SPCR |=  (MASK_BIT<<SPR0);
			SPCR &= ~(MASK_BIT<<SPR1);
		break;
		case SPI_DoubleSpeedPRES_32:
			SPSR |=  (MASK_BIT<<SPI2X);

			SPCR &= ~(MASK_BIT<<SPR0);
			SPCR |=  (MASK_BIT<<SPR1);
		break;
		case SPI_DoubleSpeedPRES_64:
			SPSR |=  (MASK_BIT<<SPI2X);

			SPCR |=  (MASK_BIT<<SPR0);
			SPCR |=  (MASK_BIT<<SPR1);
		break;
		default:
			Local_enuErorrState = ES_OUT_OF_RANGE;
			break;
		}
		if(ES_OUT_OF_RANGE != Local_enuErorrState){

			switch(Copy_pstrSPI_Config->DataOrder){
			case SPI_MSB:
				SPCR &= ~(MASK_BIT<<DORD);
				break;
			case SPI_LSB:
				SPCR |=  (MASK_BIT<<DORD);
				break;
			default:
				Local_enuErorrState = ES_OUT_OF_RANGE;
				break;
			}
			if(ES_OUT_OF_RANGE != Local_enuErorrState){

				switch(Copy_pstrSPI_Config->PhasePolarityCfg){
				case SPI_SampleAtRisingSetupAtFalling:
					SPCR &= ~(MASK_BIT<<CPOL);
					SPCR &= ~(MASK_BIT<<CPHA);
					break;
				case SPI_SetupAtRisingSampleAtFalling:
					SPCR |=  (MASK_BIT<<CPOL);
					SPCR &= ~(MASK_BIT<<CPHA);
					break;
				case SPI_SampleAtFallingSetupAtRising:
					SPCR &= ~(MASK_BIT<<CPOL);
					SPCR |=  (MASK_BIT<<CPHA);

					break;
				case SPI_SetupAtFallingSampleAtRising:
					SPCR |=  (MASK_BIT<<CPOL);
					SPCR |=  (MASK_BIT<<CPHA);
					break;
				default:
					Local_enuErorrState = ES_OUT_OF_RANGE;
				}
			}
		}
	}
	if(ES_OUT_OF_RANGE != Local_enuErorrState){	//After all previous end success >>> Enable SPI and disable SPI Interrupt
		SPCR &= ~(MASK_BIT<<SPIE);
		SPCR |=  (MASK_BIT<<SPE);
		Local_enuErorrState = ES_OK;
	}
	return Local_enuErorrState;
}

ES_t SPI_enuTranscieve(u8 Copy_u8DataSent, u8 * Copy_pu8DataRecieved,bool Copy_enuIsBlocking)
{
	ES_t Local_enuErorrState = ES_NOK;
	if(Copy_u8DataSent <=255 && Copy_u8DataSent>=0){
		SPDR = Copy_u8DataSent;
		//check for write collision if exist return NOK
		if((SPSR & (MASK_BIT<<WCOL)) != 0){
			Local_enuErorrState = ES_NOK;
			return Local_enuErorrState;
		}
		//check if we should block till data transfer complete or not
		if(true == Copy_enuIsBlocking){
			while(!( (SPSR>>SPIF)&MASK_BIT) );
		}
		//check for pointer then return the data into it
		if(NULL != Copy_pu8DataRecieved){
			*Copy_pu8DataRecieved = SPDR;
			Local_enuErorrState = ES_OK;
		}
		else{
			Local_enuErorrState = ES_POINTER_TO_VOID;
		}
	}else{
		Local_enuErorrState = ES_OUT_OF_RANGE;
	}

	return Local_enuErorrState;
}
ES_t SPI_enuSetSPI_Mode(SPI_Mode_enuType Copy_enuOperatingMode){
	ES_t Local_enuErorrState = ES_NOK;
	switch(Copy_enuOperatingMode){
	case SPI_Master:
		SPCR |=  (MASK_BIT<<MSTR);
		Local_enuErorrState = ES_OK;
		break;
	case SPI_Slave:
		SPCR &= ~(MASK_BIT<<MSTR);
		Local_enuErorrState = ES_OK;
		break;
	default:
		Local_enuErorrState = ES_OUT_OF_RANGE;
	}

	return Local_enuErorrState;
}
ES_t SPI_enuSetClockRate(SPI_PRES_enuType Copy_enuClockRate){
	ES_t Local_enuErorrState = ES_NOK;
	switch(Copy_enuClockRate){
	case SPI_NormalSpeedPRES_4:
		SPSR &= ~(MASK_BIT<<SPI2X);// for the normal speed operation

		SPCR &= ~(MASK_BIT<<SPR0); // to select the clock rate
		SPCR &= ~(MASK_BIT<<SPR1);
		break;
	case SPI_NormalSpeedPRES_16:
		SPSR &= ~(MASK_BIT<<SPI2X);

		SPCR |=  (MASK_BIT<<SPR0);
		SPCR &= ~(MASK_BIT<<SPR1);
		break;
	case SPI_NormalSpeedPRES_64:
		SPSR &= ~(MASK_BIT<<SPI2X);

		SPCR &= ~(MASK_BIT<<SPR0);
		SPCR |=  (MASK_BIT<<SPR1);
		break;
	case SPI_NormalSpeedPRES_128:
		SPSR &= ~(MASK_BIT<<SPI2X);

		SPCR |=  (MASK_BIT<<SPR0);
		SPCR |=  (MASK_BIT<<SPR1);
		break;
	case SPI_DoubleSpeedPRES_2:
		SPSR |=  (MASK_BIT<<SPI2X);

		SPCR &= ~(MASK_BIT<<SPR0);
		SPCR &= ~(MASK_BIT<<SPR1);
	break;
	case SPI_DoubleSpeedPRES_8:
		SPSR |=  (MASK_BIT<<SPI2X);

		SPCR |=  (MASK_BIT<<SPR0);
		SPCR &= ~(MASK_BIT<<SPR1);
	break;
	case SPI_DoubleSpeedPRES_32:
		SPSR |=  (MASK_BIT<<SPI2X);

		SPCR &= ~(MASK_BIT<<SPR0);
		SPCR |=  (MASK_BIT<<SPR1);
	break;
	case SPI_DoubleSpeedPRES_64:
		SPSR |=  (MASK_BIT<<SPI2X);

		SPCR |=  (MASK_BIT<<SPR0);
		SPCR |=  (MASK_BIT<<SPR1);
	break;
	default:
		Local_enuErorrState = ES_OUT_OF_RANGE;
		break;
	}

	if(ES_OUT_OF_RANGE != Local_enuErorrState){
		Local_enuErorrState = ES_OK;
	}

	return Local_enuErorrState;
}
ES_t SPI_enuSetDataTransferOrder(SPI_DataOrder_enuType Copy_enuDataOrder){
	ES_t Local_enuErorrState = ES_NOK;
	switch(Copy_enuDataOrder){
	case SPI_MSB:
		SPCR &= ~(MASK_BIT<<DORD);
		Local_enuErorrState = ES_OK;
		break;
	case SPI_LSB:
		SPCR |=  (MASK_BIT<<DORD);
		Local_enuErorrState = ES_OK;
		break;
	default:
		Local_enuErorrState = ES_OUT_OF_RANGE;
		break;
	}

	return Local_enuErorrState;
}
ES_t SPI_enuSetPhasePolarityMode(SPI_PolarityPhase_enuType	Copy_enuPhasePolarityCfg){
	ES_t Local_enuErorrState = ES_NOK;

	switch(Copy_enuPhasePolarityCfg){
	case SPI_SampleAtRisingSetupAtFalling:
		SPCR &= ~(MASK_BIT<<CPOL);
		SPCR &= ~(MASK_BIT<<CPHA);
		break;
	case SPI_SetupAtRisingSampleAtFalling:
		SPCR |=  (MASK_BIT<<CPOL);
		SPCR &= ~(MASK_BIT<<CPHA);
		break;
	case SPI_SampleAtFallingSetupAtRising:
		SPCR &= ~(MASK_BIT<<CPOL);
		SPCR |=  (MASK_BIT<<CPHA);

		break;
	case SPI_SetupAtFallingSampleAtRising:
		SPCR |=  (MASK_BIT<<CPOL);
		SPCR |=  (MASK_BIT<<CPHA);
		break;
	default:
		Local_enuErorrState = ES_OUT_OF_RANGE;
	}
	if(ES_OUT_OF_RANGE != Local_enuErorrState){
		Local_enuErorrState = ES_OK;
	}
	return Local_enuErorrState;
}

ES_t SPI_enuSetInterrupt_Enable(bool Copy_enuIsEnabled){
	ES_t Local_enuErorrState = ES_NOK;
	if(true == Copy_enuIsEnabled){
		SPCR |=  (MASK_BIT<<SPIE);
	}
	else if(false == Copy_enuIsEnabled){
		SPCR &= ~(MASK_BIT<<SPIE);
	}
	return Local_enuErorrState;
}
ES_t SPI_enuSetSPI_Enable(bool Copy_enuIsEnabled){
	ES_t Local_enuErorrState = ES_NOK;
	if(true == Copy_enuIsEnabled){
		SPCR |=  (MASK_BIT<<SPE);
	}
	else if(false == Copy_enuIsEnabled){
		SPCR &= ~(MASK_BIT<<SPE);
	}
	return Local_enuErorrState;
}

ES_t SPI_enuCallBack(CallBackFunc_t Copy_pfun_AppFun){
	ES_t Local_enuErorrState = ES_NOK;

	if(NULL != Copy_pfun_AppFun){
		SPI_pfunISR_Func = Copy_pfun_AppFun;
		Local_enuErorrState = ES_OK;
	}
	else{
		Local_enuErorrState = ES_POINTER_TO_VOID;
	}

	return Local_enuErorrState;
}

ISR(VECT_SPI_TRANSFER){
	if(NULL != SPI_pfunISR_Func){
		SPI_pfunISR_Func();
	}
}
