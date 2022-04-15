/*
 * HKPD_Program.c
 *
 *  Created on: Jan 22, 2022
 *      Author: Dell
 */

#include"../../LIB/LSTD_TYPES.h"
#include"../../MCAL/MDIO/MDIO_Interface.h"
#include"HKPD_Private.h"
#include"HKPD_Config.h"
#define F_CPU 16000000UL
#include <util/delay.h>
uint8 KPD_uint8Values[4][4]={
		{
				'7',
				'4',
				'1',
				'c'
		},
		{
				'8',
				'5',
				'2',
				'0'
		},
		{
				'9',
				'6',
				'3',
				'#'
		},
		{
				'/',
				'*',
				'-',
				'+'
		}
};
/* keypad init */
void HKPD_VidInit(void)
{
	/*Set Row PINS AS AN inPUT*/
	MDIO_Errorstate_SetPinDirection(HKPD_ROWPORT,HKPD_ROWPIN0,PIN_INPUT);
	MDIO_Errorstate_SetPinDirection(HKPD_ROWPORT,HKPD_ROWPIN1,PIN_INPUT);
	MDIO_Errorstate_SetPinDirection(HKPD_ROWPORT,HKPD_ROWPIN2,PIN_INPUT);
	MDIO_Errorstate_SetPinDirection(HKPD_ROWPORT,HKPD_ROWPIN3,PIN_INPUT);

	/*Active internal  PULL UP RESISTOR for Row PINS*/
	MDIO_Errorstate_SetPinValue(HKPD_ROWPORT,HKPD_ROWPIN0,PIN_HIGH);
	MDIO_Errorstate_SetPinValue(HKPD_ROWPORT,HKPD_ROWPIN1,PIN_HIGH);
	MDIO_Errorstate_SetPinValue(HKPD_ROWPORT,HKPD_ROWPIN2,PIN_HIGH);
	MDIO_Errorstate_SetPinValue(HKPD_ROWPORT,HKPD_ROWPIN3,PIN_HIGH);

	/*Set COLOUM PINS AS AN OUTPUTS*/
	MDIO_Errorstate_SetPinDirection(HKPD_COLPORT,HKPD_COLPIN0,PIN_OUTPUT);
	MDIO_Errorstate_SetPinDirection(HKPD_COLPORT,HKPD_COLPIN1,PIN_OUTPUT);
	MDIO_Errorstate_SetPinDirection(HKPD_COLPORT,HKPD_COLPIN2,PIN_OUTPUT);
	MDIO_Errorstate_SetPinDirection(HKPD_COLPORT,HKPD_COLPIN3,PIN_OUTPUT);

	/* Set COLOUM PINS initial value --> one*/
	MDIO_Errorstate_SetPinValue(HKPD_COLPORT,HKPD_COLPIN0,PIN_HIGH);
	MDIO_Errorstate_SetPinValue(HKPD_COLPORT,HKPD_COLPIN1,PIN_HIGH);
	MDIO_Errorstate_SetPinValue(HKPD_COLPORT,HKPD_COLPIN2,PIN_HIGH);
	MDIO_Errorstate_SetPinValue(HKPD_COLPORT,HKPD_COLPIN3,PIN_HIGH);
}

  /* keypad pressed */

uint8 HKPD_uint8GetPressed(void)
{
	uint8 Loc_uint8ColCount=0;
	uint8 Loc_uint8RowCount=0;
	uint8 Loc_uint8KeyState;
	uint8 Loc_uint8KeyValue=HKPD_NOTPRESSED;

	for(Loc_uint8ColCount=HKPD_COLINIT ; Loc_uint8ColCount<HKPD_COLEND; Loc_uint8ColCount++)
	{
		/*Select COLOUM*/

		MDIO_Errorstate_SetPinValue(HKPD_COLPORT,Loc_uint8ColCount,PIN_LOW);

		/*select row*/

		for(Loc_uint8RowCount=HKPD_ROWINIT;Loc_uint8RowCount<HKPD_ROWEND;Loc_uint8RowCount++)
		{
			MDIO_Errorstate_GetPinValue(HKPD_ROWPORT,Loc_uint8RowCount,&Loc_uint8KeyState);

			if(Loc_uint8KeyState==0)
			{
				Loc_uint8KeyValue=KPD_uint8Values[Loc_uint8ColCount-HKPD_COLINIT][Loc_uint8RowCount-HKPD_ROWINIT];
			}
			else
			{
				/*Do Nothing*/
			}

			/* DE_POuncing*/
			_delay_ms(20);

			/*to do one press*/
			while(Loc_uint8KeyState==0)
			{
				MDIO_Errorstate_GetPinValue(HKPD_ROWPORT,Loc_uint8RowCount,&Loc_uint8KeyState);
			}
		}

		/*DE_Activate for coloum*/

		MDIO_Errorstate_SetPinValue(HKPD_COLPORT,Loc_uint8ColCount,PIN_HIGH);
	}
	return Loc_uint8KeyValue;
}

