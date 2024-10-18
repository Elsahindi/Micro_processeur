#ifndef MYTIMER_H
#define MYTIMER_H

#define CHANNEL_1 1
#define CHANNEL_2 2
#define CHANNEL_3 3
#define CHANNEL_4 4

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


#define MyTimer_Base_Start(Timer) (Timer->CR1 |= TIM_CR1_CEN)
#define MyTimer_Base_Stop(Timer) (Timer->CR1 &= ~(TIM_CR1_CEN))


/**************************************************************************************************
 * @brief 
 * @param Timer: TIM_TypeDef* - Timer concerned
 * @param PriO: char - Priority from 0 to 15
 * @note: This function MyTimer_Base_Init does the initialization to make the timer available
 **************************************************************************************************/
void MyTimer_ActiveIT(TIM_TypeDef *Timer, char Prio, void (*IT_function) (void));

void TIM2_IRQHandler(void);
void TIM3_IRQHandler(void);
void TIM4_IRQHandler(void);

/**
 * @brief Initializes a PWM timer channel.
 * @param Timer Pointer to the TIM_TypeDef structure that contains 
 *              the configuration information for the timer.
 * @param Channel Specifies the channel to configure for PWM.
 * @note This function does not configure the input/output settings 
 *       nor the PWM period settings (ARR, PSC).
 */
void MyTimer_PWM(TIM_TypeDef *Timer, char Channel);

#endif

