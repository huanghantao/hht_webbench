#ifndef __HHT_CONNECTION_H__
#define __HHT_CONNECTION_H__


#include "hht_string.h"

typedef struct hht_connection_s {
    int sockfd;
    hht_str_t hostname;
    hht_str_t ip;
    hht_str_t port;
    struct addrinfo *addr;
} hht_connection_t;

#endif /* __HHT_CONNECTION_H__ */