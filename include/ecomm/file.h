#pragma once

#include "defs.h"

#ifdef __cplusplus
extern "C" {
#endif

ECOMM_API const char* es_get_filename_from_path(const char* restrict_ path);

ECOMM_API const char* es_get_file_extension(const char* restrict_ filename);

ECOMM_API int es_copy_file(const char* restrict_ dst_filename,
	const char* restrict_ src_filename);

ECOMM_API int es_copy_file_w(const wchar_t* restrict_ dst_filename,
	const wchar_t* restrict_ src_filename);

ECOMM_API int es_file_read(const char* restrict_ filename, char* restrict_* restrict_ buffer,
	size_t* size);

#ifdef __cplusplus
}
#endif
