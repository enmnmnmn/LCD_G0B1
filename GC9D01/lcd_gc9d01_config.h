#pragma once

#include "stm32g0xx_hal.h"
#include "spi.h"
#include "gpio.h"


#define LCD_COLOR_BLACK  0x0000
#define LCD_COLOR_RED    0xf800
#define LCD_COLOR_GREEN  0x07e0
#define LCD_COLOR_BLUE   0x001f
#define LCD_COLOR_YELLOW (LCD_COLOR_RED | LCD_COLOR_GREEN)
#define LCD_COLOR_CYAN   (LCD_COLOR_GREEN | LCD_COLOR_BLUE)
#define LCD_COLOR_PURPLE (LCD_COLOR_RED | LCD_COLOR_BLUE)
#define LCD_COLOR_WHITE  (LCD_COLOR_RED | LCD_COLOR_GREEN | LCD_COLOR_BLUE)


#define Delay(x)            HAL_Delay(x)
#define LCD_SPI hspi1
#define LCD_DC(Level)       HAL_GPIO_WritePin(LCD_D_C_GPIO_Port, LCD_D_C_Pin, (GPIO_PinState)Level)
#define LCD_CS(Level)       HAL_GPIO_WritePin(SPI1_CS_GPIO_Port, SPI1_CS_Pin, (GPIO_PinState)Level)
#define LCD_LED(Level)      HAL_GPIO_WritePin(LCD_Back_GPIO_Port, LCD_Back_Pin, (GPIO_PinState)Level)
#define LCD_RES(Level)      HAL_GPIO_WritePin(LCD_RES_GPIO_Port, LCD_RES_Pin, (GPIO_PinState)Level)

#define SCREEN_WIDTH 160
#define SCREEN_HEIGHT 40

