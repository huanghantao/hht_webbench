#ifndef __HHT_OPT_H__
#define __HHT_OPT_H__


#include "../config/hht_config.h"

struct hht_opt_s {
    unsigned int client_n;
    unsigned int request_n;
    char method[MAX_METHOD_LEN + 1];
};

#endif /* __HHT_OPT_H__ */