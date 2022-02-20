/*
 * File: oled_display_lib.h
 *
 * Overview:  API definitions for use with monochrome graphic OLED display module, 
 *            128 x 64 pixels, using IIC (I2C) connection to Teensy 3.2 MCU.
 *
 * Refer to the source file "oled_display_lib.c" (.ino) for details of display functions
 * and macros declared here.
 */
#ifndef OLED_DISPLAY_LIB_H
#define OLED_DISPLAY_LIB_H

// Set the OLED controller (SH1106) IIC device address here:
//
#define SH1106_I2C_ADDRESS  0x3C  // (pin SA0 tied Low)
/*
#define SH1106_I2C_ADDRESS  0x3D  // (pin SA0 tied High)
*/

// Rendering modes for display write functions...
#define CLEAR_PIXELS    0
#define SET_PIXELS      1
#define FLIP_PIXELS     2

// Character font styles;  size is cell height in pixels (including descenders).
// Use one of the font names defined here as the arg value in function: Disp_SetFont().
//
// Note:  Font size 16 is monospace only -- N/A in proportional spacing.
//        Font sizes 12 and 24 use proportional spacing -- N/A in monospace.
//
// <!> These fonts are Copyright by M.J. Bauer (2016++)  Permission granted to use freely,
//     on condition that M.J.Bauer is acknowledged as the designer (www.mjbauer.biz).
//
enum  Graphics_character_fonts
{
    MONO_8_NORM = 0,   // (0) Mono-spaced font;  char width is 5 pix
    MONO_8_BOLD_X,     // (1) N/A 
    PROP_8_NORM,       // (2) Proportional font;  char width is 3..5 pix
    PROP_8_BOLD_X,     // (3) N/A 

    MONO_12_NORM_X,    // (4) N/A
    MONO_12_BOLD_X,    // (5) N/A
    PROP_12_NORM,      // (6) Proportional font;  char width is 4..7 pix
    PROP_12_BOLD,      // (7) as above, but bold weight

    MONO_16_NORM,      // (8) Mono-spaced font;  char width is 10 pix
    MONO_16_BOLD,      // (9) as above, but bold weight
    PROP_16_NORM_X,    // (10) N/A
    PROP_16_BOLD_X,    // (10) N/A

    MONO_24_NORM_X,    // (12) N/A
    MONO_24_BOLD_X,    // (13) N/A
    PROP_24_NORM,      // (14) Proportional font;  char width is 7..15 pix
    PROP_24_BOLD_X     // (15) N/A  (already bold!)
};

//---------- Display function & macro library (API) -------------------------------------
//
#define Disp_GetMaxX()       (127)
#define Disp_GetMaxY()       (63)

void     Disp_ClearScreen(void);              // Clear OLED GDRAM and MCU RAM buffer
void     Disp_Mode(uint8_t mode);             // Set pixel write mode (set, clear, flip)
void     Disp_PosXY(uint16_t x, uint16_t y);  // Set graphics cursor position (x, y)
uint16_t Disp_GetX(void);                     // Return cursor x-coord
uint16_t Disp_GetY(void);                     // Return cursor y-coord
void     Disp_SetFont(uint8_t font_ID);       // Set font for char and text display
uint8_t  Disp_GetFont();                      // Return current font ID
void     Disp_PutChar(char uc);               // Display ASCII char at (x, y)
void     Disp_PutText(const char *str);       // Display text string at (x, y)
void     Disp_PutDigit(uint8_t bDat);         // Display hex/decimal digit value (1 char)
void     Disp_PutHexByte(uint8_t bDat);       // Display hexadecimal byte value (2 chars)

void     Disp_PutDecimal(int32_t iVal, uint8 bFieldSize);  // Show uint32_t in decimal
void     Disp_BlockFill(uint16_t w, uint16_t h);  // Fill area, w x h pixels, at (x, y)
void     Disp_ClearArea(uint16_t w, uint16_t h);  // Clear area, w x h pixels, at (x, y)
uint8_t  Disp_PutImage(uint8_t *image, uint16_t w, uint16_t h);  // Show bitmap image at (x, y)
uint16_t *Disp_ScreenCapture();  // Return a pointer to the screen buffer

void  DisplayTextCentered8p(short ypos, const char *str);
void  DisplayTextCentered12p(short ypos, const char *str);
void  DisplayTextCenteredInBox(short ypos, const char *str);  // 12p font
void  DrawBox(short w, short h);

// These macros draw various objects at the current graphics cursor position:
#define Disp_PutPixel()           Disp_BlockFill(1, 1)
#define Disp_DrawBar(w, h)        Disp_BlockFill(w, h)
#define Disp_DrawLineHoriz(len)   Disp_BlockFill(len, 1)
#define Disp_DrawLineVert(len)    Disp_BlockFill(1, len)

// The following functions are *not* meant to be accessible to the application:
void  Disp_PutChar8(uint8_t uc);
void  Disp_PutChar16(uint8_t uc);
void  Disp_PutChar16_ruff(uint8_t uc);
void  Disp_PutChar16_smooth(uint8_t uc);
void  Disp_PutChar12(uint8_t uc);
void  Disp_PutChar24(uint8_t uc);

// Controller low-level functions (defined in driver module):

void  SH1106_WriteCommand(uint8_t cmd);
void  SH1106_WriteData(uint8_t data);
void  SH1106_Init();
void  SH1106_SetContrast(unsigned level_pc);  // %
void  SH1106_ClearGDRAM();
void  SH1106_WriteBlock(uint16_t *scnBuf, uint16_t x, uint16_t y, uint16_t w, uint16_t h);
void  SH1106_Test_Pattern();

#define OLED_Display_Init()    SH1106_Init()    
#define OLED_Display_Wake()    SH1106_WriteCommand(SH1106_DISPLAYON)
#define OLED_Display_Sleep()   SH1106_WriteCommand(SH1106_DISPLAYOFF)

//-------------- SH1106 Controller Command Bytes ------------------
//
#define SH1106_SETCONTRAST 0x81
#define SH1106_DISPLAYALLON_RESUME 0xA4
#define SH1106_DISPLAYALLON 0xA5
#define SH1106_NORMALDISPLAY 0xA6
#define SH1106_INVERTDISPLAY 0xA7
#define SH1106_DISPLAYOFF 0xAE
#define SH1106_DISPLAYON 0xAF
#define SH1106_SETDISPLAYOFFSET 0xD3
#define SH1106_SETCOMPINS 0xDA
#define SH1106_SETVCOMDETECT 0xDB
#define SH1106_SETDISPLAYCLOCKDIV 0xD5
#define SH1106_SETPRECHARGE 0xD9
#define SH1106_SETMULTIPLEX 0xA8
#define SH1106_SETCOLUMNADDRLOW 0x00
#define SH1106_SETCOLUMNADDRHIGH 0x10
#define SH1106_SETSTARTLINE 0x40
#define SH1106_MEMORYMODE 0x20
#define SH1106_PAGEADDR   0xB0
#define SH1106_COMSCANINC 0xC0
#define SH1106_COMSCANDEC 0xC8
#define SH1106_SEGREMAP 0xA0
#define SH1106_CHARGEPUMP 0x8D
#define SH1106_EXTERNALVCC 0x01
#define SH1106_SWITCHCAPVCC 0x02
#define SH1106_MESSAGETYPE_COMMAND 0x80
#define SH1106_MESSAGETYPE_DATA 0x40
#define SH1106_READMODIFYWRITE_START 0xE0
#define SH1106_READMODIFYWRITE_END 0xEE

#endif  // OLED_DISPLAY_LIB_H
