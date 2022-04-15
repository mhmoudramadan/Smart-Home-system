/*
 * MDIO_Program.c
 *
 *  Created on: Jan 15, 2022
 *      Author: Dell
 */

#include "../../LIB/LSTD_TYPES.h"
#include "../../LIB/LBIT_MATH.h"
#include "MDIO_Private.h"
#include "MDIO_Interface.h"

/********* Set pin direction************/

ErrorState MDIO_Errorstate_SetPinDirection (uint8 copy_uint8PortID , uint8 copy_uint8PinNumber,uint8 copy_uint8PinDirection)

{
	ErrorState loc_Errorstate_Error_state = OK;

	if (copy_uint8PinNumber<8)
	{
		if(copy_uint8PinDirection==PIN_OUTPUT)
		{
			switch(copy_uint8PortID)
			{
			case MDIO_PORTA:
				SET_BIT(DDRA,copy_uint8PinNumber);
				break;
			case MDIO_PORTB:
				SET_BIT(DDRB,copy_uint8PinNumber);
				break;
			case MDIO_PORTC:
				SET_BIT(DDRC,copy_uint8PinNumber);
				break;
			case MDIO_PORTD:
				SET_BIT(DDRD,copy_uint8PinNumber);
				break;
			default :
				loc_Errorstate_Error_state=NOK;
				break;
			}
		}

		else if(copy_uint8PinDirection==PIN_INPUT)
		{
			switch(copy_uint8PortID)
			{
			case MDIO_PORTA:
				CLR_BIT(DDRA,copy_uint8PinNumber);
				break;
			case MDIO_PORTB:
				CLR_BIT(DDRB,copy_uint8PinNumber);
				break;
			case MDIO_PORTC:
				CLR_BIT(DDRC,copy_uint8PinNumber);
				break;
			case MDIO_PORTD:
				CLR_BIT(DDRD,copy_uint8PinNumber);
				break;
			default :
				loc_Errorstate_Error_state=NOK;
			}
		}
		else
		{
			loc_Errorstate_Error_state=NOK;
		}
	}
	else
	{
		loc_Errorstate_Error_state=NOK;
	}
	return loc_Errorstate_Error_state ;
}

/********* Set pin value************/
ErrorState MDIO_Errorstate_SetPinValue (uint8 copy_uint8PortID , uint8 copy_uint8PinNumber,uint8 copy_uint8PinValue)
{
	{
		ErrorState loc_Errorstate_Error_state = OK;

		if (copy_uint8PinNumber<8)
		{
			if(copy_uint8PinValue==PIN_HIGH)
			{
				switch(copy_uint8PortID)
				{
				case MDIO_PORTA:
					SET_BIT(PORTA,copy_uint8PinNumber);
					break;
				case MDIO_PORTB:
					SET_BIT(PORTB,copy_uint8PinNumber);
					break;
				case MDIO_PORTC:
					SET_BIT(PORTC,copy_uint8PinNumber);
					break;
				case MDIO_PORTD:
					SET_BIT(PORTD,copy_uint8PinNumber);
					break;
				default :
					loc_Errorstate_Error_state=NOK;

					break;
				}
			}

			else if(copy_uint8PinValue==PIN_LOW)
			{
				switch(copy_uint8PortID)
				{
				case MDIO_PORTA:
					CLR_BIT(PORTA,copy_uint8PinNumber);
					break;
				case MDIO_PORTB:
					CLR_BIT(PORTB,copy_uint8PinNumber);
					break;
				case MDIO_PORTC:
					CLR_BIT(PORTC,copy_uint8PinNumber);
					break;
				case MDIO_PORTD:
					CLR_BIT(PORTD,copy_uint8PinNumber);
					break;
				default :
					loc_Errorstate_Error_state=NOK;
				}
			}
			else
			{
				loc_Errorstate_Error_state=NOK;
			}
		}
		else
		{
			loc_Errorstate_Error_state=NOK;
		}
		return loc_Errorstate_Error_state ;
	}
}


/********* get pin value************/
ErrorState MDIO_Errorstate_GetPinValue (uint8 copy_uint8PortID , uint8 copy_uint8PinNumber,uint8 *puint8PinValue)
{
	ErrorState loc_Errorstate_Error_state = OK;
	if (copy_uint8PinNumber<8)
	{
		switch(copy_uint8PortID)
		{
		case MDIO_PORTA:
			*puint8PinValue= GET_BIT(PINA,copy_uint8PinNumber);
			break;
		case MDIO_PORTB:
			*puint8PinValue=GET_BIT(PINB,copy_uint8PinNumber);
			break;
		case MDIO_PORTC:
			*puint8PinValue=GET_BIT(PINC,copy_uint8PinNumber);
			break;
		case MDIO_PORTD:
			*puint8PinValue=GET_BIT(PIND,copy_uint8PinNumber);
			break;
		default :
			loc_Errorstate_Error_state=NOK;
			break;

		}
	}
	else
	{
		loc_Errorstate_Error_state=NOK;
	}
	return loc_Errorstate_Error_state;
}

/********* set port direction & value************/
ErrorState MDIO_Errorstate_SetPortDirection (uint8 copy_uint8PortID , uint8 copy_uint8PortDirection)
{
	ErrorState loc_Errorstate_Error_state = OK;

	if((copy_uint8PortDirection== PORT_OUTPUT) ||(copy_uint8PortDirection==PORT_INPUT))
	{
		switch(copy_uint8PortID)
		{
		case MDIO_PORTA:
			DDRA=copy_uint8PortDirection;

			break;
		case MDIO_PORTB:
			DDRB=copy_uint8PortDirection;
			break;
		case MDIO_PORTC:
			DDRC=copy_uint8PortDirection;
			break;
		case MDIO_PORTD:
			DDRD=copy_uint8PortDirection;
			break;
		default :
			loc_Errorstate_Error_state=NOK;
			break;
		}
	}
	else
	{
		loc_Errorstate_Error_state=NOK;
	}
	return loc_Errorstate_Error_state;
}

/*************** set port value ***********/
ErrorState MDIO_Errorstate_SetPortValue (uint8 copy_uint8PortID ,uint8 copy_uint8PortValue)
{
	ErrorState loc_Errorstate_Error_state = OK;

	if(copy_uint8PortValue<=PORT_HIGH)
	{
		switch(copy_uint8PortID)
		{
		case MDIO_PORTA:
			DDRA=copy_uint8PortValue;

			break;
		case MDIO_PORTB:
			PORTB=copy_uint8PortValue;
			break;
		case MDIO_PORTC:
			PORTC=copy_uint8PortValue;
			break;
		case MDIO_PORTD:
			PORTD=copy_uint8PortValue;
			break;
		default :
			loc_Errorstate_Error_state=NOK;
			break;
		}
	}
		else
		{
			loc_Errorstate_Error_state=NOK;
		}
		return loc_Errorstate_Error_state;
	}

ErrorState MDIO_Errorstate_Set4MostBits (uint8 copy_uint8PortID ,uint8 copy_uint8PortValue)
{
	ErrorState Loc_Errorstate_Error_state = OK;
	switch(copy_uint8PortID)
			{
			case MDIO_PORTA:
				PORTA&=0x0F;
				PORTA|=copy_uint8PortValue;
				break;
			case MDIO_PORTB:
				PORTB&=0x0F;
				PORTB|=copy_uint8PortValue;
				break;
			case MDIO_PORTC:
				PORTC&=0x0F;
				PORTC|=copy_uint8PortValue;
				break;
			case MDIO_PORTD:
				PORTD&=0x0F;
				PORTD|=copy_uint8PortValue;
				break;
			default :
				Loc_Errorstate_Error_state=NOK;
				break;
			}
	return Loc_Errorstate_Error_state;
}
