/*
 * main.c
 *
 * Created: 5/13/2024 7:35:30 PM
 *  Author: ucf_26
 */ 


#include "app.h"


timer0_t timer0;

led_t led1 = {.port_idx = PORTA_INDEX, .pin_idx=PIN0_INDEX, .led_status = LED_ON};

void tttimer0 (void) {
	LED_Toggle(&led1);
}

int main(void)
{
	Std_ret ret = E_NOT_OK;
	timer0.timer0_mode = TIMER0_FAST_PWM;
	timer0.prescaler = TIMER0_CLOCK_PRESCALER_1;
	timer0.compare_value = 128;
	timer0.preload = 0;
	timer0.action_on_ocr0 = TIMER0_SET_ON_CTC_CLR_ON_BOTTOM;
	timer0.TIMER0_CTC_InterruptHandler = NULL;


	ret = TIMER0_Init(&timer0);
	
	ret = LED_Init(&led1);
	
    while(1)
    {
		
    }
}
