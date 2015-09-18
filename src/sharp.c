/**
 * @file	sharp.c
 * @author  Eriks Zaharans
 * @date    15 Sep 2015
 *
 * @section DESCRIPTION
 *
 * Sharp Memory LCD library.
 */

/* -- Includes -- */
/* system libraries */
/* project libraries */
#include "main.h"

/* -- Defines -- */

/* -- Variables -- */
uint8_t g_SharpLcd_Power = 0;

SPI_HandleTypeDef g_SharpLcd_SpiHandle;

/* -- Functions -- */

/**
 * Initialize Sharp LCD
 * @param void No arguments
 * @return void No return
 */
void SharpLcd_Init(void)
{
	// Local variables
	GPIO_InitTypeDef GPIO_InitStruct;

	// Init GPIO
	__GPIOA_CLK_ENABLE();
	__GPIOB_CLK_ENABLE();

	// Control Pins
	GPIO_InitStruct.Pin = s_SHARPLCD__DISP | s_SHARPLCD__SCS;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLDOWN;
	GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
	HAL_GPIO_Init(s_SHARPLCD__CTRL_PORT, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = s_SHARPLCD__EXTCOMIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLDOWN;
	GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
	HAL_GPIO_Init(s_SHARPLCD__VCOM_PORT, &GPIO_InitStruct);

	// SPI Pins
	GPIO_InitStruct.Pin = s_SHARPLCD__SCLK | s_SHARPLCD__SI;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF5_SPI2;
	HAL_GPIO_Init(s_SHARPLCD__SPI_PORT, &GPIO_InitStruct);

	// Set initial state of GPIO
	s_SHARPLCD__DISP_RESET();
	s_SHARPLCD__SCS_RESET();
	s_SHARPLCD__EXTCOMIN_RESET();

	// Init SPI
	__SPI2_CLK_ENABLE();

	g_SharpLcd_SpiHandle.Instance = SPI2;
	g_SharpLcd_SpiHandle.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_32;
	g_SharpLcd_SpiHandle.Init.Mode = SPI_MODE_MASTER;
	g_SharpLcd_SpiHandle.Init.Direction = SPI_DIRECTION_2LINES;
	g_SharpLcd_SpiHandle.Init.DataSize = SPI_DATASIZE_8BIT;
	g_SharpLcd_SpiHandle.Init.CLKPolarity = SPI_POLARITY_LOW;
	g_SharpLcd_SpiHandle.Init.CLKPhase = SPI_PHASE_1EDGE;
	g_SharpLcd_SpiHandle.Init.NSS = SPI_NSS_SOFT;
	g_SharpLcd_SpiHandle.Init.FirstBit = SPI_FIRSTBIT_LSB;
	g_SharpLcd_SpiHandle.Init.TIMode = SPI_TIMODE_DISABLED;
	g_SharpLcd_SpiHandle.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLED;
	g_SharpLcd_SpiHandle.Init.CRCPolynomial = 10;
	g_SharpLcd_SpiHandle.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
	g_SharpLcd_SpiHandle.Init.NSSPMode = SPI_NSS_PULSE_DISABLED;
	HAL_SPI_Init(&g_SharpLcd_SpiHandle);

}

/**
 * Deinitialize Sharp LCD
 * @param void No arguments
 * @return void No return
 */
void SharpLcd_Deinit(void)
{
	// Deinit GPIO
	// ...
	// Control Pins
	HAL_GPIO_DeInit(s_SHARPLCD__CTRL_PORT, s_SHARPLCD__DISP);
	HAL_GPIO_DeInit(s_SHARPLCD__VCOM_PORT, s_SHARPLCD__EXTCOMIN);
	// SPI Pins
	HAL_GPIO_DeInit(s_SHARPLCD__SPI_PORT, s_SHARPLCD__SCLK|s_SHARPLCD__SI|s_SHARPLCD__SCS);

	// Deinit SPI
	__SPI2_CLK_DISABLE();
}

/**
 * Clear Sharp LCD
 * @param void No arguments
 * @return void No return
 */
void SharpLcd_Clear(void)
{
	uint8_t buf[2];

	// Chip select
	s_SHARPLCD__SCS_SET();
	// Wait
	HAL_Delay(1);

	// Set command
	buf[0] = 0x04;
	// Set dummy
	buf[1] = 0x00;

	// Send data
	HAL_SPI_Transmit(&g_SharpLcd_SpiHandle, buf, 2, 1000);

	// Wait
	HAL_Delay(1);
	// Chip deselect
	s_SHARPLCD__SCS_RESET();
	// Wait
	HAL_Delay(1);
}

/**
 * Update Sharp LCD from buffer
 * @param void No arguments
 * @return void No return
 */
void SharpLcd_UpdateFrame(uint8_t Data)
{
	uint8_t i;
	uint8_t buf[22];
	uint8_t addr = 1;

	// Chip select
	s_SHARPLCD__SCS_SET();

	// Set command
	buf[0] = 0x01;
	// Set address
	buf[1] = addr++;

	// Set data
	for(i = 0; i < 18; i++) {
		buf[2+i] = Data;
	}

	// Send start
	HAL_SPI_Transmit(&g_SharpLcd_SpiHandle, buf, 20, 1000);

	// Send all other lines
	buf[0] = 0x00;
	for(i = 0; i < 167; i++) {
		buf[1] = addr++;
		HAL_SPI_Transmit(&g_SharpLcd_SpiHandle, buf, 20, 1000);
	}

	buf[0] = 0x00;
	buf[1] = 0x00;

	HAL_SPI_Transmit(&g_SharpLcd_SpiHandle, buf, 2, 1000);

	// Chip deselect
	s_SHARPLCD__SCS_RESET();
}

void SharpLcd_PowerOn(void)
{
	// Set display power state to ON
	g_SharpLcd_Power = 1;
	// Enable display
	s_SHARPLCD__DISP_SET();
	// Delay
	HAL_Delay(1);
}

void SharpLcd_PowerOff(void)
{
	// Set display power state to OFF
	g_SharpLcd_Power = 0;
	// Disable display
	s_SHARPLCD__EXTCOMIN_RESET();
	s_SHARPLCD__DISP_RESET();
}

void SharpLcd_VcomHandle(void)
{
	static uint32_t counter = 0;

	// If display is ON
	if(g_SharpLcd_Power > 0) {

		if(counter >= 100) {
			s_SHARPLCD__EXTCOMIN_TOGGLE();
			s_MAIN__LED1_TOGGLE();
			counter = 0;
		} else {
			counter++;
		}
	}


}




void SharpLcd_DisplayBuffer(uint8_t *Buffer)
{
	// Chip select
	s_SHARPLCD__SCS_SET();

	// Send data
	HAL_SPI_Transmit(&g_SharpLcd_SpiHandle, Buffer, 168*20+2, 3000);

	// Chip deselect
	s_SHARPLCD__SCS_RESET();
}


