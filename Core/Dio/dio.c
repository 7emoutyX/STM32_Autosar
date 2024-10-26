#include "dio.h"

// Dio_Init: Initialize the GPIO pin based on configuration
void Dio_Init(Dio_ConfigType *config) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    if (config->port == GPIOA) {
        __HAL_RCC_GPIOA_CLK_ENABLE();
    } else if (config->port == GPIOB) {
        __HAL_RCC_GPIOB_CLK_ENABLE();
    } else if (config->port == GPIOC) {
        __HAL_RCC_GPIOC_CLK_ENABLE();
    } else if (config->port == GPIOD) {
        __HAL_RCC_GPIOD_CLK_ENABLE();
    }

    // Configure the pin mode
    GPIO_InitStruct.Pin = config->pin;
    if (config->mode == DIO_PIN_MODE_OUTPUT) {
        GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    } else if (config->mode == DIO_PIN_MODE_INPUT) {
        GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
        GPIO_InitStruct.Pull = GPIO_PULLUP; // Change to GPIO_PULLUP if pull-up is needed
    }

    HAL_GPIO_Init(config->port, &GPIO_InitStruct);
}

// Dio_ReadChannel: Read the level of the specified pin
Dio_LevelType Dio_ReadChannel(Dio_ConfigType *config) {
    return (Dio_LevelType)HAL_GPIO_ReadPin(config->port, config->pin);
}

// Dio_WriteChannel: Set the specified pin to the given level
void Dio_WriteChannel(Dio_ConfigType *config, Dio_LevelType level) {
    HAL_GPIO_WritePin(config->port, config->pin, (GPIO_PinState)level);
}
