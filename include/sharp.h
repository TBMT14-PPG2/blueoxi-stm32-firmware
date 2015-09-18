/**
 * @file	sharp.h
 * @author  Eriks Zaharans
 * @date    15 Sep 2015
 *
 * @section DESCRIPTION
 *
 * Sharp Memory LCD library header file.
 */

#ifndef __SHARP_H
#define __SHARP_H

/* -- Includes -- */

/* -- Defines -- */

// Display pinout
#define s_SHARPLCD__SPI_PORT			GPIOB
#define s_SHARPLCD__SCLK				GPIO_PIN_13
#define s_SHARPLCD__SI					GPIO_PIN_15

#define s_SHARPLCD__VCOM_PORT			GPIOA
#define s_SHARPLCD__EXTCOMIN			GPIO_PIN_9
#define s_SHARPLCD__EXTCOMIN_SET()		s_SHARPLCD__VCOM_PORT->BSRRL = s_SHARPLCD__EXTCOMIN
#define s_SHARPLCD__EXTCOMIN_RESET()	s_SHARPLCD__VCOM_PORT->BSRRH = s_SHARPLCD__EXTCOMIN
#define s_SHARPLCD__EXTCOMIN_TOGGLE()	s_SHARPLCD__VCOM_PORT->ODR ^= s_SHARPLCD__EXTCOMIN

#define s_SHARPLCD__CTRL_PORT			GPIOB
#define s_SHARPLCD__DISP				GPIO_PIN_14
#define s_SHARPLCD__DISP_SET()			s_SHARPLCD__CTRL_PORT->BSRRL = s_SHARPLCD__DISP
#define s_SHARPLCD__DISP_RESET()		s_SHARPLCD__CTRL_PORT->BSRRH = s_SHARPLCD__DISP
#define s_SHARPLCD__SCS					GPIO_PIN_12
#define s_SHARPLCD__SCS_SET()			s_SHARPLCD__CTRL_PORT->BSRRL = s_SHARPLCD__SCS
#define s_SHARPLCD__SCS_RESET()			s_SHARPLCD__CTRL_PORT->BSRRH = s_SHARPLCD__SCS

// Display resolution
#define s_SHARPLCD__WIDTH				144
#define s_SHARPLCD__HEIGHT				168


/* -- Constants -- */

/* -- Constants -- */

/* -- Enumurations -- */

/* -- Types -- */

/* -- Extern -- */


/* -- Function Prototypes -- */

void SharpLcd_Init(void);
void SharpLcd_Deinit(void);
void SharpLcd_Clear(void);
void SharpLcd_UpdateFrame(uint8_t Data);

void SharpLcd_PowerOn(void);
void SharpLcd_PowerOff(void);
void SharpLcd_VcomHandle(void);
void SharpLcd_DisplayBuffer(uint8_t *Buffer);



#endif /* __SHARP_H */
