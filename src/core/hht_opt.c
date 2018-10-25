#include <string.h>
#include <getopt.h>
#include <stdio.h>
#include <ctype.h>
#include <stdint.h>
#include <inttypes.h>
#include "hht_opt.h"
#include "hht_common.h"
#include "hht_http.h"
#include "parse.h"
#include "../config/hht_config.h"
#include "hht_string.h"

int hht_parse_option(int argc, char * const *argv, hht_opt_t *opt_o)
{
    int opt = 0;

    if (opt_o == NULL) {
        printf("Error: opt_o is NULL\n");
        return -1;

    }

    while ((opt = getopt(argc, argv, "Vht:c:d:m:")) != -1) {
        switch (opt) {
            case 'V': printf("hht_webbench version "VERSION"\n");return -1;
            case 'h': usage();return -1;
            case 't': opt_o->threads = atoi(optarg);break;
            case 'c': opt_o->connections = atoi(optarg);break;
            case 'd': opt_o->duration = atoi(optarg);break;
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
        fprintf(stderr, "Error: miss URL\n");
        return -1;
    }
    opt_o->url = hht_str_setto(argv[argc - 1], strlen(argv[argc - 1]));

    return 0;
}

void upper_method_name(hht_str_t *str)
{
    for (int i = 0; i < str->len; i++) {
        (str->data)[i] = toupper((str->data)[i]);
    }
}

hht_opt_t *new_hht_opt()
{
    hht_opt_t *opt;

    opt = malloc(sizeof(*opt));
    if (opt == NULL) {
        fprintf(stderr, "Error: malloc error\n");
        exit(1);
    }
    opt->threads = DEFAULT_THREADS_N;
    opt->connections = DEFAULT_CONNECTIONS_N;
    opt->duration = DEFAULT_DURATION;
    opt->url = hht_str_setto(DEFAULT_URL, strlen(DEFAULT_URL));
    opt->method = hht_str_setto(DEFAULT_METHOD, strlen(DEFAULT_METHOD));

    return opt;
}

void print_opts(hht_opt_t *opt_o)
{
    if (opt_o == NULL) {
        printf("Error: opt_o is NULL\n");
        return ;
    }
    printf("connections: %" PRIu64 "\n", opt_o->connections);
    printf("duration: %" PRIu64 "s\n", opt_o->duration);
    printf("threads: %" PRIu64 "\n", opt_o->threads);
    printf("method: %s\n", opt_o->method.data);
    printf("url: %s\n", opt_o->url.data);
}