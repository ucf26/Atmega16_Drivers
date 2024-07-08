/*
 * main.c
 *
 * Created: 5/13/2024 7:35:30 PM
 *  Author: ucf_26
 */ 


#include "app.h"

port_config_t port_obj;




int main(void)
{
	Std_ret ret = E_NOT_OK;
	port_obj.direction = 0xff;
	port_obj.logic = 0x00;
	port_obj.port_index = PORTA_INDEX;
	

	ret = DIO_Port_Init(&port_obj);
	
    while(1)
    {
		ret = DIO_Port_Togle(&port_obj);
		_delay_ms(500);
    }
}