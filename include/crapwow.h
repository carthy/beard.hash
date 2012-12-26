/*            DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
 *                    Version 2, December 2004
 *
 *            DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
 *   TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
 *
 *  0. You just DO WHAT THE FUCK YOU WANT TO.
 */

hash_t crapwow (hash_t seed, const void* buffer, size_t length);

#define crapwow_with(seed, data) ({ \
	__typeof__(data) _data = data; \
\
	crapwow(seed, &_data, sizeof(_data)); \
})
