#include "common.h"
#include <stdio.h>

void usage(void)
{
    fprintf(stderr,
            "hht_webbench [option] ... URL\n"
            "  -t <sec>          Limit the maximum time for testing (unit s). There is no time limit by default.\n"
            "  -c                Number of clients. Default four.\n"
            "  --get             Use GET request method.\n"
            "  -?|-h|--help      Show how the hht_webbench is used.\n"
            "  -V|--version      Display hht_webbench version.\n"
           );
}