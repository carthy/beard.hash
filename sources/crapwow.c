/*            DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
 *                    Version 2, December 2004
 *
 *            DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
 *   TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
 *
 *  0. You just DO WHAT THE FUCK YOU WANT TO.
 */

#include <common.h>
#include <crapwow.h>

#include <stdlib.h>
#include <assert.h>

hash_t
crapwow (hash_t seed, const void* buffer, size_t length)
{
	#if HASH_BIT == 32
		uint32_t  m   = 0x57559429;
		uint32_t  n   = 0x5052ACDB;
		uint32_t* buf = (uint32_t*) buffer;
		uint32_t  h   = length;
		uint32_t  k   = length + seed + n;

		#define fold(a, b, lo, hi) ({ \
			uint32_t _a = a; \
			uint64_t _b = b; \
			uint64_t _p = _a * _b; \
		\
			lo ^= _p & 0xFFFFFFFF; \
			hi ^= _p >> 32; \
		})

		#define mixa(in) \
			fold(in, m, k, h)

		#define mixb(in) \
			fold(in, n, h, k)

		while (length >= 8) {
			mixb(buf[0]);
			mixa(buf[1]);

			buf    += 2;
			length -= 8;
		}

		if (length >= 4) {
			mixb(buf[0]);

			buf    += 1;
			length -= 4;
		}

		if (length != 0) {
			mixa(buf[0] & ((1 << (length * 8)) - 1));
		}

		mixb(h ^ (k + n));

		#undef fold
		#undef mixa
		#undef mixb

		return k ^ h;
	#elif HASH_BIT == 64
		typedef __uint128_t uint128_t;

		uint64_t  m   = 0x95B47AA3355BA1A1;
		uint64_t  n   = 0x8A970BE7488FDA55;
		uint64_t* buf = (uint64_t*) buffer;
		uint64_t  h   = length;
		uint64_t  k   = length + seed + n;

		#define fold(a, b, lo, hi) ({ \
			uint64_t  _a = a; \
			uint128_t _b = b; \
			uint128_t _p = _a * _b; \
		\
			lo ^= _p & 0xFFFFFFFFFFFFFFFF; \
			hi ^= _p >> 64; \
		})

		#define mixa(in) \
			fold(in, m, k, h)

		#define mixb(in) \
			fold(in, n, h, k)

		while (length >= 16) {
			mixb(buf[0]);
			mixa(buf[1]);

			buf    += 2;
			length -= 16;
		}

		if (length >= 8) {
			mixb(buf[0]);

			buf    += 1;
			length -= 8;
		}

		if (length != 0) {
			mixa(buf[0] & ((1 << (length * 8)) - 1));
		}

		mixb(h ^ (k + n));

		#undef fold
		#undef mixa
		#undef mixb

		return k ^ h;
	#else
		#error "Why can't I hold so many bits?"
	#endif
}
