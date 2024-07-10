/*
 * main.c
 *
 * Created: 5/13/2024 7:35:30 PM
 *  Author: ucf_26
 */ 


#include "app.h"

interrupt_exti_t exti_int0, exti_int1, exti_int2;

led_t led1 = {.port_idx = PORTA_INDEX, .pin_idx=PIN0_INDEX, .led_status = LED_OFF};
led_t led2 = {.port_idx = PORTA_INDEX, .pin_idx=PIN1_INDEX, .led_status = LED_OFF};
led_t led3 = {.port_idx = PORTA_INDEX, .pin_idx=PIN2_INDEX, .led_status = LED_OFF};

void toog1(void){
	Std_ret ret = E_NOT_OK;
	ret = LED_Toggle(&led1);
}

void toog2(void){
	Std_ret ret = E_NOT_OK;
	ret = LED_Toggle(&led2);
}

void toog3(void){
	Std_ret ret = E_NOT_OK;
	ret = LED_Toggle(&led3);
}

int main(void)
{
	Std_ret ret = E_NOT_OK;
	exti_int0.sense_mode = EXTI_RISING_EDGE;
	exti_int0.source = EXTI_INT0;
	exti_int0.EXTI_InterruptHandler = toog1;
	
	exti_int1.sense_mode = EXTI_RISING_EDGE;
	exti_int1.source = EXTI_INT1;
	exti_int1.EXTI_InterruptHandler = toog2;
	
	exti_int2.sense_mode = EXTI_RISING_EDGE;
	exti_int2.source = EXTI_INT2;
	exti_int2.EXTI_InterruptHandler = toog3;
	
	ret = EXTI_Init(&exti_int0);
	ret = EXTI_Init(&exti_int1);
	ret = EXTI_Init(&exti_int2);
	
	ret = LED_Init(&led1);
	ret = LED_Init(&led2);
	ret = LED_Init(&led3);
	
	
	
    while(1)
    {
		
    }
}