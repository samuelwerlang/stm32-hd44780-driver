#ifndef INC_LCDPINS_H_
#define INC_LCDPINS_H_

#define LCDD0Pin 3
#define LCDD0Port GPIOC
#define LCDD1Pin 2
#define LCDD1Port GPIOC
#define LCDD2Pin 10
#define LCDD2Port GPIOC
#define LCDD3Pin 12
#define LCDD3Port GPIOC

#define LCDD4Pin 13
#define LCDD4Port GPIOB
#define LCDD5Pin 14
#define LCDD5Port GPIOB
#define LCDD6Pin 15
#define LCDD6Port GPIOB
#define LCDD7Pin 1
#define LCDD7Port GPIOB

/* RS, RW, E Pins */
#define RW_READ_MODE 1
#define RW_WRITE_MODE 0
#define RS_CHAR_MODE 1
#define RS_INSTRUCTION_MODE 0

#define LCDRSPin 12
#define LCDRSPort GPIOB
#define LCDRWPin 11
#define LCDRWPort GPIOA
#define LCDEPin 12
#define LCDEPort GPIOA

#define DELAY_BE 400U /* delay before Enable */
#define DELAY_BD 800U/* delay before disabling the enable pin */
#endif /* INC_LCDPINS_H_ */
