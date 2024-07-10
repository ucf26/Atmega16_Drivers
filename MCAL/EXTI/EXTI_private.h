/*
 * EXTI_private.h
 *
 * Created: 7/10/2024 7:54:01 PM
 *  Author: ucf_26
 */ 


#ifndef EXTI_PRIVATE_H_
#define EXTI_PRIVATE_H_


/* ----------------- Includes -----------------*/

/* ----------------- Macro Definitions -----------------*/
#define  MCUCR			(*((volatile uint8 *)0x55))
#define  MCUCSR			(*((volatile uint8 *)0x54))
#define  GICR			(*((volatile uint8 *)0x5B))
#define  GIFR			(*((volatile uint8 *)0x5A))
#define  SREG			(*((volatile uint8 *)0x5F))


/* ----------------- Macro Functions Declarations -----------------*/

/* -----------------Data Type Declarations -----------------*/

/* ----------------- Functions Declarations ----------------- */




#endif /* EXTI_PRIVATE_H_ */