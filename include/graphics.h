/**
 * @file	graphics.h
 * @author  Eriks Zaharans
 * @date    17 Sep 2015
 *
 * @section DESCRIPTION
 *
 * Graphics library header file.
 */

#ifndef __GRAPHICS_H
#define __GRAPHICS_H

/* -- Includes -- */

/* -- Defines -- */
#define s_GRAPHICS__LCD_WIDTH		s_SHARPLCD__WIDTH			// LCD Width
#define s_GRAPHICS__LCD_HEIGHT		s_SHARPLCD__HEIGHT			// LCD Height

#define s_GRAPHICS__WIDTH			(s_GRAPHICS__LCD_WIDTH / 8)	// Number of bytes for one row
#define s_GRAPHICS__HEIGHT			s_GRAPHICS__LCD_HEIGHT		// Number of rows

#define s_GRAPHICS__WIDTH_EXT		(s_GRAPHICS__WIDTH + 2)		// Number of bytes per row + address and dummy
#define s_GRAPHICS__BUFFER_SIZE		(s_GRAPHICS__HEIGHT * s_GRAPHICS__WIDTH_EXT + 2) // Size of graphics buffer

/* -- Macros -- */
#define m_Swap(a, b) { uint8_t t = a; a = b; b = t; }

/* -- Constants -- */

/* -- Constants -- */
// Horizontal byte template
//const uint8_t s_Graphics_HByteTpl[8] = {0x00,0x01,0x03,0x07,0x0F,0x1F,0x3F,0x7F,0xFF};

/* -- Enumurations -- */

/**
 * @brief Graphics Color
 */
typedef enum s_GRAPHICS_COLOR_ENUM {
	s_GRAPHICS_COLOR__BLACK = 0,
	s_GRAPHICS_COLOR__WHITE
} GraphicsColor_t;

/**
 * @brief Graphics Color
 */
typedef enum s_GRAPHICS_TEXT_ALIGNMENT_ENUM {
	s_GRAPHICS_TEXT_ALIGN__LEFT = 0,
	s_GRAPHICS_TEXT_ALIGN__CENTER,
	s_GRAPHICS_TEXT_ALIGN__RIGHT
} GraphicsTextAlignment_t;

/* -- Typedefs -- */

/**
 * @brief Graphics Object structure
 */
typedef struct s_GRAPHICS_OBJECT_STRUCT
{
	// Active buffer pointer
	uint8_t *pBuf;
	// Graphics buffers
	uint8_t buffer1[s_GRAPHICS__BUFFER_SIZE];
	uint8_t buffer2[s_GRAPHICS__BUFFER_SIZE];
	// Cursor
	uint8_t xCursor;
	uint8_t yCursor;

} GraphicsObj_t;

/* -- Function Prototypes -- */
void Graphics_Init(GraphicsObj_t *Obj);
void Graphics_ClearBuffer(GraphicsObj_t *Obj, GraphicsColor_t Color);
void Graphics_DrawPixel(GraphicsObj_t *Obj, uint8_t X, uint8_t Y, GraphicsColor_t Color);
void Graphics_DrawHLine(GraphicsObj_t *Obj, uint8_t X1, uint8_t X2, uint8_t Y, GraphicsColor_t Color);
void Graphics_DrawVLine(GraphicsObj_t *Obj, uint8_t X, uint8_t Y1, uint8_t Y2, GraphicsColor_t Color);
void Graphics_DrawLine(GraphicsObj_t *Obj, uint8_t X1, uint8_t Y1, uint8_t X2, uint8_t Y2, GraphicsColor_t Color);
void Graphics_DrawCircle(GraphicsObj_t *Obj, uint8_t X, uint8_t Y, uint8_t R, GraphicsColor_t Color);
void Graphics_FillCircle(GraphicsObj_t *Obj, uint8_t X, uint8_t Y, uint8_t R, GraphicsColor_t Color);
void Graphics_FillCircleHelper(GraphicsObj_t *Obj, uint8_t X, uint8_t Y, uint8_t R, uint8_t CornerName, int16_t Delta, GraphicsColor_t Color);
void Graphics_DrawRect(GraphicsObj_t *Obj, uint8_t X, uint8_t Y, uint8_t W, uint8_t H, GraphicsColor_t Color);
void Graphics_FillRect(GraphicsObj_t *Obj, uint8_t X, uint8_t Y, uint8_t W, uint8_t H, GraphicsColor_t Color);
void Graphics_DrawBitmap(GraphicsObj_t *Obj, uint8_t X, uint8_t Y, const uint8_t *Bitmap, uint8_t W, uint8_t H, GraphicsColor_t Color);

void Graphics_DrawChar(GraphicsObj_t *Obj, uint8_t X, uint8_t Y, uint8_t Char, GraphicsColor_t Color);
void Graphics_DrawString(GraphicsObj_t *Obj, uint8_t X, uint8_t Y, uint8_t *String, GraphicsColor_t Color);

void Graphics_DrawCharNew(GraphicsObj_t *Obj, uint8_t X, uint8_t Y, uint8_t Char, GraphicsColor_t Color);
void Graphics_DrawText(GraphicsObj_t *Obj, uint8_t X, uint8_t Y, uint8_t *String, FontInfo_t Font, GraphicsTextAlignment_t Alignment, GraphicsColor_t Color);

#endif /* __GRAPHICS_H */
