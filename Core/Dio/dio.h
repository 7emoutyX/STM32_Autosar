#ifndef DIO_H
#define DIO_H

#include "stm32wbxx_hal.h" // Include HAL library for STM32WB

// Define Dio_LevelType
typedef uint8_t Dio_LevelType;
#define STD_HIGH 1U
#define STD_LOW  0U

// Define pin modes
typedef enum {
    DIO_PIN_MODE_INPUT,
    DIO_PIN_MODE_OUTPUT
} Dio_PinModeType;

// Define Dio_ConfigType to store GPIO port, pin, and mode info
typedef struct {
    GPIO_TypeDef *port;       // GPIO port (e.g., GPIOA, GPIOB)
    uint16_t pin;             // GPIO pin (e.g., GPIO_PIN_0, GPIO_PIN_1)
    Dio_PinModeType mode;     // Input or Output
} Dio_ConfigType;

// Function prototypes for DIO module
void Dio_Init(Dio_ConfigType *config);
Dio_LevelType Dio_ReadChannel(Dio_ConfigType *config);
void Dio_WriteChannel(Dio_ConfigType *config, Dio_LevelType level);

#endif // DIO_H
