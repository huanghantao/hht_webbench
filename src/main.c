#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "config/hht_config.h"
#include "core/hht_opt.h"
#include "http/hht_http.h"

void handler(void *node);

int main(int argc, char * const *argv)
{
    hht_opt_t opt_o = { DEFAULT_CLIENT_N, DEFAULT_REQUEST_N, {sizeof(DEFAULT_METHOD) - 1, DEFAULT_METHOD} };
    hht_http_request_t *http_request_o;

    http_request_o = new_http_request();

    http_header_node_add(http_request_o, "Host: ", "localhost");
    http_header_node_add(http_request_o, "User-Agent: ", "Mozilla/5.0");
    http_header_node_add(http_request_o, "User-Agent: ", "Mozilla/5.1");

    if (hht_parse_option(argc, argv, &opt_o) == -1) {
        exit(0);
    }

    http_request_o->method = hht_str_setto(opt_o.method.data, strlen(opt_o.method.data));
    fill_http_request_buf(http_request_o);
    write(1, http_request_o->http_request_buf->buf, http_request_o->http_request_buf->len);

    return 0;
}

void handler(void *node)
{
    hht_http_header_node_t *http_header_node = list_entry(node, hht_http_header_node_t, node);
    write(1, http_header_node->key.data, http_header_node->key.len);
    printf("len: %zu\n", http_header_node->key.len);
}
