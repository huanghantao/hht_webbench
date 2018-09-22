#ifndef __HHT_HTTP_H__
#define __HHT_HTTP_H__


#include "../core/hht_string.h"

enum swHttpMethod {
    HTTP_GET, HTTP_POST, HTTP_PUT, HTTP_DELETE
};

typedef struct hht_http_headers_in_s {
    unsigned int len;
    hht_str_t host;
    // hht_str_t connection;
    // hht_str_t agent;
} hht_http_headers_in_t;

typedef struct hht_http_request_s {
    unsigned int len;
    hht_str_t method;
    hht_http_headers_in_t headers_in;
    unsigned char *http_request_buf;
} hht_http_request_t;

void http_request_init(hht_http_request_t *http_request_o);
void http_headers_in_init(hht_http_headers_in_t *http_headers_in_o);
void fill_http_request_buf(hht_http_request_t *http_request_o);
int hht_get_method_index(hht_str_t *method_str);
const char *hht_get_http_method_str(int method_index);

#endif /* __HHT_HTTP_H__ */