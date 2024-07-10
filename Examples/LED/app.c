/*
 * main.c
 *
 * Created: 5/13/2024 7:35:30 PM
 *  Author: ucf_26
 */ 


#include "app.h"

led_t led1 = {.port_idx = PORTA_INDEX, .pin_idx=PIN0_INDEX, .led_status = LED_OFF};
led_t led2 = {.port_idx = PORTA_INDEX, .pin_idx=PIN1_INDEX, .led_status = LED_OFF};
led_t led3 = {.port_idx = PORTA_INDEX, .pin_idx=PIN2_INDEX, .led_status = LED_OFF};

int main(void)
{
	Std_ret ret = E_NOT_OK;
	ret = LED_Init(&led1);
	ret = LED_Init(&led2);
	ret = LED_Init(&led3);

    while(1)
    {
		ret = LED_Toggle(&led1);
		ret = LED_Toggle(&led2);
		ret = LED_Toggle(&led3);
		_delay_ms(500);
    }
}