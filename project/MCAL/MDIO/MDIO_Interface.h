/*
 * MDIO_Interface.h
 *
 *  Created on: Jan 15, 2022
 *      Author: Dell
 */

#ifndef MCAL_MDIO_MDIO_INTERFACE_H_
#define MCAL_MDIO_MDIO_INTERFACE_H_

/*   number of  ports */
#define MDIO_PORTA  0
#define MDIO_PORTB  1
#define MDIO_PORTC  2
#define MDIO_PORTD  3

/* direction*/
#define PIN_OUTPUT  1
#define PIN_INPUT   0
// for port
#define PORT_OUTPUT  255
#define PORT_INPUT   0

/* value for input mode*/
#define PIN_LOW     0
#define PIN_HIGH    1

typedef enum
{
	PIN0,
	PIN1,
	PIN2,
	PIN3,
	PIN4,
	PIN5,
	PIN6,
	PIN7
}pin_t;
// set pin direction & value'output mode  and get value for 'input mode'
ErrorState MDIO_Errorstate_SetPinDirection (uint8 copy_uint8PortID , uint8 copy_uint8PinNumber,uint8 copy_uint8PinDirection);

ErrorState MDIO_Errorstate_SetPinValue (uint8 copy_uint8PortID , uint8 copy_uint8PinNumber,uint8 copy_uint8PinValue);

ErrorState MDIO_Errorstate_GetPinValue (uint8 copy_uint8PortID , uint8 copy_uint8PinNumber,uint8 *puint8PinValue);
// set port direction & value
ErrorState MDIO_Errorstate_SetPortDirection (uint8 copy_uint8PortID , uint8 copy_uint8PortDirection);

ErrorState MDIO_Errorstate_SetPortValue (uint8 copy_uint8PortID ,uint8 copy_uint8PortValue);

ErrorState MDIO_Errorstate_Set4MostBits (uint8 copy_uint8PortID ,uint8 copy_uint8PortValue);

#endif /* MCAL_MDIO_MDIO_INTERFACE_H_ */

