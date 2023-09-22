/*
 * TWI_Config.c
 *
 *  Created on:  Nov 13, 2021
 *  Author: 	 Hamdy Aouf
 *	Description: Here is the configuration object helper to use in initialization
 */
#include "TWI_Config.h"

TWI_Cfg_t TWI_Configs ={
	.Mode = TWI_MasterTransmitter,
	.NodeAddrress = 5, // set it to slave address in case mode is slave and if master its value do NOT care
	.ClockSpeedKHz = 100,
	.Prescaler = TWI_Pres_1,
	.IsEnabled = true,
};


