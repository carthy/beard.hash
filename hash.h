/*            DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
 *                    Version 2, December 2004
 *
 *            DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
 *   TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
 *
 *  0. You just DO WHAT THE FUCK YOU WANT TO.
 */

#include <stdint.h>
#include <string.h>
#include <stdint.h>
#include <limits.h>

typedef unsigned long hash_t;

#define HASH_BIT (sizeof(hash_t) * CHAR_BIT)

hash_t siphash (uint8_t key[16], void* buffer, size_t length);