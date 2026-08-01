/**
 * @file strutils.h
 * @brief String conversion and utility functions.
 *
 * Functions in this header provide conversion helpers between UTF-8, wide
 * strings and the ANSI code page, plus a simple ellipsize helper.
 */

#ifndef ES_STRING_UTILS_H
#define ES_STRING_UTILS_H


#include "defs.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Convert a wide (UTF-16/UTF-32) string to UTF-8.
 * @param wstr Pointer to the NUL-terminated wide string to convert.
 * @param prc Optional out parameter receiving a result code (may be NULL).
 * @return Newly allocated UTF-8 string on success (caller must free),
 *         or NULL on failure.
 */
ECOMM_API char* wstr_to_utf8(const wchar_t* const restrict_ wstr, int* prc);

/**
 * @brief Convert a UTF-8 encoded string to wide string.
 * @param str Pointer to the NUL-terminated UTF-8 string to convert.
 * @param prc Optional out parameter receiving a result code (may be NULL).
 * @return Newly allocated wide string on success (caller must free),
 *         or NULL on failure.
 */
ECOMM_API wchar_t* utf8_to_wstr(const char* const restrict_ str, int* prc);

/**
 * @brief Convert a UTF-8 string to the ANSI code page (ACP) encoding.
 * @param str Pointer to the NUL-terminated UTF-8 string to convert.
 * @param prc Optional out parameter receiving a result code (may be NULL).
 * @return Newly allocated ACP-encoded string on success (caller must free),
 *         or NULL on failure.
 */
ECOMM_API char* utf8_to_acp(const char* const restrict_ str, int* prc);

/**
 * @brief Ellipsize a source string into a destination buffer.
 *
 * If the source string does not fit into `dst` of size `dst_size`, the output
 * will be truncated and an ellipsis ("...") will be inserted where appropriate.
 *
 * @param dst Destination buffer receiving the resulting string (NUL-terminated).
 * @param dst_size Size of `dst` in bytes.
 * @param src Source NUL-terminated string.
 * @return Number of characters written (excluding terminating NUL) on success,
 *         or a negative error code on failure.
 */
ECOMM_API int es_ellipsize(char* restrict_ dst, size_t dst_size,
	const char* restrict_ src);

#ifdef __cplusplus
}
#endif

#endif /* ES_STRING_UTILS_H */
