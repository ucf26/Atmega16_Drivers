/*
 * main.c
 *
 * Created: 5/13/2024 7:35:30 PM
 *  Author: ucf_26
 */ 


#include "app.h"

usart_t usart_obj;

void rx_isr(void);
void tx_isr(void);

uint8 rec;

led_t led1 = {.port_idx = PORTA_INDEX, .pin_idx=PIN0_INDEX, .led_status = LED_OFF};
led_t led2 = {.port_idx = PORTA_INDEX, .pin_idx=PIN1_INDEX, .led_status = LED_OFF};

int main(void)
{
	Std_ret ret = E_NOT_OK;
	
	usart_obj.baud_rate = 9600;
	usart_obj.usart_data_bits = USART_DATA_BITS_8;
	usart_obj.usart_mode_of_operation = USART_ASYNC_OPERATION;
	usart_obj.usart_num_of_stop_bits = USART_ONE_STOP_BIT;
	usart_obj.usart_transmission_speed = USART_NORMAL_SPEED;
	usart_obj.usart_rx_interrupt_enable = USART_RX_INTERRUPT_ENABLE;
	usart_obj.RX_CompleteDefaultIntettuptHandler = rx_isr;
	usart_obj.usart_tx_interrupt_enable = USART_TX_INTERRUPT_ENABLE;
	usart_obj.TX_CompleteDefaultIntettuptHandler = tx_isr;
	

	ret = USART_Init(&usart_obj);
	ret = LED_Init(&led1);
	ret = LED_Init(&led2);
	
	
	
	
    while(1)
    {
		ret = USART_Read_Data_Blocking(&usart_obj, &rec);
		if(rec == '1'){
			ret = USART_Send_Data_Blocking(&usart_obj, 'o');

		}
		else {
			ret = USART_Send_Data_Blocking(&usart_obj, 'n');

		}
    }
}


void tx_isr()
{
	LED_Toggle(&led1);
	
}

void rx_isr()
{
	LED_Toggle(&led2);
}