#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "config/hht_config.h"
#include "core/hht_opt.h"
#include "http/hht_http.h"
#include "core/parse.h"

void handler(void *node);

int main(int argc, char * const *argv)
{
    hht_opt_t *opt_o;
    hht_http_request_t *http_request;
    unsigned int port = DEFAULT_PORT;
    char ip[MAX_IP_LEN + 1];

    http_request = new_http_request();

    http_header_node_add(http_request, "User-Agent", "Mozilla/5.0");
    http_header_node_add(http_request, "User-Agent", "Mozilla/5.1");

    opt_o = new_hht_opt();
    if (hht_parse_option(argc, argv, opt_o) < 0) {
        exit(0);
    }

    if (parse_url(argv[optind], http_request) < 0) {
        exit(0);
    }

    http_request->method = hht_str_setto(opt_o->method.data, strlen(opt_o->method.data));

    if (getip(http_request, ip) == 0) {
        printf("ip: %s\n", ip);
    }
    
    fill_http_request_buf(http_request);
    write(1, http_request->http_request_buf->buf, http_request->http_request_buf->len);

    return 0;
}

void handler(void *node)
{
    hht_http_header_node_t *http_header_node = list_entry(node, hht_http_header_node_t, node);
    write(1, http_header_node->value.data, http_header_node->value.len);
    printf("len: %zu\n", http_header_node->value.len);
}
