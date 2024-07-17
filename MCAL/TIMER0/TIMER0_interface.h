/*
 * TIMER0_interface.h
 *
 * Created: 7/15/2024 2:48:56 PM
 *  Author: ucf_26
 */ 


#ifndef TIMER0_INTERFACE_H_
#define TIMER0_INTERFACE_H_

/* ----------------- Includes -----------------*/
#include "TIMER0_private.h"
#include "../DIO/DIO_INTERFACE.h"

/* ----------------- Macro Definitions -----------------*/

/* Waveform Generation Mode */
#define TIMER0_NORMAL_MODE				0
#define TIMER0_PWM_PHASE_CORRECT_MODE	1
#define TIMER0_CTC_MODE					2
#define TIMER0_FAST_PWM					3

/* Compare Match Output Mode, non-PWM Mode */
#define TIMER0_OC0_DISCONNECTED 0
#define TIMER0_TOGGLE_OC0		1
#define TIMER0_CLEAR_OC0		2
#define TIMER0_SET_OC0			3

/* Compare Output Mode,Fast PWM Mode */
#define TIMER0_OC0_DISCONNECTED				0
#define TIMER0_CLR_ON_CTC_SET_ON_BOTTOM		2
#define TIMER0_SET_ON_CTC_CLR_ON_BOTTOM		3

/* Compare Output Mode,Phase Correct PWM Mode */
#define TIMER0_OC0_DISCONNECTED								0
#define TIMER0_CLR_ON_CTC_COUNT_UP_SET_ON_COUNT_DOWN		2
#define TIMER0_CLR_ON_CTC_COUNT_DOWN_SET_ON_COUNT_UP		3

/* Timer0 Clock Select */
#define TIMER0_STOPPED					0
#define TIMER0_CLOCK_PRESCALER_1		1
#define TIMER0_CLOCK_PRESCALER_8		2
#define TIMER0_CLOCK_PRESCALER_64		3
#define TIMER0_CLOCK_PRESCALER_256		4
#define TIMER0_CLOCK_PRESCALER_1024		5
#define TIMER0_EXTERNAL_FALLING_EDGE	6 
#define TIMER0_EXTERNAL_RISING_EDGE		7


/* ----------------- Macro Functions Declarations -----------------*/
#define  GENERAL_INTERRUPT_ENABLE()			(SET_BIT(SREG, 7))
#define  GENERAL_INTERRUPT_DISABLE()		(CLR_BIT(SREG, 7))


#define TIMER0_OV_FLAG_CLEAR()				(SET_BIT(TIFR, TOV0))
#define TIMER0_OV_InterruptEnable()			(SET_BIT(TIMSK, TOIE0))
#define TIMER0_OV_InterruptDisable()		(CLR_BIT(TIMSK, TOIE0))

#define TIMER0_CTC_FLAG_CLEAR()				(SET_BIT(TIFR, OCF0))
#define TIMER0_CTC_InterruptEnable()		(SET_BIT(TIMSK, OCIE0))
#define TIMER0_CTC_InterruptDisable()		(CLR_BIT(TIMSK, OCIE0))

/* -----------------Data Type Declarations -----------------*/
typedef struct{
	// PRELOADED 
	// prescaler 
	// mode 
	// interruptHandler --> ov
	// interruptHandler --> compare match 
	// pin state due to compare match 
	uint8 timer0_mode :2;
	uint8 prescaler :3;
	uint8 action_on_ocr0:2;
	uint8 reserved :1;
	uint8 preload;
	uint8 compare_value;
	
	void (*TIMER0_OV_InterruptHandler)(void);
	void (*TIMER0_CTC_InterruptHandler)(void);
	
}timer0_t;
/* ----------------- Functions Declarations ----------------- */
Std_ret TIMER0_Init(timer0_t* timer0_obj);
Std_ret TIMER0_DeInit(timer0_t* timer0_obj);


#endif /* TIMER0_INTERFACE_H_ */