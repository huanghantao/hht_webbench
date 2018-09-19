#include <stdlib.h>
#include "hht_string.h"

int string_eq(const hht_str_t *lhs, const hht_str_t *rhs)
{
    if (lhs->data == NULL && rhs->data == NULL) {
        return 0;
    }
    if (lhs->data == NULL || rhs->data == NULL) {
        return 1;
    }
    if (lhs->len != rhs->len) {
        return 1;
    }
    for (int i = 0; i < lhs->len; ++i) {
        if (lhs->data[i] != rhs->data[i]) {
            return 1;
        }
    }
    return 0;
}