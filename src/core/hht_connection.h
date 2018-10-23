#ifndef __HHT_CONNECTION_H__
#define __HHT_CONNECTION_H__


#include "hht_string.h"
#include "hht_http.h"

typedef struct hht_connection_s {
    int sockfd;
    struct addrinfo *addr;
} hht_connection_t;

hht_connection_t *new_connection(void);
int init_connection(hht_connection_t *connection, hht_http_request_t *http_request);
int make_connection(hht_connection_t *connection);

#endif /* __HHT_CONNECTION_H__ */