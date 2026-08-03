/**
 * @file file.h
 * @brief Small file utility routines (path parsing, copying, reading).
 *
 * Functions here are convenience helpers for common file operations used
 * by library clients.
 */

#ifndef ES_FILE_H
#define ES_FILE_H

#include "defs.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Extract filename component from a path.
 *
 * @param path Path string (NUL-terminated).
 * @return Pointer to the filename portion inside `path` (not a new allocation).
 *         The pointer may point inside the input string.
 */
ECOMM_API const char* es_get_filename_from_path(const char* restrict_ path);

/**
 * @brief Get the file extension from a filename.
 *
 * The returned pointer points into the provided `filename` string at the
 * extension (including the leading '.'). If no extension is present, returns
 * a pointer to the terminating NUL or NULL depending on implementation.
 *
 * @param filename NUL-terminated filename or path.
 * @return Pointer to extension inside `filename`, or NULL if none.
 */
ECOMM_API const char* es_get_file_extension(const char* restrict_ filename);

/**
 * @brief Copy a file from `src_filename` to `dst_filename`.
 *
 * @param dst_filename Destination file path.
 * @param src_filename Source file path.
 * @return 0 on success, non-zero error code on failure.
 */
ECOMM_API int es_copy_file(const char* restrict_ dst_filename,
	const char* restrict_ src_filename);

/**
 * @brief Read an entire file into a newly allocated buffer.
 *
 * The function will allocate memory for `*buffer` which the caller must free.
 *
 * @param filename Path to the file to read.
 * @param buffer Out pointer receiving allocated buffer (caller frees).
 * @param size Out parameter receiving the size of the allocated buffer.
 * @return 0 on success, non-zero error code on failure.
 */
ECOMM_API int es_file_read(const char* restrict_ filename, char* restrict_* restrict_ buffer,
	size_t* size);

/**
 * @brief Confirm if a file should be overwritten.
 *
 * @param filename Path to the file to overwrite.
 * @return 1 if confirmed, otherwise 0.
 */
ECOMM_API int es_confirm_overwrite(const char* filename);

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
/**
 * @brief Wide-character version of es_copy_file.
 *
 * @param dst_filename Destination path as wide string.
 * @param src_filename Source path as wide string.
 * @return 0 on success, non-zero error code on failure.
 */
ECOMM_API int es_copy_file_w(const wchar_t* restrict_ dst_filename,
	const wchar_t* restrict_ src_filename);

#endif /* WIN32 */

#ifdef __cplusplus
}
#endif

#endif /* ES_FILE_H */
