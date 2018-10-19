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
int hht_str_eqn(const hht_str_t *lstr, const hht_str_t *rstr, int n);
int hht_str_eq_cstr(const hht_str_t *str, const char *cstr);
int hht_str_eqn_cstr(const hht_str_t *lstr, const char *cstr, int n);
int hht_str_shallow_cpy(hht_str_t *str, unsigned char *start, unsigned char *end);
unsigned char *hht_strchr(hht_str_t *str, char ch);

#endif /* __HHT_STRING_H__ */