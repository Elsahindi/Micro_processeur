#include "MyTimer.h"
#include "Drive_GPIO.h"

void MyTimer_Base_Init( TIM_TypeDef * Tim, unsigned short ARR , unsigned short PSC){
	
	// Activate timer
	if(Tim == TIM1){
		RCC->APB2ENR = RCC->APB2ENR | RCC_APB2ENR_TIM1EN;
	}
	else if(Tim == TIM2){
		RCC->APB1ENR = RCC->APB1ENR | RCC_APB1ENR_TIM2EN;
	}
	else if(Tim == TIM3){
		RCC->APB1ENR = RCC->APB1ENR | RCC_APB1ENR_TIM3EN;
	}
	else if(Tim == TIM4){
		RCC->APB1ENR = RCC->APB1ENR | RCC_APB1ENR_TIM4EN;
	}
	
	Tim->ARR = ARR;
	Tim->PSC = PSC;
	
}