/*
 * uart.h
 *
 *  Created on: 20.6.2012
 *      Author: ohejda
 *
 *  Description: uart module using rx/tx interrupts.
 *  Functions:
 *  	uart_init .. initialization
 *  	uart_putc .. put char function
 *  	uart_puts .. put string function
 */

#ifndef UART_H_
#define UART_H_

#include <inttypes.h>
#include <stdbool.h>

// uart buffer length (mask preferred)
#define UART_TX_BUFLEN 64
#define UART_TX_BUFMASK 0x3F
#define UART_RX_BUFLEN 16
#define UART_RX_BUFMASK 0x0F

char h2c(unsigned int h); // hex to char
int8_t c2h(char c); // char to hex


void uart_init(void); // initialization
int uart_putc(char c); // put char function
int uart_puts(char *s); // put string function

#endif /* UART_H_ */
