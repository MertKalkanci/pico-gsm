#include "gsm.h"
#include "pico/stdlib.h"
#include "hardware/uart.h"
#include "hardware/gpio.h"
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

    int status;
    uart_read_ok(&status);

    if (status)
    {
        printf("STATUS OK");
    }
    else
    {
        printf("STATUS NOT OK");
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

void get_request(char ip[], char* result[])
{
//TCP CONNECTION
    char *base = 'AT+CIPSTART="TCP","",80', *tcpCommand;
    int location = 19; // starts from 1 not 0
    
    insert_string(&tcpCommand, location, &base);

    uart_puts(uartInterface > 0 ? uart1 : uart0, tcpCommand);

    int status;
    uart_read_ok(&status);

    if (status)
    {
        printf("CTP CONNECTION SUCCESFUL");
    }
    else
    {
        printf("ERROR CANT CONNECT TCP");
    }

//endregion
}

void insert_string(char* destination, int pos, char* insert)
{
    char *strC;

    strC = (char*)malloc(strlen(destination) + strlen(insert) + 1);
    strncpy(strC, destination, pos);
    strC[pos] = '\0';
    strcat(strC, insert);
    strcat(strC, destination + pos);
    strcpy(destination, strC);
    free(strC);
}


void uart_read_ok(int* isOk)
{
    char* readed = malloc(sizeof(char)*2);
    int index = 0;
    while (index < 2)
    {
        if (uart_is_readable(uartInterface > 0 ? uart1 : uart0))
        {
            readed[index] = uart_getc(uartInterface > 0 ? uart1 : uart0);
            index++;
        }
    } 

    if (strcmp(readed, "OK") == 0)
    {
        *isOk = 1;
    }
    else
    {
        *isOk = 0;
    }

    free(readed);
}