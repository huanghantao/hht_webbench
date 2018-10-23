#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include "hht_connection.h"
#include "hht_http.h"

hht_connection_t *new_connection(void)
{
    hht_connection_t *connection;

    connection = malloc(sizeof(*connection));
    if (connection == NULL) {
        fprintf(stderr, "Error: malloc error\n");
        return NULL;
    }
    return connection;
}

int init_connection(hht_connection_t *connection, hht_http_request_t *http_request)
{   
    struct addrinfo hints;
    hht_str_t key_str;
    hht_http_header_node_t *http_header_node;
    
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    key_str = hht_str_setto("Host", 4);
    http_header_node = find_http_header_node_by_key(http_request, &key_str);
    if (getaddrinfo(http_header_node->value.data, "http", &hints, &(connection->addr)) != 0) {
        fprintf(stderr, "Error: getaddrinfo error\n");
        return -1;
    }

    connection->sockfd = socket(connection->addr->ai_family, connection->addr->ai_socktype, connection->addr->ai_protocol);
    return 0;
}