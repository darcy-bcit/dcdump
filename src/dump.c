/*
 * Copyright 2020 D'Arcy Smith + the BCIT CST Datacommunications Option students.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


#include "bits.h"
#include <dc/fcntl.h>
#include <dc/unistd.h>
#include <dc/sys/stat.h>
#include <ctype.h>
#include <fcntl.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


static void process_file(int fd, size_t width);
static void display(size_t position, char *position_format, uint8_t val);
static size_t number_of_digits(const off_t value);


int main(int argc, const char *argv[])
{
    int fd;
    off_t size;
    size_t width;

    if(argc > 1)
    {
        const char *file_name;
        struct stat st;

        file_name = argv[1];
        fd = dc_open(file_name, O_RDONLY);
        dc_stat(file_name, &st);
        size = st.st_size;
    }
    else
    {
        fd = STDIN_FILENO;
        size = UINT_MAX;
    }
    
    width = number_of_digits(size);
    process_file(fd, width);
    
    if(argc > 1)
    {
        dc_close(fd);
    }
    
    return EXIT_SUCCESS;
}

size_t number_of_digits(const off_t value)
{
    return value > 0 ? (size_t)log10((double)value) + 1 : 1;
}

static void process_file(int fd, size_t width)
{
    size_t position;
    ssize_t size;
    char position_format[1 + width + 2 + 1]; // eg:"%10ld\0"
    
    sprintf(position_format, "%%%ldld", width);
    position = 0;
    
    do 
    {
        uint8_t byte;

        size = dc_read(fd, &byte, 1);

        if(size > 0)
        {
            display(position, position_format, byte);
            position++;
        }
    }
    while(size > 0); // 0 is end of file
}

static void display(size_t position, char *position_format, uint8_t byte)
{
    bool bits[8];
    char printable_bits[9];
    
    to_binary(byte, bits);
    to_printable_binary(bits, printable_bits);
    
    printf(position_format, position);
    printf(": ");
    
    if(isprint(byte))
    {
        printf("%c | ", byte);
    }
    else
    {
        printf("%c | ", ' ');
    }
    
    printf("%2X | ", byte);
    printf("%3d | ", byte);
    printf("%3o | ", byte);
    printf("%s\n", printable_bits);
}
