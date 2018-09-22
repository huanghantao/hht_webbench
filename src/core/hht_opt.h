#ifndef __HHT_OPT_H__
#define __HHT_OPT_H__


#include "../config/hht_config.h"
#include "hht_string.h"

typedef struct hht_opt_s {
    unsigned int client_n;
    unsigned int request_n;
    hht_str_t method;
} hht_opt_t;

int hht_parse_option(int argc, char * const *argv, hht_opt_t *opt_o);

#endif /* __HHT_OPT_H__ */