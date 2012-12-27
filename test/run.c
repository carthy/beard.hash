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
		siphash_update(sip, data, 10);
		siphash_update(sip, data + 10, 10);
		siphash_final(sip);

		printf("siphash:             %lu\n", siphash(key, data, 20));
		printf("siphash (streaming): %lu\n", siphash_fetch(sip));
		puts("");
	}

	{
		hash_t     seed   = 80085;
		char*      string = "200000000000";
		size_t     size   = strlen(string);
		murmur3_t* mur    = murmur3_new();

		murmur3_init(mur, seed);
		murmur3_update(mur, string, size);
		murmur3_final(mur);

		printf("murmur3:             %lu\n", murmur3(seed, string, size));
		printf("murmur3 (streaming): %lu\n", murmur3_fetch(mur));
		puts("");
	}

	return 0;
}
