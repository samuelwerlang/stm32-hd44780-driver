#include <lcd_hd44780.h>
#include "stm32f4xx_hal.h"

void SystemClock_Config(void);
void RCC_SET(GPIO_TypeDef *port);

int main(void)
{
  HAL_Init();
  //Setup RCC AHB (Port A, B and C)
  RCC_SET(GPIOB);
  RCC_SET(GPIOC);
  RCC_SET(GPIOA);

  lcd_set_ports();
  HAL_Delay(20);
  lcd_init();
  lcd_off();
  lcd_clear();
  // Entry Mode Set:
  // increments address, without shift
  lcd_send_byte(0b0110, RS_INSTRUCTION_MODE);

  // Display ON
  // display on, cursor and blink on
  lcd_send_byte(0b00001111, RS_INSTRUCTION_MODE);
  //Set DDRAM address (line 2)
  lcd_send_byte(0xC0, RS_INSTRUCTION_MODE);



  lcd_write_str("Samuel");
  lcd_write_str(" Werlang");
}






