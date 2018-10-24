#ifndef __HHT_OPT_H__
#define __HHT_OPT_H__


#include <stdint.h>
#include "../config/hht_config.h"
#include "hht_string.h"
#include "hht_include.h"

struct hht_opt_s {
    uint64_t threads;
    uint64_t connections;
    uint64_t duration;
    hht_str_t method;
    hht_str_t url;
};

hht_opt_t *new_hht_opt();
int hht_parse_option(int argc, char * const *argv, hht_opt_t *opt_o);
void upper_method_name(hht_str_t *str);
void print_opts(hht_opt_t *opt_o);
#endif /* __HHT_OPT_H__ */