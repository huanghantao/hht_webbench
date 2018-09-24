#include <string.h>
#include "hht_strbuf.h"

hht_str_buf_t *new_str_buf(void)
{
    hht_str_buf_t *str_buf;

    str_buf = calloc(1, sizeof(*str_buf));
    if (str_buf != NULL) {
        str_buf->buf = calloc(1, STEP_LEN);
        if (str_buf->buf != NULL) {
            str_buf->capacity = STEP_LEN;
            str_buf->len = 0;
        } else {
            free(str_buf);
            str_buf = NULL;
        }
    }

    return str_buf;
}

void free_str_buf(hht_str_buf_t *str_buf)
{
    if (str_buf != NULL && str_buf->buf != NULL) {
        free(str_buf->buf);
        str_buf->buf = NULL;
    }
}

size_t get_str_buf_len(hht_str_buf_t *str_buf)
{
    return str_buf ? str_buf->len : 0;
}

size_t get_str_buf_capacity(hht_str_buf_t *str_buf)
{
    return str_buf ? str_buf->capacity : 0;
}

void clear_str_buf(hht_str_buf_t *str_buf)
{
    if (str_buf != NULL) {
        memset(str_buf->buf, 0, str_buf->len);
        str_buf->len = 0;
    }
}
