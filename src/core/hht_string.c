#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hht_string.h"

hht_str_t hht_str_setto(unsigned char *cstr, int len)
{
    unsigned char *p;

    p = (unsigned char *)malloc(len + 1);
    if (p == NULL) {
        fprintf(stderr, "Error: malloc error\n");
        exit(1);
    }
    for (int i = 0; i < len; i++) {
        p[i] = cstr[i];
    }
    p[len] = 0;
    return (hht_str_t){ len, p };
}

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

int hht_str_eqn(const hht_str_t *lstr, const hht_str_t *rstr, int n)
{   
    int min_len;
    int i;

    if (lstr->data == NULL && rstr->data == NULL) {
        return 0;
    }
    if (lstr->data == NULL || rstr->data == NULL) {
        return 1;
    }

    min_len = lstr->len < rstr->len ? lstr->len : rstr->len;
    
    for (i = 0; i < min_len && i < n; ++i) {
        if (lstr->data[i] != rstr->data[i]) {
            return 1;
        }
    }

    if (i < n) {
        return 1;
    }

    return 0;
}

int hht_str_eq_cstr(const hht_str_t *str, const char *cstr)
{

    int cstr_len = strlen(cstr);

    if (str->data == NULL && cstr == NULL) {
        return 0;
    }
    if (str->data == NULL || cstr == NULL) {
        return 1;
    }
    if (str->len != cstr_len) {
        return 1;
    }
    for (int i = 0; i < str->len; ++i) {
        if (str->data[i] != cstr[i]) {
            return 1;
        }
    }
    return 0;
}

int hht_str_eqn_cstr(const hht_str_t *lstr, const char *cstr, int n)
{
    int min_len;
    int cstr_len = strlen(cstr);
    int i;

    if (lstr->data == NULL && cstr == NULL) {
        return 0;
    }
    if (lstr->data == NULL || cstr == NULL) {
        return 1;
    }

    min_len = lstr->len < cstr_len ? lstr->len : cstr_len;
    
    for (i = 0; i < min_len && i < n; ++i) {
        if (lstr->data[i] != cstr[i]) {
            return 1;
        }
    }

    if (i < n) {
        return 1;
    }
    return 0;
}

unsigned char *hht_strchr(hht_str_t *str, char ch)
{
    unsigned char *pos = str->data;

    for (int i = 0; i < str->len; i++) {
        if (*pos == ch) {
            return pos;
        }
        pos++;
    }
    return NULL;
}
