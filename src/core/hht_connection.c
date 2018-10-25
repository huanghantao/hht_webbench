#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <errno.h>
#include "hht_connection.h"
#include "hht_http.h"

hht_connection_t *new_connections(int num)
{
    hht_connection_t *connections;

    if (num <= 0) {
        printf("Error: num is less than 0\n");
        return NULL;
    }

    connections = malloc(num * sizeof(*connections));
    if (connections == NULL) {
        fprintf(stderr, "Error: malloc() error\n");
        return NULL;
    }
    return connections;
}

int init_connection(hht_connection_t *connection, hht_http_request_t *http_request)
{   
    struct addrinfo hints;
    hht_str_t key_str;
    hht_http_header_node_t *http_header_node;

    if (connection == NULL || http_request == NULL) {
        printf("Error: connection is NULL or http_request is NULL\n");
        return -1;
    }
    
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    key_str = hht_str_setto("Host", 4);
    http_header_node = find_http_header_node_by_key(http_request, &key_str);
    if (getaddrinfo(http_header_node->value.data, "http", &hints, &(connection->addr)) != 0) {
        perror("getaddrinfo() error");
        return -1;
    }

    connection->sockfd = socket(connection->addr->ai_family, connection->addr->ai_socktype, connection->addr->ai_protocol);
    if (connection->sockfd < 0) {
        perror("socket() error");
        return -1;
    }
    return 0;
}

int make_connection(hht_connection_t *connection)
{
    if (connection == NULL) {
        printf("Error: connection is NULL\n");
        return -1;
    }

    if (connect(connection->sockfd, connection->addr->ai_addr, connection->addr->ai_addrlen) != 0) {
        perror("connect() error");
        return -1;
    }

    return 0;
}