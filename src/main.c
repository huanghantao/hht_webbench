#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "config/hht_config.h"
#include "core/hht_opt.h"
#include "core/hht_http.h"
#include "core/parse.h"
#include "core/hht_connection.h"
#include "core/hht_thread.h"

void handler(void *node);
void *thread_main(void *arg);

int main(int argc, char * const *argv)
{
    hht_opt_t *opt_o;
    hht_http_request_t *http_request;
    unsigned int port = DEFAULT_PORT;
    hht_connection_t *connection;
    char recv_buf[Max_BUF_SIZE];
    hht_thread_t *threads;
    hht_thread_t *t;

    http_request = new_http_request();
    http_header_node_add(http_request, "User-Agent", "Mozilla/5.0");
    http_header_node_add(http_request, "User-Agent", "Mozilla/5.1");

    opt_o = new_hht_opt();
    if (hht_parse_option(argc, argv, opt_o) < 0) {
        exit(0);
    }
    if (parse_url(opt_o->url.data, http_request) < 0) {
        exit(0);
    }
    http_request->method = hht_str_setto(opt_o->method.data, strlen(opt_o->method.data));

    connection = new_connection();
    if (init_connection(connection, http_request) < 0) {
        exit(0);
    }
    if (make_connection(connection) < 0) {
        exit(0);
    }

    threads = malloc(opt_o->threads * sizeof(*threads));
    for (int i = 0; i < opt_o->threads; i++) {
        t = &threads[i];
        t->connections = opt_o->connections / opt_o->threads;
        pthread_create(&t->thread, NULL, &thread_main, t);
    }

    for (int i = 0; i < opt_o->threads; i++) {
        t = &threads[i];
        pthread_join(t->thread, NULL);
    }

    // send_http_request(http_request, connection);
    // read(connection->sockfd, recv_buf, Max_BUF_SIZE);
    // printf("%s", recv_buf);
    
    return 0;
}

void handler(void *node)
{
    hht_http_header_node_t *http_header_node = list_entry(node, hht_http_header_node_t, node);
    write(1, http_header_node->value.data, http_header_node->value.len);
    printf("len: %zu\n", http_header_node->value.len);
}

void *thread_main(void *arg)
{
    pthread_t tid;

    tid = pthread_self();
    printf("thread id: %ld\n", (long int)tid);
}
