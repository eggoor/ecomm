#include "pch.h"

#include <ecomm/strutils.h>

#include "defs.h"

int es_set_curr_thread_name(const char* restrict name)
{
    int rc;
    if (!name || !*name)
        return EINVAL;
        
    char norm_name[MAXTHREADNAMEBUFSIZ];
    if ((rc = es_ellipsize(norm_name, MAXTHREADNAMEBUFSIZ, name)) != 0)
		return rc;

	return pthread_setname_np(norm_name);
}
