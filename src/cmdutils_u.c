#include "pch.h"

int ef_adapt_args(int* argc_ptr, char*** argv_ptr, int* adapted)
{
	if (adapted)
		*adapted = 0;

	return 0;
}

char* ef_adapt_filename(const char* restrict filename, int* adapted)
{
	if (adapted)
		*adapted = 0;

	return (char*)filename;
}
