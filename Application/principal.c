#include "stm32f10x.h"
#include "Drive_GPIO.h"
#include "MyTimer.h"

//#define TEST
//#define GPIOTP1
#define TIMERTP2

int main ( void )
{
	// TESTS
	#ifdef TEST 
	GPIO_TypeDef *gpio[4]={GPIOA,GPIOB,GPIOC,GPIOD};
	uint8_t conf[8]={In_Floating, In_PullDown, In_PullUp, In_Analog, Out_PP, Out_OD, AltOut_PP, AltOut_OD};
	uint8_t c_gpio, c_pin, c_conf;
	
	for(c_gpio=0; c_gpio<4 ; c_gpio++){
		for(c_conf=0; c_conf<8 ; c_conf++){
			for(c_pin=0; c_pin<16 ; c_pin++){
				MyGPIO_Init(gpio[c_gpio], c_pin, conf[c_conf]);
			}
		}
	}
	#endif 
	
	#ifdef GPIOTP1
	// INITIALISATION
	
	//RCC->APB2ENR |= (0x01 << 2) | (0x01 << 3) | (0x01 << 4) ;
	MyGPIO_Init(GPIOC, 8, In_Floating); // Push button externe
	MyGPIO_Init(GPIOC, 13, In_Floating); // Push button interne
	MyGPIO_Init(GPIOC, 10, Out_PP); // LED
	
	//	GPIOA->CRL &= ~(0xF<<4) ;
	//	GPIOA->CRL |= (0x2<<4) ;
	//	GPIOC->CRH = 0x44444244;
	
	
	// LOOP
	while (1)
	{
		// READ BUTTON AND SET LED TO CORRECT STATE
		//if (((GPIOC->IDR & (0x1<<8)) != 0x0) || ((GPIOC->IDR & (0x1<<13)) != 0x0)) {   // if (IDR & Masque != 0) ...
		if ((MyGPIO_Read(GPIOC, 8) !=0)	|| (MyGPIO_Read(GPIOC,13)!=0 )){ // BUTTONS PUSHED (either of them)
			MyGPIO_Set(GPIOC,10); //GPIOC->ODR |= (0x1<<10); LED ON
		}
		else{ // NO BUTTONS PUSHED
			MyGPIO_Reset(GPIOC, 10);  //GPIOC->ODR &= ~(0x1<<10); LED OFF
		}
	}
	#endif 
	
	#ifdef TIMERTP2
	
	
	// SET UP clock 500ms
	MyTimer_Base_Init(TIM1, 4999, 7199);
	
	while(1){
	
	}
	
	#endif
}
