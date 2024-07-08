/*
 * DIO_Interface.h
 *
 * Created: 5/13/2024 7:38:51 PM
 *  Author: ucf_26
 */ 


#ifndef DIO_INTERFACE_H
#define DIO_INTERFACE_H



/* ----------------- Includes -----------------*/
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/DEVICE_CONFIG.h"
#include "../../LIB/STD_LIBRARIES.h"
#include "../../LIB/BIT_MATH.h"
#include "DIO_PRIVATE.h"


/* ----------------- Macro Definitions -----------------*/


/* ----------------- Macro Functions Declarations -----------------*/


/* -----------------Data Type Declarations -----------------*/

typedef enum {
	DIO_LOW = 0,
	DIO_HIGH
}logic_t;

typedef enum {
	DIO_PIN_INPUT = 0,
	DIO_PIN_OUTPUT
}direction_t;

typedef enum {
	PIN0_INDEX = 0,
	PIN1_INDEX,
	PIN2_INDEX,
	PIN3_INDEX,
	PIN4_INDEX,
	PIN5_INDEX,
	PIN6_INDEX,
	PIN7_INDEX
}pin_index_t;

typedef enum {
	PORTA_INDEX = 0,
	PORTB_INDEX,
	PORTC_INDEX,
	PORTD_INDEX
}port_index_t;


typedef struct {
	uint8 pin_index :3;
	uint8 port_index :2;
	logic_t logic :1;
	direction_t direction :1;
}pin_config_t;

typedef struct {
	uint8 port_index :2;
	uint8 logic :1;
	uint8 direction :1;
	uint8 reserved :4;
}port_config_t;



/* ----------------- Functions Declarations ----------------- */


Std_ret DIO_Pin_Direction_Initialize(pin_config_t *pin_cf);
Std_ret DIO_Pin_Direction_Status(pin_config_t *pin_cf, direction_t *direction);
Std_ret DIO_Pin_Write_Logic(pin_config_t *pin_cf, logic_t logic);
Std_ret DIO_Pin_Read_Logic(pin_config_t *pin_cf, logic_t *logic);
Std_ret DIO_Pin_Togle(pin_config_t *pin_cf);
Std_ret DIO_Pin_Init(pin_config_t *pin_cf);


Std_ret DIO_Port_Direction_Initialize(port_config_t *port);
Std_ret DIO_Port_Direction_Status(port_config_t *port, uint8 *direction);
Std_ret DIO_Port_Write_Logic(port_config_t *port, uint8 logic);
Std_ret DIO_Port_Read_Logic(port_config_t *port, uint8 *logic);
Std_ret DIO_Port_Togle(port_config_t *port);
Std_ret DIO_Port_Init(port_config_t *port);


#endif /* DIO_INTERFACE_H */
