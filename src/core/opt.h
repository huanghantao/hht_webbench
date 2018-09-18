#ifndef __OPT_H__
#define __OPT_H__

#include "../config/config.h"

struct opt_s {
    unsigned int client_n;
    unsigned int request_n;
    char method[DEFAULT_CLIENT_N];
};

#endif /* __OPT_H__ */