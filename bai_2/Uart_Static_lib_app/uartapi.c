

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <stdlib.h>
#include <string.h>

const char* g_uart1 = "/dev/ttyO1";
static int s_fd_uart1;

extern int serial_open(int port, long baudrate, int data_bits, int parity, int stops_bits) {
    struct termios UART_TypeDef;
    memset(&UART_TypeDef, 0, sizeof (UART_TypeDef));

    UART_TypeDef.c_iflag &= ~(IGNBRK | BRKINT | ICRNL | INLCR | PARMRK | INPCK | ISTRIP | IXON);
    UART_TypeDef.c_oflag = 0;
    UART_TypeDef.c_lflag &= ~(ECHO | ECHONL | ICANON | IEXTEN | ISIG);
    UART_TypeDef.c_cflag &= ~(CSIZE | PARENB);

    UART_TypeDef.c_cflag |= CS8;

    UART_TypeDef.c_cc[VMIN] = 1;
    UART_TypeDef.c_cc[VTIME] = 0;

    cfsetospeed(&UART_TypeDef, baudrate);
    cfsetispeed(&UART_TypeDef, baudrate);

    UART_TypeDef.c_cflag |= parity;
    UART_TypeDef.c_cflag &= ~stops_bits; // truyen so 4 

//     if (cfsetispeed (&UART_TypeDef,B115200) < 0 || cfsetospeed (&UART_TypeDef, B115200) < 0)
//     {
//     	printf ("-E- cannot setg baudrate \r\n");
//     	return -1;
//     }

    switch (port) {
        case 1:
            s_fd_uart1 = open("/dev/ttyO1", O_RDWR | O_NOCTTY | O_NDELAY);
            if (s_fd_uart1 == -1) {
                perror("Uart: Failed to open the file.\n");
                return -1;

            }
            //bbbuart_config(s_fd_uart1);
            break;
        default:
            break;
    }
    return 0;


    if (tcsetattr(port, TCSAFLUSH, &UART_TypeDef) < 0) {
        printf("-E- config failed \r\n");
        return -1;
    }

    printf("-I- config success \r\n");
    return 0;
}

extern int serial_close(int port) {
    switch (port) {
            FILE * fd;
            fd = fopen("/dev/ttyO1", "r");
            if (!fd) {
                perror("Uart: Failed to close the file.\n");
                return -1;
            }
        case 1:
            s_fd_uart1 = fclose(fd);
            if (s_fd_uart1 == -1) {
                perror("Uart: Failed to close the file.\n");
                return -1;

            }
            //bbbuart_config(s_fd_uart1);
            break;
        default:
            break;
    }
    return 0;
}

extern int serial_write(int port, char *buf, int len) {
    int nByteActual = 0;
    switch (port) {
        case 1:
            nByteActual = write(s_fd_uart1, buf, len);
            if (nByteActual < 0) {
                perror("Failed to write to the output\n");
                return -1;
            } else {
                printf("Send data successful !\r\n");
            }
            break;
        default:
            break;
    }
    return nByteActual;
}

extern int serial_read(int port, char *buf, int len) {
    int nByteActual = 0;
    switch (port) {
        case 1:
            nByteActual = read(s_fd_uart1, buf, len);
            if (nByteActual < 0) {
                perror("Failed to write to the output\n");
                return -1;
            } else {
                printf("Send data successful !\r\n");

            }
            break;
        default:
            break;
    }
    return nByteActual;
}