/*
 * HCLCD_Program.c
 *
 *  Created on: Jan 21, 2022
 *      Author: gerges
 */


#include"../../LIB/LSTD_TYPES.h"
#include"../../MCAL/MDIO/MDIO_Interface.h"
#include"HCLCD_Private.h"
#include"HCLCD_Config.h"
#define F_CPU   16000000UL
#include"util/delay.h"

void HAL_VidHCLCD_4BitModeWriteCommand(uint8 Copy_uint8Command)
{
	/*Select Command Register-->LOW*/
	MDIO_Errorstate_SetPinValue(HCLCD_ControlPort,RS_PIN,PIN_LOW);
	/*Select Write Mode*/
	MDIO_Errorstate_SetPinValue(HCLCD_ControlPort,RW_PIN,PIN_LOW);
	/*Send Command*/
	MDIO_Errorstate_Set4MostBits(HCLCD_DataPort,Copy_uint8Command);
	/*LCD Enable*/
	MDIO_Errorstate_SetPinValue(HCLCD_ControlPort,E_PIN,PIN_HIGH);
	_delay_ms(2);
	MDIO_Errorstate_SetPinValue(HCLCD_ControlPort,E_PIN,PIN_LOW);
}
void HAL_VidHCLCD_4BitModeWriteChar(uint8 Copy_uint8Char)
{
	/*Select Data Register-->HIGH*/
	MDIO_Errorstate_SetPinValue(HCLCD_ControlPort,RS_PIN,PIN_HIGH);
	/*Select Write Mode*/
	MDIO_Errorstate_SetPinValue(HCLCD_ControlPort,RW_PIN,PIN_LOW);
	/*Send 4 Most Bits of Data*/
	MDIO_Errorstate_Set4MostBits(HCLCD_DataPort,(Copy_uint8Char&0xF0));
	/*LCD Enable*/
	MDIO_Errorstate_SetPinValue(HCLCD_ControlPort,E_PIN,PIN_HIGH);
	_delay_ms(2);
	MDIO_Errorstate_SetPinValue(HCLCD_ControlPort,E_PIN,PIN_LOW);
	/*Send 4 Least Bits of Data*/
	MDIO_Errorstate_Set4MostBits(HCLCD_DataPort,(Copy_uint8Char<<4));
	/*LCD Enable*/
	MDIO_Errorstate_SetPinValue(HCLCD_ControlPort,E_PIN,PIN_HIGH);
	_delay_ms(2);
	MDIO_Errorstate_SetPinValue(HCLCD_ControlPort,E_PIN,PIN_LOW);
}
void HAL_VidHCLCD_4BitModeInit(void)
{
	/*Wait 30ms*/
	_delay_ms(30);
	/*send Function set command*/
	HAL_VidHCLCD_4BitModeWriteCommand((SET_FUNCTIONSET&0xF0));
	HAL_VidHCLCD_4BitModeWriteCommand((SET_FUNCTIONSET&0xF0));
	HAL_VidHCLCD_4BitModeWriteCommand((uint8)(SET_FUNCTIONSET<<4));
	_delay_ms(1);
	/*Send Display on off command*/
	HAL_VidHCLCD_4BitModeWriteCommand((SET_DISPLAYON_OFF&0xF0));
	HAL_VidHCLCD_4BitModeWriteCommand((SET_DISPLAYON_OFF<<4));
	_delay_ms(1);
	/*Send Display Clear command*/
	HAL_VidHCLCD_4BitModeWriteCommand((SET_DISPALYCLEAR&0xF0));
	HAL_VidHCLCD_4BitModeWriteCommand((SET_DISPALYCLEAR<<4));
	_delay_ms(2);
	/*Send Entry Mode command*/
	HAL_VidHCLCD_4BitModeWriteCommand((SET_ENTRYMODE&0xF0));
	HAL_VidHCLCD_4BitModeWriteCommand((SET_ENTRYMODE<<4));
}
void HAL_VidHCLCD_4BitModeSendCommand(uint8 Copy_uint8Command)
{
	HAL_VidHCLCD_4BitModeWriteCommand((Copy_uint8Command&0xF0));
	HAL_VidHCLCD_4BitModeWriteCommand((Copy_uint8Command<<4));
}
/*AMIT'\0'*/
void HAL_VidHCLCD_4BitModeWriteString(uint8 *Copy_uint8String)
{
	uint8 Loc_uint8Count=0;
	while(Copy_uint8String[Loc_uint8Count]!='\0')
	{
		HAL_VidHCLCD_4BitModeWriteChar(Copy_uint8String[Loc_uint8Count]);
		Loc_uint8Count++;
	}
}
/*1234*/
void HAL_VidHCLCD_4BitModeWriteNumber(uint32 Copy_uint32Number)
{
	uint8 Loc_uint8Digits[16];
	sint8 Loc_sint8Count=0;

	if(Copy_uint32Number==0)
	{
		HAL_VidHCLCD_4BitModeWriteChar(0+48);
	}
	else
	{
		while(Copy_uint32Number!=0)
		{
			Loc_uint8Digits[Loc_sint8Count]=Copy_uint32Number%10;
			Copy_uint32Number/=10;
			Loc_sint8Count++;
		}
		Loc_sint8Count-=1;
		while(Loc_sint8Count>=0)
		{
			HAL_VidHCLCD_4BitModeWriteChar(Loc_uint8Digits[Loc_sint8Count]+48);
			Loc_sint8Count--;
		}
	}
}
void HAL_VidHCLCD_4BitModeSetPosition(uint8 Copy_uint8LineNum,uint8 Copy_uint8Position)
{
	if(Copy_uint8LineNum==1)
	{
		HAL_VidHCLCD_4BitModeSendCommand(128+Copy_uint8Position);
	}
	else if(Copy_uint8LineNum==2)
	{
		HAL_VidHCLCD_4BitModeSendCommand(192+Copy_uint8Position);
	}
	else
	{
		/*Do Nothing*/
	}
}
