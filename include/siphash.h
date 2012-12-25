/*            DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
 *                    Version 2, December 2004
 *
 *            DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
 *   TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
 *
 *  0. You just DO WHAT THE FUCK YOU WANT TO.
 */

hash_t siphash (uint8_t key[16], void* buffer, size_t length);

typedef struct siphash_t siphash_t;

siphash_t* siphash_new (void);

void siphash_free (siphash_t* self);

siphash_t* siphash_init (siphash_t* self, uint8_t key[16], int compression, int finalization);

siphash_t* siphash_init_default (siphash_t* self, uint8_t key[16]);

siphash_t* siphash_update (siphash_t* self, void* buffer, size_t length);

#define siphash_update_with(self, data) ({ \
	typeof (data) _data = data; \
\
	siphash_update(self, &_data, sizeof(_data)); \
})

siphash_t* siphash_finalize (siphash_t* self);

hash_t siphash_fetch (siphash_t* self);
