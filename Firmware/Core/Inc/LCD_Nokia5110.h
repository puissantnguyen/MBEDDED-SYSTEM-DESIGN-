/*
 * LCD_Nokia5110.h
 *
 */

#ifndef LCD_NOKIA5110_H_
#define LCD_NOKIA5110_H_

#include <stdint.h>

#define LCD_SPI hspi1
#define SPI_TIMEOUT 50

// Function prototypes
void LCD_init(void);
void LCD_reset(void);
void LCD_clear(void);
void LCD_command(uint8_t cmd);
void LCD_data(uint8_t data);
void LCD_gotoXY(uint8_t x, uint8_t y);
void LCD_write_char(char ch);
void LCD_write_str(char *str);
void LCD_invert(void);

#endif /* LCD_NOKIA5110_H_ */
