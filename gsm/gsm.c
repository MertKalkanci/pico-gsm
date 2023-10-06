#include "gsm.h"
#include "pico/stdlib.h"
#include "hardware/uart.h"
#include "hardware/gpio.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

static int firstPin, secondPin, dtrPin, uartInterface;

void setup_gsm(int uart,int baudrate, int uartPinFirst, int uartPinSecond, int dtr)
{
    uart_init(uart > 0 ? uart1 : uart0, baudrate);

    gpio_set_function(uartPinFirst, GPIO_FUNC_UART);
    gpio_set_function(uartPinSecond, GPIO_FUNC_UART);


    uart_set_baudrate(uart > 0 ? uart1 : uart0, baudrate);

    if (dtrPin >= 0)
    {
        gpio_init(dtrPin);
        gpio_set_dir(dtrPin, GPIO_OUT);
        gpio_put(dtrPin, false);
    }

    sleep_ms(2000);

    uart_puts(uart > 0 ? uart1 : uart0,"AT");

    char* status;
    read_uart_gsm_message(status);

    if (status == "OK\r\n")
    {
        printf("STATUS OK");
    }
    else
    {
        printf("STATUS NOT OK");
    }

    firstPin = uartPinFirst;
    secondPin = uartPinSecond;
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

void request(char address[],char request[], char* result[]) // make request with ip
{
//TCP CONNECTION
    char* tcpCommand = 'AT+CIPSTART="TCP","",80';

    int locationTcpCommandInsert = 19; // starts from 1 not 0
    
    insert_string(tcpCommand, locationTcpCommandInsert, address);

    uart_puts(uartInterface > 0 ? uart1 : uart0, tcpCommand);

    char* status;
    read_uart_gsm_message(status);

    if (status == "OK\r\n")
    {
        printf("TCP CONNECTION SUCCESFUL");
    }
    else
    {
        printf("ERROR CANT CONNECT TCP");

        return;
    }
    //SENDING REQUEST

    int lengthOfRequest = strlen(request);
    int lengthToAddToTheRequestCommand = (int)((ceil(log10(lengthOfRequest)) + 1) * sizeof(char));

    char* requestCommand = 'AT+CIPSEND=';

    requestCommand = realloc(requestCommand, strlen(requestCommand) * sizeof(char) + sizeof(char) * lengthToAddToTheRequestCommand);

    char* requestLengthString;
    sprintf(requestLengthString, "%d", 42);

    strcat(requestCommand, requestLengthString);

    uart_puts(uartInterface > 0 ? uart1 : uart0, requestCommand);
    uart_puts(uartInterface > 0 ? uart1 : uart0, request);
    read_uart_gsm_message(&result);
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

int gsm_uart_end_check(char message[])
{
    int endLength = 2;
    int lengthOfMessage = sizeof(message) / sizeof(char);
    if (lengthOfMessage >= 2)
    {
        char* end[2] = "00";

        for (int i = 0; i < endLength; i++)
        {
            end[i] = message[lengthOfMessage - endLength + i];
        }
        
        return strcmp(end, "\r\n");
    }
    else
    {
        return 1;
    }
}

void read_uart_gsm_message(char* message[])
{
    char* internalMessage = (char*)malloc(sizeof(char));
    int status = 1;

    while (status != 0)
    {
        if (uart_is_readable(uartInterface > 0 ? uart1 : uart0))
        {
            char readedChar;
            readedChar = uart_getc(uartInterface > 0 ? uart1 : uart0);

            internalMessage = realloc(internalMessage,strlen(internalMessage) * sizeof(char) + sizeof(char));

            strcat(internalMessage, readedChar);
        }
        status = gsm_uart_end_check(internalMessage);
    }
    strcpy(message, internalMessage);
    free(internalMessage);
}

int check_empty_string(char* result)
{
    return (sizeof(result) == sizeof(NULL) && sizeof(result) == sizeof(char)) ? 1 : 0;
}