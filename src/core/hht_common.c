#include "hht_common.h"
#include <stdio.h>

void usage(void)
{
    fprintf(stderr,
            "hht_webbench [option] ... URL\n"
            "  -t                Total number of threads.\n"
            "  -c                Total number of HTTP connections to keep open\n"
            "  -d <sec>          Limit the maximum time for testing (unit s). Default: 10s.\n"
            "  -m                Use request method. Default: GET\n"
            "  -h                Show how the hht_webbench is used.\n"
            "  -V                Display hht_webbench version.\n"
           );
}