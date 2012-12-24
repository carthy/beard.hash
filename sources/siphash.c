/*            DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
 *                    Version 2, December 2004
 *
 *            DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
 *   TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
 *
 *  0. You just DO WHAT THE FUCK YOU WANT TO.
 */

#include <common.h>
#include <siphash.h>

#include <stdlib.h>
#include <assert.h>

#define ROTL64(a, b) \
	(((a) << (b)) | ((a) >> (64 - b)))

#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	#define GET64(p, i) ({ \
		uint8_t* _p = p; \
		int      _i = i; \
\
		*(uint64_t*) (_p + _i); \
	})
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	#define GET64(p, i) ({ \
		uint8_t* _p = p; \
		int      _i = i; \
\
		((uint64_t) _p[_i + 0] << 56) | ((uint64_t) _p[_i + 1] << 48) | \
		((uint64_t) _p[_i + 2] << 40) | ((uint64_t) _p[_i + 3] << 32) | \
		((uint64_t) _p[_i + 4] << 24) | ((uint64_t) _p[_i + 5] << 16) | \
		((uint64_t) _p[_i + 6] << 8)  | ((uint64_t) _p[_i + 7] << 0) \
	})
#else
	#error "I don't know the size of this endian"
#endif

hash_t
siphash (uint8_t key[16], void* buffer, size_t length)
{
	assert(buffer);

	uint64_t v0;
	uint64_t v1;
	uint64_t v2;
	uint64_t v3;
	uint64_t k0;
	uint64_t k1;
	uint64_t last7;

	k0 = GET64(key, 0);
	k1 = GET64(key, 8);
	v0 = k0 ^ 0x736F6D6570736575ull;
	v1 = k1 ^ 0x646F72616E646F6Dull;
	v2 = k0 ^ 0x6C7967656E657261ull;
	v3 = k1 ^ 0x7465646279746573ull;

	last7 = (length & 0xFFull) << 56;

	#define compress(n) \
		for (size_t i = 0; i < n; i++) { \
			v0 += v1; v2 += v3; \
			v1  = ROTL64(v1, 13); v3 = ROTL64(v3, 16); \
			v1 ^= v0; v3 ^= v2; \
			v0  = ROTL64(v0, 32); \
			v2 += v1; v0 += v3; \
			v1  = ROTL64(v1, 17); v3 = ROTL64(v3, 21); \
			v1 ^= v2; v3 ^= v0; \
			v2  = ROTL64(v2, 32); \
		}

	size_t i, blocks;
	for (i = 0, blocks = length & ~7; i < blocks; i += 8) {
		v3 ^= GET64(buffer, i);
		compress(2);
		v0 ^= GET64(buffer, i);
	}

	uint8_t* buf = buffer;
	switch (length - blocks) {
		case 7: last7 |= ((uint64_t) buf[i + 6] << 48);
		case 6: last7 |= ((uint64_t) buf[i + 5] << 40);
		case 5: last7 |= ((uint64_t) buf[i + 4] << 32);
		case 4: last7 |= ((uint64_t) buf[i + 3] << 24);
		case 3: last7 |= ((uint64_t) buf[i + 2] << 16);
		case 2: last7 |= ((uint64_t) buf[i + 1] <<  8);
		case 1: last7 |= ((uint64_t) buf[i + 0]);
	}

	v3 ^= last7;
	compress(2);
	v0 ^= last7;
	v2 ^= 0xff;
	compress(4);

	#undef compress

	uint64_t hash = v0 ^ v1 ^ v2 ^ v3;

	#if HASH_BIT == 32
		return (hash >> 32) ^ (hash & 0xFFFFFFFF);
	#elif HASH_BIT == 64
		return hash;
	#else
		#error "Why can't I hold so many bits?"
	#endif
}
