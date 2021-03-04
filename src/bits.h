#ifndef BITS_H
#define BITS_H


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


#include <stdint.h>
#include <stdbool.h>


/**
 * Convert an 8-bit byte to an array of 8 bits.
 *
 * @param byte the byte to convert.
 * @param bits where to store the bits.
 */
void to_binary(uint8_t byte, bool bits[8]);

/**
 * Convert an array of 8 bits to 8 '0' and '1's.
 *
 * @param bits the array of bits to convert.
 * @param printable the string to store the '0' and '1's. Will be null terminated.
 */
void to_printable_binary(const bool bits[8], char printable[9]);

/**
 * Concert an array of 8 bits to an 8-bit byte.
 *
 * @param bits the array of bits.
 * @param byte the byte to store the bits into.
 */
void from_binary(const bool bits[8], uint8_t *byte);

/**
 * Convert a string of 8 '0' and '1's to an array of 8 bits.
 *
 * @param printable a null terminated string of 8 '0's and '1's.
 * @param bits the array of 8 bits that stores the converted value in.
 */
void from_printable_binary(const char printable[9], bool bits[8]);


#endif
