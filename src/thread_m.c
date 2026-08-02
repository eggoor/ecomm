#include "pch.h"

int es_set_current_thread_name(const char* restrict name)
{
    if (!name || !*name)
        return EINVAL;

	return pthread_setname_np(name);
}
