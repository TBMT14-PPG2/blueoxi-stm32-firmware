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




uint8_t reverse_byte(uint8_t x)
{
    static const uint8_t table[] = {
        0x00, 0x80, 0x40, 0xc0, 0x20, 0xa0, 0x60, 0xe0,
        0x10, 0x90, 0x50, 0xd0, 0x30, 0xb0, 0x70, 0xf0,
        0x08, 0x88, 0x48, 0xc8, 0x28, 0xa8, 0x68, 0xe8,
        0x18, 0x98, 0x58, 0xd8, 0x38, 0xb8, 0x78, 0xf8,
        0x04, 0x84, 0x44, 0xc4, 0x24, 0xa4, 0x64, 0xe4,
        0x14, 0x94, 0x54, 0xd4, 0x34, 0xb4, 0x74, 0xf4,
        0x0c, 0x8c, 0x4c, 0xcc, 0x2c, 0xac, 0x6c, 0xec,
        0x1c, 0x9c, 0x5c, 0xdc, 0x3c, 0xbc, 0x7c, 0xfc,
        0x02, 0x82, 0x42, 0xc2, 0x22, 0xa2, 0x62, 0xe2,
        0x12, 0x92, 0x52, 0xd2, 0x32, 0xb2, 0x72, 0xf2,
        0x0a, 0x8a, 0x4a, 0xca, 0x2a, 0xaa, 0x6a, 0xea,
        0x1a, 0x9a, 0x5a, 0xda, 0x3a, 0xba, 0x7a, 0xfa,
        0x06, 0x86, 0x46, 0xc6, 0x26, 0xa6, 0x66, 0xe6,
        0x16, 0x96, 0x56, 0xd6, 0x36, 0xb6, 0x76, 0xf6,
        0x0e, 0x8e, 0x4e, 0xce, 0x2e, 0xae, 0x6e, 0xee,
        0x1e, 0x9e, 0x5e, 0xde, 0x3e, 0xbe, 0x7e, 0xfe,
        0x01, 0x81, 0x41, 0xc1, 0x21, 0xa1, 0x61, 0xe1,
        0x11, 0x91, 0x51, 0xd1, 0x31, 0xb1, 0x71, 0xf1,
        0x09, 0x89, 0x49, 0xc9, 0x29, 0xa9, 0x69, 0xe9,
        0x19, 0x99, 0x59, 0xd9, 0x39, 0xb9, 0x79, 0xf9,
        0x05, 0x85, 0x45, 0xc5, 0x25, 0xa5, 0x65, 0xe5,
        0x15, 0x95, 0x55, 0xd5, 0x35, 0xb5, 0x75, 0xf5,
        0x0d, 0x8d, 0x4d, 0xcd, 0x2d, 0xad, 0x6d, 0xed,
        0x1d, 0x9d, 0x5d, 0xdd, 0x3d, 0xbd, 0x7d, 0xfd,
        0x03, 0x83, 0x43, 0xc3, 0x23, 0xa3, 0x63, 0xe3,
        0x13, 0x93, 0x53, 0xd3, 0x33, 0xb3, 0x73, 0xf3,
        0x0b, 0x8b, 0x4b, 0xcb, 0x2b, 0xab, 0x6b, 0xeb,
        0x1b, 0x9b, 0x5b, 0xdb, 0x3b, 0xbb, 0x7b, 0xfb,
        0x07, 0x87, 0x47, 0xc7, 0x27, 0xa7, 0x67, 0xe7,
        0x17, 0x97, 0x57, 0xd7, 0x37, 0xb7, 0x77, 0xf7,
        0x0f, 0x8f, 0x4f, 0xcf, 0x2f, 0xaf, 0x6f, 0xef,
        0x1f, 0x9f, 0x5f, 0xdf, 0x3f, 0xbf, 0x7f, 0xff,
    };
    return table[x];
}





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



void Graphics_DrawCharNew(GraphicsObj_t *Obj, uint8_t X, uint8_t Y, uint8_t Char, GraphicsColor_t Color)
{
//	uint8_t i, j;
//	uint8_t line = 0;
//	uint8_t bitCount=0;
//	uint16_t fontIndex = sFUIDisplay_20ptDescriptors[Char-'!'].offset; //((fontDesc + c)->offset) + 2;
//
//	for (i = 0; i < 27; i++) {	// i<fontHeight
//		for (j = 0; j < sFUIDisplay_20ptDescriptors[Char-'!'].width; j++) {			//j<fontWidth
//			if (bitCount++%8 == 0) {
//				line = *(sFUIDisplay_20ptBitmaps+fontIndex++);
//			}
//			if (line & 0x80) {
//				Graphics_DrawPixel(Obj, X+i, Y+j, Color);
//			}
//			line <<= 1;
//		}
//		bitCount = 0;
//	}
}



void Graphics_DrawStringNew(GraphicsObj_t *Obj, uint8_t *text, FONT_INFO font, uint8_t font_height, uint8_t x, uint8_t y)
{
  	// - Variables -
  	uint8_t i, j;
  	uint8_t *ptr, *pStr;
	// Char
	uint16_t char_offset, char_pos;
	uint8_t char_width;
	uint8_t char_part, char_shifted;
	int8_t char_bits_left;
	// Position
	uint16_t pos_init_bit, pos_init_byte, pos_byte, x_new;


	//ptr = Obj->pBuf;
	pStr = text;



	// Calculate text width for alignment
	uint8_t textWidth = 0;
	while(*pStr)
	{
		textWidth += font.charInfo[*pStr - font.startChar].widthBits;
		textWidth += 2; // Add spacing

		pStr++;
	}
	x = (s_GRAPHICS__LCD_WIDTH - textWidth) / 2;

	// Reset text pointer
	pStr = text;

	// Calculate start position
	x_new = x;
	pos_init_bit = x % 8;
	pos_init_byte =  (x - pos_init_bit) / 8;

	// For each char
	while(*pStr)
	{
	  	// Get char info
	  	if(*pStr == ' ')
		{
		  	char_width = font.charInfo['*' - font.startChar].widthBits;
		  	x_new += (char_width + 2);
			pos_init_bit = x_new % 8;
			pos_init_byte =  (x_new - pos_init_bit) / 8;
			continue;
		}

		char_offset = font.charInfo[*pStr - font.startChar].offset;
		char_width = font.charInfo[*pStr - font.startChar].widthBits;
		char_pos = 0;

		// For each row
		for(j = 0; j < font_height; j++)
		{
		  	char_bits_left = char_width;
			pos_byte = 0;

		  	while(char_bits_left > 0)
			{

				char_part = reverse_byte(font.data[char_offset + char_pos]);

				if(pos_init_bit != 0) {

					// - Second char part -
					//char_shifted = char_part << (8 - (pos_init_bit - 1));
					char_shifted = char_part << (pos_init_bit);
					// Recalculate chars left
					char_bits_left -= (pos_init_bit - 1);
					// Save
					ptr = Obj->pBuf + 2 + ((y + j) * s_GRAPHICS__WIDTH_EXT) + pos_init_byte + (pos_byte++);
					//*(ptr) |= char_shifted;
					*(ptr) &= ~char_shifted;

					if(!(char_bits_left > 0))
					{
						char_pos++;
						break;
					}

					// - First char part -
					//char_shifted = char_part >> (pos_init_bit - 1);
					char_shifted = char_part >> (8 - (pos_init_bit));
					// Recalculate chars left
					char_bits_left -= (8 - (pos_init_bit - 1));
					// Save
					ptr = Obj->pBuf + 2 + ((y + j) * s_GRAPHICS__WIDTH_EXT) + pos_init_byte + (pos_byte);
					//*(ptr) |= char_shifted;
					*(ptr) &= ~char_shifted;



				}
				else {
					char_shifted = char_part;

					// Recalculate chars left
					char_bits_left -= 8;
					// Save
					ptr = Obj->pBuf + 2 + ((y + j) * s_GRAPHICS__WIDTH_EXT) + pos_init_byte + (pos_byte++);
					//*(ptr) |= char_shifted;
					*(ptr) &= ~char_shifted;
				}

				char_pos++;
			}
		}

		x_new += (char_width + 2);
		pos_init_bit = x_new % 8;
		pos_init_byte =  (x_new - pos_init_bit) / 8;
		pStr++;
	}
}





//    drawCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername,uint16_t color),
//    drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1,int16_t x2, int16_t y2, uint16_t color),
//    fillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1,int16_t x2, int16_t y2, uint16_t color),
//    drawRoundRect(int16_t x0, int16_t y0, int16_t w, int16_t h,int16_t radius, uint16_t color),
//    fillRoundRect(int16_t x0, int16_t y0, int16_t w, int16_t h,int16_t radius, uint16_t color),
//    drawXBitmap(int16_t x, int16_t y, const uint8_t *bitmap, int16_t w, int16_t h, uint16_t color),

//    drawChar(int16_t x, int16_t y, unsigned char c, uint16_t color,uint16_t bg, uint8_t size),
//    setCursor(int16_t x, int16_t y),
//    setTextColor(uint16_t c),
//    setTextColor(uint16_t c, uint16_t bg),
//    setTextSize(uint8_t s),
//    setTextWrap(boolean w),
//    setRotation(uint8_t r),

