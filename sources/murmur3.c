/*            DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
 *                    Version 2, December 2004
 *
 *            DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
 *   TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
 *
 *  0. You just DO WHAT THE FUCK YOU WANT TO.
 */

#include <helpers.h>
#include <murmur3.h>

#include <stdlib.h>
#include <assert.h>

#define fmix(h) _Generic((h), \
	uint32_t: fmix32, \
	uint64_t: fmix64 \
)(h)

static inline uint32_t
fmix32 (uint32_t h)
{
  h ^= h >> 16;
  h *= 0x85EBCA6B;
  h ^= h >> 13;
  h *= 0xC2B2AE35;
  h ^= h >> 16;

  return h;
}

static inline uint64_t
fmix64 (uint64_t h)
{
  h ^= h >> 33;
  h *= 0xFF51AFD7ED558CCDul;
  h ^= h >> 33;
  h *= 0xC4CEB9FE1A85EC53ul;
  h ^= h >> 33;

  return h;
}

hash_t
murmur3 (hash_t seed, void* buffer, size_t length)
{
	assert(buffer);

	#if HASH_BIT == 32
		uint8_t* buf    = buffer;
		int      number = length / 4;
		uint32_t h1     = seed;
		uint32_t c1     = 0xCC9E2D51;
		uint32_t c2     = 0x1B873593;

		uint32_t* blocks = (uint32_t*) (buf + (number * 4));
		for (int i = -number; i < 0; i++) {
			uint32_t k1 = GET32(blocks, i);

			k1 *= c1; k1 = ROTL32(k1, 15); k1 *= c2;
			h1 ^= k1; h1 = ROTL32(h1, 13);

			h1 = 0xE6546B64 + (h1 * 5);
		}

		{
			uint8_t* tail = buf + (number * 4);
			uint32_t k1   = 0;

			switch (length & 3) {
				case 3: k1 ^= tail[2] << 16;
				case 2: k1 ^= tail[1] << 8;

				case 1:
					k1 ^= tail[0];
					k1 *= c1;
					k1  = ROTL32(k1,15);
					k1 *= c2;
					h1 ^= k1;
			}
		}

		h1 ^= length;
		h1  = fmix(h1);

		return h1;
	#elif HASH_BIT == 64
		uint8_t* buf    = buffer;
		int      number = length / 16;
		uint64_t h1     = seed;
		uint64_t h2     = seed;
		uint64_t c1     = 0x87C37B91114253D5ull;
		uint64_t c2     = 0x4CF5AD432745937Full;

		uint64_t* blocks = (uint64_t*) buf;
		for (int i = 0; i < number; i++) {
			uint64_t k1 = GET64(blocks, i * 2);
			uint64_t k2 = GET64(blocks, i * 2 + 1);

			k1 *= c1; k1 = ROTL64(k1, 31); k1 *= c2;
			h1 ^= k1; h1 = ROTL64(h1, 27); h1 += h2;
			
			h1 = 0x52DCE729 + h1 * 5;

			k2 *= c2; k2 = ROTL64(k2, 33); k2 *= c1;
			h2 ^= k2; h2 = ROTL64(h2, 31); h2 += h1;

			h2 = 0x38495AB5 + h2 * 5;
		}

		{
			uint8_t* tail = buf + number * 16;
			uint64_t k1   = 0;
			uint64_t k2   = 0;

			switch (length & 15) {
				case 15: k2 ^= (uint64_t) tail[14] << 48;
				case 14: k2 ^= (uint64_t) tail[13] << 40;
				case 13: k2 ^= (uint64_t) tail[12] << 32;
				case 12: k2 ^= (uint64_t) tail[11] << 24;
				case 11: k2 ^= (uint64_t) tail[10] << 16;
				case 10: k2 ^= (uint64_t) tail[9]  << 8;

				case 9:
					k2 ^= (uint64_t) tail[8];
					k2 *= c2;
					k2  = ROTL64(k2, 33);
					k2 *= c1;
					h2 ^= k2;

				case 8: k1 ^= (uint64_t) tail[7] << 56;
				case 7: k1 ^= (uint64_t) tail[6] << 48;
				case 6: k1 ^= (uint64_t) tail[5] << 40;
				case 5: k1 ^= (uint64_t) tail[4] << 32;
				case 4: k1 ^= (uint64_t) tail[3] << 24;
				case 3: k1 ^= (uint64_t) tail[2] << 16;
				case 2: k1 ^= (uint64_t) tail[1] << 8;

				case 1:
					k1 ^= (uint64_t) tail[0];
					k1 *= c1;
					k1  = ROTL64(k1, 31);
					k1 *= c2;
					h1 ^= k1;
			}
		}

		h1 ^= length;
		h2 ^= length;

		h1 += h2;
		h2 += h1;

		h1 = fmix(h1);
		h2 = fmix(h2);

		h1 += h2;
		h2 += h1;

		return h1 ^ h2;
	#else
		#error "Why can't I hold so many bits?"
	#endif
}
