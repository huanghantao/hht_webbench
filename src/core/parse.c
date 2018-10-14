#include <stdio.h>
#include <unistd.h>
#include "parse.h"
#include "../http/hht_http.h"

int parse_url(hht_str_t *url_str, hht_http_request_t *http_request, unsigned int *port)
{
    hht_str_t *tmp_url = url_str;

	if (url_str->len > 7 && hht_str_eqn_cstr(url_str, "http://", 7) == 0) {
		tmp_url->data += 7;
	}

    write(1, tmp_url->data, tmp_url->len - 7);
	
	return 0;
}