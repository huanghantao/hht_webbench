#include <stdio.h>
#include <unistd.h>
#include "config/hht_config.h"
#include "core/hht_opt.h"
#include "http/hht_http.h"

int main(int argc, char * const *argv)
{
    hht_opt_t opt_o = { DEFAULT_CLIENT_N, DEFAULT_REQUEST_N, {DEFAULT_METHOD_LEN, "GET"} };
    hht_http_request_t http_request_o;

    if (hht_parse_option(argc, argv, &opt_o) == -1) {
        exit(0);
    }

    printf("%u %u %s\n", opt_o.client_n, opt_o.request_n, opt_o.method.data);

    hht_http_request_init(&http_request_o);
    hht_fill_http_request_buf(&http_request_o);
    write(STDOUT_FILENO, http_request_o.http_request_buf, http_request_o.len);
    return 0;
}
