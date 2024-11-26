/*
 * keypad.h
 *
 *  Created on: Jul 11, 2022
 *      Author: REZK
 */

#ifndef KEYPAD_H_
#define KEYPAD_H_

#include"micro_config.h"
#include"std_types.h"
#include"common_macros.h"


/*********************************************
 *                                           *
 *        keypad configurations              *
 *                                           *
 *********************************************/
#define N_COL 3   //number of columns
#define N_ROW 4   //number of rows

/* keypad port configuration*/
#define KEYPAD_PORT_OUT PORTB
#define KEYPAD_PORT_IN  PINB
#define KEYPAD_PORT_DIR DDRB

/*  function to get the pressed keypad key */
uint8 keypad_getpressed_key(void);


#endif /* KEYPAD_H_ */
