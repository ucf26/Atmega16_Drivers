/*
 * LED_interface.h
 *
 * Created: 7/9/2024 3:10:32 PM
 *  Author: ucf_26
 */ 


#ifndef LED_INTERFACE_H_
#define LED_INTERFACE_H_


/* ----------------- Includes -----------------*/
#include "../../MCAL/DIO/DIO_INTERFACE.h"
#include "LED_config.h"
#include "LED_private.h"

/* ----------------- Macro Definitions -----------------*/


/* ----------------- Macro Functions Declarations -----------------*/

/* -----------------Data Type Declarations -----------------*/
typedef enum {
	LED_OFF = 0,
	LED_ON	
}led_status_t;


typedef struct{
	uint8 port_idx :2;
	uint8 pin_idx :3;
	led_status_t led_status:1;
	uint8 reserved :2;
}led_t;

/* ----------------- Functions Declarations ----------------- */
Std_ret LED_Init(led_t* led_obj);
Std_ret LED_Turn_On(led_t* led_obj);
Std_ret LED_Turn_Off(led_t* led_obj);
Std_ret LED_Toggle(led_t* led_obj);

#endif /* LED_INTERFACE_H_ */