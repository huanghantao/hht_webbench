#ifndef __HHT_PARSE_H__
#define __HHT_PARSE_H__


#include "hht_string.h"
#include "../http/hht_http.h"

int parse_url(hht_str_t *url_str, hht_http_request_t *http_request, unsigned int *port);

#endif /* __HHT_PARSE_H__ */