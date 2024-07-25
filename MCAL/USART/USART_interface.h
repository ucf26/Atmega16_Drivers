/*
 * USART_interface.h
 *
 * Created: 7/22/2024 4:34:14 PM
 *  Author: ucf_26
 */ 


#ifndef USART_INTERFACE_H_
#define USART_INTERFACE_H_


/* ----------------- Includes -----------------*/
#include "USART_private.h"
#include "../DIO/DIO_INTERFACE.h"
#include "../EXTI/EXTI_interface.h"

/* ----------------- Macro Definitions -----------------*/

#define READY 1
#define NOT_READY 0


#define USART_TX_INTERRUPT_DISABLE 0
#define USART_TX_INTERRUPT_ENABLE 1

#define USART_RX_INTERRUPT_DISABLE 0
#define USART_RX_INTERRUPT_ENABLE 1

#define USART_UDR_EMPTY_INTERRUPT_DISABLE 0
#define USART_UDR_EMPTY_INTERRUPT_ENABLE 1

/* USART MODES */
#define USART_TRANSIMETTER_ENABLED 1
#define USART_TRANSIMETTER_DISABLED 0

#define USART_RECEIVER_ENABLED 1
#define USART_RECEIVER_DISABLED 0

/* Double the USART Transmission Speed - only has effect for the asynchronous operation */
#define USART_NORMAL_SPEED	0
#define USART_DOUBLE_SPEED	1

/* USART Mode Select */
#define USART_ASYNC_OPERATION		0
#define USART_SYNC_OPERATION		1

/* USART Parity Mode */
#define USART_PARITY_MODE_DISABLED		0
#define USART_PARITY_MODE_EVEN_PARITY	2
#define USART_PARITY_MODE_ODD_PARITY	3

/* Stop Bit Select */
#define USART_ONE_STOP_BIT 0
#define USART_TWO_STOP_BIT 1

/* UCPOL Clock Polarity - Synchronous mode only */
#define TRANSMIT_ON_RISING_RECEIVE_ON_FALLING 0
#define TRANSMIT_ON_FALLING_RECEIVE_ON_RISING 1

// #define USART_DOUBLE_TRANSMISSION_SPEED()		(SET_BIT())
/* ----------------- Macro Functions Declarations -----------------*/

#define RX_COMPLETE_INTERRUPT_ENABLE()		(SET_BIT(UCSRB, RXCIE))
#define RX_COMPLETE_INTERRUPT_DISABLE()		(CLR_BIT(UCSRB, RXCIE))
#define RX_COMPLETE_FLAG_STATUS()			(GET_BIT(UCSRA, RXC))

#define TX_COMPLETE_INTERRUPT_ENABLE()		(SET_BIT(UCSRB, TXCIE))
#define TX_COMPLETE_INTERRUPT_DISABLE()		(CLR_BIT(UCSRB, TXCIE))
#define TX_COMPLETE_INTERRUPT_FLAG_STATUS()	(GET_BIT(UCSRA, TXC))
#define TX_COMPLETE_INTERRUPT_FLAG_CLEAR()	(SET_BIT(UCSRA, TXC))

#define UDR_EMPTY_INTERRUPT_ENABLE()		(SET_BIT(UCSRB, UDRIE))
#define UDR_EMPTY_INTERRUPT_DISABLE()		(CLR_BIT(UCSRB, UDRIE))
#define UDR_EMPTY_FLAG_STATUS()				(GET_BIT(UCSRA, UDRE))

#define USART_RECEIVER_ENABLE()				(SET_BIT(UCSRB, RXEN))
#define USART_RECEIVER_DISABLE()			(CLR_BIT(UCSRB, RXEN))

#define USART_TRANSMITTER_ENABLE()			(SET_BIT(UCSRB, TXEN))
#define USART_TRANSMITTER_DISABLE()			(CLR_BIT(UCSRB, TXEN))

#define USART_UCSRC_SELSECT()				(SET_BIT(UCSRC, URSEL))
#define USART_UBRRH_SELSECT()				(CLR_BIT(UCSRC, URSEL))

/* -----------------Data Type Declarations -----------------*/
typedef enum{
	USART_DATA_BITS_5 = 0,
	USART_DATA_BITS_6 ,
	USART_DATA_BITS_7 ,
	USART_DATA_BITS_8 ,
	USART_DATA_BITS_9
}usart_databits_t;

typedef struct{
	uint16 baud_rate;
	usart_databits_t usart_data_bits :3;
	uint8 usart_parity_mode :2;
	uint8 usart_mode_of_operation :1;  /* Async or Sync*/
	uint8 usart_num_of_stop_bits :1;
	uint8 usart_transmission_speed :1;
	uint8 usart_transmitter_mode :1;
	uint8 usart_receiver_mode :1;
	uint8 usart_tx_interrupt_enable :1;
	uint8 usart_rx_interrupt_enable :1;
	uint8 usart_empty_udr_interrupt_enable :1;
	uint8 reserved :3;
	
	void (*RX_CompleteDefaultIntettuptHandler)(void);
	void (*TX_CompleteDefaultIntettuptHandler)(void);
	void (*UDR_EmptyDefaultIntettuptHandler)(void);
	
}usart_t;

/* ----------------- Functions Declarations ----------------- */
Std_ret USART_Init(const usart_t* usart_obj);
Std_ret USART_DeInit(const usart_t* usart_obj);

Std_ret USART_Send_Data_Blocking(const usart_t* usart_obj, uint8 Data);
Std_ret USART_Read_Data_Blocking(const usart_t* usart_obj, uint8* Data);

Std_ret USART_Send_Data_NonBlocking(const usart_t* usart_obj, uint8 Data);
Std_ret USART_Read_Data_NonBlocking(const usart_t* usart_obj, uint8* Data);

#endif /* USART_INTERFACE_H_ */