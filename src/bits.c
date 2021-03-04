/*
 * Copyright 2020-2021 D'Arcy Smith + the BCIT CST Datacommunications Option students.
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
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>


static bool get_bit_value(uint8_t val, uint8_t mask);
static void set_bit(size_t position, const char printable[9], bool bits[8]);


#define MASK_00000001 0x01
#define MASK_00000010 0x02
#define MASK_00000100 0x04
#define MASK_00001000 0x08
#define MASK_00010000 0x10
#define MASK_00100000 0x20
#define MASK_01000000 0x40
#define MASK_10000000 0x80


void to_binary(uint8_t val, bool bits[8])
{
    bits[0] = get_bit_value(val, MASK_10000000);
    bits[1] = get_bit_value(val, MASK_01000000);
    bits[2] = get_bit_value(val, MASK_00100000);
    bits[3] = get_bit_value(val, MASK_00010000);
    bits[4] = get_bit_value(val, MASK_00001000);
    bits[5] = get_bit_value(val, MASK_00000100);
    bits[6] = get_bit_value(val, MASK_00000010);
    bits[7] = get_bit_value(val, MASK_00000001);
}


static bool get_bit_value(uint8_t byte, uint8_t mask)
{
    uint8_t masked;
    bool bit;
    
    masked = byte & mask;
    
    if(masked > 0)
    {
        bit = true;
    }
    else
    {
        bit = false;
    }
    
    return bit;
}


void to_printable_binary(const bool bits[8], char printable[9])
{
    for(size_t i = 0; i < 8; i++)
    {
        char bit;

        if(bits[i])
        {
            bit = '1';
        }
        else
        {
            bit = '0';
        }

        printable[i] = bit;
    }
    
    printable[8] = '\0';
}


void from_printable_binary(const char printable[9], bool bits[8])
{
    for(size_t i = 0; i < 8; i++)
    {
        set_bit(i, printable, bits);
    }
}


static void set_bit(size_t position, const char printable[9], bool bits[8])
{
    char c;
    bool bit;
    
    c = printable[position];
    
    if(c == '0')
    {
        bit = false;
    }
    else
    {
        bit = true;
    }
    
    bits[position] = bit;
}

void from_binary(const bool bits[8], uint8_t *byte)
{
    uint8_t value;
    
    value = 0;
        
    for(size_t i = 0; i < 8; i++)
    {
        if(bits[i])
        {
            // https://stackoverflow.com/questions/47981/how-do-you-set-clear-and-toggle-a-single-bit
            value |= 1 << (7 - i);
        }
    }
    
    *byte = value;
}
