#ifndef __HHT_THREAD_H__
#define __HHT_THREAD_H__


#include <pthread.h>
#include <stdint.h>

struct hht_thread_s {
    pthread_t thread;
    uint64_t connections;
    uint64_t complete;
    uint64_t requests;
    uint64_t start;
};

#endif /* __HHT_THREAD_H__ */