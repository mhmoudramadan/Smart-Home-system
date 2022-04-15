/*
 * MEXTI_Program.c
 *
 *  Created on: Feb 4, 2022
 *      Author: Dell
 */
#include "../../LIB/LSTD_TYPES.h"
#include "../../LIB/LBIT_MATH.h"
#include "MEXTI_Private.h"
#include "MEXTI_Interface.h"
#include "MEXTI_Config.h"

void (*CALLBACK)(void);

void MEXTI_VidInitEXTI0(void)
{
	/*Select sense control*/
#if SET_SENCECONTROL_EXTI0==MEXTI_RISING_EDGE
	SET_BIT(MCUCR,1);
	SET_BIT(MCUCR,0);
#elif SET_SENCECONTROL_EXTI0==MEXTI_FALLING_EDGE
	SET_BIT(MCUCR,1);
	CLR_BIT(MCUCR,0);
#elif SET_SENCECONTROL_EXTI0==MEXTI_ANYLOGICALCHANGE
	CLR_BIT(MCUCR,1);
	SET_BIT(MCUCR,0);

#elif SET_SENCECONTROL_EXTI0==MEXTI_LOW_LEVEL
	CLR_BIT(MCUCR,1);
	CLR_BIT(MCUCR,0);
#else
#error "Sense Control option of EXTI0 is not valid"

#endif
	/*Enable EXTI 0*/
	SET_BIT(GICR,6);

}

void MEXTI_VidSenseControlSelect(uint8 copy_uint8EXTI_ID,uint8 copy_uint8EXTI_SenseControl)
{
	switch (copy_uint8EXTI_ID)
	{
	case EXTI0:
		if(copy_uint8EXTI_SenseControl==MEXTI_RISING_EDGE)
		{
			SET_BIT(MCUCR,1);
			SET_BIT(MCUCR,0);
		}
		else if(copy_uint8EXTI_SenseControl==MEXTI_FALLING_EDGE)
		{
			SET_BIT(MCUCR,1);
			CLR_BIT(MCUCR,0);
		}
		else if(copy_uint8EXTI_SenseControl==MEXTI_ANYLOGICALCHANGE)
		{
			CLR_BIT(MCUCR,1);
			SET_BIT(MCUCR,0);
		}
		else if(copy_uint8EXTI_SenseControl==MEXTI_LOW_LEVEL)
		{
			CLR_BIT(MCUCR,1);
			CLR_BIT(MCUCR,0);
		}
		else
		{
			/*do nothing*/
		}
		break;
	}
}
void MEXTI0_VidSetCallBack(void (*PtrToFun)(void))
{
	CALLBACK=PtrToFun;
}

/*EXTI0*/
void __vector_1(void)   __attribute__((signal));
void __vector_1(void)
{
	CALLBACK();
}
