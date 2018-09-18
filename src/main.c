#include <stdio.h>
#include "config/config.h"
#include "core/opt.h"
#include "core/common.h"

int main(int argc, char const *argv[])
{
    int opt = 0;
    struct opt_s opt_o = {
        .client_n = DEFAULT_CLIENT_N,
        .request_n = DEFAULT_REQUEST_N,
        .method = "GET"
    };

    if(argc == 1) {
        usage();
        return 0;
    }

    return 0;
}




