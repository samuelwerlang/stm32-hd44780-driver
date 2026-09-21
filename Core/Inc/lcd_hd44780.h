/*
 * lcdpins.h
 *
 *  Created on: 16 de set. de 2026
 *      Author: smwerlang
 */

#include <inttypes.h>
#include "stm32f4xx_hal.h"
#include "lcd_config.h"


void lcd_setup(GPIO_TypeDef *port, uint8_t pnum);
void lcd_set_ports(void);
void lcd_send_bit(GPIO_TypeDef *port, uint8_t pnum, uint8_t bit_state);
void lcd_send_byte(uint8_t c, uint8_t rs_mode);
void RCC_SET(GPIO_TypeDef *port);

//LCD main Functions
void lcd_init(void);
void lcd_entry_increment(void);
void lcd_on(void);
void lcd_off();
void lcd_clear(void);
void lcd_home(void);
int lcd_set_cursor(uint8_t x, uint8_t y);
void lcd_write_char(char c);
void lcd_write_str(const char *str);
