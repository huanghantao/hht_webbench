#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include "hht_http.h"
#include "../config/hht_config.h"
#include "../core/hht_string.h"

static const char *http_method_strs[] = {
    "GET", "POST", "PUT", "DELETE"
};

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

hht_http_header_node_t *new_http_header_node(char *key, char *value)
{
    hht_http_header_node_t *http_header_node;

    http_header_node = (hht_http_header_node_t *)calloc(1, sizeof(*http_header_node));
    if (http_header_node != NULL) {
        INIT_LIST_HEAD(&(http_header_node->node));
        http_header_node->key = hht_str_setto(key, sizeof(key) - 1);
        http_header_node->value = hht_str_setto(value, sizeof(value) - 1);
    }

    return http_header_node;
}

hht_http_request_t *new_http_request(void)
{
    hht_http_request_t *http_request;

    http_request = (hht_http_request_t *)calloc(1, sizeof(*http_request));
    if (http_request != NULL) {
        http_request->method = hht_str_setto(DEFAULT_METHOD, DEFAULT_METHOD_LEN);
        http_request->path = hht_str_setto(DEFAULT_PATH, DEFAULT_PATH_LEN);
        http_request->protocol = hht_str_setto(DEFAULT_PROTOCOL, DEFAULT_PROTOCOL_LEN);
        http_request->headers_in_list = new_http_header_node("Host: ", "localhost");
        if (http_request->headers_in_list == NULL) {
            free(http_request);
            return NULL;
        }
        http_request->http_request_buf = new_str_buf();
    }

    return http_request;
}
