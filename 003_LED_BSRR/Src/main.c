#include <stdint.h>
// #include "stm32f4xx.h" // did not work, so I included the specific header for STM32F407xx series
#include "stm32f407xx.h" // Include the header file for STM32F407xx series

#define GPIODEN     (1U << 3)

#define PIN13       (1U << 13)



int main(void)
{

    RCC->AHB1ENR |= GPIODEN; // Enable clock for GPIOD 
    GPIOD->MODER |= (1U << 26); // Set pin 13 as output 
    GPIOD->MODER &= ~(1U << 27); // Set pin 13 as output 
    /* Loop forever */
	while (1)
    {
        GPIOD->BSRR = PIN13; // Set pin 13 (turn on LED)
        for (int i = 0; i < 1000000; i++); // Delay

        GPIOD->BSRR = (1<<29); // Reset pin 13 (turn off LED)
        for (int i = 0; i < 1000000; i++); // Delay

        
    }
    return 0;
}
