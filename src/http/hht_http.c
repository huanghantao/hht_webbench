#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include "hht_http.h"
#include "../config/hht_config.h"
#include "../core/hht_string.h"
#include "../core/hht_list.h"
#include "../core/hash.h"

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
        if (key == NULL) {
            http_header_node->key.data = NULL;
            http_header_node->key.len = 0;
            http_header_node->key_hash = 0;
        } else {
            http_header_node->key = hht_str_setto(key, strlen(key));
            http_header_node->key_hash = hash_func(http_header_node->key.data, http_header_node->key.len);
        }
        if (value == NULL) {
            http_header_node->value.data = NULL;
            http_header_node->value.len = 0;
        } else {
            http_header_node->value = hht_str_setto(value, strlen(value));
        }
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
        http_request->headers_in_list = new_http_header_node(NULL, NULL);
        if (http_request->headers_in_list == NULL) {
            free(http_request);
            return NULL;
        }
        http_request->http_request_buf = new_str_buf();
    }

    return http_request;
}

void http_header_node_add(hht_http_request_t *http_request, unsigned char *key, unsigned char *value)
{
    hht_http_header_node_t *http_header_node = new_http_header_node(key, value);
    hht_http_header_node_t *temp_http_header_node;
    hht_str_t key_str = hht_str_setto(key, strlen(key));

    if (http_header_node != NULL) {
        temp_http_header_node = find_http_header_node_by_key(http_request, &key_str);
        if (temp_http_header_node != NULL) { /* exist key */
            temp_http_header_node->value = hht_str_setto(value, strlen(value));
            return ;
        }
        list_add_tail(&(http_request->headers_in_list->node), &(http_header_node->node));
    }
}

void http_header_node_each(hht_http_request_t *http_request, void (*handler)(void *node))
{
    hht_list_head_t *head_node = &(http_request->headers_in_list->node);
    hht_list_head_t *pos = head_node->next;
    for (; pos != head_node; pos = pos->next) {
        handler(pos);
    }
}

int fill_http_request_buf(hht_http_request_t *http_request)
{
    hht_list_head_t *head_node = &(http_request->headers_in_list->node);
    hht_list_head_t *pos = head_node->next;
    hht_http_header_node_t *http_header_node;
    hht_str_t wrap = hht_str_setto("\r\n", strlen("\r\n"));

    if (append_fstr_buf(http_request->http_request_buf, 
            "%s %s %s\r\n", 
            http_request->method.data, 
            http_request->path.data, 
            http_request->protocol.data) < 0) {
                return -1;
    }

    for (; pos != head_node; pos = pos->next) {
        http_header_node = list_entry(pos, hht_http_header_node_t, node);
        if (append_fstr_buf(http_request->http_request_buf, 
                "%s: %s\r\n", 
                http_header_node->key.data, 
                http_header_node->value.data) < 0) {
            return -1;
        }
    }
}

hht_http_header_node_t *find_http_header_node_by_key(hht_http_request_t *http_request, hht_str_t *key)
{
    hht_list_head_t *head_node = &(http_request->headers_in_list->node);
    hht_list_head_t *pos = head_node->next;
    hht_http_header_node_t *http_header_node;

    for (; pos != head_node; pos = pos->next) {
        http_header_node = list_entry(pos, hht_http_header_node_t, node);
        if (http_header_node->key_hash == hash_func(key->data, key->len)) {
            return http_header_node;
        }
    }

    return NULL;
}

hht_http_header_node_t *find_http_header_node(hht_http_request_t *http_request, hht_str_t *key, hht_str_t *value)
{
    hht_http_header_node_t *http_header_node;

    http_header_node = find_http_header_node_by_key(http_request, key);
    if (http_header_node != NULL && hht_str_eq(&(http_header_node->value), value) == 0) {
        return http_header_node;
    }

    return NULL;
}
