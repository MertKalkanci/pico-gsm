#ifndef GSM_H
#define GSM_H

static int txPin, rxPin, dtrPin;

void setup_gsm(int uart,int baudrate,int tx, int rx, int dtr); //SET DTR -1 IF YOU DONT WANT TO USE SLEEP FEATURE ALSO INIT STDIO BEFORE CALLING FUNCTION

void disable_sleep();
void enable_sleep();

void request(char address[], char request[], char* result[]);

void send_sms(char num[], char message[]);

void insert_string(char* destination, int pos, char* insert);

int gsm_uart_end_check(char message[]);

void read_uart_gsm_message(char* message[]);

int check_empty_string(char* result);

#endif // !GSM_H
