#ifndef __HHT_OPT_H__
#define __HHT_OPT_H__


#include "../config/hht_config.h"
#include "hht_string.h"

typedef struct hht_opt_s {
    unsigned int client_n;
    unsigned int request_n;
    hht_str_t method;
} hht_opt_t;

hht_opt_t *new_hht_opt_t();
int hht_parse_option(int argc, char * const *argv, hht_opt_t *opt_o);
void upper_method_name(hht_str_t *str);
#endif /* __HHT_OPT_H__ */