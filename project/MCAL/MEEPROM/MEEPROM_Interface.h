/*
 * MEEPROM_Interface.h
 *
 *  Created on: Apr 13, 2022 4:46:15 AM
 *      Author: mahmoud ramadan 
 */

#ifndef MCAL_MEEPROM_MEEPROM_INTERFACE_H_
#define MCAL_MEEPROM_MEEPROM_INTERFACE_H_

uint8 MEEPROM_uint8ReadByteFromAddress( uint16  copy_uint16Address, uint8 *data);
void MEEPROM_VidReadBlockFromAddress( uint16 copy_uint16Address, uint8* dist, uint16 size);
void MEEPROM_VidWriteByteToAddress(uint16 copy_uint16Address,uint8 copy_uint8Data);
void MEEPROM_VidWriteBlockToAddress(uint16 copy_uint16Address,uint8* copy_uint8Data,uint16 copy_uint16size);

#endif /* MCAL_MEEPROM_MEEPROM_INTERFACE_H_ */
