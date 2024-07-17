/*
 * TIMER0_private.h
 *
 * Created: 7/15/2024 2:49:47 PM
 *  Author: ucf_26
 */ 


#ifndef TIMER0_PRIVATE_H_
#define TIMER0_PRIVATE_H_

/* ----------------- Includes -----------------*/

/* ----------------- Macro Definitions -----------------*/

#define  TCCR0			(*((volatile uint8 *)0x53))
#define  TCNT0			(*((volatile uint8 *)0x52))
#define  OCR0			(*((volatile uint8 *)0x5C))
#define  TIMSK			(*((volatile uint8 *)0x59))
#define  TIFR			(*((volatile uint8 *)0x58))
#define  SREG			(*((volatile uint8 *)0x5F))

// TCCR0
#define CS00 0
#define CS01 1
#define CS02 2
#define WGM01 3
#define COM00 4
#define COM01 5
#define WGM00 6
#define FOC0 7

// TIMSK
#define TOIE0 0
#define OCIE0 1

// TIFR
#define TOV0 0
#define OCF0 1


/* ----------------- Macro Functions Declarations -----------------*/

/* -----------------Data Type Declarations -----------------*/

/* ----------------- Functions Declarations ----------------- */


#endif /* TIMER0_PRIVATE_H_ */