/*
 * SPI_config.h
 *
 *  Created on: Oct 30, 2021
 *  Author: 	 Hamdy Aouf
 *	Description: File of all needed parameters or configurations would be used to control the SPI
 */

#ifndef SPI_CONFIG_H_
#define SPI_CONFIG_H_



typedef enum{
	/*Select SPI Mode*/
	SPI_Slave,
	SPI_Master,
}SPI_Mode_enuType;

typedef enum{
	/*Select which bit to transmit first*/
	SPI_MSB,
	SPI_LSB,
}SPI_DataOrder_enuType;

typedef enum{
	SPI_SampleAtRisingSetupAtFalling,
	SPI_SetupAtRisingSampleAtFalling,
	SPI_SampleAtFallingSetupAtRising,
	SPI_SetupAtFallingSampleAtRising,
}SPI_PolarityPhase_enuType;
//SPI_SampleAtRising	00
//SPI_SetupAtRising		01
//SPI_SampleAtFalling	10
//SPI_SetupAtFalling	11
typedef enum{
	/* The Following are when the speed is normal*/
	SPI_NormalSpeedPRES_4,
	SPI_NormalSpeedPRES_16,
	SPI_NormalSpeedPRES_64,
	SPI_NormalSpeedPRES_128,
	/* The Following are when the speed is doubled*/
	SPI_DoubleSpeedPRES_2,
	SPI_DoubleSpeedPRES_8,
	SPI_DoubleSpeedPRES_32,
	SPI_DoubleSpeedPRES_64,
}SPI_PRES_enuType;


typedef struct{
	SPI_PRES_enuType 			ClockRate:3;
	SPI_Mode_enuType 			OperatingMode:1;
	SPI_DataOrder_enuType 		DataOrder:1;
	SPI_PolarityPhase_enuType	PhasePolarityCfg:2;
}SPI_Cfg_t;


#endif /* SPI_CONFIG_H_ */
