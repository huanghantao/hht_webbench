#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "parse.h"
#include "../http/hht_http.h"

int parse_url(const char *url, hht_http_request_t *http_request, unsigned int *port)
{
	hht_str_t url_str = hht_str_setto((unsigned char *)url, strlen((const char *)url));
	hht_str_t key_str = hht_str_setto("Host", 4);
	hht_str_t host_str;
	hht_http_header_node_t *http_header_node;
	unsigned char *pos1;
	unsigned char *pos2;

	if (url_str.len < 7 || hht_str_eqn_cstr(&url_str, "http://", 7) != 0) {
		printf("Please input the correct http protocol\n");
		return -1;
	}

	url_str.data += 7;
	url_str.len -= 7;

	if ((pos1 = hht_strchr(&url_str, '/')) == NULL) {
		printf("Path is required\n");
		return -1;
	}

	if ((pos2 = hht_strchr(&url_str, ':')) != NULL) {
		host_str = hht_str_setto(url_str.data, pos2 - url_str.data);
	} else {
		host_str = hht_str_setto(url_str.data, pos1 - url_str.data);
	}

	http_header_node = find_http_header_node_by_key(http_request, &key_str);
	http_header_node->value = hht_str_setto(host_str.data, host_str.len);

	hht_str_free(&url_str);
	hht_str_free(&key_str);
	hht_str_free(&host_str);

	return 0;
}