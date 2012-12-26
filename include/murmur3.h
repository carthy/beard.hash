/*            DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
 *                    Version 2, December 2004
 *
 *            DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
 *   TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
 *
 *  0. You just DO WHAT THE FUCK YOU WANT TO.
 */

hash_t murmur3 (hash_t seed, const void* buffer, size_t length);

typedef struct murmur3_t murmur3_t;

murmur3_t* murmur3_new (void);

void murmur3_free (murmur3_t* self);

murmur3_t* murmur3_init (murmur3_t* self, hash_t seed);

murmur3_t* murmur3_init_default (murmur3_t* self);

murmur3_t* murmur3_update (murmur3_t* self, const void* buffer, size_t length);

#define murmur3_update_with(self, data) ({ \
	typeof (data) _data = data; \
\
	murmur3_update(self, &_data, sizeof(_data)); \
})

murmur3_t* murmur3_final (murmur3_t* self);

hash_t murmur3_fetch (murmur3_t* self);
