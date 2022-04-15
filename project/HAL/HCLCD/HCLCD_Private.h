/*
 * HCLCD_Private.h
 *
 *
 */

#ifndef HAL_HCLCD_HCLCD_PRIVATE_H_
#define HAL_HCLCD_HCLCD_PRIVATE_H_

#define FUNCTIONSET_4BITMODE_2LINES    0b00101000
#define FUNCTIONSET_4BITMODE_1LINES    0b00100100
#define FUNCTIONSET_8BITMODE_2LINES    0b00111000
#define FUNCTIONSET_8BITMODE_1LINES    0b00110100

#define DISPLAYON_CURSORON_BLINKING        0b00001111
#define DISPLAYON_CURSORON_NOBLINKING      0b00001110
#define DISPLAYON_CURSOROFF                0b00001100
#define DISPLAYOFF                         0b00001000

#define DISPLAY_CLEAR       0x01

#define ENTRYMODE_INCREASE_SHIFT      0b00000111
#define ENTRYMODE_DECREASE_SHIFT      0b00000101
#define ENTRYMODE_INCREASE_NOSHIFT    0b00000110
#define ENTRYMODE_DECREASE_NOSHIFT    0b00000100

void HAL_VidHCLCD_4BitModeWriteCommand(uint8 Copy_uint8Command);

#endif /* HAL_HCLCD_HCLCD_PRIVATE_H_ */
