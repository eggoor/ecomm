/**
 * @file defs.h
 * @brief Common macro definitions and export helpers for the ecomm library.
 *
 * This header declares small portability and utility macros used across the
 * public API of the library:
 *  - `restrict_` � portability wrapper for `restrict`.
 *  - `ES_MIN` � small min macro.
 *  - `ECOMM_API` � DLL-export/import macro for Windows builds.
 *
 * These macros are intended for public consumption by library users.
 */

#ifndef ES_DEFINITIONS_H
#define ES_DEFINITIONS_H

#ifdef __cplusplus
#define restrict_
#else
#define restrict_ restrict
#endif

/**
 * @def ECOMM_API
 * @brief Export/import macro for the ecomm public API.
 *
 * On Windows this expands to `__declspec(dllexport)` when building the
 * library and `__declspec(dllimport)` when using the shared library. On
 * other platforms it is empty.
 */
#if defined(_WIN32) || defined(__CYGWIN__)
  #ifdef ECOMM_BUILD_SHARED
    #define ECOMM_API __declspec(dllexport)
  #elif defined(ECOMM_USE_SHARED)
    #define ECOMM_API __declspec(dllimport)
  #else
    #define ECOMM_API
  #endif
#else
  #define ECOMM_API
#endif

#endif /* ES_DEFINITIONS_H */
