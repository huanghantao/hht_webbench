#include <stdio.h>
#include <getopt.h>
#include <string.h>
#include <stdlib.h>
#include "config/config.h"
#include "core/opt.h"
#include "core/common.h"

int main(int argc, char * const *argv)
{
    int opt = 0;
    struct opt_s opt_o = {
        .client_n = DEFAULT_CLIENT_N,
        .request_n = DEFAULT_REQUEST_N,
        .method = "GET"
    };

    while ((opt = getopt(argc, argv, "Vhc:n:t:m:")) != -1) {
        switch (opt) {
            case 'V': printf("hht_webbench version "VERSION"\n");return 2;
            case 'h': usage();return 2;
            case 'c': opt_o.client_n = atoi(optarg);break;
            case 'n': opt_o.request_n = atoi(optarg);break;
            case 'm': 
                memcpy(opt_o.method, optarg, METHOD_LEN);break;
            default: usage();return 2;
        }
    }

    if(optind == argc) {
        fprintf(stderr, "hht_webbench: missing URL!\n");
        usage();
        return 2;
    }

    printf("%u %u %s\n", opt_o.client_n, opt_o.request_n, opt_o.method);
    return 0;
}