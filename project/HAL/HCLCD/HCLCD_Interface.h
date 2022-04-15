/*
 * HCLCD_Interface.h
 *
 *
 */

#ifndef HAL_HCLCD_HCLCD_INTERFACE_H_
#define HAL_HCLCD_HCLCD_INTERFACE_H_

void HAL_VidHCLCD_4BitModeSendCommand(uint8 Copy_uint8Command);
void HAL_VidHCLCD_4BitModeWriteChar(uint8 Copy_uint8Char);
void HAL_VidHCLCD_4BitModeInit(void);
void HAL_VidHCLCD_4BitModeWriteString(uint8* copy_uint8String);
void HAL_VidHCLCD_4BitModeWriteNumber(uint32  copy_uint32Number);
void HAL_VidHCLCD_4BitModeSetPosition(uint8 copy_uint8LineNum,uint8 copy_uint8LinePosition);

#endif /* HAL_HCLCD_HCLCD_INTERFACE_H_ */
