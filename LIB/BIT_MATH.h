/*
 * BIT_MATH.h
 *
 * Created: 5/18/2024 2:05:55 AM
 *  Author: ucf_26
 */ 

#ifndef BIT_MATH_H
#define BIT_MATH_H

/* Section : Includes */

/* Section : Macro Functions Declarations */

#define SET_BIT(REG, POS)  (REG|=(1<<POS))
#define CLR_BIT(REG, POS)  (REG&= ~(1<<POS))
#define TOG_BIT(REG, POS)  (REG^=(1<<POS))
#define GET_BIT(REG, POS)  (uint8)((REG>>POS)&((uint8)1))


/* Section : Data Type Declarations */

/* Section : Macro Declarations */

/* Section : Functions Declarations */


#endif /* BIT_MATH_H */