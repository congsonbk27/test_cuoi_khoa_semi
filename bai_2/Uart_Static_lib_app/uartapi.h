
#ifndef _UART_H_
#define _UART_H_ 

extern int serial_open(int port, long baudrate, int data_bits, int parity, int stops_bits);
extern int serial_close(int port);
extern int serial_write(int port, char *buf, int len);
extern int serial_read(int port, char *buf, int len);

#endif