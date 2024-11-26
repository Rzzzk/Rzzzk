/*
 * std_types.h
 *
 *  Created on: Jul 11, 2022
 *      Author: REZK
 */

#ifndef STD_TYPES_H_
#define STD_TYPES_H_

typedef unsigned char   bool  ;  //boolean data type

 /*     boolean values        */
#ifndef TRUE
#define TRUE (1u)
#endif

#ifndef FALSE
#define FALSE (0u)
#endif

#ifndef HIGH
#define HIGH (1u)
#endif


#ifndef LOW
#define LOW (0u)
#endif

typedef unsigned char             uint8  ;   //0:255
typedef signed char               sint8  ;   //-128:+127
typedef unsigned short            uint16 ;   //0:65535
typedef signed short              sint16 ;   //-32768:+32767
typedef unsigned long             uint32 ;
typedef signed long               sint32 ;
typedef unsigned long long        uint64 ;
typedef signed long long          sint64 ;

typedef float                     float32 ;
typedef double                    float64 ;


#endif /* STD_TYPES_H_ */
