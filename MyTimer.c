#include "MyTimer.h"
#include "Drive_GPIO.h"

void (*tim_2_callback) (void);
void (*tim_3_callback) (void);
void (*tim_4_callback) (void);


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

void MyTimer_ActiveIT(TIM_TypeDef * Tim, char Prio, void (*IT_function) (void)){
	Tim->DIER |= (0x1); // enable UIE
	
	if(Tim == TIM2){
		tim_2_callback = IT_function;
		NVIC_EnableIRQ(TIM2_IRQn);
		NVIC_SetPriority(TIM2_IRQn,Prio);
	}
	else if(Tim == TIM3){
		tim_3_callback = IT_function;
		NVIC_EnableIRQ(TIM3_IRQn);
		NVIC_SetPriority(TIM3_IRQn,Prio);
	}
	else if(Tim == TIM4){
		tim_4_callback = IT_function;
		NVIC_EnableIRQ(TIM4_IRQn);
		NVIC_SetPriority(TIM4_IRQn,Prio);
	}
	
}
void TIM2_IRQHandler(void){
	TIM2->SR &= ~(TIM_SR_UIF);
	//MyGPIO_Toggle(GPIOA, 5);
	
	(*tim_2_callback)();
	
}

void TIM3_IRQHandler(void){
	TIM3->SR &= ~(TIM_SR_UIF);
	MyGPIO_Toggle(GPIOA, 5);
	
	(*tim_3_callback)();
	
}

void TIM4_IRQHandler(void){
	TIM4->SR &= ~(TIM_SR_UIF);
	MyGPIO_Toggle(GPIOA, 5);
	
	(*tim_4_callback)();
	
}

void MyTimer_PWM(TIM_TypeDef *Tim, char Channel){
	
	if(Channel == CHANNEL_1 ){
		// Tim->CCER &= ~(    );
		// Tim->CCMR1 &= ~(    );
		
		Tim->CCER |= TIM_CCER_CC1E;
		Tim->CCMR1 |= TIM_CCMR1_OC1M;
	}
	else if(Channel == CHANNEL_2 ){
		Tim->CCER |= TIM_CCER_CC2E;
		Tim->CCMR1 |= TIM_CCMR1_OC2M;
	}
	else if(Channel == 	CHANNEL_3 ){
		Tim->CCER |= TIM_CCER_CC3E;
		Tim->CCMR2 |= TIM_CCMR2_OC3M;
	}
	else if(Channel == CHANNEL_4 ){
		Tim->CCER |= TIM_CCER_CC4E;
		Tim->CCMR2 |= TIM_CCMR2_OC4M;
	}
}

void PWM_set(TIM_TypeDef *Tim ,char Channel,unsigned short value){
	
	if (Channel == CHANNEL_1){
		Tim->CCR1 = value;
	}
	if (Channel == CHANNEL_2){
		Tim->CCR2 = value;
	}
	if (Channel == CHANNEL_3){
		Tim->CCR3 = value;
	}
	if (Channel == CHANNEL_4){
		Tim->CCR4 = value;
	}
}



