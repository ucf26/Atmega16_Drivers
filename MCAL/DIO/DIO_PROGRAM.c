/*
 * DIO_Program.c
 *
 * Created: 5/13/2024 7:40:08 PM
 *  Author: ucf_26
 */ 


#include "DIO_INTERFACE.h"


Std_ret DIO_Pin_Direction_Initialize(pin_config_t *pin_cfg)
{
	Std_ret ret = E_NOT_OK;
	if(NULL == pin_cfg)
	{
		ret = E_NOT_OK;
	}
	else 
	{
		switch(pin_cfg->direction)
		{
			case DIO_PIN_INPUT:
				switch (pin_cfg->port_index)
				{
					case PORTA_INDEX: CLR_BIT(DDRA, pin_cfg->pin_index); break;
					case PORTB_INDEX: CLR_BIT(DDRB, pin_cfg->pin_index); break;
					case PORTC_INDEX: CLR_BIT(DDRC, pin_cfg->pin_index); break;
					case PORTD_INDEX: CLR_BIT(DDRD, pin_cfg->pin_index); break;
					default: break;
				}
				break;
				
			case DIO_PIN_OUTPUT:
				switch (pin_cfg->port_index)
				{
					case PORTA_INDEX: SET_BIT(DDRA, pin_cfg->pin_index); break;
					case PORTB_INDEX: SET_BIT(DDRB, pin_cfg->pin_index); break;
					case PORTC_INDEX: SET_BIT(DDRC, pin_cfg->pin_index); break;
					case PORTD_INDEX: SET_BIT(DDRD, pin_cfg->pin_index); break;
					default: break;
				}
				break;	
			default: break;
		}
		ret = E_OK;
	}
	return ret;
}

Std_ret DIO_Pin_Direction_Status(pin_config_t *pin_cfg, direction_t *direction)
{
	Std_ret ret = E_NOT_OK;
	if(NULL == pin_cfg)
	{
		ret = E_NOT_OK;
	}
	else
	{
		switch (pin_cfg->port_index)
		{
			case PORTA_INDEX: *direction = GET_BIT(PORTA, pin_cfg->pin_index); break;
			case PORTB_INDEX: *direction = GET_BIT(PORTB, pin_cfg->pin_index); break;
			case PORTC_INDEX: *direction = GET_BIT(PORTC, pin_cfg->pin_index); break;
			case PORTD_INDEX: *direction = GET_BIT(PORTD, pin_cfg->pin_index); break;
			default: break;
		}
		ret = E_OK;
	}
	return ret;
}

Std_ret DIO_Pin_Write_Logic(pin_config_t *pin_cfg, logic_t logic)
{
	Std_ret ret = E_NOT_OK;
	if(NULL == pin_cfg)
	{
		ret = E_NOT_OK;
	}
	else
	{
		switch(logic)
		{
			case DIO_LOW:
				switch (pin_cfg->port_index)
				{
					case PORTA_INDEX: CLR_BIT(PORTA, pin_cfg->pin_index); break;
					case PORTB_INDEX: CLR_BIT(PORTB, pin_cfg->pin_index); break;
					case PORTC_INDEX: CLR_BIT(PORTC, pin_cfg->pin_index); break;
					case PORTD_INDEX: CLR_BIT(PORTD, pin_cfg->pin_index); break;
					default: break;
				}
				break;
				
			case DIO_HIGH:
				switch (pin_cfg->port_index)
				{
					case PORTA_INDEX: SET_BIT(PORTA, pin_cfg->pin_index); break;
					case PORTB_INDEX: SET_BIT(PORTB, pin_cfg->pin_index); break;
					case PORTC_INDEX: SET_BIT(PORTC, pin_cfg->pin_index); break;
					case PORTD_INDEX: SET_BIT(PORTD, pin_cfg->pin_index); break;
					default: break;
				}
				break;
			
			default: break;
		}
		ret = E_OK;
	}
	return ret;
}

Std_ret DIO_Pin_Read_Logic(pin_config_t *pin_cfg, logic_t *logic)
{
	Std_ret ret = E_NOT_OK;
	if(NULL == pin_cfg)
	{
		ret = E_NOT_OK;
	}
	else
	{
		switch (pin_cfg->port_index)
		{
			case PORTA_INDEX: *logic = GET_BIT(PINA, pin_cfg->pin_index); break;
			case PORTB_INDEX: *logic = GET_BIT(PINB, pin_cfg->pin_index); break;
			case PORTC_INDEX: *logic = GET_BIT(PINC, pin_cfg->pin_index); break;
			case PORTD_INDEX: *logic = GET_BIT(PIND, pin_cfg->pin_index); break;
			default: break;
		}
		ret = E_OK;
	}
	return ret;
}

Std_ret DIO_Pin_Togle(pin_config_t *pin_cfg)
{
	Std_ret ret = E_NOT_OK;
	if(NULL == pin_cfg)
	{
		ret = E_NOT_OK;
	}
	else
	{
		switch (pin_cfg->port_index)
		{
			case PORTA_INDEX: TOG_BIT(PORTA, pin_cfg->pin_index); break;
			case PORTB_INDEX: TOG_BIT(PORTB, pin_cfg->pin_index); break;
			case PORTC_INDEX: TOG_BIT(PORTC, pin_cfg->pin_index); break;
			case PORTD_INDEX: TOG_BIT(PORTD, pin_cfg->pin_index); break;
			default: break;
		}
		ret = E_OK;
	}
	return ret;
}

Std_ret DIO_Pin_Init(pin_config_t *pin_cfg)
{
	Std_ret ret = E_NOT_OK;
	if(NULL == pin_cfg)
	{
		ret = E_NOT_OK;
	}
	else
	{
		ret = DIO_Pin_Direction_Initialize(pin_cfg);
		ret = DIO_Pin_Write_Logic(pin_cfg, pin_cfg->logic);
	}
	return ret;
}
