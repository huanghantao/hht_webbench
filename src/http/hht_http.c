#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "hht_http.h"
#include "../config/hht_config.h"
#include "../core/hht_string.h"

static const char *http_method_strs[] = {
    "GET", "POST", "PUT", "DELETE"
};

void hht_http_request_init(hht_http_request_t *http_request_o)
{
    http_request_o->len = 0;
    http_request_o->method = hht_str_setto(DEFAULT_METHOD, DEFAULT_METHOD_LEN);
    http_request_o->len += http_request_o->method.len + 1;
    http_request_o->path = hht_str_setto(DEFAULT_PATH, DEFAULT_PATH_LEN);
    http_request_o->len += http_request_o->path.len + 1;
    http_request_o->protocol = hht_str_setto(DEFAULT_PROTOCOL, DEFAULT_PROTOCOL_LEN);
    http_request_o->len += http_request_o->protocol.len + 2;
    hht_http_headers_in_init(&(http_request_o->headers_in));
    http_request_o->len += http_request_o->headers_in.len;
    http_request_o->http_request_buf = NULL;
}

void hht_http_headers_in_init(hht_http_headers_in_t *http_headers_in_o)
{
    http_headers_in_o->host = hht_str_setto(DEFAULT_HOST, DEFAULT_HOST_LEN);
    http_headers_in_o->len = http_headers_in_o->host.len + 4;
}

void hht_fill_http_request_buf(hht_http_request_t *http_request_o)
{
    char *vptr;

    http_request_o->http_request_buf = (unsigned char *)malloc(http_request_o->len);
    vptr = http_request_o->http_request_buf;

    memcpy(vptr, http_request_o->method.data, http_request_o->method.len);
    vptr += http_request_o->method.len;
    *vptr = ' ';
    vptr += 1;
    memcpy(vptr, http_request_o->path.data, http_request_o->path.len);
    vptr += http_request_o->path.len;
    *vptr = ' ';
    vptr += 1;
    memcpy(vptr, http_request_o->protocol.data, http_request_o->protocol.len);
    vptr += http_request_o->protocol.len;
    memcpy(vptr, "\r\n", 2);
    vptr += 2;
    // memcpy(vptr, "\r\n\r\n", 4);
}

int hht_get_method_index(hht_str_t *method_str)
{
    int i;

    for (i = 0; i < HTTP_DELETE; ++i) {
        if (strcasecmp(http_method_strs[i], method_str->data) == 0) {
            return i;
        }
    }

    return -1;
}

const char *hht_get_http_method_str(int method_index)
{
    if (method_index < 0 || method_index > HTTP_DELETE) {
        return NULL;
    }

    return http_method_strs[method_index];
}
