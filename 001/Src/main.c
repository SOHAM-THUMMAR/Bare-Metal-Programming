// where LED is connected?
// PD12
#include <stdint.h>
#include <stdio.h>



#define  PERIPH_BASE           (0x40000000ul)
#define  AHB1PERIPH_OFFSET     (0x00020000ul)
#define  AHB1PERIPH_BASE       (PERIPH_BASE + AHB1PERIPH_OFFSET) // 0x40020000
#define RCC_OFFEST             (0x3800ul)

#define RCC_BASE               (AHB1PERIPH_BASE + RCC_OFFEST) // 0x40023800

#define  GPIO_D_OFFSET         (0X00000C00ul)
#define  GPIO_D_BASE           (AHB1PERIPH_BASE + GPIO_D_OFFSET) // 0x40020C00

#define RCC_AHB1ENR_OFFSET     (0x30ul)
#define RCC_AHB1EN_R           (*(volatile uint32_t *)(RCC_BASE + RCC_AHB1ENR_OFFSET)) // 0x40023830

#define MODE_REG_OFFSET        (0x00ul)
#define GPIO_D_MODE_R          (*(volatile uint32_t *)(GPIO_D_BASE + MODE_REG_OFFSET))  // 0x40020C00

#define OD_REG_OFFSET         (0x14ul)
#define GPIO_D_OD_R           (*(volatile uint32_t *)(GPIO_D_BASE + OD_REG_OFFSET))   // 0x40020C14

#define GPIODEN                (1 << 3)

#define PIN12                  (1 << 12)



int main(void){

    RCC_AHB1EN_R |= GPIODEN; // enable clock for GPIOD

    GPIO_D_MODE_R |= (1 << 24); // set pin 12 as output
    GPIO_D_MODE_R &= ~(1 << 25); // setting 25th bit as 0 for output mode

    while(1){

        GPIO_D_OD_R |= PIN12; // set pin 12 high
        for(int i = 0; i < 1000000; i++); // delay
        GPIO_D_OD_R &= ~PIN12; // set pin 12 low
        for(int i = 0; i < 1000000; i++); // delay
    }



    return 0;
}
































