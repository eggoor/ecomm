#pragma once

#include "defs.h"

#ifdef __cplusplus
extern "C" {
#endif

ECOMM_API char* wstr_to_utf8(const wchar_t* const restrict_ wstr, int* prc);

ECOMM_API wchar_t* utf8_to_wstr(const char* const restrict_ str, int* prc);

ECOMM_API char* utf8_to_acp(const char* const restrict_ str, int* prc);

ECOMM_API int es_ellipsize(char* restrict_ dst, size_t dst_size,
	const char* restrict_ src);

#ifdef __cplusplus
}
#endif
