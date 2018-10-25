#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include "hht_http.h"
#include "../config/hht_config.h"
#include "hht_string.h"
#include "hht_list.h"
#include "hash.h"
#include "hht_socket.h"

static const char *http_method_strs[] = {
    "GET", "POST", "PUT", "DELETE"
};

int hht_get_method_index(hht_str_t *method_str)
{
    int i;

    if (method_str == NULL) {
        printf("Error: method_str is NULL");
        return -1;
    }

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

    http_request = (hht_http_request_t *)malloc(sizeof(*http_request));
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
    } else {
        fprintf(stderr, "Error: malloc error\n");
        exit(1);
    }

    return http_request;
}

void http_header_node_add(hht_http_request_t *http_request, unsigned char *key, unsigned char *value)
{
    hht_http_header_node_t *http_header_node;
    hht_http_header_node_t *temp_http_header_node;
    hht_str_t key_str;

    if (http_request == NULL) {
        printf("Error: http_request is NULL\n");
        return ;
    }

    key_str = hht_str_setto(key, strlen(key));
    http_header_node = new_http_header_node(key, value);
    if (http_header_node != NULL) {
        temp_http_header_node = find_http_header_node_by_key(http_request, &key_str);
        if (temp_http_header_node != NULL) { /* exist key */
            temp_http_header_node->value = hht_str_setto(value, strlen(value));
            return ;
        }
        list_add_tail(&(http_request->headers_in_list->node), &(http_header_node->node));
    }

    hht_str_free(&key_str);
}

void http_header_node_each(hht_http_request_t *http_request, void (*handler)(void *node))
{
    hht_list_head_t *head_node = &(http_request->headers_in_list->node);
    hht_list_head_t *pos = head_node->next;

    if (http_request == NULL) {
        printf("Error: http_request is NULL\n");
        return ;
    }
    
    for (; pos != head_node; pos = pos->next) {
        handler(pos);
    }
}

int fill_http_request_buf(hht_http_request_t *http_request)
{
    hht_list_head_t *head_node = &(http_request->headers_in_list->node);
    hht_list_head_t *pos = head_node->next;
    hht_http_header_node_t *http_header_node;
    hht_str_t wrap;

    if (http_request == NULL) {
        printf("Error: http_request is NULL\n");
        return -1;
    }

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
    wrap = hht_str_setto("\r\n", 2);
    append_str_buf(http_request->http_request_buf, &wrap);
    return 0;
}

hht_http_header_node_t *find_http_header_node_by_key(hht_http_request_t *http_request, hht_str_t *key)
{
    uint64_t hash;
    hht_list_head_t *head_node = &(http_request->headers_in_list->node);
    hht_list_head_t *pos = head_node->next;
    hht_http_header_node_t *http_header_node;

    if (http_request == NULL) {
        printf("Error: http_request is NULL\n");
        return NULL;
    }

    hash = hash_func(key->data, key->len);

    for (; pos != head_node; pos = pos->next) {
        http_header_node = list_entry(pos, hht_http_header_node_t, node);
        if (http_header_node->key_hash == hash) {
            return http_header_node;
        }
    }

    return NULL;
}

hht_http_header_node_t *find_http_header_node(hht_http_request_t *http_request, hht_str_t *key, hht_str_t *value)
{
    hht_http_header_node_t *http_header_node;

    if (http_request == NULL) {
        printf("Error: http_request is NULL\n");
        return NULL;
    }

    http_header_node = find_http_header_node_by_key(http_request, key);
    if (http_header_node != NULL && hht_str_eq(&(http_header_node->value), value) == 0) {
        return http_header_node;
    }

    return NULL;
}

int getip(hht_http_request_t *http_request, char *ip)
{
    hht_http_header_node_t *http_header_node;
    hht_str_t key_str;

    if (http_request == NULL) {
        printf("Error: http_request is NULL\n");
        return -1;
    }

    key_str = hht_str_setto("Host", 4);
    http_header_node = find_http_header_node_by_key(http_request, &key_str);
    if (http_header_node == NULL) {
        return -1;
    }
    if (hostname_to_ip(http_header_node->value.data, ip) < 0) {
        fprintf(stderr, "Error: hostname to ip error");
        return -1;
    }

    return 0;
}

int send_http_request(hht_http_request_t *http_request, hht_connection_t *connection)
{
    size_t bytes_sent;
    size_t bytes_to_send = http_request->http_request_buf->len;
    size_t total_bytes_sent = 0;

    if (http_request == NULL || connection == NULL) {
        printf("Error: http_request or connection is NULL\n");
        return -1;
    }

    fill_http_request_buf(http_request);

    while (1) {
        bytes_sent = send(connection->sockfd, http_request->http_request_buf->buf, http_request->http_request_buf->len, 0);
        total_bytes_sent += bytes_sent;

        if (total_bytes_sent >= bytes_to_send) {
            break;
        }
    }

    return total_bytes_sent;
}
