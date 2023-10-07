#include "gsm/gsm.h"
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include <stdio.h>
#include <string.h>

static int pinOne = 16, pinTwo = 17, dtrPin = 18, uartId = 0,baudRate = 115200;

const uint ledPin = 25;

char* sampleWebsite = "geeksforgeeks.org";
char* sampleRequest = "GET /";

int main()
{
	stdio_init_all();

	gpio_init(ledPin);
	gpio_set_dir(ledPin, GPIO_OUT);

	setup_gsm(uartId, baudRate, pinOne, pinTwo, dtrPin);

	request_sample();
}

void request_sample()
{
	char* result;
	request(sampleWebsite, sampleRequest, result);

	printf("REQUEST RESULT:\n\n");

	if (check_empty_string(result) != 1) // MAKE SURE TO CHECK IS POINTER CHANGED
	{
		for (int i = 0; i < 10; i++)
		{
			sleep_ms(200);
			gpio_put(ledPin, true);
			sleep_ms(200);
			gpio_put(ledPin, false);
		}

		int length = strlen(result);
		for (int i = 0; i < length; i++)
		{
			sleep_ms(500);
			gpio_put(ledPin, true);
			sleep_ms(500);
			gpio_put(ledPin, false);
			printf("%c", result[i]);
		}
	}
}

