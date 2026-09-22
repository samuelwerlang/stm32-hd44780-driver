/*This is a trivial code sample describing how to utilize the lcd_hd44780 driver functions */
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
  lcd_entry_increment();
  lcd_on();


  lcd_set_cursor(2, 1);
  lcd_write_str("Hello World");
}




