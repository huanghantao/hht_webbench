#include "hash.h"

uint64_t hash_func(unsigned char *key, size_t len)
{
    uint64_t hash = 5381;

    for (; len >= 8; len -= 8) {
        hash = ((hash << 5) + hash) + *key++;
        hash = ((hash << 5) + hash) + *key++;
        hash = ((hash << 5) + hash) + *key++;
        hash = ((hash << 5) + hash) + *key++;
        hash = ((hash << 5) + hash) + *key++;
        hash = ((hash << 5) + hash) + *key++;
        hash = ((hash << 5) + hash) + *key++;
        hash = ((hash << 5) + hash) + *key++;
    }
    switch (len) {
        case 7: hash = ((hash << 5) + hash) + *key++;
        case 6: hash = ((hash << 5) + hash) + *key++;
        case 5: hash = ((hash << 5) + hash) + *key++;
        case 4: hash = ((hash << 5) + hash) + *key++;
        case 3: hash = ((hash << 5) + hash) + *key++;
        case 2: hash = ((hash << 5) + hash) + *key++;
        case 1: hash = ((hash << 5) + hash) + *key++; break;
        case 0: break;
    }
    return hash;
}