/*
 * TIMER0_program.c
 *
 * Created: 7/15/2024 2:48:07 PM
 *  Author: ucf_26
 */ 


#include "TIMER0_interface.h"


void (*TIMER0_OV_DefaultInterruptHandler)(void) = NULL;
void (*TIMER0_CTC_DefaultInterruptHandler)(void) = NULL;

static void TIMER0_Normal_Mode_Config(timer0_t* timer0_obj);
static void TIMER0_PWM_PHASE_CORRECT_MODE_Config(timer0_t* timer0_obj);
static void TIMER0_CTC_Mode_Config(timer0_t* timer0_obj);
static void TIMER0_FastPWM_Mode_Config(timer0_t* timer0_obj);


static void TIMER0_Set_Mode(uint8 mode);
static void TIMER0_Set_PreScaler(uint8 prescaler);
static void TIMER0_Set_PreLoaded_Value(uint8 preload);
static void TIMER0_Set_OCR0_Value(uint8 mode);
static void TIMER0_Set_Compare_Output_NonPWM(uint8 mode);
static void TIMER0_Set_Compare_Output_FastPWM(uint8 mode);
static void TIMER0_Set_Compare_Output_PhaseCorrectPWM(uint8 mode);


Std_ret TIMER0_Init(timer0_t* timer0_obj)
{
	Std_ret ret = E_NOT_OK;
	if(NULL == timer0_obj)
	{
		ret = E_NOT_OK;
	}
	else 
	{
		switch(timer0_obj->timer0_mode)
		{
			case TIMER0_NORMAL_MODE: 
				TIMER0_Normal_Mode_Config(timer0_obj); 
				break;
			case TIMER0_PWM_PHASE_CORRECT_MODE: 
				TIMER0_PWM_PHASE_CORRECT_MODE_Config(timer0_obj);;
				break;
			case TIMER0_CTC_MODE: 
				TIMER0_CTC_Mode_Config(timer0_obj);
				break;
			case TIMER0_FAST_PWM:
				TIMER0_FastPWM_Mode_Config(timer0_obj);
				break;
			default: break;
		}
		
	}
	return ret;
}
Std_ret TIMER0_DeInit(timer0_t* timer0_obj)
{
	Std_ret ret = E_NOT_OK;
	if(NULL == timer0_obj)
	{
		ret = E_NOT_OK;
	}
	else
	{
		/* Disable Over Flow Interrupt */
		TIMER0_OV_InterruptDisable();
		
		/* Disable CTC Interrupt */
		TIMER0_CTC_InterruptDisable();
		
		/* Disconnect OC0 */
		TIMER0_Set_Compare_Output_NonPWM(TIMER0_OC0_DISCONNECTED);
		
		/* Turn Off Clock Sources */
		TIMER0_Set_PreScaler(TIMER0_STOPPED);
	}
	return ret;
}


/* --------------------------------------------- Helper Functions --------------------------------------------- */

static void TIMER0_Normal_Mode_Config(timer0_t* timer0_obj)
{
	/* Set Mode */
	TIMER0_Set_Mode(timer0_obj->timer0_mode);
	
	/* Set prescaler */
	TIMER0_Set_PreScaler(timer0_obj->prescaler);
	
	/* set preload */
	TIMER0_Set_PreLoaded_Value(timer0_obj->preload);
	
	/* Set ISR */
	TIMER0_OV_DefaultInterruptHandler = timer0_obj->TIMER0_OV_InterruptHandler;
	
	/* Clear Timer0 Interrupt Flag */
	TIMER0_OV_FLAG_CLEAR();
	
	/* Enable Interrupt */
	GENERAL_INTERRUPT_ENABLE();
	TIMER0_OV_InterruptEnable();
}

static void TIMER0_PWM_PHASE_CORRECT_MODE_Config(timer0_t* timer0_obj)
{
	/* Set Mode */
	TIMER0_Set_Mode(timer0_obj->timer0_mode);
	
	/* Set prescaler */
	TIMER0_Set_PreScaler(timer0_obj->prescaler);
	
	/* Set OCR0 Value */
	OCR0 = (uint8)(timer0_obj->compare_value);
	
	/* Action on Compare Match */
	TIMER0_Set_Compare_Output_PhaseCorrectPWM(timer0_obj->action_on_ocr0);
}

static void TIMER0_CTC_Mode_Config(timer0_t* timer0_obj)
{
	/* Set Mode */
	TIMER0_Set_Mode(timer0_obj->timer0_mode);
	
	/* Set prescaler */
	TIMER0_Set_PreScaler(timer0_obj->prescaler);
	
	/* set preload */
	TIMER0_Set_PreLoaded_Value(timer0_obj->preload);
	
	/* Set Interrupt Handler */
	TIMER0_CTC_DefaultInterruptHandler = timer0_obj->TIMER0_CTC_InterruptHandler;
	
	/* Set OCR0 Value */
	OCR0 = (uint8)(timer0_obj->compare_value);
	
	/* Action on Compare Match */
	TIMER0_Set_Compare_Output_NonPWM(timer0_obj->action_on_ocr0);
	
	/* Clear Timer0 Interrupt Flag */
	TIMER0_CTC_FLAG_CLEAR();
	
	/* Enable Interrupt */
	GENERAL_INTERRUPT_ENABLE();
	TIMER0_CTC_InterruptEnable();
}

static void TIMER0_FastPWM_Mode_Config(timer0_t* timer0_obj)
{
	/* Set Mode */
	TIMER0_Set_Mode(timer0_obj->timer0_mode);
	
	/* Set prescaler */
	TIMER0_Set_PreScaler(timer0_obj->prescaler);
	
	/* Set OCR0 Value */
	OCR0 = (uint8)(timer0_obj->compare_value);
	
	/* Action on Compare Match */
	TIMER0_Set_Compare_Output_FastPWM(timer0_obj->action_on_ocr0);
}


static void TIMER0_Set_Mode(uint8 mode)
{
	switch(mode)
	{
		case TIMER0_NORMAL_MODE: 
			CLR_BIT(TCCR0, WGM01); CLR_BIT(TCCR0, WGM00); 
			break;
		case TIMER0_PWM_PHASE_CORRECT_MODE:
			CLR_BIT(TCCR0, WGM01); SET_BIT(TCCR0, WGM00);
			break;
		case TIMER0_CTC_MODE:
			SET_BIT(TCCR0, WGM01); CLR_BIT(TCCR0, WGM00);
			break;
		case TIMER0_FAST_PWM:
			SET_BIT(TCCR0, WGM01); SET_BIT(TCCR0, WGM00);
			break;
		default:break;
	}
}
static void TIMER0_Set_PreScaler(uint8 prescaler)
{
	switch(prescaler)
	{
		case TIMER0_STOPPED:
			CLR_BIT(TCCR0, CS02); CLR_BIT(TCCR0, CS01); CLR_BIT(TCCR0, CS00);
			break;
		case TIMER0_CLOCK_PRESCALER_1:
			CLR_BIT(TCCR0, CS02); CLR_BIT(TCCR0, CS01); SET_BIT(TCCR0, CS00);
			break;
		case TIMER0_CLOCK_PRESCALER_8:
			CLR_BIT(TCCR0, CS02); SET_BIT(TCCR0, CS01); CLR_BIT(TCCR0, CS00);
			break;	
		case TIMER0_CLOCK_PRESCALER_64:
			CLR_BIT(TCCR0, CS02); SET_BIT(TCCR0, CS01); SET_BIT(TCCR0, CS00);
			break;
		case TIMER0_CLOCK_PRESCALER_256:
			SET_BIT(TCCR0, CS02); CLR_BIT(TCCR0, CS01); CLR_BIT(TCCR0, CS00);
			break;
		case TIMER0_CLOCK_PRESCALER_1024:
			SET_BIT(TCCR0, CS02); CLR_BIT(TCCR0, CS01); SET_BIT(TCCR0, CS00);
			break;
		case TIMER0_EXTERNAL_FALLING_EDGE:
			SET_BIT(TCCR0, CS02); SET_BIT(TCCR0, CS01); CLR_BIT(TCCR0, CS00);
			break;
		case TIMER0_EXTERNAL_RISING_EDGE:
			SET_BIT(TCCR0, CS02); SET_BIT(TCCR0, CS01); SET_BIT(TCCR0, CS00);
			break;
		
		default:break;
	}
}
static void TIMER0_Set_PreLoaded_Value(uint8 preload)
{
	TCNT0 = preload;
}
static void TIMER0_Set_Compare_Output_NonPWM(uint8 mode)
{
	pin_config_t Temp_Pin = {.direction = DIO_PIN_OUTPUT, .port_index = PORTB_INDEX, .pin_index = PIN3_INDEX, .logic=DIO_LOW};
	
	Std_ret ret = DIO_Pin_Init(&Temp_Pin);
	
	switch(mode)
	{
		case TIMER0_OC0_DISCONNECTED:
			CLR_BIT(TCCR0, COM01); CLR_BIT(TCCR0, COM00);
			break;
		case TIMER0_TOGGLE_OC0:
			CLR_BIT(TCCR0, COM01); SET_BIT(TCCR0, COM00);
			break;
		case TIMER0_CLEAR_OC0:
			SET_BIT(TCCR0, COM01); CLR_BIT(TCCR0, COM00);
			break;
		case TIMER0_SET_OC0:
			SET_BIT(TCCR0, COM01); SET_BIT(TCCR0, COM00);
			break;
		default: break;
	}
}
static void TIMER0_Set_Compare_Output_FastPWM(uint8 mode)
{
	pin_config_t Temp_Pin = {.direction = DIO_PIN_OUTPUT, .port_index = PORTB_INDEX, .pin_index = PIN3_INDEX, .logic=DIO_LOW};
	
	Std_ret ret = DIO_Pin_Init(&Temp_Pin);
	
	switch(mode)
	{
		case TIMER0_OC0_DISCONNECTED:
		CLR_BIT(TCCR0, COM01); CLR_BIT(TCCR0, COM00);
		break;
		case TIMER0_CLR_ON_CTC_SET_ON_BOTTOM:
		SET_BIT(TCCR0, COM01); CLR_BIT(TCCR0, COM00);
		break;
		case TIMER0_SET_ON_CTC_CLR_ON_BOTTOM:
		SET_BIT(TCCR0, COM01); SET_BIT(TCCR0, COM00);
		break;
		default: break;
	}
}
static void TIMER0_Set_Compare_Output_PhaseCorrectPWM(uint8 mode)
{
	pin_config_t Temp_Pin = {.direction = DIO_PIN_OUTPUT, .port_index = PORTB_INDEX, .pin_index = PIN3_INDEX, .logic=DIO_LOW};
	
	Std_ret ret = DIO_Pin_Init(&Temp_Pin);
	
	switch(mode)
	{
		case TIMER0_OC0_DISCONNECTED:
		CLR_BIT(TCCR0, COM01); CLR_BIT(TCCR0, COM00);
		break;
		case TIMER0_CLR_ON_CTC_COUNT_UP_SET_ON_COUNT_DOWN:
		SET_BIT(TCCR0, COM01); CLR_BIT(TCCR0, COM00);
		break;
		case TIMER0_CLR_ON_CTC_COUNT_DOWN_SET_ON_COUNT_UP:
		SET_BIT(TCCR0, COM01); SET_BIT(TCCR0, COM00);
		break;
		default: break;
	}
}


/* Timer0 Over Flow Interrupt ISR */
void __vector_9(void)   __attribute__((signal));
void __vector_9(void)
{
	TIMER0_OV_FLAG_CLEAR();
	if(TIMER0_OV_DefaultInterruptHandler != NULL)
	{
		TIMER0_OV_DefaultInterruptHandler();
	}
}

/* Timer0 CTC Interrupt ISR */
void __vector_19(void)   __attribute__((signal));
void __vector_19(void)
{
	TIMER0_CTC_FLAG_CLEAR();
	if(TIMER0_CTC_DefaultInterruptHandler != NULL)
	{
		TIMER0_CTC_DefaultInterruptHandler();
	}
}


