#ifndef MYTIMER_H
#define MYTIMER_H

#include "stm32f10x.h" 

typedef struct {
                 // Device header
	TIM_TypeDef * Timer ; // TIM1 à TIM4
	unsigned short ARR ;
	unsigned short PSC ;
} MyTimer_Struct_TypeDef ;

/**
 * @brief 
 * @param -> Parameter in the form of a structure (its address) containing basic information
 * @Note -> Function to be launched systematically before going into more detail in the config files (PWM, encoder, etc.)
 */
void MyTimer_Base_Init( TIM_TypeDef * Timer, unsigned short ARR , unsigned short PSC ) ;

#define MyTimer_Base_Start ( Timer ) ( . . . )
#define MyTimer_Base_Stop ( Timer ) ( . . . )

#endif

