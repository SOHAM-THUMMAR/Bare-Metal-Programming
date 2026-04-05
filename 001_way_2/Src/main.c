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

#define GPIO_D_EN                (1 << 3)

#define PIN14                  (1 << 14)


typedef struct{
    volatile uint32_t DUMMY [12]; // offset 0x00 to 0x2C
    volatile uint32_t AHB1ENR; // offset 0x30
} RCC_TypeDef;

typedef struct{
    volatile uint32_t MODER; // offset 0x00
    volatile uint32_t DUMMY [4]; // offset 0x04 to 0x10
    volatile uint32_t ODR; // offset 0x14 
} GPIO_TypeDef;

#define RCC         ((RCC_TypeDef *) RCC_BASE)
#define GPIO_D       ((GPIO_TypeDef *) GPIO_D_BASE)


int main(void){

    RCC->AHB1ENR |= GPIO_D_EN; // enable clock for GPIO_D
    GPIO_D->MODER |= (1 << 28); // set pin 12 to output
    GPIO_D->MODER &= ~(1 << 29); // setting 25th bit as 0 for output mode

    while(1){
        GPIO_D->ODR ^= PIN14; // toggle pin 14
        for(int i = 0; i < 1000000; i++); // delay
    }

    return 0;
}
































