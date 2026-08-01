#pragma once

#ifdef __cplusplus
#define restrict_
#else
#define restrict_ restrict
#endif

#define ES_MIN(a, b) ((a) < (b) ? (a) : (b))

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
