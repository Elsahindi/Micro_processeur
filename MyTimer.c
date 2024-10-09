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
	
	// If you want a timer period 500ms
	// Calculate Tpsc = T0 * (PSC + 1) = 1/10000 choose PSC : prescaler = 7199, To = 1/72MHz
	// Ttimer = 500ms = (ARR +1) * Tpsc => ARR = 4999
	Tim->ARR = ARR;
	Tim->PSC = PSC;
	
}

void MyTimer_ActiveIT(TIM_TypeDef * Tim, char Prio){
	Tim->DIER |= (0x1); // enable UIE
	
	if(Tim == TIM2){
		NVIC_EnableIRQ(TIM2_IRQn);
		NVIC_SetPriority(TIM2_IRQn,Prio);
	}
	else if(Tim == TIM3){
		NVIC_EnableIRQ(TIM3_IRQn);
		NVIC_SetPriority(TIM3_IRQn,Prio);
	}
	else if(Tim == TIM4){
		NVIC_EnableIRQ(TIM4_IRQn);
		NVIC_SetPriority(TIM4_IRQn,Prio);
	}
	
}