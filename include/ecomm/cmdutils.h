/**
 * @file cmdutils.h
 * @brief Command-line argument utilities.
 *
 * Helpers to adapt or normalize argv/argc for different platforms and
 * runtime environments.
 */

#ifndef ES_CMD_UTILS_H
#define ES_CMD_UTILS_H

#include "defs.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Adapt command-line arguments for the current runtime.
 *
 * Some platforms or runtimes require transforming or normalizing the argv
 * array (for example wide-to-narrow conversions on Windows). This function
 * updates the supplied `argc_ptr`/`argv_ptr` pair if adaptation was
 * performed.
 *
 * @param argc_ptr Pointer to argc value.
 * @param argv_ptr Pointer to argv array pointer.
 * @param adapted Out parameter set to non-zero if adaptation was performed,
 *                zero otherwise.
 * @return 0 on success, non-zero on failure.
 */
int es_adapt_args(int* argc_ptr, char*** argv_ptr, int* adapted);

#ifdef __cplusplus
}
#endif

#endif /* ES_CMD_UTILS_H */
