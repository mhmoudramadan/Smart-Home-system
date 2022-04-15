/*
 * HTEMPERATURE_Program.c
 *
 *  Created on: Mar 21, 2022
 *      Author: Dell
 */

#include"../../LIb/LSTD_TYPES.h"
#include"../../MCAL/MDIO/MDIO_Interface.h"
#include"../../MCAL/MADC/MADC_Interface.h"
#include"HTEMPERATURE_Interface.h"

void HTEMP_VidInit(void)
{
	MADC_VidSingleConversion_Init();
}

uint8 HTEMP_uintGetTemp(uint8 copy_uint8Channel)
{
	MADC_VidADCStartSingleConversion(copy_uint8Channel);
	uint16 Loc_AnalogValueMV=0;
	uint32 Loc_DigitalValue=0;
	uint16 Loc_TemperatureValue=0;
	Loc_DigitalValue = MADC_uint16Read();
	Loc_AnalogValueMV=(Loc_DigitalValue*5000) / (1024);
	Loc_TemperatureValue=Loc_AnalogValueMV / (10);
	return Loc_TemperatureValue;
}

