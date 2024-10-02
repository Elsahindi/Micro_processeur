#ifndef MYGPIO_H
#define MYGPIO_H

#include "stm32f10x.h"

/**
 * Structure to represent a GPIO pin configuration.
 */
typedef struct {
    GPIO_TypeDef *GPIO; /**< Pointer to the GPIO port. */
    uint8_t GPIO_Pin; /**< Pin number (0-15). */
    uint8_t GPIO_Conf; /**< Pin configuration. */
} MyGPIO_Struct_TypeDef;

/**
 * GPIO pin configuration definitions.
 */
#define In_Floating  0b0100 /**< Floating input. */
#define In_PullDown  0b1000 /**< Pull-down input. */
#define In_PullUp    0b1000 /**< Pull-up input. */
#define In_Analog    0b0000 /**< Analog input. */
#define Out_PP       0b0010 /**< Push-pull output. */
#define Out_OD       0b0110 /**< Open-drain output. */
#define AltOut_PP    0b1010 /**< Alternate push-pull output. */
#define AltOut_OD    0b1110 /**< Alternate open-drain output. */

/**
 * Function prototypes for GPIO operations.
 */
void MyGPIO_Init(GPIO_TypeDef *GPIO, uint8_t GPIO_Pin, uint8_t GPIO_Conf);
int MyGPIO_Read(GPIO_TypeDef *GPIO, uint8_t GPIO_Pin);
void MyGPIO_Set(GPIO_TypeDef *GPIO, uint8_t GPIO_Pin);
void MyGPIO_Reset(GPIO_TypeDef *GPIO, uint8_t GPIO_Pin);
void MyGPIO_Toggle(GPIO_TypeDef *GPIO, uint8_t GPIO_Pin);

#endif /* MYGPIO_H */