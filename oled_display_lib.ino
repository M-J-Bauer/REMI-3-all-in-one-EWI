/*
  |  File:          oled_display_lib.ino
  |
  |  Overview:      Library functions for monochrome graphic OLED display module,
  |                 128 x 64 pixels, using IIC (I2C) connection to Teensy 3.2 MCU.
  |
  |  Platform:      This version customized to suit SH1106 OLED controller.
  |                 Teensyduino library is needed for the "Wire" class IIC driver functions.
  |
  |  Originated:    2021,  M.J. Bauer  [www.mjbauer.biz]
*/
#include <Wire.h>  // Arduino IIC (I2C, TWI) library def's
#include "oled_display_lib.h"

/*`````````````````````````````````````````````````````````````````````````````````````````````````
    Font definition -- 5 x 8 pixels -- MONO-SPACED;  96 ASCII characters
    Char cell: 5 x 8 pixels (8 bytes/char); each byte is a row of 5 pixels, left justified.

    Format:  char bits = b7..b3,  blank bits = b2, b1 and b0;  b7 is LHS.
             Lower-case descenders use the 8th byte.
*/
const uint8_t  font_table_mono_5x8[] =
{
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,   // space
  0x20, 0x20, 0x20, 0x20, 0x20, 0x00, 0x20, 0x00,   // !
  0x50, 0x50, 0x50, 0x00, 0x00, 0x00, 0x00, 0x00,   // "
  0x50, 0x50, 0xF8, 0x50, 0xF8, 0x50, 0x50, 0x00,   // #
  0x20, 0x78, 0xA0, 0x70, 0x28, 0xF0, 0x20, 0x00,   // $
  0xC0, 0xC8, 0x10, 0x20, 0x40, 0x98, 0x18, 0x00,   // %
  0x20, 0x50, 0x50, 0x60, 0xA8, 0x90, 0x68, 0x00,   // &
  0x20, 0x20, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00,   // '
  0x10, 0x20, 0x40, 0x40, 0x40, 0x20, 0x10, 0x00,   // (
  0x40, 0x20, 0x10, 0x10, 0x10, 0x20, 0x40, 0x00,   // )
  0x00, 0x20, 0xA8, 0x70, 0xA8, 0x20, 0x00, 0x00,   // *
  0x00, 0x20, 0x20, 0xF8, 0x20, 0x20, 0x00, 0x00,   // +
  0x00, 0x00, 0x00, 0x00, 0x60, 0x60, 0x20, 0x40,   // ,
  0x00, 0x00, 0x00, 0xF8, 0x00, 0x00, 0x00, 0x00,   // -
  0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x60, 0x00,   // .
  0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x00, 0x00,   // /

  0x70, 0x88, 0x98, 0xA8, 0xC8, 0x88, 0x70, 0x00,   // 0
  0x20, 0x60, 0x20, 0x20, 0x20, 0x20, 0x70, 0x00,   // 1
  0x70, 0x88, 0x08, 0x10, 0x20, 0x40, 0xF8, 0x00,   // 2
  0xF8, 0x10, 0x20, 0x10, 0x08, 0x88, 0x70, 0x00,   // 3
  0x10, 0x30, 0x50, 0x90, 0xF8, 0x10, 0x10, 0x00,   // 4
  0xF8, 0x80, 0xF0, 0x08, 0x08, 0x88, 0x70, 0x00,   // 5
  0x30, 0x40, 0x80, 0xF0, 0x88, 0x88, 0x70, 0x00,   // 6
  0xF8, 0x08, 0x10, 0x20, 0x40, 0x40, 0x40, 0x00,   // 7
  0x70, 0x88, 0x88, 0x70, 0x88, 0x88, 0x70, 0x00,   // 8
  0x70, 0x88, 0x88, 0x78, 0x08, 0x10, 0x60, 0x00,   // 9
  0x00, 0x60, 0x60, 0x00, 0x60, 0x60, 0x00, 0x00,   // :
  0x00, 0x60, 0x60, 0x00, 0x60, 0x60, 0x20, 0x40,   // ;
  0x08, 0x10, 0x20, 0x40, 0x20, 0x10, 0x08, 0x00,   // <
  0x00, 0x00, 0xF8, 0x00, 0xF8, 0x00, 0x00, 0x00,   // =
  0x80, 0x40, 0x20, 0x10, 0x20, 0x40, 0x80, 0x00,   // >
  0x70, 0x88, 0x08, 0x10, 0x20, 0x00, 0x20, 0x00,   // ?

  0x30, 0x48, 0xB8, 0xA8, 0xB8, 0x80, 0x78, 0x00,   // @
  0x70, 0x88, 0x88, 0xF8, 0x88, 0x88, 0x88, 0x00,   // A
  0xF0, 0x88, 0x88, 0xF0, 0x88, 0x88, 0xF0, 0x00,   // B
  0x70, 0x88, 0x80, 0x80, 0x80, 0x88, 0x70, 0x00,   // C
  0xE0, 0x90, 0x88, 0x88, 0x88, 0x90, 0xE0, 0x00,   // D
  0xF8, 0x80, 0x80, 0xF0, 0x80, 0x80, 0xF8, 0x00,   // E
  0xF8, 0x80, 0x80, 0xF0, 0x80, 0x80, 0x80, 0x00,   // F
  0x78, 0x80, 0x80, 0x98, 0x88, 0x88, 0x78, 0x00,   // G
  0x88, 0x88, 0x88, 0xF8, 0x88, 0x88, 0x88, 0x00,   // H
  0x70, 0x20, 0x20, 0x20, 0x20, 0x20, 0x70, 0x00,   // I
  0x38, 0x10, 0x10, 0x10, 0x10, 0x90, 0x60, 0x00,   // J
  0x88, 0x90, 0xA0, 0xC0, 0xA0, 0x90, 0x88, 0x00,   // K
  0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xF8, 0x00,   // L
  0x88, 0xD8, 0xA8, 0xA8, 0x88, 0x88, 0x88, 0x00,   // M
  0x88, 0xC8, 0xA8, 0x98, 0x88, 0x88, 0x88, 0x00,   // N
  0x70, 0x88, 0x88, 0x88, 0x88, 0x88, 0x70, 0x00,   // O

  0xF0, 0x88, 0x88, 0xF0, 0x80, 0x80, 0x80, 0x00,   // P
  0x70, 0x88, 0x88, 0x88, 0xA8, 0x90, 0x68, 0x04,   // Q
  0xF0, 0x88, 0x88, 0xF0, 0xA0, 0x90, 0x88, 0x00,   // R
  0x70, 0x88, 0x80, 0x70, 0x08, 0x88, 0x70, 0x00,   // S
  0xF8, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x00,   // T
  0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x70, 0x00,   // U
  0x88, 0x88, 0x88, 0x50, 0x50, 0x20, 0x20, 0x00,   // V
  0x88, 0x88, 0x88, 0xA8, 0xA8, 0xA8, 0x50, 0x00,   // W
  0x88, 0x88, 0x50, 0x20, 0x50, 0x88, 0x88, 0x00,   // X
  0x88, 0x88, 0x88, 0x70, 0x20, 0x20, 0x20, 0x00,   // Y
  0xF8, 0x08, 0x10, 0x20, 0x40, 0x80, 0xF8, 0x00,   // Z
  0x38, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x38,   // [
  0x00, 0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x00,   // back-slash
  0xE0, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0xE0,   // ]
  0x20, 0x50, 0x88, 0x00, 0x00, 0x00, 0x00, 0x00,   // ^
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF8, 0x00,   // _

  0x20, 0x20, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00,   // `
  0x00, 0x00, 0x70, 0x08, 0x78, 0x88, 0x78, 0x00,   // a
  0x80, 0x80, 0xB0, 0xC8, 0x88, 0x88, 0xF0, 0x00,   // b
  0x00, 0x00, 0x70, 0x88, 0x80, 0x80, 0x70, 0x00,   // c
  0x08, 0x08, 0x68, 0x98, 0x88, 0x88, 0x78, 0x00,   // d
  0x00, 0x00, 0x70, 0x88, 0xF8, 0x80, 0x70, 0x00,   // e
  0x30, 0x48, 0x40, 0xF0, 0x40, 0x40, 0x40, 0x00,   // f
  0x00, 0x00, 0x78, 0x88, 0x98, 0x68, 0x08, 0x70,   // g
  0x80, 0x80, 0xB0, 0xC8, 0x88, 0x88, 0x88, 0x00,   // h
  0x20, 0x00, 0x60, 0x20, 0x20, 0x20, 0x70, 0x00,   // i
  0x10, 0x00, 0x30, 0x10, 0x10, 0x10, 0x90, 0x60,   // j
  0x80, 0x80, 0x90, 0xA0, 0xD0, 0x88, 0x88, 0x00,   // k
  0x60, 0x20, 0x20, 0x20, 0x20, 0x20, 0x70, 0x00,   // l
  0x00, 0x00, 0xD0, 0xA8, 0xA8, 0xA8, 0x88, 0x00,   // m
  0x00, 0x00, 0xF0, 0x88, 0x88, 0x88, 0x88, 0x00,   // n
  0x00, 0x00, 0x70, 0x88, 0x88, 0x88, 0x70, 0x00,   // o

  0x00, 0x00, 0xF0, 0x88, 0x88, 0xF0, 0x80, 0x80,   // p
  0x00, 0x00, 0x78, 0x88, 0x88, 0x78, 0x08, 0x08,   // q
  0x00, 0x00, 0xB0, 0xC8, 0x80, 0x80, 0x80, 0x00,   // r
  0x00, 0x00, 0x70, 0x80, 0x70, 0x08, 0x70, 0x00,   // s
  0x40, 0x40, 0xE0, 0x40, 0x40, 0x48, 0x30, 0x00,   // t
  0x00, 0x00, 0x88, 0x88, 0x88, 0x98, 0x68, 0x00,   // u
  0x00, 0x00, 0x88, 0x88, 0x88, 0x50, 0x20, 0x00,   // v
  0x00, 0x00, 0x88, 0x88, 0xA8, 0xA8, 0x50, 0x00,   // w
  0x00, 0x00, 0x88, 0x50, 0x20, 0x50, 0x88, 0x00,   // x
  0x00, 0x00, 0x88, 0x88, 0x88, 0x78, 0x08, 0xF0,   // y
  0x00, 0x00, 0xF8, 0x10, 0x20, 0x40, 0xF8, 0x00,   // z
  0x18, 0x20, 0x20, 0x40, 0x40, 0x20, 0x20, 0x18,   // {
  0x20, 0x20, 0x20, 0x00, 0x20, 0x20, 0x20, 0x00,   // |
  0xC0, 0x20, 0x20, 0x10, 0x10, 0x20, 0x20, 0xC0,   // }
  0x00, 0xC8, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00,   // ~
  0xA8, 0x50, 0xA8, 0x50, 0xA8, 0x50, 0xA8, 0x00    // del
};


/*`````````````````````````````````````````````````````````````````````````````````````````````````
  |    Font definition -- Char cell: 5 x 8 pixels -- PROPORTIONAL spacing.
  |    Char cell: 5 x 8 pixels (8 bytes/char); each data byte is a row of 5 pixels.
  |
  |    Table format: 8 bytes per character --
  |           byte[0] bit 7 is descender flag, if true, shift char bitmap down 1 row;
  |           byte[0] bits 2:0 specify width of character (1..5 pixels);
  |           byte[1:7] (7 bytes) contain the character bitmap image
  |
  |    Note:  Most chars start on the top row and are 5 dots wide.
  |           Upper-case letters are all 5 dots wide (same as mono font), except 'I'.
  |           Digits and lower-case letters are mostly 4 dots wide, with a few exceptions,
  |           e.g. '1', 'i', 'j', 'l', etc.
  |           Descenders use the 8th row in the bitmap cell.
  |           Special cases, e.g. 'j', '[', '{', etc, are handled by Disp_PutChar#().
  |
  |  <!> This font Copyright by M.J.Bauer (2016++)  Permission is granted to use freely,
  |      on condition that M.J.Bauer is acknowledged as the font designer (www.mjbauer.biz).
*/
const  uint8_t  font_table_prop_5x8[] =
{
  0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,   // space
  0x03, 0x40, 0x40, 0x40, 0x40, 0x40, 0x00, 0x40,   // !
  0x03, 0xA0, 0xA0, 0xA0, 0x00, 0x00, 0x00, 0x00,   // "
  0x05, 0x50, 0x50, 0xF8, 0x50, 0xF8, 0x50, 0x50,   // #
  0x05, 0x20, 0x78, 0xA0, 0x70, 0x28, 0xF0, 0x20,   // $
  0x05, 0xC0, 0xC8, 0x10, 0x20, 0x40, 0x98, 0x18,   // %
  0x05, 0x20, 0x50, 0x50, 0x60, 0xA8, 0x90, 0x68,   // &
  0x03, 0x40, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00,   // '
  0x04, 0x20, 0x40, 0x80, 0x80, 0x80, 0x40, 0x20,   // (
  0x04, 0x40, 0x20, 0x10, 0x10, 0x10, 0x20, 0x40,   // )
  0x05, 0x00, 0x20, 0xA8, 0x70, 0xA8, 0x20, 0x00,   // *
  0x05, 0x00, 0x20, 0x20, 0xF8, 0x20, 0x20, 0x00,   // +
  0x83, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x80,   // ,
  0x04, 0x00, 0x00, 0x00, 0xF0, 0x00, 0x00, 0x00,   // -
  0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40,   // .
  0x05, 0x00, 0x08, 0x10, 0x20, 0x40, 0x80, 0x00,   // /

  0x04, 0x60, 0x90, 0x90, 0x90, 0x90, 0x90, 0x60,   // 0
  0x03, 0x40, 0xC0, 0x40, 0x40, 0x40, 0x40, 0xE0,   // 1
  0x04, 0x60, 0x90, 0x10, 0x20, 0x40, 0x80, 0xF0,   // 2
  0x04, 0x60, 0x90, 0x10, 0x20, 0x10, 0x90, 0x60,   // 3
  0x04, 0x10, 0x30, 0x50, 0x90, 0xF0, 0x10, 0x10,   // 4
  0x04, 0xF0, 0x80, 0xE0, 0x10, 0x10, 0x90, 0x60,   // 5
  0x04, 0x20, 0x40, 0x80, 0xE0, 0x90, 0x90, 0x60,   // 6
  0x04, 0xF0, 0x10, 0x20, 0x40, 0x80, 0x80, 0x80,   // 7
  0x04, 0x60, 0x90, 0x90, 0x60, 0x90, 0x90, 0x60,   // 8
  0x04, 0x60, 0x90, 0x90, 0x70, 0x10, 0x20, 0x40,   // 9
  0x03, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x40,   // :
  0x83, 0x00, 0x40, 0x00, 0x00, 0x00, 0x40, 0x80,   // ;
  0x04, 0x10, 0x20, 0x40, 0x80, 0x40, 0x20, 0x10,   // <
  0x05, 0x00, 0x00, 0xF8, 0x00, 0xF8, 0x00, 0x00,   // =
  0x04, 0x80, 0x40, 0x20, 0x10, 0x20, 0x40, 0x80,   // >
  0x05, 0x70, 0x88, 0x08, 0x10, 0x20, 0x00, 0x20,   // ?

  0x05, 0x30, 0x48, 0xB8, 0xA8, 0xB8, 0x80, 0x78,   // @
  0x05, 0x20, 0x50, 0x88, 0x88, 0xF8, 0x88, 0x88,   // A
  0x05, 0xF0, 0x88, 0x88, 0xF0, 0x88, 0x88, 0xF0,   // B
  0x05, 0x70, 0x88, 0x80, 0x80, 0x80, 0x88, 0x70,   // C
  0x05, 0xE0, 0x90, 0x88, 0x88, 0x88, 0x90, 0xE0,   // D
  0x05, 0xF8, 0x80, 0x80, 0xF0, 0x80, 0x80, 0xF8,   // E
  0x05, 0xF8, 0x80, 0x80, 0xF0, 0x80, 0x80, 0x80,   // F
  0x05, 0x78, 0x80, 0x80, 0x98, 0x88, 0x88, 0x78,   // G
  0x05, 0x88, 0x88, 0x88, 0xF8, 0x88, 0x88, 0x88,   // H
  0x03, 0xE0, 0x40, 0x40, 0x40, 0x40, 0x40, 0xE0,   // I
  0x04, 0x70, 0x10, 0x10, 0x10, 0x10, 0x90, 0x60,   // J
  0x05, 0x88, 0x90, 0xA0, 0xC0, 0xA0, 0x90, 0x88,   // K
  0x05, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xF8,   // L
  0x05, 0x88, 0xD8, 0xA8, 0xA8, 0x88, 0x88, 0x88,   // M
  0x05, 0x88, 0xC8, 0xA8, 0x98, 0x88, 0x88, 0x88,   // N
  0x05, 0x70, 0x88, 0x88, 0x88, 0x88, 0x88, 0x70,   // O

  0x05, 0xF0, 0x88, 0x88, 0xF0, 0x80, 0x80, 0x80,   // P
  0x05, 0x70, 0x88, 0x88, 0x88, 0xA8, 0x90, 0x68,   // Q
  0x05, 0xF0, 0x88, 0x88, 0xF0, 0xA0, 0x90, 0x88,   // R
  0x05, 0x70, 0x88, 0x80, 0x70, 0x08, 0x88, 0x70,   // S
  0x05, 0xF8, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,   // T
  0x05, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x70,   // U
  0x05, 0x88, 0x88, 0x88, 0x50, 0x50, 0x20, 0x20,   // V
  0x05, 0x88, 0x88, 0x88, 0xA8, 0xA8, 0xA8, 0x50,   // W
  0x05, 0x88, 0x88, 0x50, 0x20, 0x50, 0x88, 0x88,   // X
  0x05, 0x88, 0x88, 0x88, 0x70, 0x20, 0x20, 0x20,   // Y
  0x05, 0xF8, 0x08, 0x10, 0x20, 0x40, 0x80, 0xF8,   // Z
  0x03, 0xC0, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,   // [
  0x05, 0x00, 0x80, 0x40, 0x20, 0x10, 0x08, 0x00,   // back-slash
  0x03, 0x60, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,   // ]
  0x05, 0x20, 0x50, 0x88, 0x00, 0x00, 0x00, 0x00,   // ^
  0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0,   // _

  0x03, 0x80, 0x80, 0x40, 0x00, 0x00, 0x00, 0x00,   // `
  0x04, 0x00, 0x00, 0x60, 0x10, 0x70, 0x90, 0x70,   // a
  0x04, 0x80, 0x80, 0xE0, 0x90, 0x90, 0x90, 0xE0,   // b
  0x04, 0x00, 0x00, 0x70, 0x80, 0x80, 0x80, 0x70,   // c
  0x04, 0x10, 0x10, 0x70, 0x90, 0x90, 0x90, 0x70,   // d
  0x04, 0x00, 0x00, 0x60, 0x90, 0xF0, 0x80, 0x70,   // e
  0x04, 0x30, 0x40, 0x40, 0xF0, 0x40, 0x40, 0x40,   // f
  0x84, 0x00, 0x70, 0x90, 0x90, 0x70, 0x10, 0xE0,   // g
  0x04, 0x80, 0x80, 0xE0, 0x90, 0x90, 0x90, 0x90,   // h
  0x03, 0x40, 0x00, 0xC0, 0x40, 0x40, 0x40, 0x40,   // i
  0x03, 0x40, 0x00, 0xC0, 0x40, 0x40, 0x40, 0x40,   // j
  0x04, 0x80, 0x80, 0x90, 0xA0, 0xC0, 0xA0, 0x90,   // k
  0x03, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x20,   // l
  0x05, 0x00, 0x00, 0xD0, 0xA8, 0xA8, 0xA8, 0x88,   // m
  0x04, 0x00, 0x00, 0xE0, 0x90, 0x90, 0x90, 0x90,   // n
  0x04, 0x00, 0x00, 0x60, 0x90, 0x90, 0x90, 0x60,   // o

  0x84, 0x00, 0xE0, 0x90, 0x90, 0xE0, 0x80, 0x80,   // p
  0x84, 0x00, 0x70, 0x90, 0x90, 0x70, 0x10, 0x10,   // q
  0x04, 0x00, 0x00, 0xB0, 0xC0, 0x80, 0x80, 0x80,   // r
  0x04, 0x00, 0x00, 0x70, 0x80, 0x60, 0x10, 0xE0,   // s
  0x04, 0x40, 0x40, 0xE0, 0x40, 0x40, 0x40, 0x30,   // t
  0x04, 0x00, 0x00, 0x90, 0x90, 0x90, 0x90, 0x70,   // u
  0x04, 0x00, 0x00, 0x90, 0x90, 0x90, 0xA0, 0x40,   // v
  0x05, 0x00, 0x00, 0x88, 0x88, 0xA8, 0xA8, 0x50,   // w
  0x05, 0x00, 0x00, 0x88, 0x50, 0x20, 0x50, 0x88,   // x
  0x84, 0x00, 0x90, 0x90, 0x90, 0x70, 0x10, 0xE0,   // y
  0x04, 0x00, 0x00, 0xF0, 0x10, 0x20, 0x40, 0xF0,   // z
  0x03, 0x30, 0x40, 0x40, 0x80, 0x80, 0x40, 0x40,   // {
  0x03, 0x20, 0x20, 0x20, 0x00, 0x20, 0x20, 0x20,   // |
  0x03, 0xC0, 0x20, 0x20, 0x10, 0x10, 0x20, 0x20,   // }
  0x05, 0x00, 0xC8, 0x30, 0x00, 0x00, 0x00, 0x00,   // ~
  0x05, 0xA8, 0x50, 0xA8, 0x50, 0xA8, 0x50, 0xA8    // del
};


/*`````````````````````````````````````````````````````````````````````````````````````````````````
  |    Font definition -- 10 x 14 pixels -- Decimal digits 0 ~ 9 only.
  |    Char cell: 12 x 16 pixels (16 WORDS/char); each word is a row of 10 pixels.
  |
  |    The table defines symbols with a smoother appearance than that obtained by simply
  |    doubling the size of the dots from font_table_mono_5x8[].
  |
  |    Function Disp_PutChar16_smooth() references this table.
  |
  |  <!> This font Copyright by M.J.Bauer (2016++).  Permission is granted to use freely,
  |      on condition that M.J.Bauer is acknowledged as the font designer (www.mjbauer.biz).
*/
const  uint8_t  font_table_digit_10x16[] =
{
  0x1E, 0x00, 0x3F, 0x00, 0x73, 0x80, 0x61, 0x80, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0,
  0xC0, 0xC0, 0xC0, 0xC0, 0x61, 0x80, 0x73, 0x80, 0x3F, 0x00, 0x1E, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x0C, 0x00, 0x1C, 0x00, 0x3C, 0x00, 0x3C, 0x00, 0x0C, 0x00, 0x0C, 0x00, 0x0C, 0x00, 0x0C, 0x00,
  0x0C, 0x00, 0x0C, 0x00, 0x0C, 0x00, 0x0C, 0x00, 0x3F, 0x00, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x3F, 0x00, 0x7F, 0x80, 0xE1, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0x01, 0xC0, 0x03, 0x80, 0x07, 0x00,
  0x0E, 0x00, 0x1C, 0x00, 0x38, 0x00, 0x70, 0x00, 0xFF, 0xC0, 0xFF, 0xC0, 0x00, 0x00, 0x00, 0x00,
  0x3F, 0x00, 0x7F, 0x80, 0xE1, 0xC0, 0xC0, 0xC0, 0x00, 0xC0, 0x01, 0xC0, 0x0F, 0x80, 0x0F, 0x80,
  0x01, 0xC0, 0x00, 0xC0, 0xC0, 0xC0, 0xE1, 0xC0, 0x7F, 0x80, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x03, 0x00, 0x07, 0x00, 0x0F, 0x00, 0x1F, 0x00, 0x3B, 0x00, 0x73, 0x00, 0xE3, 0x00, 0xC3, 0x00,
  0xFF, 0xC0, 0xFF, 0xC0, 0x03, 0x00, 0x03, 0x00, 0x03, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x7F, 0x80, 0x7F, 0x80, 0x60, 0x00, 0x60, 0x00, 0x60, 0x00, 0x7F, 0x00, 0x7F, 0x80, 0x01, 0xC0,
  0x00, 0xC0, 0x00, 0xC0, 0xC0, 0xC0, 0xE1, 0xC0, 0x7F, 0x80, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x1F, 0x00, 0x3F, 0x00, 0x70, 0x00, 0xE0, 0x00, 0xC0, 0x00, 0xC0, 0x00, 0xFF, 0x00, 0xFF, 0x80,
  0xC1, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xE1, 0xC0, 0x7F, 0x80, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00,
  0xFF, 0xC0, 0xFF, 0xC0, 0xC0, 0xC0, 0x01, 0xC0, 0x03, 0x80, 0x07, 0x00, 0x0E, 0x00, 0x0C, 0x00,
  0x18, 0x00, 0x18, 0x00, 0x30, 0x00, 0x30, 0x00, 0x60, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x3F, 0x00, 0x7F, 0x80, 0xE1, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xE1, 0xC0, 0x7F, 0x80, 0x7F, 0x80,
  0xE1, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xE1, 0xC0, 0x7F, 0x80, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x3F, 0x00, 0x7F, 0x80, 0xE1, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xE0, 0xC0, 0x7F, 0xC0, 0x3F, 0xC0,
  0x00, 0xC0, 0x00, 0xC0, 0x01, 0xC0, 0x03, 0x80, 0x3F, 0x00, 0x3E, 0x00, 0x00, 0x00, 0x00, 0x00
};


/*`````````````````````````````````````````````````````````````````````````````````````````````````
  |    Font definition -- Char cell: 7 x 12 pixels -- PROPORTIONAL spacing.
  |                       Each data byte is a row of up to 7 pixels (10 bytes/char)
  |
  |    Table format: 11 bytes per character --
  |           byte[0] bit 7 is descender flag, if true, shift char bitmap down 2 rows;
  |           byte[0] bits 2:0 specify width of character (1..7 pixels);
  |           byte[1:10] (10 bytes) contain the character bitmap image.
  |
  |    Note:  Most chars start on the top row and are 6 dots wide
  |           Upper-case letters are mostly 6 dots wide and occupy the top 10 rows.
  |           Lower-case letters without descenders occupy 7 rows (4th to 10th row).
  |           Lower-case descenders use the 11th and 12th rows in the bitmap image.
  |
  |  <!> This font Copyright by M.J.Bauer (2016++)  Permission is granted to use freely,
  |      on condition that M.J.Bauer is acknowledged as the font designer (www.mjbauer.biz).
*/
const  uint8_t  font_table_prop_7x12[] =
{
  0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // SPACE
  0x04, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x00, 0x00, 0x20,  // !
  0x04, 0x50, 0x50, 0x50, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // "
  0x06, 0x48, 0x48, 0xFC, 0x48, 0x48, 0x48, 0xFC, 0x48, 0x48, 0x00,  // #
  0x07, 0x28, 0x7E, 0xA8, 0xA8, 0x7C, 0x2A, 0x2A, 0xFC, 0x28, 0x28,  // $
  0x07, 0x00, 0x60, 0x92, 0x64, 0x08, 0x10, 0x20, 0x4C, 0x92, 0x0C,  // %
  0x07, 0x00, 0x30, 0x48, 0x48, 0x30, 0x50, 0x8A, 0x8C, 0x88, 0x76,  // &
  0x04, 0x20, 0x20, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // '
  0x05, 0x10, 0x20, 0x20, 0x40, 0x40, 0x40, 0x40, 0x20, 0x20, 0x10,  // (
  0x05, 0x40, 0x20, 0x20, 0x10, 0x10, 0x10, 0x10, 0x20, 0x20, 0x40,  // )
  0x05, 0x00, 0x20, 0xA8, 0x70, 0xA8, 0x20, 0x00, 0x00, 0x00, 0x00,  // *
  0x05, 0x00, 0x00, 0x00, 0x20, 0x20, 0xF8, 0x20, 0x20, 0x00, 0x00,  // +
  0x83, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x60, 0x20, 0x40,  // ,
  0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF8, 0x00, 0x00, 0x00, 0x00,  // -
  0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x60,  // .
  0x05, 0x08, 0x08, 0x10, 0x10, 0x20, 0x20, 0x40, 0x40, 0x80, 0x80,  // /

  0x06, 0x78, 0x84, 0x84, 0x8C, 0x94, 0xA4, 0xC4, 0x84, 0x84, 0x78,  // 0
  0x05, 0x20, 0x60, 0xA0, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0xF8,  // 1
  0x06, 0x78, 0x84, 0x04, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0xFC,  // 2
  0x06, 0x78, 0x84, 0x04, 0x04, 0x18, 0x04, 0x04, 0x04, 0x84, 0x78,  // 3
  0x06, 0x08, 0x18, 0x28, 0x48, 0x88, 0x88, 0xFC, 0x08, 0x08, 0x08,  // 4
  0x06, 0xFC, 0x80, 0x80, 0x80, 0x78, 0x04, 0x04, 0x04, 0x84, 0x78,  // 5
  0x06, 0x78, 0x80, 0x80, 0x80, 0xF8, 0x84, 0x84, 0x84, 0x84, 0x78,  // 6
  0x06, 0xFC, 0x04, 0x08, 0x08, 0x10, 0x10, 0x20, 0x20, 0x40, 0x40,  // 7
  0x06, 0x78, 0x84, 0x84, 0x84, 0x78, 0x84, 0x84, 0x84, 0x84, 0x78,  // 8
  0x06, 0x78, 0x84, 0x84, 0x84, 0x84, 0x7C, 0x04, 0x04, 0x04, 0x78,  // 9
  0x03, 0x00, 0x00, 0x00, 0x60, 0x60, 0x00, 0x00, 0x00, 0x60, 0x60,  // :
  0x83, 0x00, 0x60, 0x60, 0x00, 0x00, 0x00, 0x60, 0x60, 0x20, 0x40,  // ;
  0x04, 0x00, 0x00, 0x10, 0x20, 0x40, 0x80, 0x40, 0x20, 0x10, 0x00,  // <
  0x05, 0x00, 0x00, 0x00, 0x00, 0xF8, 0x00, 0x00, 0xF8, 0x00, 0x00,  // =
  0x04, 0x00, 0x00, 0x80, 0x40, 0x20, 0x10, 0x20, 0x40, 0x80, 0x00,  // >
  0x06, 0x78, 0x84, 0x04, 0x04, 0x08, 0x10, 0x20, 0x20, 0x00, 0x20,  // ?

  0x07, 0x00, 0x38, 0x44, 0x92, 0xAA, 0xAA, 0x9C, 0x40, 0x3C, 0x00,  // @
  0x06, 0x78, 0x84, 0x84, 0x84, 0xFC, 0x84, 0x84, 0x84, 0x84, 0x84,  // A
  0x06, 0xF8, 0x44, 0x44, 0x44, 0x78, 0x44, 0x44, 0x44, 0x44, 0xF8,  // B
  0x06, 0x78, 0x84, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x84, 0x78,  // C
  0x06, 0xF8, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0xF8,  // D
  0x06, 0xFC, 0x80, 0x80, 0x80, 0xF8, 0x80, 0x80, 0x80, 0x80, 0xFC,  // E
  0x06, 0xFC, 0x80, 0x80, 0x80, 0xF8, 0x80, 0x80, 0x80, 0x80, 0x80,  // F
  0x06, 0x78, 0x84, 0x80, 0x80, 0x80, 0x9C, 0x84, 0x84, 0x84, 0x78,  // G
  0x06, 0x84, 0x84, 0x84, 0x84, 0xFC, 0x84, 0x84, 0x84, 0x84, 0x84,  // H
  0x04, 0x70, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x70,  // I
  0x06, 0x3C, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x88, 0x70,  // J
  0x06, 0x84, 0x88, 0x90, 0xA0, 0xC0, 0xA0, 0x90, 0x88, 0x84, 0x84,  // K
  0x06, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xFC,  // L
  0x07, 0x82, 0xC6, 0xAA, 0xAA, 0x92, 0x92, 0x82, 0x82, 0x82, 0x82,  // M
  0x06, 0x84, 0xC4, 0xA4, 0x94, 0x8C, 0x84, 0x84, 0x84, 0x84, 0x84,  // N
  0x06, 0x78, 0x84, 0x84, 0x84, 0x84, 0x84, 0x84, 0x84, 0x84, 0x78,  // O

  0x06, 0xF8, 0x84, 0x84, 0x84, 0x84, 0xF8, 0x80, 0x80, 0x80, 0x80,  // P
  0x06, 0x78, 0x84, 0x84, 0x84, 0x84, 0x84, 0x94, 0x94, 0x88, 0x74,  // Q
  0x06, 0xF8, 0x84, 0x84, 0x84, 0x84, 0xF8, 0xA0, 0x90, 0x88, 0x84,  // R
  0x06, 0x7C, 0x80, 0x80, 0x80, 0x78, 0x04, 0x04, 0x04, 0x04, 0xF8,  // S
  0x07, 0xFE, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,  // T
  0x06, 0x84, 0x84, 0x84, 0x84, 0x84, 0x84, 0x84, 0x84, 0x84, 0x78,  // U
  0x07, 0x82, 0x82, 0x82, 0x82, 0x44, 0x44, 0x28, 0x28, 0x10, 0x10,  // V
  0x07, 0x82, 0x82, 0x82, 0x82, 0x82, 0x92, 0x92, 0x92, 0x92, 0x6C,  // W
  0x07, 0x82, 0x82, 0x44, 0x28, 0x10, 0x10, 0x28, 0x44, 0x82, 0x82,  // X
  0x07, 0x82, 0x82, 0x82, 0x82, 0x44, 0x28, 0x10, 0x10, 0x10, 0x10,  // Y
  0x07, 0xFE, 0x02, 0x04, 0x08, 0x10, 0x10, 0x20, 0x40, 0x80, 0xFE,  // Z
  0x05, 0x70, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,  // [
  0x05, 0x80, 0x80, 0x40, 0x40, 0x20, 0x20, 0x10, 0x10, 0x08, 0x08,  // back-slash
  0x05, 0x70, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,  // ]
  0x05, 0x20, 0x50, 0x88, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // ^
  0x85, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFC, 0x00,  // _

  0x04, 0x40, 0x20, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // `
  0x06, 0x00, 0x00, 0x00, 0x78, 0x04, 0x7C, 0x84, 0x84, 0x84, 0x7C,  // a
  0x06, 0x80, 0x80, 0x80, 0xF8, 0x84, 0x84, 0x84, 0x84, 0x84, 0x78,  // b
  0x06, 0x00, 0x00, 0x00, 0x78, 0x84, 0x80, 0x80, 0x80, 0x84, 0x78,  // c
  0x06, 0x04, 0x04, 0x04, 0x7C, 0x84, 0x84, 0x84, 0x84, 0x84, 0x78,  // d
  0x06, 0x00, 0x00, 0x00, 0x78, 0x84, 0x84, 0xF8, 0x80, 0x80, 0x78,  // e
  0x05, 0x38, 0x40, 0x40, 0x40, 0xF0, 0x40, 0x40, 0x40, 0x40, 0x40,  // f
  0x86, 0x00, 0x78, 0x84, 0x84, 0x84, 0x84, 0x7C, 0x04, 0x04, 0x78,  // g
  0x06, 0x80, 0x80, 0x80, 0xF8, 0x84, 0x84, 0x84, 0x84, 0x84, 0x84,  // h
  0x04, 0x00, 0x20, 0x00, 0x60, 0x20, 0x20, 0x20, 0x20, 0x20, 0x70,  // i
  0x84, 0x00, 0x60, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0xC0,  // j
  0x06, 0x80, 0x80, 0x80, 0x88, 0x90, 0xA0, 0xE0, 0x90, 0x88, 0x84,  // k
  0x04, 0xC0, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x30,  // l
  0x07, 0x00, 0x00, 0x00, 0x6C, 0x92, 0x92, 0x92, 0x92, 0x82, 0x82,  // m
  0x06, 0x00, 0x00, 0x00, 0x78, 0x84, 0x84, 0x84, 0x84, 0x84, 0x84,  // n
  0x06, 0x00, 0x00, 0x00, 0x78, 0x84, 0x84, 0x84, 0x84, 0x84, 0x78,  // o

  0x86, 0x00, 0x78, 0x84, 0x84, 0x84, 0x84, 0xF8, 0x80, 0x80, 0x80,  // p
  0x86, 0x00, 0x78, 0x84, 0x84, 0x84, 0x84, 0x7C, 0x04, 0x04, 0x04,  // q
  0x06, 0x00, 0x00, 0x00, 0x78, 0x84, 0x84, 0x80, 0x80, 0x80, 0x80,  // r
  0x06, 0x00, 0x00, 0x00, 0x78, 0x84, 0x80, 0x78, 0x04, 0x84, 0x78,  // s
  0x05, 0x00, 0x40, 0x40, 0xF0, 0x40, 0x40, 0x40, 0x40, 0x40, 0x38,  // t
  0x06, 0x00, 0x00, 0x00, 0x84, 0x84, 0x84, 0x84, 0x84, 0x84, 0x78,  // u
  0x06, 0x00, 0x00, 0x00, 0x84, 0x84, 0x84, 0x84, 0x88, 0x90, 0x60,  // v
  0x07, 0x00, 0x00, 0x00, 0x82, 0x82, 0x82, 0x92, 0x92, 0x92, 0x6C,  // w
  0x07, 0x00, 0x00, 0x00, 0x82, 0x44, 0x28, 0x10, 0x28, 0x44, 0x82,  // x
  0x86, 0x00, 0x84, 0x84, 0x84, 0x84, 0x84, 0x7C, 0x04, 0x04, 0x78,  // y
  0x06, 0x00, 0x00, 0x00, 0xFC, 0x04, 0x08, 0x10, 0x20, 0x40, 0xFC,  // z
  0x06, 0x18, 0x20, 0x20, 0x20, 0x20, 0xC0, 0x20, 0x20, 0x20, 0x20,  // {
  0x05, 0x20, 0x20, 0x20, 0x20, 0x20, 0x00, 0x20, 0x20, 0x20, 0x20,  // |
  0x06, 0xC0, 0x20, 0x20, 0x20, 0x20, 0x18, 0x20, 0x20, 0x20, 0x20,  // }
  0x07, 0x00, 0x00, 0x00, 0x60, 0x92, 0x0C, 0x00, 0x00, 0x00, 0x00,  // ~
  0x06, 0x00, 0x00, 0x00, 0x00, 0x30, 0x30, 0x00, 0x00, 0x00, 0x00   // DEL
};

// Display buffer:  64 rows x 8 cols x 16 bits (1 bit/pixel)
static  uint16_t screenBuffer[64][8];

static  uint8_t  PixelMode;     // Pixel writing mode (see Disp_SetMode())
static  uint16_t CursorPosX;    // screen cursor position, X-coord
static  uint16_t CursorPosY;    // screen cursor position, Y-coord
static  uint8_t  FontProp;      // Font style (0: monospaced, 1: proportional)
static  uint8_t  FontSize;      // Char cell height (8, 12, 16 or 24 pixels)
static  uint8_t  FontWeight;    // 0 = Normal;  1 = Bold

// List of chars that are not rendered in bold typeface in size 8 font...
static  uint8_t  NotBoldCharList[] = { '"', '#', 39, ',', '.', ':', ';', '@' };


/*----------------------------------------------------------------------------------
  |  Name         :  Disp_ClearScreen()
  |  Function     :  Clear OLED module GDRAM and MCU screen buffer.
  |                  Position graphics cursor at upper LHS = (0, 0).
  |  Input        :  --
  |  Return       :  --
  +-----------------------------------------------------------------------------------*/
void  Disp_ClearScreen(void)
{
  int     wordcount = 0;
  uint16_t  *pBuf = &screenBuffer[0][0];

  while (wordcount++ < 512)
  {
    *pBuf++ = 0;
  }

  SH1106_ClearGDRAM();

  PixelMode = SET_PIXELS;
  FontSize = 8;
  FontWeight = 0;
  CursorPosX = 0;
  CursorPosY = 0;
}

/*----------------------------------------------------------------------------------
  |  Name         :  Disp_Mode()
  |  Function     :  Set global pixel write mode for all display functions,
  |                  except Disp_ClearScreen() which always clears pixels.
  |                  Default mode after Disp_ClearScreen() is SET_PIXELS.
  |
  |  Input        :  mode = CLEAR_PIXELS (0), SET_PIXELS (1), or FLIP_PIXELS (2)
  +----------------------------------------------------------------------------------*/
void  Disp_Mode(uint8_t mode)
{
  PixelMode = mode;
}


/*----------------------------------------------------------------------------------
  |  Name         :  Disp_PosXY()
  |  Function     :  Set graphics cursor position to (x, y) coords
  |  Input        :  x, y coords
  +-----------------------------------------------------------------------------------*/
void  Disp_PosXY(uint16_t x, uint16_t y)
{
  CursorPosX = x;
  CursorPosY = y;
}


/*----------------------------------------------------------------------------------
  |  Name         :  Disp_GetX()
  |  Function     :  Returns graphics cursor X-coord (0..127)
  |  Input        :  --
  |  Return       :  CursorPosX
  +----------------------------------------------------------------------------------*/
uint16_t  Disp_GetX(void)
{
  return CursorPosX;
}


/*----------------------------------------------------------------------------------
  |  Name         :  Disp_GetY()
  |  Function     :  Returns graphics cursor Y-coord (0..63)
  |  Input        :  --
  |  Return       :  CursorPosY
  +----------------------------------------------------------------------------------*/
uint16_t  Disp_GetY(void)
{
  return CursorPosY;
}


/*----------------------------------------------------------------------------------
  |  Name         :  Disp_BlockFill()
  |
  |  Function     :  Fills a rectangular block of the screen with pixels,
  |                  using global writing mode (set, clear or flip),
  |                  at the graphics cursor position (x, y).
  |                  Cursor position remains unchanged.
  |
  |  Input        :  w, h = width and height (pixels) of block to be filled
  |
  |  Return       :  --
  +----------------------------------------------------------------------------------*/
void  Disp_BlockFill(uint16_t w, uint16_t h)
{
  uint16_t  rowBuffer[8];         // pixel pattern for filling whole row
  int     row, col, i;            // row and column word index for screen buffer
  int     firstCol;               // first (leftmost) column-word in a row to be modified
  int     lastCol;                // last (rightmost) column-word in a row to be modified
  int     offset;                 // shift offset (# of bits) from word boundary
  uint16_t  pixelWord;            // bits in column-word to be modified
  uint8_t   carryIn, carryOut;
  int     count;
  int     x = CursorPosX;
  int     y = CursorPosY;

  if (x > 127)  x = 0;            // prevent writing past end-of-row
  if ((x + w) > 128) w = 128 - x;

  firstCol = x / 16;
  lastCol = (x + w - 1) / 16;
  offset = x % 16;

  for (col = 0;  col < 8;  col++)  // clear row buffer
  {
    rowBuffer[col] = 0;
  }

  // Set w pixels (bits) in row buffer, aligned on word boundary of firstCol
  for ((count = w, col = firstCol);  col <= lastCol;  col++)
  {
    if (count >= 16)
    {
      rowBuffer[col] = 0xFFFF;
      count -= 16;
    }
    else  // less than 16 bits remaining
    {
      for (i = 0;  i < count;  i++)
      {
        rowBuffer[col] >>= 1;
        rowBuffer[col] |= 0x8000;
      }
      break;
    }
  }

  // Shift row to the right x bits, in effect, so that first pixel is at x-coord
  for (i = 0;  i < offset;  i++)
  {
    for ((carryIn = 0, col = firstCol);  col <= lastCol;  col++)
    {
      carryOut = (uint8_t) (rowBuffer[col] & 0x0001);  // carry = b0
      rowBuffer[col] >>= 1;
      if (carryIn) rowBuffer[col] |= 0x8000;  // b15 = 1
      else  rowBuffer[col] &= ~0x8000;        // b15 = 0
      carryIn = carryOut;
    }
  }

  // Update screen buffer
  for (row = y;  row < (y + h) && row < 64;  row++)
  {
    for (col = firstCol;  col <= lastCol && col < 8;  col++)
    {
      pixelWord = screenBuffer[row][col];

      if (PixelMode == SET_PIXELS) pixelWord |= rowBuffer[col];
      else if (PixelMode == CLEAR_PIXELS) pixelWord &= ~rowBuffer[col];
      else  pixelWord ^= rowBuffer[col];  // FLIP_PIXELS

      screenBuffer[row][col] = pixelWord;
    }
  }

  // Update OLED module -- write block (w x h) pixels of screen buffer at (x, y) to GDRAM
  SH1106_WriteBlock((uint16_t *) screenBuffer, x, y, w, h);
}

/*----------------------------------------------------------------------------------
  |  Name         :  Disp_ClearArea()
  |  Function     :  Clear a rectangular area of the screen at cursor pos'n.
  |                  Exits with cursor repositioned at (x, y) as on entry;
  |                    and with pixel write mode = SET_PIXELS.
  |  Input        :  w, h = width & height of area to be cleared.
  |  Return       :  --
  +-----------------------------------------------------------------------------------*/
void  Disp_ClearArea(uint16_t w, uint16_t h)
{
  uint16 save_X = CursorPosX;
  uint16 save_Y = CursorPosY;
  
  Disp_Mode(CLEAR_PIXELS);
  Disp_BlockFill(w, h);  
  Disp_Mode(SET_PIXELS);
  CursorPosX = save_X;
  CursorPosY = save_Y;
}

/*----------------------------------------------------------------------------------
  |  Name         :  Disp_PutImage()
  |
  |  Function     :  Render bitmap image at current (x, y) using currently
  |                  selected writing mode (i.e. set, clear or flip pixels).
  |                  Cursor position is not affected.
  |
  |                  The bitmap image is assumed to be an array of bytes, ordered
  |                  as array[h][n], where n is the minimum number of bytes needed
  |                  to hold one row of pixels, i.e. w pixels, and h is the height
  |                  of the image in pixels. Bit 7 of each byte is the LHS pixel.
  |
  |  Input        :  (uint8_t| ) imageData = pointer to bit-map image data
  |                  (uint16_t)  w = image width, h = image height, pixels
  |
  |  Return       :  TRUE (1) if any pixel in the image definition is high (=1) AND
  |                  the corresponding pixel on the screen is already set (=1) before
  |                  the image is written;  otherwise return FALSE (0).
  +----------------------------------------------------------------------------------*/
uint8_t  Disp_PutImage(uint8_t *imageData, uint16_t w, uint16_t h)
{
  uint16_t  rowBuffer[8];         // row of 128 pixels forming the image
  int     row, col, i;            // row and column word index for screen buffer
  int     firstCol;               // first (leftmost) column-word in a row to be modified
  int     lastCol;                // last (rightmost) column-word in a row to be modified
  int     offset;                 // shift offset (# of bits) from word boundary
  uint16_t  pixelWord;            // bits in column-word to be modified
  uint8_t  *pData;
  uint16_t  bitmask;
  uint8_t   carryIn, carryOut;
  int     count;
  int     imageBytesInRow;        // minimum number of bytes to hold w pixels (1 row)
  uint8_t   collision = 0;        // return value (0 or 1)
  uint16_t  x = CursorPosX;
  uint16_t  y = CursorPosY;

  if (x > 127)  x = 0;            // prevent writing past end-of-row
  if ((x + w) > 128) w = 128 - x;

  firstCol = x / 16;
  lastCol = (x + w - 1) / 16;
  offset = x % 16;
  imageBytesInRow = (w / 8) + ((w % 8) ? 1 : 0);

  for (row = y;  row < (y + h) && row < 64;  row++)
  {
    pData = (uint8_t *)imageData + ((row - y) * imageBytesInRow);  // point to (next) row
    rowBuffer[lastCol] = 0;  // clear garbage

    // Copy row of image data to row buffer, aligned on word boundary of firstCol
    for ((count = w, col = firstCol);  col <= lastCol;  col++)
    {
      rowBuffer[col] = (uint16_t) * pData << 8;  // High-order (left) byte
      pData++;
      rowBuffer[col] |= (uint16_t) * pData;  // Low-order (right) byte, maybe garbage
      pData++;

      if (count < 16)  // less than 16 bits remaining
      {
        bitmask = 0x0000;
        for (i = 0;  i < count;  i++)
        {
          bitmask >>= 1;
          bitmask |= 0x8000;
        }
        rowBuffer[col] &= bitmask;  // mask off "out of bounds" pixels
        break;
      }
      else  count -= 16;  // next col.
    }

    // Shift row to the right x bits, in effect, so that first pixel is at x-coord
    for (i = 0;  i < offset;  i++)
    {
      for ((carryIn = 0, col = firstCol);  col <= lastCol;  col++)
      {
        carryOut = (uint8_t) (rowBuffer[col] & 0x0001);  // carry = b0
        rowBuffer[col] >>= 1;
        if (carryIn) rowBuffer[col] |= 0x8000;  // b15 = 1
        else  rowBuffer[col] &= ~0x8000;        // b15 = 0
        carryIn = carryOut;
      }
    }

    // Update 1 row in screen buffer
    for (col = firstCol;  col <= lastCol && col < 8;  col++)
    {
      pixelWord = screenBuffer[row][col];
      if (pixelWord & rowBuffer[col]) collision = 1;

      if (PixelMode == SET_PIXELS) pixelWord |= rowBuffer[col];
      else if (PixelMode == CLEAR_PIXELS) pixelWord &= ~rowBuffer[col];
      else  pixelWord ^= rowBuffer[col];  // FLIP_PIXELS

      screenBuffer[row][col] = pixelWord;
    }
  }

  // Update OLED module -- write block (w x h) pixels of screen buffer at (x, y) to GDRAM
  SH1106_WriteBlock((uint16_t *) screenBuffer, x, y, w, h);

  return  collision;
}


/*----------------------------------------------------------------------------------
  |  Name         :  Disp_ScreenCapture()
  |  Function     :  Return a pointer to the screen buffer.
  |                  The buffer is 512 words ordered as screenBuffer[rows][cols],
  |                  where rows == 64 and cols == 8. Each column is 16 pixels.
  |
  |  Note         :  The screenBuffer[] array is not ordered the same as the GDRAM
  |                  memory in the SH1106 controller.
  |                  (See Disp_ClearScreen() for a map of the SH1106 GDRAM buffer.)
  |  Input        :  --
  |  Return       :  (uint16_t| ) address of local screenBuffer[]
  +-----------------------------------------------------------------------------------*/
uint16_t  *Disp_ScreenCapture()
{
  return  (uint16_t *) &screenBuffer[0][0];
}


/*----------------------------------------------------------------------------------
  |  Name         :  Disp_SetFont()
  |  Function     :  Set font style for text display using functions...
  |                  Disp_PutChar(), Disp_PutText(), etc.
  |
  |  Input        :  uint8_t  font_ID = one of the following...
  |
  |     MONO_8_NORM      Mono-spaced font;  char width is 5 pix
  |     PROP_8_NORM      Proportional font;  char width is 3..5 pix
  |     PROP_12_NORM     Proportional font;  char width is 4..7 pix
  |     PROP_12_BOLD     as above, but bold weight (width + 1)
  |     MONO_16_NORM     Mono-spaced font;  char width is 10 pix
  |     MONO_16_BOLD     as above, but bold weight (width + 1)
  |     PROP_24_NORM     Proportional font;  char width is 7..15 pix
  |
  +-----------------------------------------------------------------------------------*/
void  Disp_SetFont(uint8_t font_ID)
{
  FontWeight = font_ID & 1;            // b0 (0: normal, 1: bold)
  FontProp = (font_ID >> 1) & 1;       // b1 (0: monospaced, 1: proportional)
  FontSize = 8 + 4 * (font_ID >> 2);   // b3:b2 (0: 8p, 1: 12p, 2: 16p, 3: 24p)
  if (font_ID >= 12) FontSize = 24;    // corrected
}


/*----------------------------------------------------------------------------------
  |  Name         :  Disp_GetFont()
  |  Function     :  Get current font ID setting
  |
  |  Input        :  --
  |  Return       :  uint8_t  font_ID = 0 .. 15
  +----------------------------------------------------------------------------------*/
uint8_t  Disp_GetFont()
{
  uint8_t  size_id = (FontSize - 8) / 4;   // 0, 1, 2, 4

  if (size_id == 4) size_id = 3;  // corrected

  return  (size_id << 2) + (FontProp << 1) + FontWeight;
}


/*----------------------------------------------------------------------------------
  |  Name         :  Disp_PutChar()
  |  Function     :  Show ASCII char at current (x, y) using selected font.
  |  Input        :  (uint8_t) uc = ASCII char to be displayed
  |  Return       :  --
  +-----------------------------------------------------------------------------------*/
void  Disp_PutChar(char uc)
{
  if (FontSize >= 24)  Disp_PutChar24(uc);
  else if (FontSize >= 16)  Disp_PutChar16(uc);
  else if (FontSize >= 12)  Disp_PutChar12(uc);
  else  Disp_PutChar8(uc);
}


/*----------------------------------------------------------------------------------
  |  Name         :  Disp_PutText()
  |  Function     :  Show text string at (x, y) using selected font.
  |                  Stops at first non-printable char found (e.g. NUL).
  |                  Truncates text beyond the right boundary of the screen
  |                  if the string is too long to fit on the current line.
  |
  |  Input        :  str = pointer to ASCII string (NUL terminated)
  |  Return       :  --
  +-----------------------------------------------------------------------------------*/
void  Disp_PutText(const char *str)
{
  uint8_t  b;

  while ((b = *str) >= 0x20)
  {
    Disp_PutChar(b);
    str++;
  }
}


/*-------------------------------------------------------------------------------------
  |  Name         :  Disp_PutDigit()
  |  Function     :  Show hex/decimal digit value (1 char)
  |
  |  Input        :  bDat = nybble to be converted and output
  |  Return       :  --
  +--------------------------------------------------------------------------------------*/
void  Disp_PutDigit(uint8_t bDat)
{
  bDat &= 0x0F;
  if (bDat < 10) Disp_PutChar('0' + bDat);
  else Disp_PutChar('A' + bDat - 10);
}


/*---------------------------------------------------------------------------------------
  |  Name         :  Disp_PutHexByte()
  |  Function     :  Show hexadecimal byte value (2 chars)
  |
  |  Input        :  bDat = byte data
  |  Return       :  --
  +---------------------------------------------------------------------------------------*/
void  Disp_PutHexByte(uint8_t bDat)
{
  Disp_PutDigit(bDat >> 4);      // MS digit
  Disp_PutDigit(bDat & 0x0F);    // LS digit
}


/*
*   Function:   Disp_PutDecimal
*
*   Purpose:    Displays a 32-bit integer as a signed decimal number, up to 10 digits,
*               right justified in the specified field, with leading zeros suppressed.
*               Negative numbers are output with a 'minus' sign to the left of the first
*               significant digit. The field size includes the minus sign.
*
*   Args:       (int32) lVal = signed longword to be converted and output
*               (uint8) bFieldSize = minimum number of character places (1..12)
*/
void  Disp_PutDecimal(int32_t lVal, uint8 bFieldSize)
{
  uint8    acDigit[12];  // ASCII result string, acDigit[0] is LSD
  int      idx;
  int      iSignLoc = 0;
  uint8    c;
  uint8    yNegative = 0;
  uint8    yLeadingZero = 1;

  if (bFieldSize > 12)  bFieldSize = 12;
  if (bFieldSize < 1)  bFieldSize = 1;
  if (lVal < 0)  { yNegative = 1;  lVal = 0 - lVal; }  // make value absolute

  for (idx = 0;  idx < 12;  idx++)  // begin conversion with LSD
  {
      c = '0' + (uint8)(lVal % 10);
      acDigit[idx] = c;
      lVal = lVal / 10;
  }

  for (idx = 11;  idx >= 0;  idx--)  // begin processing with MSD
  {
      c = acDigit[idx];
      if ( idx != 0 && c == '0' && yLeadingZero )  // leave digit 0 (LSD) alone
          acDigit[idx] = ' ';

      if (idx == 0 || c != '0')  // found 1st significant digit (MSD)
      {
          yLeadingZero = 0;
          if (iSignLoc == 0) iSignLoc = idx + 1;
      }
  }

  if (yNegative) acDigit[iSignLoc] = '-';  // if +ve, there will be a SPACE

  for (idx = 11;  idx >= 0;  idx--)  // begin output with MSD (or sign)
  {
      c = acDigit[idx];
      if (idx < bFieldSize || c != ' ') Disp_PutChar(c);
  }
}

// Function supports MONO_8_NORM font only.
//
void  DisplayTextCentered8p(short ypos, const char *str)
{
  short nchars = strlen(str);
  short xpos = (128 - nchars * 6) / 2;
  
  if (xpos < 0)  xpos = 0;
  Disp_SetFont(MONO_8_NORM); 
  Disp_PosXY(xpos, ypos);
  Disp_PutText(str);
}

// Function supports PROP_12_NORM font only.
//
void  DisplayTextCentered12p(short ypos, const char *str)
{
  short nchars = strlen(str);
  short xpos = (128 - nchars * 8) / 2;

  if (xpos < 0)  xpos = 0;
  Disp_SetFont(PROP_12_NORM); 
  Disp_PosXY(xpos, ypos);
  Disp_PutText(str);
}

// Function supports PROP_12_NORM font only.
//
void  DisplayTextCenteredInBox(short ypos, const char *str)
{
  short strWidth = strlen(str) * 8;  // approx.
  short xpos = (128 - strWidth) / 2;

  Disp_SetFont(PROP_12_NORM);
  Disp_PosXY(xpos, ypos);
  Disp_PutText(str);
  Disp_PosXY(xpos-4, ypos-3);
  DrawBox(strWidth+6, 16);
}


void  DrawBox(short w, short h)
{
  short  xorg = Disp_GetX();
  short  yorg = Disp_GetY();

  Disp_PosXY(xorg+1, yorg);
  Disp_DrawLineHoriz(w-1);
  Disp_PosXY(xorg, yorg+1);
  Disp_DrawLineVert(h-1);
  Disp_PosXY(xorg+1, yorg+h);
  Disp_DrawLineHoriz(w-1);
  Disp_PosXY(xorg+w, yorg+1);
  Disp_DrawLineVert(h-1);
}


//==============================  Private functions  =====================================

/*----------------------------------------------------------------------------------------
  |  Name         :  Disp_PutChar8()
  |
  |  Function     :  Display character from 5 x 8 font in normal size (5 x 8 pixels)
  |                  at current cursor position.
  |                  On return, CursorPosX is advanced (6 pixels if mono-spaced)
  |
  |  Input        :  uint8_t uc = ASCII char code
  |  Return       :  --
*/
void  Disp_PutChar8(uint8_t uc)
{
  short   i;
  uint8_t   bitmap[10];  // char cell buffer
  uint8_t  *pData;
  uint8_t   width;       // symbol width (pixels)
  bool    descender;   // True => shift bitmap down 1 pixel in cell

  if (uc < 32) return;  // non-printable

  if (FontProp)  // proportional width font
  {
    pData = (uint8_t *) &font_table_prop_5x8[(uc - 32) * 8];  // use prop'l table!

    width = *pData & 0x0F;
    descender = *pData & 0x80;
    pData++;
    bitmap[7] = 0x00;  // clear bottom row

    for (i = 0;  i < 7;  i++, pData++)  // copy from table to cell buffer
    {
      if (descender) bitmap[i + 1] = *pData; // shift down a row
      else  bitmap[i] = *pData;
    }
    // special cases -- top row
    if (descender) bitmap[0] = 0x00;  // top row is blank
    // special cases -- bottom row
    if (uc == 'j') bitmap[7] = 0x80;  // .. 'j' has a hook
    else if (uc == '[') bitmap[7] = 0xC0;
    else if (uc == ']') bitmap[7] = 0x60;
    else if (uc == '{' ) bitmap[7] = 0x30;
    else if (uc == '}' ) bitmap[7] = 0xC0;

    Disp_PutImage(bitmap, 5, 8);
    CursorPosX += width + 1;
  }
  else  // mono-spaced font
  {
    pData = (uint8_t *) &font_table_mono_5x8[(uc - 32) * 8];  // use mono table!

    for (i = 0;  i < 8;  i++, pData++)
    {
      bitmap[i] = *pData;
    }

    Disp_PutImage(bitmap, 6, 8);
    CursorPosX += 6;
  }
}


/*----------------------------------------------------------------------------------------
  |  Name         :  Disp_PutChar16()
  |
  |  Function     :  Display character in size 16 font... Char-cell 12 x 16 pix.
  |                  On return, PosX is advanced 12 pixels.
  |
  |  Input        :  uint8_t uc = (ext'd) ASCII char code
  |  Return       :  --
*/
void   Disp_PutChar16(uint8_t uc)
{
  if (uc < 32) return;  // non-printable

  if (uc >= '0' && uc <= '9') Disp_PutChar16_smooth(uc);  // digit 0 ~ 9
  else  Disp_PutChar16_ruff(uc);    // all other symbols

  CursorPosX += 12;
  if (FontWeight) CursorPosX++;  // bold
}


/*----------------------------------------------------------------------------------------
  |  Name         :  Disp_PutChar16_ruff()
  |
  |  Function     :  Display character from 5 x 8 font table in double size --
  |                        10 x 16 pix for normal weight; 11 x 16 pix in bold weight.
  |  Note         :  Some special chars do not allow bold weight.
  |
  |  Input        :  uint8_t uc = (ext'd) ASCII char code
  |  Return       :  --
*/
void   Disp_PutChar16_ruff(uint8_t uc)
{
  short  exceptions = ARRAY_SIZE(NotBoldCharList);
  short  i, j, k;
  uint8_t  bitmap[20][2];  // image is 2 cols x 16 rows
  uint8_t *pData;
  uint8_t  dots;
  uint16_t bitmask8;
  uint16_t bitmask16;
  uint16_t pixels;
  uint16_t shifted;
  uint8_t  allow_bold = 1;

  for (i = 0; i < exceptions; i++)
  {
    if (uc == NotBoldCharList[i]) {
      allow_bold = 0;
      break;
    }
  }
  if (uc > 127) allow_bold = 0;  // special symbol

  pData = (uint8_t *) &font_table_mono_5x8[(uc - 32) * 8];

  // Double the size of the character image from the font table...
  for (j = 0, k = 0;  j < 8;  j++, pData++)   // j is offset into font table
  {
    bitmask8 = 0x80;
    bitmask16 = 0xC000;
    dots = *pData;        // a "dot" (1 bit in *pData) becomes two pixels
    pixels = 0;
    for (i = 0;  i < 8;  i++)  // build a 16-bit row of pixels
    {
      if (dots & bitmask8) pixels |= bitmask16;
      bitmask8 >>= 1;
      bitmask16 >>= 2;
    }

    // Apply bold typeface if requested...
    if (FontWeight >= 1 && allow_bold)
    {
      shifted = pixels >> 1;
      pixels |= shifted;
    }

    // Construct 2 identical rows of the character bitmap
    bitmap[k][0] = HI_BYTE(pixels);    // Even numbered row of 16 pixels
    bitmap[k][1] = LO_BYTE(pixels);
    k++;
    bitmap[k][0] = HI_BYTE(pixels);    // Odd numbered row of 16 pixels
    bitmap[k][1] = LO_BYTE(pixels);
    k++;
  }

  Disp_PutImage((uint8_t *) bitmap, 12, 16);
}


/*----------------------------------------------------------------------------------------
  |  Name         :  Disp_PutChar16_smooth()
  |
  |  Function     :  Display character in font size 16 (10 x 16 pix)
  |                  using a special "high definition" font table.
  |                  Only decimal digits 0 ~ 9 are supported in this revision.
  |
  |  Input        :  uint8_t uc = (ext'd) ASCII char code, '0' to '9' only.
  |  Return       :  --
*/
void   Disp_PutChar16_smooth(uint8_t uc)
{
  uint8_t  *bitmap;

  bitmap = (uint8_t *) &font_table_digit_10x16[(uc - '0') * 32];

  Disp_PutImage(bitmap, 12, 16);
}


/*----------------------------------------------------------------------------------------
  |  Name         :  Disp_PutChar12()
  |  Function     :  Display character from 7 x 12 font in size 7 x 12 pixels
  |                  for normal weight, or 8 x 12 pix if bold weight selected.
  |                  This is a PROPORTIONALLY SPACED font (variable width).
  |                  On return, PosX is advanced (width + 2) px for normal weight,
  |                  (width + 3) for bold.
  |  Input        :  uint8_t uc = ASCII char code (32..127)
  |  Return       :  --
*/
void  Disp_PutChar12(uint8_t uc)
{
  uint8_t  bitmap[16];
  uint8_t  shifted;
  uint8_t *pData = bitmap;  // points to bitmap first, then font table
  uint8_t  width;           // symbol width (pixels) in font table
  bool   descender;       // True => symbol has descender (2 pixels)
  bool   allowBold = TRUE;
  int  i;

  if (uc < 32) return;  // non-printable

  for (i = 0; i < 16; i++)  {
    *pData++ = 0;  // Clear the symbol bitmap image buffer
  }

  // Flag symbols which should not be made bold
  if (uc == '@' || uc == '"' || uc == '$' || uc == '#'
      ||  uc == '.' || uc == ',' || uc == ':' || uc == ';' ) allowBold = FALSE;

  pData = (uint8_t *) &font_table_prop_7x12[(uc - 32) * 11];  // Point to font table

  width = *pData & 0x0F;
  descender = *pData & 0x80;
  pData++;
  bitmap[0] = 0x00;  // clear top 2 rows in cell (for symbols with descender)
  bitmap[1] = 0x00;

  for (i = 0;  i < 10;  i++, pData++)  // copy bitmap image of symbol
  {
    if (descender)  // symbols with descender are shifted down 2 pixels
    {
      bitmap[i + 2] = *pData;
      shifted = *pData >> 1;
      if (FontWeight > 0 && allowBold)  bitmap[i + 2] |= shifted; // make bold
    }
    else  // regular symbol -- no descender --
    {
      bitmap[i] = *pData;
      shifted = *pData >> 1;
      if (FontWeight > 0 && allowBold)  bitmap[i] |= shifted;  // make bold
    }
  }

  if (uc == 'j')  bitmap[1] = bitmap[5];  // Special case: 'j' has a dot on 2nd row
  // More special cases: These symbols have dots on the 2nd bottom row = top row
  if (uc == '[' || uc == ']' || uc == '|' || uc == '{' || uc == '}' )
    bitmap[10] = bitmap[0];

  Disp_PutImage(bitmap, 8, 12);
  CursorPosX += width + 2;
  if (FontWeight > 0) CursorPosX++;
}


/*----------------------------------------------------------------------------------------
  |  Name         :  Disp_PutChar24()
  |  Function     :  Display character from 7 x 12 font in double size (14 x 24 pix)
  |                  Bold weight is not supported... already bold enough!
  |                  On return, PosX is advanced by the symbol width + 3.
  |  Input        :  uint8_t uc = (ext'd) ASCII char code
  |  Return       :  --
*/
void  Disp_PutChar24(uint8_t uc)
{
  uint8_t  bitmap[30][2];      // char-cell image 14 (w) x 24 (h) px
  uint8_t *pData;              // points to bitmap first, then font table
  bool   allowBold = TRUE;   // make symbol 1 pixel fatter
  uint8_t  width;              // symbol width defined in font table
  bool   descender;          // True => symbol has descender (2 pixels)
  uint16_t bitmask8;
  uint16_t bitmask16;
  uint16_t pixels;
  uint16_t shifted;
  int    i, j, k;

  if (uc < 32) return;  // non-printable

  // Flag symbols which should not be made fatter...
  if (uc == '@' || uc == '"' || uc == '$' || uc == '#'
      ||  uc == '.' || uc == ',' || uc == ':' || uc == ';' ) allowBold = FALSE;

  pData = &bitmap[0][0];
  for (i = 0; i < 60; i++)  {
    *pData++ = 0;  // Clear the bitmap image
  }

  pData = (uint8_t *) &font_table_prop_7x12[(uc - 32) * 11];  // Point to font table

  width = *pData & 0x0F;
  descender = *pData & 0x80;
  pData++;

  // Double the size of the character image from the font table...
  for (j = 0, k = 0;  j < 10;  j++, k += 2, pData++)  // j is the row index (0..11)
  {
    bitmask8 = 0x80;
    bitmask16 = 0xC000;
    pixels = 0;

    for (i = 0;  i < 8;  i++)  // build a 16-bit row of pixels
    {
      if (*pData & bitmask8) pixels |= bitmask16; // create a dot (2 x 2 pix))
      bitmask8 >>= 1;
      bitmask16 >>= 2;
    }

    if (allowBold)  // Size 24 font has dots 3 pixels thick...
    {
      shifted = pixels >> 1;
      pixels |= shifted;
    }

    if (descender)  // symbols with descender are shifted down 4 pixels
    {
      bitmap[k + 5][0] = bitmap[k + 4][0] = HI_BYTE(pixels); // k = j * 2
      bitmap[k + 5][1] = bitmap[k + 4][1] = LO_BYTE(pixels);
    }
    else  // regular symbol
    {
      bitmap[k + 1][0] = bitmap[k + 0][0] = HI_BYTE(pixels); //  k = j * 2
      bitmap[k + 1][1] = bitmap[k + 0][1] = LO_BYTE(pixels);
    }
  }

  // Special case:  'j' has a dot on the 2nd row = 5th row
  if (uc == 'j')
  {
    bitmap[3][0] = bitmap[2][0] = bitmap[10][0];  // left 8 px
    bitmap[3][1] = bitmap[2][1] = bitmap[10][1];  // right 8 px
  }
  // More special cases:  These symbols have dots on the 2nd bottom row = top row
  if (uc == '[' || uc == ']' || uc == '|' || uc == '{' || uc == '}' )
  {
    bitmap[21][0] = bitmap[20][0] = bitmap[0][0];
    bitmap[21][1] = bitmap[20][1] = bitmap[0][1];
  }

  Disp_PutImage((uint8_t *) bitmap, 16, 24);
  CursorPosX += (width * 2) + 3;
}


//===============  SH1106 OLED CONTROLLER DRIVER FUNCTIONS (IIC)  ==================

/*----------------------------------------------------------------------------------
  |  Name         :  SH1106_WriteCommand()
  |  Function     :  Write 8-bit command to SH1106 controller
  |  Entry arg(s) :  cmd byte
  |  Return       :  --
*/
void  SH1106_WriteCommand(uint8_t cmd)
{
  Wire1.beginTransmission(SH1106_I2C_ADDRESS);
  Wire1.write(SH1106_MESSAGETYPE_COMMAND);
  Wire1.write(cmd);
  Wire1.endTransmission();
}


/*----------------------------------------------------------------------------------
  |  Name         :  SH1106_WriteData()
  |  Function     :  Write 8-bit data to SH1106 controller
  |  Entry arg(s) :  data byte
  |  Return       :  --
*/
void  SH1106_WriteData(uint8_t data)
{
  Wire1.beginTransmission(SH1106_I2C_ADDRESS);
  Wire1.write(SH1106_MESSAGETYPE_DATA);
  Wire1.write(data);
  Wire1.endTransmission();
}


/*----------------------------------------------------------------------------------
  |  Name         :  SH1106_Init()
  |  Function     :  Initialize SH1106 controller.
  |  Input        :  --
  |  Return       :  --
  |  Note         :  SH1106 GDRAM not cleared
*/
void  SH1106_Init(void)
{
  SH1106_WriteCommand(SH1106_DISPLAYOFF);            // 0xAE
  SH1106_WriteCommand(SH1106_SETDISPLAYCLOCKDIV);    // 0xD5
  SH1106_WriteCommand(0x80);                         // (suggested)
  SH1106_WriteCommand(SH1106_SETMULTIPLEX);          // 0xA8
  SH1106_WriteCommand(0x3F);
  SH1106_WriteCommand(SH1106_SETDISPLAYOFFSET);      // 0xD3
  SH1106_WriteCommand(0x00);                         // no offset

  SH1106_WriteCommand(SH1106_SETSTARTLINE | 0);      // line #0
  SH1106_WriteCommand(SH1106_CHARGEPUMP);            // 0x8D
  SH1106_WriteCommand(0x10);
  SH1106_WriteCommand(SH1106_MEMORYMODE);            // 0x20
  SH1106_WriteCommand(0x00);                         // use KS0108 format
  SH1106_WriteCommand(SH1106_SEGREMAP | 1);          // 0xA0
  SH1106_WriteCommand(SH1106_COMSCANDEC);

  SH1106_WriteCommand(SH1106_SETCOMPINS);            // 0xDA
  SH1106_WriteCommand(0x12);
  SH1106_WriteCommand(SH1106_SETCONTRAST);           // 0x81
  SH1106_WriteCommand(0x80);                         // POR value = 0x80
  SH1106_WriteCommand(SH1106_SETPRECHARGE);          // 0xD9
  SH1106_WriteCommand(0x22);
  SH1106_WriteCommand(SH1106_SETVCOMDETECT);         // 0xDB
  SH1106_WriteCommand(0x40);

  SH1106_WriteCommand(SH1106_DISPLAYALLON_RESUME);   // 0xA4
  SH1106_WriteCommand(SH1106_NORMALDISPLAY);         // 0xA6
  SH1106_WriteCommand(SH1106_DISPLAYON);             // 0xAF
}


/*----------------------------------------------------------------------------------
  |  Name         :  SH1106_SetContrast()
  |  Function     :  Set OLED display contrast (brightness).
  |  Input        :  level_pc:  contrast level (0..100 %)
  |  Return       :  --
*/
void  SH1106_SetContrast(unsigned level_pc)
{
  if (level_pc > 100)  level_pc = 100;
  SH1106_WriteCommand(SH1106_SETCONTRAST);
  SH1106_WriteCommand((level_pc * 255) / 100);
}


/*----------------------------------------------------------------------------------
  |  Name         :  SH1106_ClearGDRAM()
  |
  |  Function     :  Clear entire SH1106 controller graphics data RAM.
  |                  MCU RAM screen buffer is not cleared. (Use Disp_ClearScreen())
  |
  |  GDRAM format in SH1106 controller (132 x 64 pixels):
  |  ````````````````````````````````````````````````````
  |                0 -------------- Segment --------------- 131
  |       Page 0   ||||||||||||||||||||||||||||||||||||||||||||
  |       Page 1   ||||||||||||||||||||||||||||||||||||||||||||
  |       Page 2   ||||||||||||||||||||||||||||||||||||||||||||
  |       Page 3   ||||||||||||||||||||||||||||||||||||||||||||
  |       Page 4   ||||||||||||||||||||||||||||||||||||||||||||
  |       Page 5   ||||||||||||||||||||||||||||||||||||||||||||
  |       Page 6   ||||||||||||||||||||||||||||||||||||||||||||
  |       Page 7   ||||||||||||||||||||||||||||||||||||||||||||
  |
  |  Legend: Page = 8 lines.  Data byte (|) = 8 pixels vertical, bit 0 is at the top.
  |
  |  NB: The first 2 pixels on each line (segments 0 and 1) are not displayed.
  +------------------------------------------------------------------------------------*/
void  SH1106_ClearGDRAM(void)
{
  int   page, partition, segment;  // 16 segments per partition

  for (page = 0;  page < 8;  page++)
  {
    // Set GDRAM start of page address -- there are 8 pages
    SH1106_WriteCommand(SH1106_PAGEADDR + page);

    for (partition = 0;  partition < 9;  partition++)
    {
      // Set column/segment address for this partition
      SH1106_WriteCommand(SH1106_SETCOLUMNADDRLOW);  // AddrLow = 0
      SH1106_WriteCommand(SH1106_SETCOLUMNADDRHIGH + partition);
      // write 16 segments (max.) in auto-increment mode
      Wire1.beginTransmission(SH1106_I2C_ADDRESS);
      Wire1.write(SH1106_MESSAGETYPE_DATA);

      for (segment = 0;  segment < 16;  segment++)
      {
        if (partition == 8 && segment > 3) break;  // done 132 segments
        Wire1.write(0);
      }
      Wire1.endTransmission();
    }
  }
}


/*----------------------------------------------------------------------------------
  |  Function   :  SH1106_WriteBlock()
  |
  |  Overview   :  Copies a rectangular block of pixels from an external screen
  |                buffer in MCU RAM to the SH1106 controller GDRAM (graphics data RAM).
  |                In general, the GDRAM memory format differs from the MCU RAM screen
  |                buffer, so a transformation of some sort needs to be performed.
  |                The screen buffer format is optimized for speed in display functions.
  |
  |  Input:        scnBuf = address of screen buffer in MCU RAM
  |                x, y = pixel coords of upper LHS of block to be copied
  |                w, h = width and height (pixels) of block to be copied
  |
  |  Return     :  --
  |
  |  Notes:     :  The (external) screen buffer is formatted as 8 "columns" horizonally
  |                by 64 "rows" vertically. Each column has 16 pixels. The leftmost
  |                pixel is stored in the MS bit (bit15) of the column.
  |                See also: Disp_PutImage().
  +------------------------------------------------------------------------------------*/
void  SH1106_WriteBlock(uint16_t *scnBuf, uint16_t x, uint16_t y, uint16_t w, uint16_t h)
{
  uint8_t   page;                   // page address in SH1106 (1 page = 8 rows)
  uint8_t   x_coord;                // pixel horizontal coordinate
  int       row, col;               // row and column word index for screen buffer
  int       firstPage;              // first (top) page to be modified
  int       lastPage;               // last (bottom) page to be modified
  int       firstCol;               // first (leftmost) column in a row to be modified
  int       lastCol;                // last (rightmost) column in a row to be modified
  int       offset;                 // address offset of pixel word in scnBuf
  uint8_t   segAddr;                // segment address for write
  uint8_t   pixels;                 // 8 pixels aligned vertically (LS bit at top)
  uint8_t   bitmask;
  uint16_t  pixelWord[8];           // 8 rows x 16 pixels in a "column" to be modified
  uint16_t  *pBuf;

  if (y > 63)  y = 0;               // prevent writing past end-of-screen (vert.)
  if ((y + h) > 63)  h = 63 - y;

  if (x > 127)  x = 0;              // prevent writing past end-of-row (horiz.)
  if ((x + w) > 128)  w = 128 - x;

  firstPage = y / 8;
  lastPage = (y + h - 1) / 8;

  firstCol = x / 16;
  lastCol = (x + w - 1) / 16;

  for (page = firstPage;  page <= lastPage;  page++)
  {
    SH1106_WriteCommand(SH1106_PAGEADDR | page);   // set page address (0..7)

    for (col = firstCol;  col <= lastCol && col < 8;  col++)
    {
      // Grab a bunch of 16 (H) x 8 (V) pixels from buffer...
      offset = page * 64 + col;  // 64 words per buffer "page"
      pBuf = scnBuf + offset;
      for (row = 0;  row < 8;  row++)  // 8 rows in SH1106 page
      {
        pixelWord[row] = *pBuf;
        pBuf += 8;  // next row (advance 8 col's)
      }

      segAddr = col * 16 + 2;   // the first 2 pixels on any line are duds!
      SH1106_WriteCommand(SH1106_SETCOLUMNADDRLOW + (segAddr & 0xF));
      SH1106_WriteCommand(SH1106_SETCOLUMNADDRHIGH + (segAddr >> 4));
      // Write bunch of pixels, 16 (H) x 8 (V) to SH1106 controller
      Wire1.beginTransmission(SH1106_I2C_ADDRESS);
      Wire1.write(SH1106_MESSAGETYPE_DATA);

      for (x_coord = 0;  x_coord < 16;  x_coord++)
      {
        // transpose horiz pixels in pixelWord[8] to vertical pixelByte
        pixels = 0;
        bitmask = 0x01;
        for (row = 0;  row < 8;  row++)
        {
          if (pixelWord[row] & 0x8000) pixels |= bitmask;
          bitmask = bitmask << 1;   // next pixel down
          pixelWord[row] = pixelWord[row] << 1;  // next pixel right
        }
        // write 8 pixels (vertical) to SH1106 controller
        Wire1.write(pixels);  // segment address auto increments
      }
      Wire1.endTransmission();
    }
  }
}


/*----------------------------------------------------------------------------------
  |  Name         :  SH1106_Test_Pattern()
  |
  |  Function     :  Low-level test of SH1106 graphics write sequence.
  |                  The MCU RAM buffer is bypassed, i.e. not used.
  |                  The screen should show a pattern of diagonal lines,
  |                  slope -45 degrees, thickness 1 pixel, spaced 8 pixels apart,
  |                  within an area 128 x 64 pixels.
  |  Input        :  --
  |  Note         :  May be called without first calling SH1106_ClearGDRAM(),
  |                  but then random pixels may appear in segments 130, 131.
  +------------------------------------------------------------------------------------*/
void  SH1106_Test_Pattern()
{
  int    page, column, line;  // a "column" is 8 pixels wide in this context
  uint8_t  segAddr;
  uint8_t  pixels;

  for (page = 0;  page < 8;  page++)
  {
    // Set GDRAM start of page address -- there are 8 pages
    SH1106_WriteCommand(SH1106_PAGEADDR + page);

    for (column = 0;  column < 16;  column++)   // 16 "columns" of 8 pix
    {
      // Set segment address for this column
      segAddr = column * 8 + 2;
      SH1106_WriteCommand(SH1106_SETCOLUMNADDRLOW + (segAddr & 0xF));
      SH1106_WriteCommand(SH1106_SETCOLUMNADDRHIGH + (segAddr >> 4));

      // write 8 segments in auto-increment mode
      Wire1.beginTransmission(SH1106_I2C_ADDRESS);
      Wire1.write(SH1106_MESSAGETYPE_DATA);
      pixels = 0x01;  // top pixel

      for (line = 0;  line < 8;  line++)  // 8 lines x 8 pix
      {
        Wire1.write(pixels);
        pixels = pixels << 1;   // move 1 pixel down
      }
      Wire1.endTransmission();
    }
  }
}

// END-OF-FILE
