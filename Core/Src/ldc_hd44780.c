#include  <inttypes.h>
#include <lcd_hd44780.h>

static void time_delay(int delay) {
	volatile int i;
	for (i = 0; i < delay; i++)	;
}

void lcd_setup(GPIO_TypeDef *port, uint8_t pnum) {
	port->MODER &= ~(1U << (pnum*2 + 1));
	port->MODER |= (1U << (pnum*2));
	port->OTYPER &= ~(1U << pnum);
	port->OSPEEDR |=(1U << (pnum*2 + 1)) | (1U << (pnum*2));
	port->PUPDR &= ~(1U << pnum);
}

void lcd_set_ports(void) {
	lcd_setup(LCDD0Port, LCDD0Pin);
	lcd_setup(LCDD1Port, LCDD1Pin);
	lcd_setup(LCDD2Port, LCDD2Pin);
	lcd_setup(LCDD3Port, LCDD3Pin);
	lcd_setup(LCDD4Port, LCDD4Pin);
	lcd_setup(LCDD5Port, LCDD5Pin);
	lcd_setup(LCDD6Port, LCDD6Pin);
	lcd_setup(LCDD7Port, LCDD7Pin);
	lcd_setup(LCDRSPort, LCDRSPin);
	lcd_setup(LCDRWPort, LCDRWPin);
	lcd_setup(LCDEPort, LCDEPin);
}

void RCC_SET(GPIO_TypeDef *port) {
		if (port == GPIOA)
			RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
		if (port == GPIOB)
			RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
		if (port == GPIOC)
			RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
		if (port == GPIOD)
			RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
		if (port == GPIOE)
			RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN;
		if (port == GPIOH)
			RCC->AHB1ENR |= RCC_AHB1ENR_GPIOHEN;
}

static void lcd_enable(int delay) {
	time_delay(delay);
	lcd_send_bit(LCDEPort, LCDEPin, 1);
}

static void lcd_disable(int delay) {
	time_delay(delay);
	lcd_send_bit(LCDEPort, LCDEPin, 0);
}

static void set_RW (uint8_t rw_mode) {
	lcd_send_bit(LCDRWPort, LCDRWPin, rw_mode);
}

static void set_RS (uint8_t rs_mode) {
	lcd_send_bit(LCDRSPort, LCDRSPin, rs_mode);
}

void lcd_send_bit(GPIO_TypeDef *port, uint8_t pnum, uint8_t bit_state) {

	if (bit_state) {
				  port->BSRR = (1U << pnum);
			  } else {
				  port->BSRR = (1U << (pnum + 16));
				}
}

void lcd_send_byte(uint8_t c, uint8_t rs_mode) {
    const uint8_t mask = 0b00000001;

    set_RW(RW_WRITE_MODE);

    if (rs_mode == RS_CHAR_MODE)
        set_RS(RS_CHAR_MODE);
    else
        set_RS(RS_INSTRUCTION_MODE);

    lcd_send_bit(LCDD0Port, LCDD0Pin, (c & (mask << 0)));
    lcd_send_bit(LCDD1Port, LCDD1Pin, (c & (mask << 1)));
    lcd_send_bit(LCDD2Port, LCDD2Pin, (c & (mask << 2)));
    lcd_send_bit(LCDD3Port, LCDD3Pin, (c & (mask << 3)));
    lcd_send_bit(LCDD4Port, LCDD4Pin, (c & (mask << 4)));
    lcd_send_bit(LCDD5Port, LCDD5Pin, (c & (mask << 5)));
    lcd_send_bit(LCDD6Port, LCDD6Pin, (c & (mask << 6)));
    lcd_send_bit(LCDD7Port, LCDD7Pin, (c & (mask << 7)));

    lcd_enable(DELAY_BE);
    lcd_disable(DELAY_BD);
}

void lcd_init() {
	  lcd_send_byte(0x30, RS_INSTRUCTION_MODE);
	  HAL_Delay(5);
	  lcd_send_byte(0x30, RS_INSTRUCTION_MODE);
	  HAL_Delay(1);
	  lcd_send_byte(0x30, RS_INSTRUCTION_MODE);
	  lcd_send_byte(0x38, RS_INSTRUCTION_MODE); /* 8 bits, 2 lines, 5x8 font */
}

void lcd_on() {
	lcd_send_byte(0xC, RS_INSTRUCTION_MODE);
}

void lcd_off() {
	lcd_send_byte(0x08, RS_INSTRUCTION_MODE);
}

void lcd_clear() {
	lcd_send_byte(0x01, RS_INSTRUCTION_MODE);
}

void lcd_write_char(char c) {
	lcd_send_byte(c, RS_CHAR_MODE);
}

void lcd_write_str(const char *str) {

	while (*str) {
		lcd_send_byte(*str, RS_CHAR_MODE);
		str++;
	}
}
