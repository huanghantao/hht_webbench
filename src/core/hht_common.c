#include "hht_common.h"
#include <stdio.h>

void usage(void)
{
    fprintf(stderr,
            "hht_webbench [option] ... URL\n"
            "  -t <sec>          Limit the maximum time for testing (unit s). Default: no time limit.\n"
            "  -c                Number of clients. Default four. Default: 4\n"
            "  -n                Total number of requests for all clients. Default: 1000\n"
            "  -m                Use GET / POST request method. Default: GET\n"
            "  -h                Show how the hht_webbench is used.\n"
            "  -V                Display hht_webbench version.\n"
           );
}