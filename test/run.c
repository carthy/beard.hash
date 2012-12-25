#include <stdio.h>
#include <hash.h>

int
main (int argc, char* argv[])
{
	{
		uint8_t    key[16]  = {0};
		uint8_t    data[20] = {0};
		siphash_t* sip      = siphash_new();

		siphash_init_default(sip, key);
		siphash_update(sip, data, 20);
		siphash_finalize(sip);

		printf("siphash:             %lu\n", siphash(key, data, 20));
		printf("siphash (streaming): %lu\n", siphash_fetch(sip));
	}

	return 0;
}
