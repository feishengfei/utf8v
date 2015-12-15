#ifndef UTF8V_H
#define UTF8V_H

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

#define DEBUG 0

#define debug_print(fmt, ...) \
	do { \
	if (DEBUG) \
		fprintf(stderr, "%s:%d:%s(): " fmt, __FILE__, \
	__LINE__, __func__, __VA_ARGS__); \
	} while (0)


/* utf8v_validate
 *
 * validate a byte 'array'
 * return -1 if wrong size information
 * return 1 if invalid byte sequences
 * return 0 if sequence is valid.
 */

int
    utf8v_validate(unsigned char*, int);

int
    valid_first_range(unsigned char byte);

int
    valid_second_range(unsigned char byte, unsigned char second);

int
    valid_third_range(unsigned char byte, unsigned char second, unsigned char third);

int
    valid_fourth_range(unsigned char byte,
                       unsigned char second,
                       unsigned char third,
                       unsigned char fourth);
int
    extract_sequence_length(unsigned char first_byte);

#ifdef __cplusplus
}
#endif

#endif /* UTF8V_H */
