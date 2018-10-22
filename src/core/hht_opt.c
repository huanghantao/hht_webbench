#include <string.h>
#include <getopt.h>
#include <stdio.h>
#include <ctype.h>
#include "hht_opt.h"
#include "hht_common.h"
#include "../http/hht_http.h"
#include "parse.h"
#include "../config/hht_config.h"
#include "hht_string.h"

int hht_parse_option(int argc, char * const *argv, hht_opt_t *opt_o)
{
    int opt = 0;

    while ((opt = getopt(argc, argv, "Vhc:n:t:m:")) != -1) {
        switch (opt) {
            case 'V': printf("hht_webbench version "VERSION"\n");return -1;
            case 'h': usage();return -1;
            case 'c': opt_o->client_n = atoi(optarg);break;
            case 'n': opt_o->request_n = atoi(optarg);break;
            case 'm': opt_o->method = hht_str_setto(optarg, strlen(optarg));break;
            default: usage();return -1;
        }
    }

    if (hht_get_method_index(&(opt_o->method)) < 0) {
        fprintf(stderr, "Error: The request method is invalid\n");
        return -1;
    }

    upper_method_name(&(opt_o->method));

    if(optind == argc) {
        fprintf(stderr, "Error: hht_webbench: Missing URL!\n");
        return -1;
    }
    return 0;
}

void upper_method_name(hht_str_t *str)
{
    for (int i = 0; i < str->len; i++) {
        (str->data)[i] = toupper((str->data)[i]);
    }
}

hht_opt_t *new_hht_opt_t()
{
    hht_opt_t *opt;

    opt = malloc(sizeof(*opt));
    opt->client_n = DEFAULT_CLIENT_N;
    opt->method = hht_str_setto(DEFAULT_METHOD, strlen(DEFAULT_METHOD));
    opt->request_n = DEFAULT_REQUEST_N;

    return opt;
}