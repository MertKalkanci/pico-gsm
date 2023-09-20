#ifndef GSM_H
#define GSM_H

#include "pico/uart.h"
#include "pico/stdlib.h"
#include <stdio.h>



void setup_gsm(int uart,int baudrate,int tx, int rx, int dtr); //SET DTR -1 IF YOU DONT WANT TO USE SLEEP FEATURE

void disable_sleep();
void enable_sleep();

void get_request(char[] url,*char[] result);

void send_sms

#endif // !GSM_H
