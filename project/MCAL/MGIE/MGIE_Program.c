/*
 * MGIE_Program.c
 *
 *  Created on: Feb 4, 2022
 *      Author: Dell
 */

#include"../../LIB/LSTD_TYPES.h"
#include"../../LIB/LBIT_MATH.h"
#include"MGIE_Private.h"
void MGIE_Enable(void)
{
	SET_BIT(SREG,7);
}
void MGIE_Disable(void)
{
	CLR_BIT(SREG,7);
}
