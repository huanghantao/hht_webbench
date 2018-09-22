#include <stdlib.h>
#include "hht_string.h"

int hht_str_eq(const hht_str_t *lstr, const hht_str_t *rstr)
{
    if (lstr->data == NULL && rstr->data == NULL) {
        return 0;
    }
    if (lstr->data == NULL || rstr->data == NULL) {
        return 1;
    }
    if (lstr->len != rstr->len) {
        return 1;
    }
    for (int i = 0; i < lstr->len; ++i) {
        if (lstr->data[i] != rstr->data[i]) {
            return 1;
        }
    }
    return 0;
}