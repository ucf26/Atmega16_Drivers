/*
 * .c
 *
 * Created: 7/9/2024 3:09:48 PM
 *  Author: ucf_26
 */ 

#include "LED_interface.h"


Std_ret LED_Init(led_t* led_obj)
{
	Std_ret ret = E_NOT_OK;
	if(NULL == led_obj)
	{
		ret = E_NOT_OK;
	}
	else 
	{
		pin_config_t pin_temp = {.direction = DIO_PIN_OUTPUT, .logic = led_obj->led_status, .pin_index=led_obj->pin_idx, .port_index=led_obj->port_idx };
		ret = DIO_Pin_Init(&pin_temp);
	}
	return ret;
}

Std_ret LED_Turn_On(led_t* led_obj){
	Std_ret ret = E_NOT_OK;
	if(NULL == led_obj)
	{
		ret = E_NOT_OK;
	}
	else
	{
		pin_config_t pin_temp = {.direction = DIO_PIN_OUTPUT, 
								.logic = led_obj->led_status, 
								.pin_index=led_obj->pin_idx, 
								.port_index=led_obj->port_idx };
								
		ret = DIO_Pin_Write_Logic(&pin_temp, DIO_HIGH);
	}
	return ret;
}

Std_ret LED_Turn_Off(led_t* led_obj){
	Std_ret ret = E_NOT_OK;
	if(NULL == led_obj)
	{
		ret = E_NOT_OK;
	}
	else
	{
		pin_config_t pin_temp = {.direction = DIO_PIN_OUTPUT, .logic = led_obj->led_status, .pin_index=led_obj->pin_idx, .port_index=led_obj->port_idx };
		ret = DIO_Pin_Write_Logic(&pin_temp, DIO_LOW);
	}
	return ret;
}

Std_ret LED_Toggle(led_t* led_obj){
	Std_ret ret = E_NOT_OK;
	if(NULL == led_obj)
	{
		ret = E_NOT_OK;
	}
	else
	{
		pin_config_t pin_temp = {.direction = DIO_PIN_OUTPUT, .logic = led_obj->led_status, .pin_index=led_obj->pin_idx, .port_index=led_obj->port_idx };
		ret = DIO_Pin_Togle(&pin_temp);
	}
	return ret;
}
