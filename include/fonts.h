/**
 * @file	fonts.h
 * @author  Eriks Zaharans
 * @date    18 Sep 2015
 *
 * @section DESCRIPTION
 *
 * Font library header file.
 */

#ifndef __FONTS_H
#define __FONTS_H

/* -- Includes -- */

/* -- Defines -- */

// This structure describes a single character's display information
typedef struct
{
	const uint8_t widthBits;					// width, in bits (or pixels), of the character
	const uint16_t offset;					// offset of the character's bitmap, in bytes, into the the FONT_INFO's data array

} FONT_CHAR_INFO;

// Describes a single font
typedef struct
{
	const uint8_t 			heightPages;	// height, in pages (8 pixels), of the font's characters
	const uint8_t 			startChar;		// the first character in the font (e.g. in charInfo and data)
	const uint8_t 			endChar;		// the last character in the font
	const uint8_t			spacePixels;	// number of pixels that a space character takes up
	const FONT_CHAR_INFO*	charInfo;		// pointer to array of char information
	const uint8_t*			data;			// pointer to generated array of character visual representation

} FONT_INFO;



/* -- Exported Variables -- */
extern const uint8_t s_Font_Default[];


// Font data for SF UI Display 20pt
extern const uint8_t sFUIDisplay_20ptBitmaps[];
extern const FONT_INFO sFUIDisplay_20ptFontInfo;
extern const FONT_CHAR_INFO sFUIDisplay_20ptDescriptors[];


// Font data for Calibri 16pt
extern const uint8_t calibri_16ptBitmaps[];
extern const FONT_INFO calibri_16ptFontInfo;
extern const FONT_CHAR_INFO calibri_16ptDescriptors[];


#endif /* __FONTS_H */
