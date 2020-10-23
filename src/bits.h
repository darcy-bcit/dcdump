#ifndef BITS_H
#define BITS_H


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
