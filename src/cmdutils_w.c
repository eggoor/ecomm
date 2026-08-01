#include "pch.h"

#include <ecomm/defs.h>

int es_adapt_args(int* argc_ptr, char*** argv_ptr, int* adapted)
{
	char* argstr_flat;
	wchar_t** argv_w;
	int i, buffsize = 0, offset = 0;

	int win32_argc = 0;
	argv_w = CommandLineToArgvW(GetCommandLineW(), &win32_argc);
	if (win32_argc <= 0 || !argv_w)
		return EINVAL;

	/* determine the UTF-8 buffer size (including NULL-termination symbols) */
	for (i = 0; i < win32_argc; i++)
		buffsize += WideCharToMultiByte(CP_UTF8, 0, argv_w[i], -1,
			NULL, 0, NULL, NULL);

	char** win32_argv_utf8 = malloc(sizeof(char*) * (win32_argc + 1) + buffsize);
	if (!win32_argv_utf8) {
		LocalFree(argv_w);
		return ENOMEM;
	}

	if (adapted)
		*adapted = 1;

	argstr_flat = (char*)win32_argv_utf8 + sizeof(char*) * (win32_argc + 1);

	for (i = 0; i < win32_argc; i++) {
		win32_argv_utf8[i] = &argstr_flat[offset];
		offset += WideCharToMultiByte(CP_UTF8, 0, argv_w[i], -1,
			&argstr_flat[offset],
			buffsize - offset, NULL, NULL);
	}

	win32_argv_utf8[i] = NULL;
	LocalFree(argv_w);

	*argc_ptr = win32_argc;
	*argv_ptr = win32_argv_utf8;

	return 0;
}
