#ifndef __HHT_STRBUF_H__
#define __HHT_STRBUF_H__


#include <stdlib.h>
#include "hht_string.h"

#define STEP_LEN 512

typedef struct hht_str_buf_s {
    size_t len;
    size_t capacity;
    unsigned char *buf;
} hht_str_buf_t;

static int expand_buffer(hht_str_buf_t *str_buf, size_t nbytes);
hht_str_buf_t *new_str_buf(void);
void free_str_buf(hht_str_buf_t *str_buf);
size_t get_str_buf_len(hht_str_buf_t *str_buf);
size_t get_str_buf_capacity(hht_str_buf_t *str_buf);
void clear_str_buf(hht_str_buf_t *str_buf);
int append_str_buf(hht_str_buf_t *str_buf, hht_str_t *str);
int append_fstr_buf(hht_str_buf_t *str_buf, const char *format, ...);

#endif /* __HHT_STRBUF_H__ */