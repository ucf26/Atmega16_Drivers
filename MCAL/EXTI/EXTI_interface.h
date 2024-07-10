/*
 * EXTI_interface.h
 *
 * Created: 7/10/2024 7:53:34 PM
 *  Author: ucf_26
 */ 


#ifndef EXTI_INTERFACE_H_
#define EXTI_INTERFACE_H_

/* ----------------- Includes -----------------*/
#include "EXTI_config.h"
#include "EXTI_private.h"
#include "../DIO/DIO_INTERFACE.h"


/* ----------------- Macro Definitions -----------------*/
#define  INT0     6
#define  INT2     5
#define  INT1     7


/* ----------------- Macro Functions Declarations -----------------*/
#define  GENERAL_INTERRUPT_ENABLE()			(SET_BIT(SREG, 7))
#define  GENERAL_INTERRUPT_DISABLE()		(CLR_BIT(SREG, 7))

// INT0
#define  EXTI_INT0_ENABLE()				(SET_BIT(GICR, INT0))
#define  EXTI_INT0_DISABLE()			(CLR_BIT(GICR, INT0))
#define  EXTI_INT0_FLAG_CLEAR()			(CLR_BIT(GIFR, INT0))

// INT1
#define  EXTI_INT1_ENABLE()				(SET_BIT(GICR, INT1))
#define  EXTI_INT1_DISABLE()			(CLR_BIT(GICR, INT1))
#define  EXTI_INT1_FLAG_CLEAR()			(CLR_BIT(GIFR, INT1))

// INT0
#define  EXTI_INT2_ENABLE()				(SET_BIT(GICR, INT2))
#define  EXTI_INT2_DISABLE()			(CLR_BIT(GICR, INT2))
#define  EXTI_INT2_FLAG_CLEAR()			(CLR_BIT(GIFR, INT2))


/* -----------------Data Type Declarations -----------------*/
typedef enum{
	EXTI_LOW_LEVEL = 0,
	EXTI_ON_CHANGE,
	EXTI_FALLING_EDGE,
	EXTI_RISING_EDGE
}sense_mode_t;

typedef enum{
	EXTI_INT0 = 0,
	EXTI_INT1,
	EXTI_INT2
}interrupt_src_t;

typedef struct{
	void (*EXTI_InterruptHandler)(void);
	sense_mode_t sense_mode :2;
	interrupt_src_t source:2;
}interrupt_exti_t;


/* ----------------- Functions Declarations ----------------- */
Std_ret EXTI_Init(interrupt_exti_t* _exti);
Std_ret EXTI_De_Init(interrupt_exti_t* _exti);


#endif /* EXTI_INTERFACE_H_ */