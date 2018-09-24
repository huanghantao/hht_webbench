#include <string.h>
#include <stdarg.h>
#include <stdio.h>
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

static int expand_buffer(hht_str_buf_t *str_buf, size_t nbytes)
{
    char *new_buf;
    int diff;
    size_t new_capacity;

    diff = nbytes - (str_buf->capacity - str_buf->len);
    if (diff <= 0) /* The remaining size is enough */
        return 0;
    
    new_capacity = str_buf->capacity + (diff / STEP_LEN + 1) * STEP_LEN;
    new_buf = realloc(str_buf->buf, new_capacity);
    if (new_buf != NULL) {
        str_buf->buf = new_buf;
        memset(str_buf->buf + str_buf->capacity, 0, new_capacity - str_buf->capacity);
        str_buf->capacity = new_capacity;
        return 0;
    } else {
        return -1;
    }
}

int append_str_buf(hht_str_buf_t *str_buf, hht_str_t *str)
{
    if (str_buf == NULL || str == NULL)
        return -1;
    if (expand_buffer(str_buf, str->len) == 0) {
        memcpy(str_buf->buf + str_buf->len, str->data, str->len);
        str_buf->len += str->len;
        str_buf->buf[str_buf->len] = 0;
        return str->len;
    } else {
        return -1;
    }
}

int append_fstr_buf(hht_str_buf_t *str_buf, const char *format, ...)
{
    size_t n;
    int ret;
    va_list args;

    if (str_buf == NULL)
        return -1;
    
    while (1) {
        n = str_buf->capacity - str_buf->len;
        va_start(args, format);
        ret = vsnprintf(str_buf->buf + str_buf->len, n, format, args);
        va_end(args);
        if (ret >= 0 && ret < n) {
            str_buf->len += ret;
            return ret;
        } else if (ret < 0) {
            return ret;
        } else { /* The remaining size is not enough */
            if (expand_buffer(str_buf, ret - n)) {
                return -1;
            }
        }
    }

    return ret;
}
