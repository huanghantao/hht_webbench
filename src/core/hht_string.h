#ifndef __HHT_STRING_H__
#define __HHT_STRING_H__


#include <stdlib.h>

typedef struct hht_str_s {
    size_t len;
    unsigned char *data;
} hht_str_t;

#define hht_str(str) { sizeof(str) - 1, (unsigned char *)str }

static inline hht_str_t hht_str_setto(unsigned char *cstr, int len)
{
    return (hht_str_t){ len, cstr };
}
static inline void hht_str_free(hht_str_t *str)
{
    free(str->data);
}
int hht_str_eq(const hht_str_t *lstr, const hht_str_t *rstr);

#endif /* __HHT_STRING_H__ */