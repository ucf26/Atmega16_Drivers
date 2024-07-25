/*
 * USART_program.c
 *
 * Created: 7/22/2024 4:33:45 PM
 *  Author: ucf_26
 */ 


#include "USART_interface.h"

static uint8 L_counter = 0;
		
static void (*RX_CompleteIntettuptHandler)(void);
static void (*TX_CompleteIntettuptHandler)(void);
static void (*UDR_EmptyIntettuptHandler)(void);


static void USART_Mode_Select(const usart_t* usart_obj);
static void USART_Set_BaudRate(const usart_t* usart_obj);
static void USART_Set_Parity(const usart_t* usart_obj);
static void USART_Data_Size(const usart_t* usart_obj);
static void USART_Set_Stop_Bit(const usart_t* usart_obj);
static void USART_Set_Clock_Polarity(const usart_t* usart_obj);
static void USART_Interrupt_Config(const usart_t* usart_obj);

Std_ret USART_Init(const usart_t* usart_obj)
{
	Std_ret ret = E_NOT_OK;
	if(NULL == usart_obj)
	{
		ret = E_NOT_OK;
	}
	else 
	{
		/* enabling the	Transmitter or the Receiver depending on the usage*/
		
		USART_TRANSMITTER_ENABLE();
		USART_RECEIVER_ENABLE();
		
		/* setting the baud rate*/
		USART_Set_BaudRate(usart_obj);

		
		/* setting frame format*/
		USART_Set_Stop_Bit(usart_obj);
		USART_Data_Size(usart_obj);
		
		/* Mode */
		USART_Mode_Select(usart_obj);

		/* Configure Interrupts */
		USART_Interrupt_Config(usart_obj);
	}
	return ret;
}

Std_ret USART_Send_Data_Blocking(const usart_t* usart_obj, uint8 Data)
{
	Std_ret ret = E_NOT_OK;
	if(NULL == usart_obj)
	{
		ret = E_NOT_OK;
	}	
	else 
	{
		while(!(UCSRA & (1 << UDRE)));
		TXB = Data;
		ret = E_OK;
	}
	return ret;
}

Std_ret USART_Read_Data_Blocking(const usart_t* usart_obj, uint8* Data)
{
	Std_ret ret = E_NOT_OK;
	if(NULL == usart_obj)
	{
		ret = E_NOT_OK;
	}
	else
	{
		while(!(UCSRA & (1 << RXC)));
		*Data = RXB;
		ret = E_OK;
	}
	return ret;
}

Std_ret USART_Send_Data_NonBlocking(const usart_t* usart_obj, uint8 Data)
{
	Std_ret ret = E_NOT_OK;
	if(NULL == usart_obj)
	{
		ret = E_NOT_OK;
	}
	else
	{
		if(!(UCSRA & (1 << UDRE))) TXB = Data;
		ret = E_OK;
	}
	return ret;
}

Std_ret USART_Read_Data_NonBlocking(const usart_t* usart_obj, uint8* Data)
{
	Std_ret ret = E_NOT_OK;
	if(NULL == usart_obj)
	{
		ret = E_NOT_OK;
	}
	else
	{
		ret = E_OK;
		if(!(UCSRA & (1 << RXC))) *Data = RXB;
	}
	return ret;
}

Std_ret USART_DeInit(const usart_t* usart_obj)
{
	Std_ret ret = E_NOT_OK;
	if(NULL == usart_obj)
	{
		ret = E_NOT_OK;
	}
	else
	{
		USART_RECEIVER_DISABLE();
		USART_TRANSMITTER_DISABLE();
		ret = E_OK;
	}
	return ret;
}


/* ---------------------------------- Helper Functions ---------------------------------- */


static void USART_Mode_Select(const usart_t* usart_obj)
{
	// USART_UCSRC_SELSECT();
	switch(usart_obj->usart_mode_of_operation)
	{
		case USART_ASYNC_OPERATION:
			CLR_BIT(UCSRC, UMSEL);
			break;
		case USART_SYNC_OPERATION:
			SET_BIT(UCSRC, UMSEL);
			break;
		default: break;
	}
}

static void USART_Set_BaudRate(const usart_t* usart_obj)
{
	uint32 L_UBRR = 0, bb = usart_obj->baud_rate;
	
	if(USART_DOUBLE_SPEED == usart_obj->usart_transmission_speed)
	{
		L_UBRR = (F_CPU / 8 / bb) - 1 ;
	}
	else {
		L_UBRR = (F_CPU / 16 / bb) - 1 ;
	}
	USART_UBRRH_SELSECT();
	UBRRH = (uint8)(L_UBRR>>8);
	UBRRL = (uint8)(L_UBRR);
}

static void USART_Data_Size(const usart_t* usart_obj)
{
	USART_UCSRC_SELSECT();
	switch(usart_obj->usart_data_bits)
	{
		case USART_DATA_BITS_5:
			CLR_BIT(UCSRB, UCSZ2); CLR_BIT(UCSRC, UCSZ1); CLR_BIT(UCSRC, UCSZ0);
			break;
		case USART_DATA_BITS_6:
			CLR_BIT(UCSRB, UCSZ2); CLR_BIT(UCSRC, UCSZ1); SET_BIT(UCSRC, UCSZ0);
			break;
		case USART_DATA_BITS_7:
			CLR_BIT(UCSRB, UCSZ2); SET_BIT(UCSRC, UCSZ1); CLR_BIT(UCSRC, UCSZ0);
			break;
		case USART_DATA_BITS_8:
			CLR_BIT(UCSRB, UCSZ2); SET_BIT(UCSRC, UCSZ1); SET_BIT(UCSRC, UCSZ0);
			break;
		case USART_DATA_BITS_9:
			SET_BIT(UCSRB, UCSZ2); SET_BIT(UCSRC, UCSZ1); SET_BIT(UCSRC, UCSZ0);
			break;
			
		default: break;
	}
}

static void USART_Set_Parity(const usart_t* usart_obj)
{
	USART_UCSRC_SELSECT();
	switch(usart_obj->usart_parity_mode)
	{
		case USART_PARITY_MODE_DISABLED:
			CLR_BIT(UCSRC, UPM1); CLR_BIT(UCSRC, UPM1);
			break;
		case USART_PARITY_MODE_EVEN_PARITY:
			SET_BIT(UCSRC, UPM1); CLR_BIT(UCSRC, UPM1);
			break;
		case USART_PARITY_MODE_ODD_PARITY:
			SET_BIT(UCSRC, UPM1); SET_BIT(UCSRC, UPM1);
			break;
		default: break;
	}
}

static void USART_Set_Stop_Bit(const usart_t* usart_obj)
{
	USART_UCSRC_SELSECT();
	switch(usart_obj->usart_num_of_stop_bits)
	{
		case USART_ONE_STOP_BIT:
			CLR_BIT(UCSRC, USBS);
			break;
		case USART_TWO_STOP_BIT:
			SET_BIT(UCSRC, USBS);
			break;
		break;
	}
}

static void USART_Set_Clock_Polarity(const usart_t* usart_obj)
{
	USART_UCSRC_SELSECT();
	switch(usart_obj->usart_parity_mode)
	{
		case TRANSMIT_ON_RISING_RECEIVE_ON_FALLING:
			CLR_BIT(UCSRC, UCPOL);
			break;
		case TRANSMIT_ON_FALLING_RECEIVE_ON_RISING:
			SET_BIT(UCSRC, UCPOL);
			break;
		default:break;
	}
}

static void USART_Interrupt_Config(const usart_t* usart_obj)
{
	if(USART_TX_INTERRUPT_ENABLE==usart_obj->usart_tx_interrupt_enable)
	{
		GENERAL_INTERRUPT_ENABLE();
		TX_COMPLETE_INTERRUPT_ENABLE();
		TX_CompleteIntettuptHandler = usart_obj->TX_CompleteDefaultIntettuptHandler;
	}
	else { /* Nothing */ }
		
	if(USART_RX_INTERRUPT_ENABLE==usart_obj->usart_tx_interrupt_enable)
	{
		GENERAL_INTERRUPT_ENABLE();
		RX_COMPLETE_INTERRUPT_ENABLE();
		RX_CompleteIntettuptHandler = usart_obj->RX_CompleteDefaultIntettuptHandler;
	}
	else { /* Nothing */ }
	
	if(USART_UDR_EMPTY_INTERRUPT_ENABLE==usart_obj->usart_empty_udr_interrupt_enable)
	{
		GENERAL_INTERRUPT_ENABLE();
		UDR_EMPTY_INTERRUPT_ENABLE();
		UDR_EmptyIntettuptHandler = usart_obj->UDR_EmptyDefaultIntettuptHandler;
	}
	else { /* Nothing */ }
}


/* ---------------------------------- ISRs ---------------------------------- */

/* USART, Rx Complete */
void __vector_11(void) __attribute__((signal));
void __vector_11(void){
	if(RX_CompleteIntettuptHandler){
		RX_CompleteIntettuptHandler();
		
	}
}

/* USART Data Register Empty */
void __vector_12(void) __attribute__((signal));
void __vector_12(void){
	if(UDR_EmptyIntettuptHandler){
		UDR_EmptyIntettuptHandler();
		
	}
}

/* USART, Tx Complete */
void __vector_13(void) __attribute__((signal));
void __vector_13(void){
	if(TX_CompleteIntettuptHandler){
		TX_CompleteIntettuptHandler();
		
	}
}