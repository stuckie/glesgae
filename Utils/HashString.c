#include "HashString.h"

GAE_HashString_t GAE_HashString_create(const char* string) {
	int c;
	GAE_HashString_t hash = 0U;

	while ((c = *string++))
		hash = ((hash << 5) + hash) ^ c;

	return hash;
}

GAE_BOOL GAE_HashString_compare(void* const A, void* const B) {
	GAE_HashString_t* a = (GAE_HashString_t*)A;
	GAE_HashString_t* b = (GAE_HashString_t*)B;

	return *a==*b;
}

//const GAE_HashString_t GAE_INVALID_HASHSTRING = (GAE_HashString_t)(-931176343); /*GAE_HashString_create("INVALID_HASHSTRING");*/
