/*
 * SPI_Config.c
 *
 *  Created on: Oct 30, 2021
 *  Author: 	 Hamdy Aouf
 *	Description: Here is the configuration object helper to use in initialization
 */

#include "SPI_config.h"

SPI_Cfg_t SPI_Configs = {
		.ClockRate 		= SPI_NormalSpeedPRES_64,
		.OperatingMode 	= SPI_Master,
		.DataOrder 		= SPI_MSB,
		.PhasePolarityCfg = SPI_SampleAtRisingSetupAtFalling,
};
