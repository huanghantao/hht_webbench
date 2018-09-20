#ifndef __HHT_STRING_H__
#define __HHT_STRING_H__


typedef struct hht_str_s {
    unsigned int len;
    unsigned char *data;
} hht_str_t;

#define hht_string(str) { sizeof(str) - 1, (unsigned char *) str }

static inline hht_str_t hht_string_setto(unsigned char *cstr, int len)
{
    return (hht_str_t){len, cstr};
}
int hht_string_eq(const hht_str_t *lhs, const hht_str_t *rhs);

#endif /* __HHT_STRING_H__ */