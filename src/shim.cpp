#include <stdio.h>
#include <stdlib.h>

#include <dlfcn.h>

#include <vector>
#include <string>
#include <regex>
#include <algorithm>

#include "include/capi/cef_urlrequest_capi.h"
#include "include/capi/cef_request_capi.h"

#ifdef DEBUG
#define debug(fmt, args...) printf("[SHIM] " fmt, ## args)
#else
#define debug(fmt, args...)
#endif

std::regex r(".*i.scdn.co/image.*");

extern "C" {

cef_urlrequest_t* cef_urlrequest_create(
    struct _cef_request_t* request,
    struct _cef_urlrequest_client_t* client,
    struct _cef_request_context_t* request_context);

}

cef_urlrequest_t* cef_urlrequest_create(
    struct _cef_request_t* request,
    struct _cef_urlrequest_client_t* client,
    struct _cef_request_context_t* request_context) {

    typedef cef_urlrequest_t*(*cef_urlrequest_create_t)(struct _cef_request_t*, struct _cef_urlrequest_client_t*, struct _cef_request_context_t*);
    cef_urlrequest_create_t real_cef_urlrequest_create = nullptr;

    real_cef_urlrequest_create = (cef_urlrequest_create_t)dlsym(RTLD_NEXT, "cef_urlrequest_create");

    cef_string_userfree_utf16_t url_utf16 = request->get_url(request);
    cef_string_utf8_t url_utf8 = {};
    cef_string_utf16_to_utf8(url_utf16->str, url_utf16->length, &url_utf8);

    debug("%s\n", url_utf8.str);

    if (std::regex_match(std::string(url_utf8.str), r)) {
        debug("ICON URL FOUND\n");

        char url[] = "https://cataas.com/cat";
        cef_string_t cef_url = {};
        cef_string_utf8_to_utf16(url, strlen(url), &cef_url);

        cef_string_multimap_t mulmap = cef_string_multimap_alloc();

        cef_string_utf8_t key = {};
        cef_string_utf8_set("accept", 6, &key, false);

        cef_string_utf8_t value = {};
        cef_string_utf8_set("image/jpeg", 10, &value, false);

        request->set_url(request, &cef_url);
        request->set_header_map(request, mulmap);
        request->set_post_data(request, nullptr);

        cef_string_multimap_free(mulmap);
    }

    cef_string_userfree_utf16_free(url_utf16);
    return real_cef_urlrequest_create(request, client, request_context);
}

