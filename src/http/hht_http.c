#include <stdlib.h>
#include <string.h>
#include "hht_http.h"
#include "../config/hht_config.h"
#include "../core/hht_string.h"

void http_request_init(hht_http_request_t *http_request_o)
{
    http_request_o->len = 0;
    http_request_o->method = hht_string_setto(DEFAULT_METHOD, DEFAULT_METHOD_LEN);
    http_request_o->len += http_request_o->method.len + 2;
    http_headers_in_init(&(http_request_o->headers_in));
    http_request_o->len += http_request_o->headers_in.len;
    http_request_o->http_request_buf = NULL;
}

void http_headers_in_init(hht_http_headers_in_t *http_headers_in_o)
{
    http_headers_in_o->host = hht_string_setto(DEFAULT_HOST, DEFAULT_HOST_LEN);
    http_headers_in_o->len = http_headers_in_o->host.len + 4;
}

void fill_http_request_buf(hht_http_request_t *http_request_o)
{
    void *vptr;

    http_request_o->http_request_buf = (unsigned char *)malloc(http_request_o->len);
    vptr = http_request_o->http_request_buf;
    memcpy(vptr, http_request_o->method.data, http_request_o->method.len);
    vptr += http_request_o->method.len;
    memcpy(vptr, "\r\n", 2);
    vptr += 2;
    memcpy(vptr, http_request_o->headers_in.host.data, http_request_o->headers_in.host.len);
    vptr += http_request_o->headers_in.host.len;
    memcpy(vptr, "\r\n\r\n", 4);
}
