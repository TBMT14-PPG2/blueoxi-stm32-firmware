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

} FontCharInfo_t;

// Describes a single font
typedef struct
{
	const uint8_t 			height;			// height, in rows, of the font's characters
	const uint8_t 			startChar;		// the first character in the font (e.g. in charInfo and data)
	const uint8_t 			endChar;		// the last character in the font
	const uint8_t			spacePixels;	// number of pixels that a space character takes up
	const FontCharInfo_t*	charInfo;		// pointer to array of char information
	const uint8_t*			data;			// pointer to generated array of character visual representation

} FontInfo_t;



/* -- Exported Variables -- */
extern const uint8_t s_Font_Default[];



/* Font data for Apple LiGothic 16pt */
extern const uint8_t appleLiGothic_16ptBitmaps[];
extern const FontInfo_t appleLiGothic_16ptFontInfo;
extern const FontCharInfo_t appleLiGothic_16ptDescriptors[];


#endif /* __FONTS_H */
