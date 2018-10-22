#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include "hht_socket.h"

int hostname_to_ip(char *hostname, char *ip)
{
    int rv;
    int sockfd;
    struct addrinfo hints;
    struct addrinfo *servinfo;
    struct addrinfo *p;
    struct sockaddr_in *h;
 
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
 
    if ((rv = getaddrinfo(hostname, "http", &hints, &servinfo)) != 0) {
        fprintf(stderr, "Error: getaddrinfo: %s\n", gai_strerror(rv));
        return -1;
    }
 
    for(p = servinfo; p != NULL; p = p->ai_next) {
        h = (struct sockaddr_in *) p->ai_addr;
        strcpy(ip, inet_ntoa(h->sin_addr));
        return 0;
    }

    freeaddrinfo(servinfo);
    return 0;
}