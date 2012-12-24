#include <stdio.h>
#include <hash.h>

int
main (int argc, char* argv[])
{
	uint8_t key[16]  = { 0 };
	uint8_t data[20] = { 1 };

	printf("%llu\n", siphash(key, data, 20));

	return 0;
}
