#ifndef __HHT_OPT_H__
#define __HHT_OPT_H__


#include "../config/hht_config.h"
#include "hht_string.h"

struct hht_opt_s {
    unsigned int client_n;
    unsigned int request_n;
    hht_str_t method;
};

#endif /* __HHT_OPT_H__ */