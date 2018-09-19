#include <stdio.h>
#include <getopt.h>
#include <string.h>
#include <stdlib.h>
#include "config/hht_config.h"
#include "core/hht_opt.h"
#include "core/hht_common.h"
#include "core/hht_string.h"

int hht_parse_option(int argc, char * const *argv, struct hht_opt_s *opt_o);

int main(int argc, char * const *argv)
{
    struct hht_opt_s opt_o = { DEFAULT_CLIENT_N, DEFAULT_REQUEST_N, {GET_METHOD_LEN, "GET"} };

    if (hht_parse_option(argc, argv, &opt_o) == -1) {
        exit(0);
    }

    printf("%u %u %s\n", opt_o.client_n, opt_o.request_n, opt_o.method.data);
    return 0;
}

int hht_parse_option(int argc, char * const *argv, struct hht_opt_s *opt_o)
{
    int opt = 0;
    hht_str_t tmp_s1 = hht_string("GET");
    hht_str_t tmp_s2 = hht_string("POST");

    while ((opt = getopt(argc, argv, "Vhc:n:t:m:")) != -1) {
        switch (opt) {
            case 'V': printf("hht_webbench version "VERSION"\n");return -1;
            case 'h': usage();return -1;
            case 'c': opt_o->client_n = atoi(optarg);break;
            case 'n': opt_o->request_n = atoi(optarg);break;
            case 'm': opt_o->method = string_setto(optarg, strlen(optarg));break;
            default: usage();return -1;
        }
    }
    if (string_eq(&(opt_o->method), &(tmp_s1)) != 0 && string_eq(&(opt_o->method), &(tmp_s2)) != 0) {
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