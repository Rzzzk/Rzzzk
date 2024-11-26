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
#define N_COL 4   //number of columns
#define N_ROW 4   //number of rows

/* keypad port configuration*/
#define KEYPAD_PORT_OUT PORTC
#define KEYPAD_PORT_IN PINC
#define KEYPAD_PORT_DIR DDRC

/*  function to get the pressed keypad key */
uint8 keypad_getpressed_key(void);


#endif /* KEYPAD_H_ */
