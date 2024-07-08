/*
 * DIO_PRIVATE.h
 *
 * Created: 5/18/2024 2:16:45 AM
 *  Author: ucf_26
 */ 


#ifndef DIO_PRIVATE_H
#define DIO_PRIVATE_H

/* Section : Includes */


/* Section : Macro Functions Declarations */


/* Section : Data Type Declarations */


/* Section : Macro Declarations */


#define PORTA	(*((volatile uint8 *)0x3B))
#define DDRA	(*((volatile uint8 *)0x3A))
#define PINA	(*((volatile uint8 *)0x39))


#define PORTB	(*((volatile uint8 *)0x38))
#define DDRB	(*((volatile uint8 *)0x37))
#define PINB	(*((volatile uint8 *)0x36))


#define PORTC	(*((volatile uint8 *)0x35))
#define DDRC	(*((volatile uint8 *)0x34))
#define PINC	(*((volatile uint8 *)0x33))


#define PORTD	(*((volatile uint8 *)0x32))
#define DDRD	(*((volatile uint8 *)0x31))
#define PIND	(*((volatile uint8 *)0x30))



/* Section : Functions Declarations */


#endif /* DIO_PRIVATE_H */