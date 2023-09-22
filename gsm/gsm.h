#ifndef GSM_H
#define GSM_H


static int txPin, rxPin, dtrPin;

void setup_gsm(int uart,int baudrate,int tx, int rx, int dtr); //SET DTR -1 IF YOU DONT WANT TO USE SLEEP FEATURE ALSO INIT STDIO BEFORE CALLING FUNCTION

void disable_sleep();
void enable_sleep();

void get_request(char ip[],char* result[]);

void send_sms(char num[], char message[]);

void insert_string(char* destination, int pos, char* insert);

void uart_read_ok(int* isOk);

#endif // !GSM_H
