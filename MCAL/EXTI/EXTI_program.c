/*
 * EXTI_program.c
 *
 * Created: 7/10/2024 7:53:15 PM
 *  Author: ucf_26
 */ 

#include "EXTI_interface.h"

static void (* EXTI_IN0_InterruptHandler)(void) = NULL;
static void (* EXTI_IN1_InterruptHandler)(void) = NULL;
static void (* EXTI_IN2_InterruptHandler)(void) = NULL;


static Std_ret EXTI_INTx_setHandler(interrupt_exti_t* _exti, interrupt_src_t src);
static Std_ret EXTI_INTx_setSenceMode(interrupt_exti_t* _exti, sense_mode_t mode);


static Std_ret EXTI_INT0_SetMode(sense_mode_t mode);
static Std_ret EXTI_INT1_SetMode(sense_mode_t mode);
static Std_ret EXTI_INT2_SetMode(sense_mode_t mode);

static Std_ret EXTI_INTx_InterruptEnable(interrupt_src_t src);
static Std_ret EXTI_INTx_InterruptDisable(interrupt_src_t src);

Std_ret EXTI_Init(interrupt_exti_t* _exti)
{
	Std_ret ret = E_NOT_OK;
	if(NULL == _exti)
	{
		ret = E_NOT_OK;
	}
	else 
	{
		/* Disable Interrupt */
		GENERAL_INTERRUPT_DISABLE();
		ret = EXTI_INTx_InterruptDisable(_exti->source);
		
		/* Clear Interrupt Flag */
		EXTI_INT0_FLAG_CLEAR();
		
		/* Set Sense Mode */
		ret = EXTI_INTx_setSenceMode(_exti, _exti->sense_mode);
		
		/* Set Interrupt Handler */
		ret = EXTI_INTx_setHandler(_exti, _exti->source);
		
		/* Enable Interrupt */
		GENERAL_INTERRUPT_ENABLE();
		ret = EXTI_INTx_InterruptEnable(_exti->source);
	}
	return ret;
}

Std_ret EXTI_De_Init(interrupt_exti_t* _exti)
{
	Std_ret ret = E_NOT_OK;
	if(NULL == _exti)
	{
		ret = E_NOT_OK;
	}
	else
	{
		/* Disable Interrupt */
		GENERAL_INTERRUPT_DISABLE();
		ret = EXTI_INTx_InterruptDisable(_exti->source);
	}
	return ret;
}


/*------------------------------------------ Helper Functions Implementations ------------------------------------------*/
static Std_ret EXTI_INTx_setHandler(interrupt_exti_t* _exti, interrupt_src_t src)
{
	Std_ret ret = E_NOT_OK;
	if((NULL == _exti) || (src < EXTI_INT0) || (src > EXTI_INT2))
	{
		ret = E_NOT_OK;
	}
	else {
		switch(src)
		{
			case EXTI_INT0: EXTI_IN0_InterruptHandler = _exti->EXTI_InterruptHandler; break;
			case EXTI_INT1: EXTI_IN1_InterruptHandler = _exti->EXTI_InterruptHandler; break;
			case EXTI_INT2: EXTI_IN2_InterruptHandler = _exti->EXTI_InterruptHandler; break;
			default: break;
		}
	}
	return ret;
}


static Std_ret EXTI_INTx_setSenceMode(interrupt_exti_t* _exti, sense_mode_t mode)
{
	Std_ret ret = E_NOT_OK;
	if(0)
	{
		ret = E_NOT_OK;
	}
	else {
		switch(_exti->source)
		{
			case EXTI_INT0: ret = EXTI_INT0_SetMode(mode); break;
			case EXTI_INT1: ret = EXTI_INT1_SetMode(mode); break;
			case EXTI_INT2: ret = EXTI_INT2_SetMode(mode); break;
			default: break;
		}
	}
	return ret;
}


static Std_ret EXTI_INT0_SetMode(sense_mode_t mode)
{
	Std_ret ret = E_NOT_OK;
	if((mode < EXTI_LOW_LEVEL) || (mode > EXTI_RISING_EDGE))
	{
		ret = E_NOT_OK;
	}
	else {
		switch(mode)
		{
			case EXTI_LOW_LEVEL:	CLR_BIT(MCUCR, 1); CLR_BIT(MCUCR, 0); break;
			case EXTI_ON_CHANGE:	CLR_BIT(MCUCR, 1); SET_BIT(MCUCR, 0); break;
			case EXTI_FALLING_EDGE: SET_BIT(MCUCR, 1); CLR_BIT(MCUCR, 0); break;
			case EXTI_RISING_EDGE:	SET_BIT(MCUCR, 1); SET_BIT(MCUCR, 0); break;
			default: break;
		}
	}
	return ret;
}


static Std_ret EXTI_INT1_SetMode(sense_mode_t mode)
{
	Std_ret ret = E_NOT_OK;
	if((mode < EXTI_LOW_LEVEL) || (mode > EXTI_RISING_EDGE))
	{
		ret = E_NOT_OK;
	}
	else {
		switch(mode)
		{
			case EXTI_LOW_LEVEL:	CLR_BIT(MCUCR, 3); CLR_BIT(MCUCR, 2); break;
			case EXTI_ON_CHANGE:	CLR_BIT(MCUCR, 3); SET_BIT(MCUCR, 2); break;
			case EXTI_FALLING_EDGE: SET_BIT(MCUCR, 3); CLR_BIT(MCUCR, 2); break;
			case EXTI_RISING_EDGE:	SET_BIT(MCUCR, 3); SET_BIT(MCUCR, 2); break;
			default: break;
		}
	}
	return ret;
}


static Std_ret EXTI_INT2_SetMode(sense_mode_t mode)
{
	Std_ret ret = E_NOT_OK;
	if((mode < EXTI_FALLING_EDGE) || (mode > EXTI_RISING_EDGE))
	{
		ret = E_NOT_OK;
	}
	else {
		switch(mode)
		{
			case EXTI_FALLING_EDGE: CLR_BIT(MCUCSR, 6); break;
			case EXTI_RISING_EDGE:	SET_BIT(MCUCSR, 6); break;
			default: break;
		}
	}
	return ret;
}

static Std_ret EXTI_INTx_InterruptEnable(interrupt_src_t src)
{
	Std_ret ret = E_NOT_OK;
	if((src < EXTI_INT0) || (src > EXTI_INT2))
	{
		ret = E_NOT_OK;
	}
	else {
		switch(src)
		{
			case EXTI_INT0: EXTI_INT0_ENABLE();  break;
			case EXTI_INT1: EXTI_INT1_ENABLE();  break;
			case EXTI_INT2: EXTI_INT2_ENABLE();  break;
			default: break;
		}
		ret = E_OK;
	}
	return ret;
}

static Std_ret EXTI_INTx_InterruptDisable(interrupt_src_t src)
{
	Std_ret ret = E_NOT_OK;
	if((src < EXTI_INT0) || (src > EXTI_INT2))
	{
		ret = E_NOT_OK;
	}
	else {
		switch(src)
		{
			case EXTI_INT0: EXTI_INT0_DISABLE();  break;
			case EXTI_INT1: EXTI_INT1_DISABLE();  break;
			case EXTI_INT2: EXTI_INT2_DISABLE();  break;
			default: break;
		}
		ret = E_OK;
	}
	return ret;
}


void __ector_1(void) __attribute__((signal));
void __vector_1(void){
	EXTI_INT0_FLAG_CLEAR();
	if(EXTI_IN0_InterruptHandler){
		EXTI_IN0_InterruptHandler();
	}
}

void __vector_2(void) __attribute__((signal));
void __vector_2(void){
	EXTI_INT1_FLAG_CLEAR();
	if(EXTI_IN1_InterruptHandler){
		EXTI_IN1_InterruptHandler();
	}
}

void __vector_18(void) __attribute__((signal));
void __vector_18(void){
	EXTI_INT2_FLAG_CLEAR();
	if(EXTI_IN2_InterruptHandler){
		EXTI_IN2_InterruptHandler();
	}
}