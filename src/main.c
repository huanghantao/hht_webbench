#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "config/hht_config.h"
#include "core/hht_opt.h"
#include "core/hht_http.h"
#include "core/parse.h"
#include "core/hht_connection.h"
#include "core/hht_thread.h"
#include "core/hht_include.h"


struct hht_thread_arg_s {
    hht_thread_t *thread;
    hht_http_request_t *http_request;
};

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
    hht_thread_arg_t *thread_args;

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

    threads = malloc(opt_o->threads * sizeof(*threads));
    if (threads == NULL) {
        printf("Error: malloc error");
        exit(0);
    }
    thread_args = malloc(sizeof(*thread_args));
    thread_args->http_request = http_request;
    for (uint64_t i = 0; i < opt_o->threads; i++) {
        t = &threads[i];
        t->connections = opt_o->connections / opt_o->threads;
        thread_args->thread = t;
        pthread_create(&t->thread, NULL, &thread_main, thread_args);
    }

    for (uint64_t i = 0; i < opt_o->threads; i++) {
        t = &threads[i];
        pthread_join(t->thread, NULL);
    }

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
    hht_thread_arg_t *thread_args;

    thread_args = arg;
    thread_args->thread->cs = new_connections(thread_args->thread->connections);
    if (thread_args->thread->cs == NULL) {
        printf("Error: new_connections error");
        pthread_exit(NULL);
    }
    for (uint64_t i = 0; i < thread_args->thread->connections; i++) {
        init_connection(&((thread_args->thread->cs)[i]), thread_args->http_request);
    }
    for (uint64_t i = 0; i < thread_args->thread->connections; i++) {
        printf("%d\n", (thread_args->thread->cs + i)->sockfd);
    }
}
