/*
 * UARTDriver.c
 *
 *  Created on: 14 jul. 2019
 *      Author: lucky
 */

#include "MKL25Z4.h"
#include "UARTDriver.h"
#include "UARTDriver.h"

void UART_vfnDriverInit (void){
	NVIC->ISER[0]|=(1<<UART0_IRQn);
	SIM->SCGC4|=SIM_SCGC4_UART0_MASK;
	SIM->SOPT2|=SIM_SOPT2_UART0SRC(1);
	SIM->SCGC5|=SIM_SCGC5_PORTA_MASK;
	PORTA->PCR[1]|=PORT_PCR_MUX(2);							//PIN Rx
	PORTA->PCR[2]|=PORT_PCR_MUX(2);							// PIN Tx
	UART0->BDH |= UART0_BDH_SBNS_MASK;						// 2b STOP
	UART0->BDH |= 0X1;
	UART0->BDL |= 0XB6;										//BAUD rate=9600
	UART0->C1 = 0;
	UART0->C2|=UART_C2_RIE_MASK; 							//Interrupcion
	//UART0->C1 &= ~(UART0_C1_M_MASK);
	//UART0->C1 &= ~(UART0_C1_PE_MASK);						//Enable Parity
	//UART0->C1=UART0_C1_PT_MASK;							//ODD Parity
	UART0->S2=0;											//LSB or MSB
	UART0->C4=UART0_C4_OSR(4);								//Oversampling 16
	UART0->C2 |= UART0_C2_TE_MASK|UART0_C2_RE_MASK;			//Enable Tx and RX
}

uint8 UART_bfnSend (uint8 bTxData){
	if(UART0->S1&UART_S1_TDRE_MASK){
		UART0->D=bTxData;
		return SUCCESS;
	}
	return ERROR;
}
uint8 UART_bfnRead (uint8 *bpRxData){
	if(UART0->S1&UART_S1_RDRF_MASK){
		*bpRxData=UART0->D;
		return SUCCESS;
	}
	return ERROR;
}

extern uint8_t UARTVal;

void UART0_INT ( void )
{
	UARTVal = UART0->D;
	UART_bfnSend ( UARTVal );
}
