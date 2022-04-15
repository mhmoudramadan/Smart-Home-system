/*
 * MUART_Program.c
 *
 *  Created on: Feb 26, 2022
 *      Author: Dell
 */
#include"../../LIB/LSTD_TYPES.h"
#include"../../LIB/LBIT_MATH.h"
#include"MUART_Private.h"
#include"MUART_Config.h"

void (*CALLBACK) (void);
 void MUART_VidInit(void)
{
	 uint8 Loc_uint8TempRegister=0;
	 SET_BIT(Loc_uint8TempRegister,7);

	   	   /*Mode UART Select */
#if UART_SELECTMODE == UART_ASYNCHRONOUS
	 CLR_BIT(Loc_uint8TempRegister,6);
#elif UART_SELECTMODE == UART_SYNCHRONOUS
	 SET_BIT(Loc_uint8TempRegister,6);
#else
#error"UART Mode Select Option Is Not Valid.."
#endif

	 	 /*UART Parity Mode Option CHECK*/
#if UART_PARITYCHECK_MODE   == PARTIYCHECK_DISABLED
	 CLR_BIT(Loc_uint8TempRegister,4);
	 CLR_BIT(Loc_uint8TempRegister,4);
#elif UART_PARITYCHECK_MODE == PARTIYCHECK_ENABLED_EVEN
	 CLR_BIT(Loc_uint8TempRegister,4);
	 SET_BIT(Loc_uint8TempRegister,5);
#elif UART_PARITYCHECK_MODE == PARTIYCHECK_ENABLED_ODD
	 SET_BIT(Loc_uint8TempRegister,4);
	 SET_BIT(Loc_uint8TempRegister,5);
#else
#error"PARTIY Check Option Is Not Valid.."
#endif

	 	 /*STOP Bit Option*/
#if UART_STOPBIT == ONE_BIT
	 CLR_BIT(Loc_uint8TempRegister,3);
#elif UART_STOPBIT == TWO_BIT
	 SET_BIT(Loc_uint8TempRegister,3);
#else
#error"Stop Bit Option Is Not Valid.."
#endif

	 	 /*Size of Data Bit */
#if UART_NUMBEROFDATA_BIT == CHAR_5Bit
	 CLR_BIT(Loc_uint8TempRegister,1);
	 CLR_BIT(Loc_uint8TempRegister,2);
	 CLR_BIT(UCSRB,2);
#elif UART_NUMBEROFDATA_BIT== CHAR_6Bit
	 SET_BIT(Loc_uint8TempRegister,1);
	 CLR_BIT(Loc_uint8TempRegister,2);
	 CLR_BIT(UCSRB,2);
#elif UART_NUMBEROFDATA_BIT==CHAR_7Bit
	 CLR_BIT(Loc_uint8TempRegister,1);
	 SET_BIT(Loc_uint8TempRegister,2);
	 CLR_BIT(UCSRB,2);
#elif UART_NUMBEROFDATA_BIT==CHAR_8Bit
	 SET_BIT(Loc_uint8TempRegister,1);
	 SET_BIT(Loc_uint8TempRegister,2);
	 CLR_BIT(UCSRB,2);
#elif UART_NUMBEROFDATA_BIT==CHAR_9Bit
	 SET_BIT(Loc_uint8TempRegister,1);
	 SET_BIT(Loc_uint8TempRegister,2);
	 SET_BIT(UCSRB,2);
#else
	 #error"Data Bit Option Is Not Valid.."
#endif
	 UCSRC=Loc_uint8TempRegister;
	 	 	  /*Set BaudRate -->9600*/
	 UBRRL=UART_BAUDRATE;
	          /*Enable Receiver*/
	 SET_BIT(UCSRB,4);
	          /*Enable transmit*/
	 SET_BIT(UCSRB,3);
	          /*Enable Transmit TX Interrupt*/
	 SET_BIT(UCSRB,6);
	          /*Enable Receiver RX Interrupt*/
	 SET_BIT(UCSRB,7);
	          /*Data Register Interrupt Enable*/
	 SET_BIT(UCSRB,5);

 }
 void MUART_VidSendChar(uint8 copy_uint8Char)
 {
	 /*Wait until UDR is Empty*/
	 while(GET_BIT(UCSRA,5==0));
	 UDR=copy_uint8Char;
	 /*Check for Transmission complete */
	 while(GET_BIT(UCSRA,6==0));
	 /*Clear Flag*/
	 SET_BIT(UCSRA,6);
 }
 void MUART_vidSendString(uint8 *copy_uint8String)
 {
	 uint8 Loc_uint8count=0;
	 while(copy_uint8String[Loc_uint8count]!='\0')
	 {
		 /*Wait until UDR is Empty*/
		 while(GET_BIT(UCSRA,5==0));
		 UDR=copy_uint8String[Loc_uint8count];
		 Loc_uint8count++;
		 /*Check for Transmission complete */
		 while(GET_BIT(UCSRA,6==0));
		 /*Clear Flag*/
		 SET_BIT(UCSRA,6);
	 }
 }
 uint8 MUART_uint8ReciverChar(void)
 {
	 while(GET_BIT(UCSRA,7)==0);
	 return UDR;
 }
 void MUART_VidReciveString(uint8 *copy_uint8string)
 {
	 uint8 Loc_counter=0;
	 copy_uint8string[Loc_counter]=MUART_uint8ReciverChar();
	 do
	 {
		 Loc_counter++;
		 copy_uint8string[Loc_counter]=MUART_uint8ReciverChar();
	 }while(copy_uint8string[Loc_counter] != '#');
	 copy_uint8string[Loc_counter]='\0';
 }
  /*TX*/
 void __vector_15(void)   __attribute__((signal));
 void __vector_15(void)
 {
	 CALLBACK();
 }
 /*RX*/
 void __vector_13(void)   __attribute__((signal));
 void __vector_13(void)
 {
	 CALLBACK();
 }
 /*UART DATA Register Empty*/
 void __vector_14(void)   __attribute__((signal));
 void __vector_14(void)
 {
	 CALLBACK();
 }
