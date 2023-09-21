#include "gsm.h"
#include "hardware/uart.h"
#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include "hardware/uart.h"
#include <stdio.h>
#include <string.h>

static int txPin, rxPin, dtrPin, uartInterface;

void setup_gsm(int uart,int baudrate, int tx, int rx, int dtr)
{
    uart_init(uart > 0 ? uart1 : uart0, baudrate);

    gpio_set_function(rx, GPIO_FUNC_UART);
    gpio_set_function(tx, GPIO_FUNC_UART);


    uart_set_baudrate(uart > 0 ? uart1 : uart0, baudrate);

    if (dtrPin >= 0)
    {
        gpio_init(dtrPin);
        gpio_set_dir(dtrPin, GPIO_OUT);
        gpio_put(dtrPin, false);
    }

    sleep_ms(2000);

    uart_puts(uart > 0 ? uart1 : uart0,"AT");

    char status[2];

    for (int i = 0; i < 2; i++)
    {
        if (uart_is_readable(uart > 0 ? uart1 : uart0))
        {
            status[i] = uart_getc(uart > 0 ? uart1 : uart0);
        }
    }

    if(strcmp(status,"OK"))
    { 
        printf("Status: OK");
    }
    else
    {
        printf("Status: SIM WORKS BUT NOT OK CANT COMMUNICATE");
    }


    txPin = tx;
    rxPin = rx;
    dtrPin = dtr;
    uartInterface = uart;
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

