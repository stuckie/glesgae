#ifndef _HASH_STRING_H_
#define _HASH_STRING_H_

#include "../GAE_Types.h"

GAE_HashString_t GAE_HashString_create(const char* string);
GAE_BOOL GAE_HashString_compare(void* const A, void* const B);

#define GAE_INVALID_HASHSTRING (GAE_HashString_t)(-931176343)

#endif
