#ifndef __HHT_HTTP_H__
#define __HHT_HTTP_H__


#include "../core/hht_string.h"
#include "../core/hht_list.h"
#include "../core/hht_strbuf.h"

enum hht_http_method {
    HTTP_GET, HTTP_POST, HTTP_PUT, HTTP_DELETE
};

typedef struct hht_http_header_node_s {
    hht_list_head_t node;
    hht_str_t *key;
    hht_str_t *value;
} hht_http_header_node_t;

typedef struct hht_http_request_s {
    hht_str_t method;
    hht_str_t path;
    hht_str_t protocol;
    hht_http_header_node_t headers_in_list;
    hht_str_buf_t *http_request_buf;
} hht_http_request_t;

hht_http_request_t *new_http_request(void);
int hht_get_method_index(hht_str_t *method_str);
const char *hht_get_http_method_str(int method_index);

#endif /* __HHT_HTTP_H__ */