#include <stdio.h>
#include <getopt.h>
#include <string.h>
#include <stdlib.h>
#include "config/hht_config.h"
#include "core/hht_opt.h"
#include "core/hht_common.h"

int hht_parse_option(int argc, char * const *argv, struct hht_opt_s *opt_o);

int main(int argc, char * const *argv)
{
    struct hht_opt_s opt_o = {DEFAULT_CLIENT_N, DEFAULT_REQUEST_N, "GET"};

    if (hht_parse_option(argc, argv, &opt_o) == -1) {
        exit(0);
    }

    printf("%u %u %s\n", opt_o.client_n, opt_o.request_n, opt_o.method);
    return 0;
}

int hht_parse_option(int argc, char * const *argv, struct hht_opt_s *opt_o)
{
    int opt = 0;

    while ((opt = getopt(argc, argv, "Vhc:n:t:m:")) != -1) {
        switch (opt) {
            case 'V': printf("hht_webbench version "VERSION"\n");return -1;
            case 'h': usage();return -1;
            case 'c': opt_o->client_n = atoi(optarg);break;
            case 'n': opt_o->request_n = atoi(optarg);break;
            case 'm': 
                    memcpy(opt_o->method, optarg, MAX_METHOD_LEN);
                    (opt_o->method)[MAX_METHOD_LEN] = 0;break;
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