/*
 * main.c
 *
 * Created: 5/13/2024 7:35:30 PM
 *  Author: ucf_26
 */ 


#include "app.h"

pin_config_t pin1 = {
	.pin_index = PIN0_INDEX,
	.port_index = PORTC_INDEX,
	.direction = DIO_PIN_INPUT,
	.logic = DIO_LOW
};

pin_config_t pin2 = {
	.pin_index = PIN1_INDEX,
	.port_index = PORTC_INDEX,
	.direction = DIO_PIN_OUTPUT,
	.logic = 0
};

volatile uint8 logic = 0L;

int main(void)
{
	Std_ret ret = E_NOT_OK;
	ret = DIO_Pin_Init(&pin1);
	ret = DIO_Pin_Init(&pin2);
	logic = 0;
	
    while(1)
    {
		ret = DIO_Pin_Read_Logic(&pin1, &logic);
		
		if(logic == 1){
			ret = DIO_Pin_Write_Logic(&pin2, DIO_HIGH);
			
			
		}else {
			ret = DIO_Pin_Write_Logic(&pin2, DIO_LOW);
			
		}
    }
}