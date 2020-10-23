#include "bits.h"
#include <dc/fcntl.h>
#include <dc/unistd.h>
#include <fcntl.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


#define BINARY_STRING_SIZE sizeof(char) * 8


static void process_file(int fd);


int main(int argc, char *argv[])
{
    int fd;
    
    if(argc > 1)
    {
        const char *file_name;

        file_name = argv[1];
        fd = dc_open(file_name, O_RDONLY);
    }
    else
    {
        fd = STDIN_FILENO;
    }
    
    process_file(fd);
    
    if(argc > 1)
    {
        dc_close(fd);
    }
    
    return EXIT_SUCCESS;
}

static void process_file(int fd)
{
    ssize_t size;
    
    do
    {
        char binary_string[9];
        bool bits[8];
        uint8_t byte;
        
        size = dc_read(fd, binary_string, BINARY_STRING_SIZE);
        
        if(size > 0 && size != (ssize_t)BINARY_STRING_SIZE)
        {
            fprintf(stderr, "read %zd bytes, expected: %ld\n", size, BINARY_STRING_SIZE);
            exit(EXIT_FAILURE);
        }
        
        if(size > 0)
        {
            binary_string[BINARY_STRING_SIZE] = '\0';
            from_printable_binary(binary_string, bits);
            from_binary(bits, &byte);
            printf("%c", byte);
        }
    }
    while(size > 0); // 0 is end of file

    printf("\n");
}
