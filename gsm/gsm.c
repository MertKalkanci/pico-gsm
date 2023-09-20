#include "gsm.h"
#include "pico/uart.h"
#include "pico/stdlib.h"
#include <stdio.h>

#define UART_0 uart0
#define UART_1 uart1


void setup_gsm(int uart,int baudrate, int tx, int rx, int dtr)
{
    if (uart > 0)
    {
        uart_init(uart1, baudrate);
    }
    else
    {
        uart_init(uart_0, baudrate);
    }

    gpio_set_function(rx, GPIO_FUNC_UART);
    gpio_set_function(tx, GPIO_FUNC_UART);
}