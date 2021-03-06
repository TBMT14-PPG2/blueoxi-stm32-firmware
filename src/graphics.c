/**
 * @file	graphics.c
 * @author  Eriks Zaharans
 * @date    17 Sep 2015
 *
 * @section DESCRIPTION
 *
 * Graphics library.
 */

/* -- Includes -- */
/* system libraries */
/* project libraries */
#include "main.h"

/* -- Defines -- */

/* -- Variables -- */

/* -- Functions -- */


/**
 * Init Graphics object
 * @param Obj 		Pointer to graphics object
 * @return void 	Return void
 */
void Graphics_Init(GraphicsObj_t *Obj)
{
	// Init first buffer as active
	Obj->pBuf = Obj->buffer1;
}

/**
 * Swap active buffer
 * @param Obj 		Pointer to graphics object
 * @return void 	Return void
 */
void Graphics_SwapBuffer(GraphicsObj_t *Obj)
{
	if(Obj->pBuf == Obj->buffer1) {
		Obj->pBuf = Obj->buffer2;
	} else {
		Obj->pBuf = Obj->buffer1;
	}
}

/**
 * Clear active buffer
 * @param Obj 		Pointer to graphics object
 * @return void 	Return void
 */
void Graphics_ClearBuffer(GraphicsObj_t *Obj, GraphicsColor_t Color)
{
	uint8_t i;
	uint8_t *ptr;

	// Clear buffer depending on the color
	if(Color == s_GRAPHICS_COLOR__WHITE) {
		memset(Obj->pBuf, 0xFF, sizeof(uint8_t) * s_GRAPHICS__BUFFER_SIZE);
	} else {
		memset(Obj->pBuf, 0x00, sizeof(uint8_t) * s_GRAPHICS__BUFFER_SIZE);
	}

	ptr = Obj->pBuf;
	// Set write CMD on the first byte
	*(ptr++) = 0x01;
	// Set row addresses in buffer
	for(i = 0; i < s_GRAPHICS__HEIGHT; i++) {
		*(ptr) = i+1;
		ptr += s_GRAPHICS__WIDTH_EXT;
	}
}

/**
 * Draw pixel in the buffer
 * @param Obj 		Pointer to graphics object
 * @param X 		X position
 * @param Y 		Y position
 * @param Color		Color of the pixel
 * @return void 	Return void
 */
void Graphics_DrawPixel(GraphicsObj_t *Obj, uint8_t X, uint8_t Y, GraphicsColor_t Color)
{
	uint8_t *ptr;
	uint8_t xByte, xBit;

	// TODO: Check range

	xByte = X / 8;
	xBit = X % 8;

	// Go to right byte in the buffer
	ptr = Obj->pBuf + (s_GRAPHICS__WIDTH_EXT * Y) + xByte + 2;
	// Set or Reset pixel
	if(Color == s_GRAPHICS_COLOR__WHITE) {
		*(ptr) |= 1 << xBit;
	} else {
		*(ptr) &= ~(1 << xBit);
	}
}

/**
 * Draw a horizontal line in the buffer
 * @param Obj 		Pointer to graphics object
 * @param X1 		X1 position
 * @param X2 		X2 position
 * @param Y 		Y position
 * @param Color		Color of the pixel
 * @return void 	Return void
 */
void Graphics_DrawHLine(GraphicsObj_t *Obj, uint8_t X1, uint8_t X2, uint8_t Y, GraphicsColor_t Color)
{
	uint8_t i;
	uint8_t *ptr;
	uint8_t xByte, xBit, xLen;

	// TODO: Check range

	// Calculate X
	if(X1 <= X2) {
		xByte = X1 / 8;
		xBit = X1 % 8;
		xLen = X2 - X1;
	} else {
		xByte = X2 / 8;
		xBit = X2 % 8;
		xLen = X1 - X2;
	}

	// Go to right byte in the buffer
	ptr = Obj->pBuf + (s_GRAPHICS__WIDTH_EXT * Y) + xByte + 2;
	// Choose color
	if(Color == s_GRAPHICS_COLOR__WHITE) {
		// Set pixels
		for(i = 0; i < xLen; i++) {
			*(ptr) |= 1 << xBit;
			xBit++;
			if(xBit == 8) {
				ptr++;
				xBit = 0;
			}
		}
	} else {
		// Reset pixels
		for(i = 0; i < xLen; i++) {
			*(ptr) &= ~(1 << xBit);
			xBit++;
			if(xBit == 8) {
				ptr++;
				xBit = 0;
			}
		}
	}
}

/**
 * Draw a vertical line in the buffer
 * @param Obj 		Pointer to graphics object
 * @param X 		X position
 * @param Y1 		Y1 position
 * @param Y2 		Y2 position
 * @param Color		Color of the pixel
 * @return void 	Return void
 */
void Graphics_DrawVLine(GraphicsObj_t *Obj, uint8_t X, uint8_t Y1, uint8_t Y2, GraphicsColor_t Color)
{
	uint8_t i;
	uint8_t *ptr;
	uint8_t xByte, xBit;
	uint8_t yStart, yLen;

	// TODO: Check range

	// Calculate X
	xByte = X / 8;
	xBit = X % 8;

	// Calculate Y
	if(Y1 <= Y2) {
		yStart = Y1;
		yLen = Y2 - Y1;
	} else {
		yStart = Y2;
		yLen = Y1 - Y2;
	}

	// Go to right byte in the buffer
	ptr = Obj->pBuf + (s_GRAPHICS__WIDTH_EXT * yStart) + xByte + 2;
	// Choose color
	if(Color == s_GRAPHICS_COLOR__WHITE) {
		// Set pixels
		for(i = 0; i < yLen; i++) {
			*(ptr) |= 1 << xBit;
			ptr += s_GRAPHICS__WIDTH_EXT;
		}
	} else {
		// Reset pixels
		for(i = 0; i < yLen; i++) {
			*(ptr) &= ~(1 << xBit);
			ptr += s_GRAPHICS__WIDTH_EXT;
		}
	}
}

/**
 * Draw a line in the buffer
 * Adapted from Adafruit_GFX library
 * @param Obj 		Pointer to graphics object
 * @param X1 		X1 position
 * @param Y1 		Y1 position
 * @param X2 		X2 position
 * @param Y2 		Y2 position
 * @param Color		Color of the pixel
 * @return void 	Return void
 */
void Graphics_DrawLine(GraphicsObj_t *Obj, uint8_t X1, uint8_t Y1, uint8_t X2, uint8_t Y2, GraphicsColor_t Color)
{
	// TODO: Check range

	int16_t steep = abs(Y2 - Y1) > abs(X2 - X1);
	if (steep) {
		m_Swap(X1, Y1);
		m_Swap(X2, Y2);
	}

	if (X1 > X2) {
		m_Swap(X1, X2);
		m_Swap(Y1, Y2);
	}

	int16_t dx, dy;
	dx = X2 - X1;
	dy = abs(Y2 - Y1);

	int16_t err = dx / 2;
	int16_t ystep;

	if (Y1 < Y2) {
		ystep = 1;
	} else {
		ystep = -1;
	}

	for (; X1 <= X2; X1++) {
		if (steep) {
			Graphics_DrawPixel(Obj, Y1, X1, Color);
		} else {
			Graphics_DrawPixel(Obj, X1, Y1, Color);
		}
		err -= dy;
		if (err < 0) {
			Y1 += ystep;
			err += dx;
		}
	}
}



/**
 * Draw a circle in the buffer
 * Adapted from Adafruit_GFX library
 * @param Obj 		Pointer to graphics object
 * @param X 		Center X position
 * @param Y 		Center Y position
 * @param R 		Radius of circle
 * @param Color		Color of the pixel
 * @return void 	Return void
 */
void Graphics_DrawCircle(GraphicsObj_t *Obj, uint8_t X, uint8_t Y, uint8_t R, GraphicsColor_t Color)
{
	int16_t f = 1 - R;
	int16_t ddF_x = 1;
	int16_t ddF_y = -2 * R;
	int16_t x = 0;
	int16_t y = R;

	Graphics_DrawPixel(Obj, X  , Y+R, Color);
	Graphics_DrawPixel(Obj, X  , Y-R, Color);
	Graphics_DrawPixel(Obj, X+R, Y  , Color);
	Graphics_DrawPixel(Obj, X-R, Y  , Color);

	while (x<y) {
		if (f >= 0) {
			y--;
			ddF_y += 2;
			f += ddF_y;
		}
		x++;
		ddF_x += 2;
		f += ddF_x;

		Graphics_DrawPixel(Obj, X + x, Y + y, Color);
		Graphics_DrawPixel(Obj, X - x, Y + y, Color);
		Graphics_DrawPixel(Obj, X + x, Y - y, Color);
		Graphics_DrawPixel(Obj, X - x, Y - y, Color);
		Graphics_DrawPixel(Obj, X + y, Y + x, Color);
		Graphics_DrawPixel(Obj, X - y, Y + x, Color);
		Graphics_DrawPixel(Obj, X + y, Y - x, Color);
		Graphics_DrawPixel(Obj, X - y, Y - x, Color);
	}
}

/**
 * Fill a circle in the buffer
 * Adapted from Adafruit_GFX library
 * @param Obj 		Pointer to graphics object
 * @param X 		Center X position
 * @param Y 		Center Y position
 * @param R 		Radius of circle
 * @param Color		Color of the pixel
 * @return void 	Return void
 */
void Graphics_FillCircle(GraphicsObj_t *Obj, uint8_t X, uint8_t Y, uint8_t R, GraphicsColor_t Color)
{
	Graphics_DrawVLine(Obj, X, Y-R, Y+R+1, Color);
	Graphics_FillCircleHelper(Obj, X, Y, R, 3, 0, Color);
}

/**
 * Fill circle helper function
 * Adapted from Adafruit_GFX library
 * @param Obj 			Pointer to graphics object
 * @param X 			Center X position
 * @param Y 			Center Y position
 * @param R 			Radius of circle
 * @param CornerName 	Radius of circle
 * @param Delta			Radius of circle
 * @param Color			Color of the pixel
 * @return void 		Return void
 */
void Graphics_FillCircleHelper(	GraphicsObj_t *Obj,
								uint8_t X,
								uint8_t Y,
								uint8_t R,
								uint8_t CornerName,
								int16_t Delta,
								GraphicsColor_t Color)
{
	int16_t f = 1 - R;
	int16_t ddF_x = 1;
	int16_t ddF_y = -2 * R;
	int16_t x = 0;
	int16_t y = R;

	while (x<y) {
		if (f >= 0) {
			y--;
			ddF_y += 2;
			f += ddF_y;
		}
		x++;
		ddF_x += 2;
		f += ddF_x;

		if (CornerName & 0x1) {
			Graphics_DrawVLine(Obj, X+x, Y-y, Y+y+1+Delta, Color);
			Graphics_DrawVLine(Obj, X+y, Y-x, Y+x+1+Delta, Color);
		}
		if (CornerName & 0x2) {
			Graphics_DrawVLine(Obj, X-x, Y-y, Y+y+1+Delta, Color);
			Graphics_DrawVLine(Obj, X-y, Y-x, Y+x+1+Delta, Color);
		}
	}
}


/**
 * Draw rectangle in the buffer
 * Adapted from Adafruit_GFX library
 * @param Obj 			Pointer to graphics object
 * @param X 			Start X position
 * @param Y 			Start Y position
 * @param W 			Width of rectangle
 * @param H 			Height of rectangle
 * @param Color			Color of the pixel
 * @return void 		Return void
 */
void Graphics_DrawRect(GraphicsObj_t *Obj, uint8_t X, uint8_t Y, uint8_t W, uint8_t H, GraphicsColor_t Color)
{
	Graphics_DrawHLine(Obj, X, X+W, Y, Color);
	Graphics_DrawHLine(Obj, X, X+W, Y+H-1, Color);
	Graphics_DrawVLine(Obj, X, Y, Y+H, Color);
	Graphics_DrawVLine(Obj, X+W-1, Y, Y+H, Color);
}

/**
 * Fill rectangle in the buffer
 * Adapted from Adafruit_GFX library
 * @param Obj 			Pointer to graphics object
 * @param X 			Start X position
 * @param Y 			Start Y position
 * @param W 			Width of rectangle
 * @param H 			Height of rectangle
 * @param Color			Color of the pixel
 * @return void 		Return void
 */
void Graphics_FillRect(GraphicsObj_t *Obj, uint8_t X, uint8_t Y, uint8_t W, uint8_t H, GraphicsColor_t Color)
{
	uint8_t i;

	for (i = X; i < X+W; i++) {
		Graphics_DrawVLine(Obj, i, Y, Y+H, Color);
	}
}

/**
 * Draw bitmap in the buffer
 * @param Obj 			Pointer to graphics object
 * @param X 			Start X position
 * @param Y 			Start Y position
 * @param Bitmap 		Pointer to bitmap
 * @param W 			Width of bitmap
 * @param H 			Height of bitmap
 * @param Color			Color of the pixels
 * @return void 		Return void
 */
void Graphics_DrawBitmap(	GraphicsObj_t *Obj,
							uint8_t X,
							uint8_t Y,
							const uint8_t *Bitmap,
							uint8_t W,
							uint8_t H,
							GraphicsColor_t Color)
{
	uint8_t i, j, byteWidth = (W + 7) / 8;
	uint8_t *ptr;

	// TODO: Can be optimized

	for(j = 0; j < H; j++) {
		for(i = 0; i < W; i++ ) {
			ptr = Bitmap + j * byteWidth + i / 8;
			if(!(*(ptr) & (128 >> (i & 7)))) {
				Graphics_DrawPixel(Obj, X+i, Y+j, Color);
			}
		}
	}
}

/**
 * Draw a char in the buffer
 * Adapted from Adafruit_GFX library
 * @param Obj 			Pointer to graphics object
 * @param X 			Start X position
 * @param Y 			Start Y position
 * @param Char 			Char to draw
 * @param Color			Color of the pixel
 * @return void 		Return void
 */
void Graphics_DrawChar(GraphicsObj_t *Obj, uint8_t X, uint8_t Y, uint8_t Char, GraphicsColor_t Color)
{
	uint8_t i, j;
	uint8_t line;

	// TODO: Check range

	for(i = 0; i < 6; i++)
	{
		if (i == 5) {
			line = 0x0;
		} else {
			line = *(s_Font_Default+(Char*5)+i);
		}

		for (j = 0; j < 8; j++)
		{
			if (line & 0x1) {
				Graphics_DrawPixel(Obj, X+i, Y+j, Color);
			}
			line >>= 1;
		}
	}
}

/**
 * Draw a text string in the buffer
 * @param Obj 			Pointer to graphics object
 * @param X 			Start X position
 * @param Y 			Start Y position
 * @param String 		Pointer to string to be drawn
 * @param Color			Color of the pixel
 * @return void 		Return void
 */
void Graphics_DrawString(GraphicsObj_t *Obj, uint8_t X, uint8_t Y, uint8_t *String, GraphicsColor_t Color)
{
	uint8_t x, y;

	// TODO: Check range

	x = X;
	y = Y; // TODO: handle multiline text
	while(*String)
	{
		Graphics_DrawChar(Obj, x, Y, *(String), Color);
		x += 6; // Next char
		String++;
	}
}

/**
 * Draw a text string in the buffer (Custom fonts)
 * @param Obj 			Pointer to graphics object
 * @param X 			Start X position
 * @param Y 			Start Y position
 * @param String 		Pointer to string to be drawn
 * @param Font 			Font structure
 * @param Alignment 	Text alignment
 * @param Color			Color of the pixels
 * @return void 		Return void
 */
void Graphics_DrawText(	GraphicsObj_t *Obj,
						uint8_t X,
						uint8_t Y,
						uint8_t *String,
						FontInfo_t Font,
						GraphicsTextAlignment_t Alignment,
						GraphicsColor_t Color)
{
	// TODO: Clean code!!!

  	// - Variables -
  	uint8_t i, j;
  	uint8_t *ptr, *pStr;
	// Char
	uint16_t char_offset, char_pos;
	uint8_t char_width;
	uint8_t char_part, char_shifted;
	int8_t char_bits_left;
	// Position
	uint16_t initBitPos, initBytePos, bytePos, xNew;

	// Alignment
	uint8_t textWidth = 0;


	// Calculate offset for alignment
	// Set pointer to string
	pStr = String;
	// Loop through chars
	while(*pStr)
	{
		textWidth += Font.charInfo[*pStr - Font.startChar].widthBits;
		textWidth += 2; // Add spacing

		pStr++;
	}
	switch(Alignment)
	{
		case s_GRAPHICS_TEXT_ALIGN__LEFT :
			xNew = X;
			break;
		case s_GRAPHICS_TEXT_ALIGN__CENTER :
			xNew = (s_GRAPHICS__LCD_WIDTH - textWidth) / 2;
			break;
		case s_GRAPHICS_TEXT_ALIGN__RIGHT :
			xNew = s_GRAPHICS__LCD_WIDTH - textWidth - X;
			break;
		default :
			xNew = X;
			break;
	}

	// Reset text pointer
	pStr = String;

	// Calculate start position
	initBitPos = xNew % 8;
	initBytePos =  (xNew - initBitPos) / 8;

	// For each char
	while(*pStr)
	{
	  	// Get char info
	  	if(*pStr == ' ')
		{
		  	char_width = Font.charInfo['*' - Font.startChar].widthBits;
		  	xNew += (char_width + 2);
		  	initBitPos = xNew % 8;
		  	initBytePos =  (xNew - initBitPos) / 8;
			continue;
		}

		char_offset = Font.charInfo[*pStr - Font.startChar].offset;
		char_width = Font.charInfo[*pStr - Font.startChar].widthBits;
		char_pos = 0;

		// For each row
		for(j = 0; j < Font.height; j++)
		{
		  	char_bits_left = char_width;
		  	bytePos = 0;

		  	while(char_bits_left > 0)
			{

				char_part = Font.data[char_offset + char_pos];

				if(initBitPos != 0) {

					// - Second char part -
					//char_shifted = char_part << (8 - (pos_init_bit - 1));
					char_shifted = char_part << (initBitPos);
					// Recalculate chars left
					char_bits_left -= (8 - initBitPos);
					// Save
					ptr = Obj->pBuf + 2 + ((Y + j) * s_GRAPHICS__WIDTH_EXT) + initBytePos + (bytePos++);
					if(Color == s_GRAPHICS_COLOR__BLACK) {
						*(ptr) &= ~char_shifted;
					} else {
						*(ptr) |= char_shifted;
					}

					if(char_bits_left <= 0)
					{
						char_pos++;
						break;
					}

					// - First char part -
					//char_shifted = char_part >> (pos_init_bit - 1);
					char_shifted = char_part >> (8 - (initBitPos));
					// Recalculate chars left
					char_bits_left -= (initBitPos);
					// Save
					ptr = Obj->pBuf + 2 + ((Y + j) * s_GRAPHICS__WIDTH_EXT) + initBytePos + (bytePos);
					if(Color == s_GRAPHICS_COLOR__BLACK) {
						*(ptr) &= ~char_shifted;
					} else {
						*(ptr) |= char_shifted;
					}

				}
				else {
					char_shifted = char_part;

					// Recalculate chars left
					char_bits_left -= 8;
					// Save
					ptr = Obj->pBuf + 2 + ((Y + j) * s_GRAPHICS__WIDTH_EXT) + initBytePos + (bytePos++);
					if(Color == s_GRAPHICS_COLOR__BLACK) {
						*(ptr) &= ~char_shifted;
					} else {
						*(ptr) |= char_shifted;
					}
				}

				char_pos++;
			}
		}

		xNew += (char_width + 2);
		initBitPos = xNew % 8;
		initBytePos =  (xNew - initBitPos) / 8;
		pStr++;
	}
}





//    drawCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername,uint16_t color),
//    drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1,int16_t x2, int16_t y2, uint16_t color),
//    fillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1,int16_t x2, int16_t y2, uint16_t color),
//    drawRoundRect(int16_t x0, int16_t y0, int16_t w, int16_t h,int16_t radius, uint16_t color),
//    fillRoundRect(int16_t x0, int16_t y0, int16_t w, int16_t h,int16_t radius, uint16_t color),
//    drawXBitmap(int16_t x, int16_t y, const uint8_t *bitmap, int16_t w, int16_t h, uint16_t color),

//    setCursor(int16_t x, int16_t y),
//    setTextWrap(boolean w),
//    setRotation(uint8_t r),

