/*
 * common_macros.h
 *
 *  Created on: Jul 11, 2022
 *      Author: REZK
 */

#ifndef COMMON_MACROS_H_
#define COMMON_MACROS_H_

#define SET_BIT(REG,BIT) (REG|=(1<<BIT)) // set a bit in the register
#define CLEAR_BIT(REG,BIT) (REG&=(~(1<<BIT))) // clear a bit in the register
#define TOGGLE_BIT(REG,BIT) (REG^=(1<<BIT)) // toggle a bit in the register

#define ROT_R(REG,NUM) (REG = (REG>>NUM) | (REG<<(8-NUM)) ) // rotate register to right
#define ROT_L(REG,NUM) (REG = (REG<<NUM) | (REG>>(8-NUM)) ) // rotate register to lift

/* return  true , if the bit is set */
#define BIT_IS_SET(REG,BIT)  ( REG & (1<<BIT) )

/* return  true , if the bit is clear */
#define BIT_IS_CLEAR(REG,BIT)  ( !(REG & (1<<BIT)) )



#endif /* COMMON_MACROS_H_ */
