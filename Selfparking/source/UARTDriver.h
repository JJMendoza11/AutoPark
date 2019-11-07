/*
 * UARTDriver.h
 *
 *  Created on: 14 jul. 2019
 *      Author: lucky
 */

#ifndef UARTDRIVER_H_
#define UARTDRIVER_H_

typedef unsigned char uint8;

#define UART0_INT		UART0_IRQHandler
#define ERROR 			0
#define SUCCESS			1

void UART_vfnDriverInit ( void );
uint8 UART_bfnSend ( uint8 bTxData );
uint8 UART_bfnRead ( uint8 * bpRxData );
void UART0_INT ( void );


#endif /* UARTDRIVER_H_ */
