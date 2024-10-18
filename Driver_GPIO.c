#include "DRIVE_GPIO.H"


// Initialising the GPIO given (in use)
void MyGPIO_Init(GPIO_TypeDef *GPIO, uint8_t GPIO_Pin, uint8_t GPIO_Conf){
	// Enable port
	if(GPIO == GPIOA){ // PORT A
		RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	}
	else if (GPIO == GPIOB){
		RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
	}
	else if (GPIO == GPIOC){
		RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
	}
	else if (GPIO == GPIOD){
		RCC->APB2ENR |= RCC_APB2ENR_IOPDEN;
	}
	
	// config branches
	
	// reset 
	MyGPIO_Reset(GPIO, GPIO_Pin);
	if (GPIO_Pin < 8){
		GPIO->CRL &= ~((0b1111)<<(GPIO_Pin * 4)); 
		GPIO->CRL |= (GPIO_Conf<<(GPIO_Pin * 4));
	}
	else{
		GPIO->CRH &= ~((0b1111)<<((GPIO_Pin-8) * 4)); 
		GPIO->CRH |= (GPIO_Conf<<((GPIO_Pin-8) * 4));
	}
}

// READ VALUE = Returns if pin at 1 or 0
int MyGPIO_Read(GPIO_TypeDef *GPIO, uint8_t GPIO_Pin){
	return (GPIO->IDR & (0b1<<GPIO_Pin)); // GPIO->IDR & (0x1<<13) return either 1 or 0
}

// TURN ON = Sets pin at 1 or 0
void MyGPIO_Set(GPIO_TypeDef *GPIO, uint8_t GPIO_Pin){
		GPIO->ODR |= (0b1<<GPIO_Pin);
}

// TURN OFF = reset pin to 0 
void MyGPIO_Reset(GPIO_TypeDef *GPIO, uint8_t GPIO_Pin){
	GPIO->ODR &= ~(0b1<<GPIO_Pin);
}

// Alternate state
void MyGPIO_Toggle(GPIO_TypeDef *GPIO, uint8_t GPIO_Pin){
	if (MyGPIO_Read(GPIO, GPIO_Pin) == 0){ // if 0 set to 1
		MyGPIO_Set(GPIO,GPIO_Pin);
	}
	else{ // if 1 set to 0
		MyGPIO_Reset(GPIO, GPIO_Pin);
	}
}