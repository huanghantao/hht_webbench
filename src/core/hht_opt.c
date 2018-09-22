#include <string.h>
#include <getopt.h>
#include <stdio.h>
#include "hht_opt.h"
#include "hht_common.h"
#include "../http/hht_http.h"

int hht_parse_option(int argc, char * const *argv, hht_opt_t *opt_o)
{
    int opt = 0;

    while ((opt = getopt(argc, argv, "Vhc:n:t:m:")) != -1) {
        switch (opt) {
            case 'V': printf("hht_webbench version "VERSION"\n");return -1;
            case 'h': usage();return -1;
            case 'c': opt_o->client_n = atoi(optarg);break;
            case 'n': opt_o->request_n = atoi(optarg);break;
            case 'm': opt_o->method = hht_string_setto(optarg, strlen(optarg));break;
            default: usage();return -1;
        }
    }

    if (hht_get_method_index(&(opt_o->method)) < 0) {
        fprintf(stderr, "Error: The request method is invalid\n");
        return -1;
    }
    
    if(optind == argc) {
        fprintf(stderr, "Error: hht_webbench: Missing URL!\n");
        return -1;
    }
    return 0;
}