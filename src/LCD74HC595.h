#ifndef LCD74HC595_h
#define LCD74HC595_h

#include <inttypes.h>
#include "Print.h"

/*
    LCD                   74hc595                         Arduino
                          STCP(12) ---------------------- LatchPin
                          SHCP(11) ---------------------- ClockPin
                          DS(14)   ---------------------- DataPin
     D4(14) ------------- Q(PIN_DATA)
     D5(15) --------------Q(PIN_DATA+1)
     D6(16) ------------- Q(PIN_DATA+2)
     D7(17) ------------- Q(PIN_DATA+3)
     RS(4)  ------------- Q(PIN_RS)
     EN(6)  ------------- Q(PIN_EN) 
     GND(1),RW(5),K(16)-- GND(8),!G(13) ----------------- GND
     VDD(2),A(15) ------- Vcc(16),!SCLR(10)-------------- 5v
     V0 ->resistor
*/

// pins
#define PIN_EN 2
#define PIN_RS 1
#define PIN_DATA 3

// commands
#define LCD_CLEARDISPLAY 0x01
#define LCD_RETURNHOME 0x02
#define LCD_ENTRYMODESET 0x04
#define LCD_DISPLAYCONTROL 0x08
#define LCD_CURSORSHIFT 0x10
#define LCD_FUNCTIONSET 0x20
#define LCD_SETCGRAMADDR 0x40
#define LCD_SETDDRAMADDR 0x80

// flags for display entry mode
#define LCD_ENTRYRIGHT 0x00
#define LCD_ENTRYLEFT 0x02
#define LCD_ENTRYSHIFTINCREMENT 0x01
#define LCD_ENTRYSHIFTDECREMENT 0x00

// flags for display on/off control
#define LCD_DISPLAYON 0x04
#define LCD_DISPLAYOFF 0x00
#define LCD_CURSORON 0x02
#define LCD_CURSOROFF 0x00
#define LCD_BLINKON 0x01
#define LCD_BLINKOFF 0x00

// flags for display/cursor shift
#define LCD_DISPLAYMOVE 0x08
#define LCD_CURSORMOVE 0x00
#define LCD_MOVERIGHT 0x04
#define LCD_MOVELEFT 0x00

// flags for function set
#define LCD_2LINE 0x08
#define LCD_1LINE 0x00
#define LCD_5x10DOTS 0x04
#define LCD_5x8DOTS 0x00

class LCD74HC595 : public Print {
public:

  LCD74HC595(uint8_t, uint8_t, uint8_t, uint8_t =PIN_RS, uint8_t =PIN_EN, uint8_t =PIN_DATA);
    
  void begin(uint8_t cols, uint8_t rows, uint8_t charsize = LCD_5x8DOTS);

  void clear();
  void home();

  void noDisplay();
  void display();
  void noBlink();
  void blink();
  void noCursor();
  void cursor();
  void scrollDisplayLeft();
  void scrollDisplayRight();
  void leftToRight();
  void rightToLeft();
  void autoscroll();
  void noAutoscroll();

  void setRowOffsets(int row1, int row2, int row3, int row4);
  void createChar(uint8_t, uint8_t[]);
  void setCursor(uint8_t, uint8_t); 
  virtual size_t write(uint8_t);
  void command(uint8_t);
  
  using Print::write;
private:
  void sendHalf(uint8_t, uint8_t);
  void send(uint8_t, uint8_t);
  void send74595(uint8_t, uint8_t, uint8_t);

  uint8_t _ds_pin;
  uint8_t _shcp_pin;
  uint8_t _stcp_pin;

  uint8_t _data_pin;
  uint8_t _rs_mask;
  uint8_t _en_mask;

  uint8_t _displayfunction;
  uint8_t _displaycontrol;
  uint8_t _displaymode;

  uint8_t _numlines;
  uint8_t _row_offsets[4];
};

#endif

