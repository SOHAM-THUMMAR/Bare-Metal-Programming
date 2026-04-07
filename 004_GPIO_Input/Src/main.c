#include <stdint.h>
#include "stm32f407xx.h"

#define GPIOAEN     (1U << 0)
#define GPIODEN     (1U << 3)

#define PIN0        (1U << 0)
#define PIN12       (1U << 12)

int main(void)
{
    // Enable clocks
    RCC->AHB1ENR |= GPIOAEN;
    RCC->AHB1ENR |= GPIODEN;

    // PA0 as input
    GPIOA->MODER &= ~(3U << (0 * 2));

    // Enable pull-down (IMPORTANT for stable input)
    GPIOA->PUPDR &= ~(3U << (0 * 2));
    GPIOA->PUPDR |=  (2U << (0 * 2));

    // PD12 as output
    GPIOD->MODER &= ~(3U << (12 * 2));  // clear
    GPIOD->MODER |=  (1U << (12 * 2));  // set output mode

    while (1)
    {
        if (GPIOA->IDR & PIN0)
        {
            GPIOD->BSRR = PIN12;          // ON
        }
        else
        {
            GPIOD->BSRR = (PIN12 << 16);  // OFF
        }
    }
}