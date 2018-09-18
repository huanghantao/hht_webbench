#include <stdio.h>
#include <getopt.h>
#include <string.h>
#include <stdlib.h>
#include "config/config.h"
#include "core/opt.h"
#include "core/common.h"

int parse_option(int argc, char * const *argv, struct opt_s *opt_o);

int main(int argc, char * const *argv)
{
    struct opt_s opt_o = {
        .client_n = DEFAULT_CLIENT_N,
        .request_n = DEFAULT_REQUEST_N,
        .method = "GET"
    };

    if (parse_option(argc, argv, &opt_o) == -1) {
        exit(0);
    }

    printf("%u %u %s\n", opt_o.client_n, opt_o.request_n, opt_o.method);
    return 0;
}

int parse_option(int argc, char * const *argv, struct opt_s *opt_o) {
    int opt = 0;

    while ((opt = getopt(argc, argv, "Vhc:n:t:m:")) != -1) {
        switch (opt) {
            case 'V': printf("hht_webbench version "VERSION"\n");return 2;
            case 'h': usage();return -1;
            case 'c': opt_o->client_n = atoi(optarg);break;
            case 'n': opt_o->request_n = atoi(optarg);break;
            case 'm': 
                memcpy(opt_o->method, optarg, METHOD_LEN - 1);break;
            default: usage();return -1;
        }
    }
    if (strcmp(opt_o->method, "GET") != 0 && strcmp(opt_o->method, "POST") != 0) {
        fprintf(stderr, "The request method only supports GET and POST\n");
        usage();
        return -1;
    }
    if(optind == argc) {
        fprintf(stderr, "hht_webbench: Missing URL!\n");
        usage();
        return -1;
    }
    return 0;
}