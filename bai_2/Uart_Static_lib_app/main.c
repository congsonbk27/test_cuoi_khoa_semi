#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <stdlib.h>
#include <string.h>
#include "uartapi.h"

int main() {
    printf("hello uart\n");
    int status_open = serial_open(1,  115200,  8,  4, 0 );
    if(status_open < 0)
    {
        printf("open uart 1 failed\n");
        return -1;
    }
    int len_read, len_write;
    char buf[255] = {0};
    while(1)
    {
        len_read = serial_read(1 , buf,  255);
        if(len_read > 0)
        {
            printf("du lieu nhan duoc %d byte \n", len_read);
            len_write = serial_write(1 , buf,  len_read);
            if(len_write > 0)
            {
                printf("da gui %d byte\n", len_write);
            }
            else
            {
                printf("gui du lieu bi loi\n");
                break;
            }
        }
    }
    serial_close(1);
    return 0;
}