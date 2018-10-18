#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "parse.h"
#include "../http/hht_http.h"

int parse_url(const char *url, hht_http_request_t *http_request, unsigned int *port)
{
	hht_str_t url_str = hht_str_setto((unsigned char *)url, strlen((const char *)url));
	hht_str_t key_str = hht_str_setto("Host", 4);
	hht_http_header_node_t *http_header_node;

	if (url_str.len > 7 && hht_str_eqn_cstr(&url_str, "http://", 7) == 0) {
		url_str.data += 7;
		url_str.len -= 7;
		http_header_node = find_http_header_node_by_key(http_request, &key_str);
		http_header_node->value = url_str;
	}

	return 0;
}