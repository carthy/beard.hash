/*            DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
 *                    Version 2, December 2004
 *
 *            DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
 *   TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
 *
 *  0. You just DO WHAT THE FUCK YOU WANT TO.
 */

hash_t siphash (const uint8_t key[16], const void* buffer, size_t length);

#define siphash_with(key, data) ({ \
	__typeof__(data) _data = data; \
\
	siphash(key, &_data, sizeof(_data)); \
})

typedef struct siphash_t siphash_t;

siphash_t* siphash_new (void);

void siphash_free (siphash_t* self);

siphash_t* siphash_init (siphash_t* self, const uint8_t key[16], int compression, int finalization);

siphash_t* siphash_init_default (siphash_t* self, const uint8_t key[16]);

siphash_t* siphash_update (siphash_t* self, const void* buffer, size_t length);

#define siphash_update_with(self, data) ({ \
	__typeof__(data) _data = data; \
\
	siphash_update(self, &_data, sizeof(_data)); \
})

siphash_t* siphash_final (siphash_t* self);

hash_t siphash_fetch (siphash_t* self);
