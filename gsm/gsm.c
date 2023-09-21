#include "gsm.h"
#include "hardware/uart.h"
#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include "hardware/uart.h"
#include <stdio.h>

#define UART_0 uart0
#define UART_1 uart1

static int txPin, rxPin, dtrPin;

void setup_gsm(int uart,int baudrate, int tx, int rx, int dtr)
{
    if (uart > 0)
    {
        uart_init(uart1, baudrate);
    }
    else
    {
        uart_init(uart0, baudrate);
    }

    gpio_set_function(rx, GPIO_FUNC_UART);
    gpio_set_function(tx, GPIO_FUNC_UART);

    txPin = tx;
    rxPin = rx;
    dtrPin = dtr;

    if (dtrPin >= 0)
    {
        gpio_init(dtrPin);
        gpio_set_dir(dtrPin, GPIO_OUT);
        gpio_put(dtrPin, false);
    }

    sleep_ms(2000);
}

void disable_sleep()
{
    if (dtrPin >= 0)
    {
        gpio_put(dtrPin, false);
    }
}
void enable_sleep()
{

    if (dtrPin >= 0)
    {
        gpio_put(dtrPin, true);
    }
}

