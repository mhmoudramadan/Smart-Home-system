/*
 * MEPPROM_Program.c
 *
 *  Created on: Apr 13, 2022 4:46:44 AM
 *      Author: mahmoud ramadan 
 */
#include"../../LIB/LSTD_TYPES.h"
#include"avr/eeprom.h"
#include"MEEPROM_Interface.h"

uint8 MEEPROM_uint8ReadByteFromAddress(uint16 copy_uint16Address, uint8 *data)
{
	/* Wait for completion of previous write */
		while (((EECR & (1 << EEWE))>>EEWE)==1);
		/* Set up address register */
		EEAR = copy_uint16Address;
		/* Start EEPROM read by writing EERE */
		EECR |= (1 << EERE);
		/* Return data from data register */
		(*data) = EEDR;
		return EEDR;
}
void MEEPROM_VidReadBlockFromAddress( uint16 copy_uint16Address, uint8* dist, uint16 size)
{
	/* Wait for completion of previous write */
		while (((EECR & (1 << EEWE))>>EEWE)==1);

		uint16 counter = 0;//the counter of bytes that are read

		while (counter < size) //loop until move all bytes to the given array
		{
			/* Set up address register */
			EEAR = copy_uint16Address + counter;
			/* Start EEPROM read by writing EERE */
			EECR |= (1 << EERE);
			/* move data from data register to the array */
			*(dist + counter) = EEDR;

			counter++;//increase the bytes counter
		}
}
void MEEPROM_VidWriteByteToAddress(uint16 copy_uint16Address,uint8 copy_uint8Data)
{
	/* Wait for completion of previous write process*/
		while ( ( (EECR & (1 << EEWE) ) >>EEWE ) == 1)
		;
		/* Set up address register */
		EEAR = copy_uint16Address;

		/* Read the byte in the address of EEAR */
		EECR |= (1 << EERE);
		/*compare the value read to the value to be written*/
		if (EEDR != copy_uint8Data)
		{//if they are not equal then write the data move the data to EEDR*/
			EEDR = copy_uint8Data;

			/* Write logical one to EEMWE */
			EECR |= (1 << EEMWE);
			/* Start EEPROM write by setting EEWE */
			EECR |= (1 << EEWE);
		}
		else
		{
			/*Do Nothing*/
		}
}
void MEEPROM_VidWriteBlockToAddress(uint16 copy_uint16Address,uint8* copy_uint8Data,uint16 copy_uint16size)
{
	uint16 counter = 0;

		while (counter < copy_uint16size)
		{
			/* Wait for completion of previous write process*/
			while (( (EECR & (1 << EEWE) ) >>EEWE ) == 1)
			;
			/* Set up address register */
			EEAR = copy_uint16Address + counter;

			/* Read the byte in the address of EEAR */
			EECR |= (1 << EERE);
			if (EEDR != (*(copy_uint8Data + counter)))//compare the value read to the value to be written
			{
				/*if they are not equal then write the data move the data to EEDR*/
				EEDR = *(copy_uint8Data + counter);

				/* Write logical one to EEMWE */
				EECR |= (1 << EEMWE);
				/* Start EEPROM write by setting EEWE */
				EECR |= (1 << EEWE);
			}
			else
			{
				/*Do nothing*/
			}
			counter++;
		}
}
