/*            DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
 *                    Version 2, December 2004
 *
 *            DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
 *   TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
 *
 *  0. You just DO WHAT THE FUCK YOU WANT TO.
 */

#include <common.h>

#define likely(x) \
	__builtin_expect(!!(x), 1)

#define unlikely(x) \
	__builtin_expect(!!(x), 0)

#define ROTL32(a, b) \
	(((a) << (b)) | ((a) >> (32 - (b))))

#define ROTL64(a, b) \
	(((a) << (b)) | ((a) >> (64 - (b))))

#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	#define GET32(p, i) ({ \
		void* _p = p; \
		int   _i = i; \
	\
		*(uint32_t*) (_p + _i); \
	})
	
	#define GET64(p, i) ({ \
		void* _p = p; \
		int   _i = i; \
	\
		*(uint64_t*) (_p + _i); \
	})
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	#define GET32(p, i) ({ \
		uint8_t* _p = p; \
		int      _i = i; \
\
		((uint32_t) _p[_i + 0] << 24) | ((uint32_t) _p[_i + 1] << 16) | \
		((uint32_t) _p[_i + 2] << 8)  | ((uint32_t) _p[_i + 3] << 0) \
	})

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
	#error "I don't see any huge endian"
#endif
