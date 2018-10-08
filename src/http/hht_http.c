#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include "hht_http.h"
#include "../config/hht_config.h"
#include "../core/hht_string.h"
#include "../core/hht_list.h"

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

hht_http_header_node_t *new_http_header_node(unsigned char *key, unsigned char *value)
{
    hht_http_header_node_t *http_header_node;

    http_header_node = (hht_http_header_node_t *)calloc(1, sizeof(*http_header_node));
    if (http_header_node != NULL) {
        INIT_LIST_HEAD(&(http_header_node->node));
        http_header_node->key = hht_str_setto(key, strlen(key));
        http_header_node->value = hht_str_setto(value, strlen(value));
    }

    return http_header_node;
}

hht_http_request_t *new_http_request(void)
{
    hht_http_request_t *http_request;

    http_request = (hht_http_request_t *)calloc(1, sizeof(*http_request));
    if (http_request != NULL) {
        http_request->method = hht_str_setto(DEFAULT_METHOD, sizeof(DEFAULT_METHOD) - 1);
        http_request->path = hht_str_setto(DEFAULT_PATH, sizeof(DEFAULT_PATH) - 1);
        http_request->protocol = hht_str_setto(DEFAULT_PROTOCOL, sizeof(DEFAULT_PROTOCOL) - 1);
        http_request->headers_in_list = new_http_header_node("", "");
        if (http_request->headers_in_list == NULL) {
            free(http_request);
            return NULL;
        }
        http_request->http_request_buf = new_str_buf();
    }

    return http_request;
}

void http_header_node_add(hht_http_request_t *http_request_o, unsigned char *key, unsigned char *value)
{
    hht_http_header_node_t *http_header_node = new_http_header_node(key, value);
    if (http_header_node != NULL) {
        list_add_tail(&(http_request_o->headers_in_list->node), &(http_header_node->node));
    }
}

void http_header_node_each(hht_http_request_t *http_request_o, void (*handler)(void *node))
{
    hht_list_head_t *head_node = &(http_request_o->headers_in_list->node);
    hht_list_head_t *pos = head_node->next;
    for (; pos != head_node; pos = pos->next) {
        handler(pos);
    }
}

void fill_http_request_buf(hht_http_request_t *http_request_o)
{
    hht_list_head_t *head_node = &(http_request_o->headers_in_list->node);
    hht_list_head_t *pos = head_node->next;
    hht_http_header_node_t *http_header_node;
    hht_str_t wrap = hht_str_setto("\r\n", strlen("\r\n"));
    for (; pos != head_node; pos = pos->next) {
        http_header_node = list_entry(pos, hht_http_header_node_t, node);
        append_str_buf(http_request_o->http_request_buf, &(http_header_node->key));
        append_str_buf(http_request_o->http_request_buf, &(http_header_node->value));
        append_str_buf(http_request_o->http_request_buf, &wrap);
    }
}
