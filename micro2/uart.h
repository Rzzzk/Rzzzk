/*
 * uart.h
 *
 *  Created on: Jul 11, 2022
 *      Author: REZK
 */

#ifndef UART_H_
#define UART_H_

#define USART_BAUDRATE 9600
#include "micro_config.h"
#include "std_types.h"
#include "common_macros.h"

void UART_init(void);
void UART_sendByte(const uint8 data);
uint8 UART_reseiveByte(void);
void UART_sendString(const uint8 *str);
void UART_reseiveString(uint8 *str);

/* function to send and receive password */

void UART_sendPass(uint8 arr[]);
void UART_reseivePass(uint8 arr[]);

#endif /* UART_H_ */
