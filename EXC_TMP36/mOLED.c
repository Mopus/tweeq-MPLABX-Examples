#include <stdio.h>
#include <stdlib.h>
#include <p32xxxx.h>                // Processor defs
#define _SUPPRESS_PLIB_WARNING 1
#include <plib.h>

#include "HMain.h"

#define BLACK 0
#define WHITE 1

//#define SSD1306_128_64
#define SSD1306_128_32

#if defined SSD1306_128_64
  #define SSD1306_LCDWIDTH                  128
  #define SSD1306_LCDHEIGHT                 64
#endif
#if defined SSD1306_128_32
  #define SSD1306_LCDWIDTH                  128
  #define SSD1306_LCDHEIGHT                 32
#endif

#define SSD1306_SETCONTRAST 0x81
#define SSD1306_DISPLAYALLON_RESUME 0xA4
#define SSD1306_DISPLAYALLON 0xA5
#define SSD1306_NORMALDISPLAY 0xA6
#define SSD1306_INVERTDISPLAY 0xA7
#define SSD1306_DISPLAYOFF 0xAE
#define SSD1306_DISPLAYON 0xAF

#define SSD1306_SETDISPLAYOFFSET 0xD3
#define SSD1306_SETCOMPINS 0xDA

#define SSD1306_SETVCOMDETECT 0xDB

#define SSD1306_SETDISPLAYCLOCKDIV 0xD5
#define SSD1306_SETPRECHARGE 0xD9

#define SSD1306_SETMULTIPLEX 0xA8

#define SSD1306_SETLOWCOLUMN 0x00
#define SSD1306_SETHIGHCOLUMN 0x10

#define SSD1306_SETSTARTLINE 0x40

#define SSD1306_MEMORYMODE 0x20
#define SSD1306_COLUMNADDR 0x21
#define SSD1306_PAGEADDR   0x22

#define SSD1306_COMSCANINC 0xC0
#define SSD1306_COMSCANDEC 0xC8

#define SSD1306_SEGREMAP 0xA0

#define SSD1306_CHARGEPUMP 0x8D

#define SSD1306_EXTERNALVCC 0x1
#define SSD1306_SWITCHCAPVCC 0x2

// Scrolling #defines
#define SSD1306_ACTIVATE_SCROLL 0x2F
#define SSD1306_DEACTIVATE_SCROLL 0x2E
#define SSD1306_SET_VERTICAL_SCROLL_AREA 0xA3
#define SSD1306_RIGHT_HORIZONTAL_SCROLL 0x26
#define SSD1306_LEFT_HORIZONTAL_SCROLL 0x27
#define SSD1306_VERTICAL_AND_RIGHT_HORIZONTAL_SCROLL 0x29
#define SSD1306_VERTICAL_AND_LEFT_HORIZONTAL_SCROLL 0x2A

#define cs_high     _RB4 = 1;
#define cs_low      _RB4 = 0;

#define dc_high     _RA4 = 1;
#define dc_low      _RA4 = 0;

#define rst_high    _RA0 = 1;
#define rst_low     _RA0 = 0;

extern const unsigned char mOLED_Font[];

unsigned char mOLED_Screen_Mem[512];
unsigned char mOLED_Pen_Colour;

//#=================================================================================================
//#
//#-------------------------------------------------------------------------------------------------
void mOLED_SSD1306_cmd(unsigned short c) {
    cs_high;
    dc_low;
    nop;
    cs_low;

    SPI1_Write_8(c);
    nop;
    cs_high;
}

//#=================================================================================================
//#
//#-------------------------------------------------------------------------------------------------
void mOLED_Init( void )
{
    _TRISA4 = 0;
    _TRISA0 = 0;
    _TRISB4 = 0;
    _TRISB1 = 0;
    SPI1_Init();

    rst_high;
    // VDD (3.3V) goes high at start, lets just chill for a ms
    Delayms(10);
    rst_low;
    // wait 10ms
    Delayms(20);
    rst_high;

    // Init sequence for 128x32 OLED module
    mOLED_SSD1306_cmd(SSD1306_DISPLAYOFF);                    // 0xAE
    mOLED_SSD1306_cmd(SSD1306_SETDISPLAYCLOCKDIV);            // 0xD5
    mOLED_SSD1306_cmd(0x80);                                  // the suggested ratio 0x80
    mOLED_SSD1306_cmd(SSD1306_SETMULTIPLEX);                  // 0xA8
    mOLED_SSD1306_cmd(0x1F);
    mOLED_SSD1306_cmd(SSD1306_SETDISPLAYOFFSET);              // 0xD3
    mOLED_SSD1306_cmd(0x0);                                   // no offset
    mOLED_SSD1306_cmd(SSD1306_SETSTARTLINE | 0x0);            // line #0
    mOLED_SSD1306_cmd(SSD1306_CHARGEPUMP);                    // 0x8D

    //mOLED_SSD1306_cmd(0x10);    //SSD1306_EXTERNALVCC 0x1
    mOLED_SSD1306_cmd(0x14);    //SSD1306_SWITCHCAPVCC 0x2

    mOLED_SSD1306_cmd(SSD1306_MEMORYMODE);                    // 0x20
    mOLED_SSD1306_cmd(0x00);                                  // 0x0 act like ks0108
    mOLED_SSD1306_cmd(SSD1306_SEGREMAP | 0x1);
    mOLED_SSD1306_cmd(SSD1306_COMSCANDEC);
    mOLED_SSD1306_cmd(SSD1306_SETCOMPINS);                    // 0xDA
    mOLED_SSD1306_cmd(0x02);
    mOLED_SSD1306_cmd(SSD1306_SETCONTRAST);                   // 0x81
    mOLED_SSD1306_cmd(0x8F);
    mOLED_SSD1306_cmd(SSD1306_SETPRECHARGE);                  // 0xd9

    //mOLED_SSD1306_cmd(0x22);    //SSD1306_EXTERNALVCC 0x1
    mOLED_SSD1306_cmd(0xF1);    //SSD1306_SWITCHCAPVCC 0x2


    mOLED_SSD1306_cmd(SSD1306_SETVCOMDETECT);                 // 0xDB
    mOLED_SSD1306_cmd(0x40);
    mOLED_SSD1306_cmd(SSD1306_DISPLAYALLON_RESUME);           // 0xA4
    mOLED_SSD1306_cmd(SSD1306_NORMALDISPLAY);                 // 0xA6

    mOLED_SSD1306_cmd(SSD1306_DISPLAYON);//--turn on oled panel

    mOLED_Pen_Colour = 1;
}

//#=================================================================================================
//#
//#-------------------------------------------------------------------------------------------------
void mOLED_Clear(void)
{
unsigned short i;

    mOLED_SSD1306_cmd(SSD1306_COLUMNADDR);
    mOLED_SSD1306_cmd(0);   // Column start address (0 = reset)
    mOLED_SSD1306_cmd(127); // Column end address (127 = reset)

    mOLED_SSD1306_cmd(SSD1306_PAGEADDR);
    mOLED_SSD1306_cmd(0); // Page start address (0 = reset)
    mOLED_SSD1306_cmd(3); // Page end addres
   
    for (i=0; i<(SSD1306_LCDWIDTH*SSD1306_LCDHEIGHT/8); i++)
    {
        cs_high;
        dc_high;
        nop; nop;
        cs_low;
        SPI1_Write_8(0x00);
        mOLED_Screen_Mem[i] = 0;
        cs_high;
    }
}
//#=================================================================================================
//#
//#-------------------------------------------------------------------------------------------------
void mOLED_Clear_Array(void)
{
unsigned short i;
    for (i=0; i<(SSD1306_LCDWIDTH*SSD1306_LCDHEIGHT/8); i++)
    {
        mOLED_Screen_Mem[i] = 0;
    }
}


//#=================================================================================================
//#
//#-------------------------------------------------------------------------------------------------
void mOLED_Set_Pixel(int x, int y)
{
    mOLED_SSD1306_cmd(SSD1306_COLUMNADDR);
    mOLED_SSD1306_cmd(x);   // Column start address (0 = reset)
    mOLED_SSD1306_cmd(x+1); // Column end address (127 = reset)

    mOLED_SSD1306_cmd(SSD1306_PAGEADDR);
    mOLED_SSD1306_cmd(y); // Page start address (0 = reset)
    mOLED_SSD1306_cmd(y+1); // Page end addres

    cs_high;
    //nop;
    dc_high;
    nop;
    cs_low;
    SPI1_Write_8(1);
    nop;
    cs_high;
}
//#=================================================================================================
//#
//#-------------------------------------------------------------------------------------------------
void mOLED_UnSet_Pixel(int x, int y)
{
    mOLED_SSD1306_cmd(SSD1306_COLUMNADDR);
    mOLED_SSD1306_cmd(x);   // Column start address (0 = reset)
    mOLED_SSD1306_cmd(x+1); // Column end address (127 = reset)

    mOLED_SSD1306_cmd(SSD1306_PAGEADDR);
    mOLED_SSD1306_cmd(y); // Page start address (0 = reset)
    mOLED_SSD1306_cmd(y+1); // Page end addres

    cs_high;
    //nop;
    dc_high;
    nop;
    cs_low;
    SPI1_Write_8(0);
    nop;
    cs_high;
}

//#=================================================================================================
//#
//#-------------------------------------------------------------------------------------------------
void mOLED_Refresh( void )
{
unsigned int i;

    mOLED_SSD1306_cmd(SSD1306_COLUMNADDR);
    mOLED_SSD1306_cmd(0);   // Column start address (0 = reset)
    mOLED_SSD1306_cmd(127); // Column end address (127 = reset)

    mOLED_SSD1306_cmd(SSD1306_PAGEADDR);
    mOLED_SSD1306_cmd(0); // Page start address (0 = reset)
    mOLED_SSD1306_cmd(3); // Page end addres

    for (i=0; i<512; i++)
    {
        cs_high;
        dc_high;
        nop;
        cs_low;
        SPI1_Write_8(mOLED_Screen_Mem[i]);
        nop;
        cs_high;
    }
}

//#=================================================================================================
//#
//#-------------------------------------------------------------------------------------------------
void mOLED_Draw_Font(int x, int y, unsigned char c)
{
unsigned int i, tt, ff;
    tt = x + y*128;
    ff = (c - 0x20) * 8;

    for (i=0; i<8; i++)
    {
        mOLED_Screen_Mem[tt + i] = mOLED_Font[ff + i]; // | mOLED_Screen_Mem[tt + i];
    }
}
//#=================================================================================================
//#
//#-------------------------------------------------------------------------------------------------
void mOLED_Draw_Font_OR(int x, int y, unsigned char c)
{
unsigned int i, tt, ff;
    tt = x + y*128;
    ff = (c - 0x20) * 8;

    for (i=0; i<8; i++)
    {
        mOLED_Screen_Mem[tt + i] = mOLED_Font[ff + i] | mOLED_Screen_Mem[tt + i];
    }
}
//#=================================================================================================
//#
//#-------------------------------------------------------------------------------------------------
void mOLED_Print_Str(int x, int y, char * sz)
{
    while (*sz != '\0') {
        mOLED_Draw_Font_OR(x, y, *sz);
        //OledAdvanceCursor();
        x = x + 8;
        sz += 1;
    }
}

//#=================================================================================================
//#
//#-------------------------------------------------------------------------------------------------
void mOLED_Print_DEC(int x, int y, int val)
{
char TStr[16];
    itoa(TStr, val, 10);
    mOLED_Print_Str(x, y, TStr);
}
//#=================================================================================================
//#
//#-------------------------------------------------------------------------------------------------
void mOLED_Print_Val(int x, int y, int val, int base)
{
char TStr[16];
    itoa(TStr, val, base);
    mOLED_Print_Str(x, y, TStr);
}

//#=================================================================================================
//#
//#-------------------------------------------------------------------------------------------------
void mOLED_Draw_Point(int x, int y)
{
int tt;
    tt = x + (y/8)*128;
    if (mOLED_Pen_Colour == 0)
    {
        mOLED_Screen_Mem[tt] = mOLED_Screen_Mem[tt] & ~(1 << (y % 8));
    }else
    {
        mOLED_Screen_Mem[tt] = mOLED_Screen_Mem[tt] | (1 << (y % 8));
    }
}
//#=================================================================================================
//#
//#-------------------------------------------------------------------------------------------------
void mOLED_UnDraw_Point(int x, int y)
{
int tt;
    tt = x + (y/8)*128;
    mOLED_Screen_Mem[tt] = mOLED_Screen_Mem[tt] & ~(1 << (y % 8));
}


//#=================================================================================================
//#
//#-------------------------------------------------------------------------------------------------
void mOLED_startscrollright(int start, int stop){
	mOLED_SSD1306_cmd(SSD1306_RIGHT_HORIZONTAL_SCROLL);
	mOLED_SSD1306_cmd(0X00);
	mOLED_SSD1306_cmd(start);
	mOLED_SSD1306_cmd(0X00);
	mOLED_SSD1306_cmd(stop);
	mOLED_SSD1306_cmd(0X01);
	mOLED_SSD1306_cmd(0XFF);
	mOLED_SSD1306_cmd(SSD1306_ACTIVATE_SCROLL);
}
//#=================================================================================================
//#
//#-------------------------------------------------------------------------------------------------
void mOLED_scrolldiagLeft(int start, int stop){
	mOLED_SSD1306_cmd(SSD1306_SET_VERTICAL_SCROLL_AREA);
	mOLED_SSD1306_cmd(0X00);
	mOLED_SSD1306_cmd(SSD1306_LCDHEIGHT);
	mOLED_SSD1306_cmd(SSD1306_VERTICAL_AND_LEFT_HORIZONTAL_SCROLL);
	mOLED_SSD1306_cmd(0X00);
	mOLED_SSD1306_cmd(start);
	mOLED_SSD1306_cmd(0X00);
	mOLED_SSD1306_cmd(stop);
	mOLED_SSD1306_cmd(0X01);
	mOLED_SSD1306_cmd(SSD1306_ACTIVATE_SCROLL);
}
//#=================================================================================================
//#
//#-------------------------------------------------------------------------------------------------
void mOLED_scrolldiagRight(int start, int stop){
	mOLED_SSD1306_cmd(SSD1306_SET_VERTICAL_SCROLL_AREA);
	mOLED_SSD1306_cmd(0X00);
	mOLED_SSD1306_cmd(SSD1306_LCDHEIGHT);
	mOLED_SSD1306_cmd(SSD1306_VERTICAL_AND_LEFT_HORIZONTAL_SCROLL);
	mOLED_SSD1306_cmd(0X00);
	mOLED_SSD1306_cmd(start);
	mOLED_SSD1306_cmd(0X00);
	mOLED_SSD1306_cmd(stop);
	mOLED_SSD1306_cmd(0X01);
	mOLED_SSD1306_cmd(SSD1306_ACTIVATE_SCROLL);
}

//#=================================================================================================
//#
//#-------------------------------------------------------------------------------------------------
#define swap(a, b) { int t = a; a = b; b = t; }
void mOLED_Draw_Line(int x0, int y0, int x1, int y1, int c)
{
// Bresenham's algorithm - thx wikpedia
  int steep = abs(y1 - y0) > abs(x1 - x0);
  if (steep) {
    swap(x0, y0);
    swap(x1, y1);
  }
  if (x0 > x1) {
    swap(x0, x1);
    swap(y0, y1);
  }

  int dx, dy;
  dx = x1 - x0;
  dy = abs(y1 - y0);

  int err = dx / 2;
  int ystep;

  if (y0 < y1) {
    ystep = 1;
  } else {
    ystep = -1;
  }

  for (; x0<=x1; x0++)
  {
    if (steep) {
      mOLED_Draw_Point(y0, x0);
    } else {
      mOLED_Draw_Point(x0, y0);
    }
    err -= dy;
    if (err < 0) {
      y0 += ystep;
      err += dx;
    }
  }
}
//#=================================================================================================
//#
//#-------------------------------------------------------------------------------------------------
void mOLED_Draw_Circle(int x0, int y0, int r)
{
  int f = 1 - r;
  int ddF_x = 1;
  int ddF_y = -2 * r;
  int x = 0;
  int y = r;

  mOLED_Draw_Point(x0  , y0+r);
  mOLED_Draw_Point(x0  , y0-r);
  mOLED_Draw_Point(x0+r, y0  );
  mOLED_Draw_Point(x0-r, y0  );

  while (x<y) {
    if (f >= 0) {
      y--;
      ddF_y += 2;
      f += ddF_y;
    }
    x++;
    ddF_x += 2;
    f += ddF_x;

    mOLED_Draw_Point(x0 + x, y0 + y);
    mOLED_Draw_Point(x0 - x, y0 + y);
    mOLED_Draw_Point(x0 + x, y0 - y);
    mOLED_Draw_Point(x0 - x, y0 - y);
    mOLED_Draw_Point(x0 + y, y0 + x);
    mOLED_Draw_Point(x0 - y, y0 + x);
    mOLED_Draw_Point(x0 + y, y0 - x);
    mOLED_Draw_Point(x0 - y, y0 - x);
  }
}


