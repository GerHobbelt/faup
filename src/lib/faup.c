/*
 * DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE 
 * Version 2, December 2004 
 *
 * Copyright (C) 2012-2013 Sebastien Tricaud <sebastien@honeynet.org> 
 *
 * Everyone is permitted to copy and distribute verbatim or modified 
 * copies of this license document, and changing it is allowed as long 
 * as the name is changed. 
 *
 * DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE 
 * TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION 
 *
 *  0. You just DO WHAT THE FUCK YOU WANT TO.
 */

#include <faup/faup.h>
#ifdef FAUP_LUA_MODULES
#include <faup/modules.h>
#endif


#include <stdlib.h>

faup_handler_t *faup_init(faup_options_t *options)
{
    faup_handler_t *fh;
    int retval;

    fh = malloc(sizeof(faup_handler_t));
    if (!fh) {
      fprintf(stderr, "Could not allocate a faup_handler_t\n");
      return NULL;
    }
    fh->options_handled_externally = options?1:0;
    fh->faup.decoded = false;
    fh->faup.url_type = FAUP_URL_HAS_NO_TLD;
    memset(&fh->faup.features, 0, sizeof(fh->faup.features));

    if (options) {
        fh->options = options;
    } else {
        fh->options = faup_options_new();
    }
#ifdef FAUP_LUA_MODULES
    retval = faup_modules_new(fh);
#endif

	return fh;
}

// reload the TLD tree from the file on disk
// useful if you have an external process fetching new copies from
// https://publicsuffix.org/ and need faup to notice
void faup_reload_tld_mozilla_list(faup_handler_t *fh)
{

	faup_tld_tree_free(fh->options->tld_tree, NULL, 0);
	fh->options->tld_tree = faup_tld_tree_new();
}

char *faup_get_version(void)
{
  return FAUP_VERSION;
}

void faup_terminate(faup_handler_t *fh)
{
#ifdef FAUP_LUA_MODULES
    faup_modules_terminate(fh->modules);
#endif
    if (!fh->options_handled_externally) {
	    if (fh->options) {
		    faup_options_free(fh->options);
	    }
    }
    free(fh);
}

int32_t faup_get_scheme_pos(faup_handler_t *fh)
{
        return faup_get_pos(fh, scheme);
}

uint32_t faup_get_scheme_size(faup_handler_t *fh)
{
        return faup_get_size(fh, scheme);
}

int32_t faup_get_credential_pos(faup_handler_t *fh)
{
        return faup_get_pos(fh, credential);
}

uint32_t faup_get_credential_size(faup_handler_t *fh)
{
        return faup_get_size(fh, credential);
}

int32_t faup_get_subdomain_pos(faup_handler_t *fh)
{
        return faup_get_pos(fh, subdomain);
}

uint32_t faup_get_subdomain_size(faup_handler_t *fh)
{
        return faup_get_size(fh, subdomain);
}

int32_t faup_get_domain_pos(faup_handler_t *fh)
{
        return faup_get_pos(fh, domain);
}

uint32_t faup_get_domain_size(faup_handler_t *fh)
{
        return faup_get_size(fh, domain);
}

int32_t faup_get_domain_without_tld_pos(faup_handler_t *fh)
{
        return faup_get_pos(fh, domain_without_tld);
}

uint32_t faup_get_domain_without_tld_size(faup_handler_t *fh)
{
        return faup_get_size(fh, domain_without_tld);
}

int32_t faup_get_host_pos(faup_handler_t *fh)
{
        return faup_get_pos(fh, host);
}

uint32_t faup_get_host_size(faup_handler_t *fh)
{
        return faup_get_size(fh, host);
}

int32_t faup_get_tld_pos(faup_handler_t *fh)
{
        return faup_get_pos(fh, tld);
}

uint32_t faup_get_tld_size(faup_handler_t *fh)
{
        return faup_get_size(fh, tld);
}

int32_t faup_get_port_pos(faup_handler_t *fh)
{
        return faup_get_pos(fh, port);
}

uint32_t faup_get_port_size(faup_handler_t *fh)
{
        return faup_get_size(fh, port);
}

int32_t faup_get_resource_path_pos(faup_handler_t *fh)
{
        return faup_get_pos(fh, resource_path);
}

uint32_t faup_get_resource_path_size(faup_handler_t *fh)
{
        return faup_get_size(fh, resource_path);
}

int32_t faup_get_query_string_pos(faup_handler_t *fh)
{
        return faup_get_pos(fh, query_string);
}

uint32_t faup_get_query_string_size(faup_handler_t *fh)
{
        return faup_get_size(fh, query_string);
}

int32_t faup_get_fragment_pos(faup_handler_t *fh)
{
        return faup_get_pos(fh, fragment);
}

uint32_t faup_get_fragment_size(faup_handler_t *fh)
{
        return faup_get_size(fh, fragment);
}

