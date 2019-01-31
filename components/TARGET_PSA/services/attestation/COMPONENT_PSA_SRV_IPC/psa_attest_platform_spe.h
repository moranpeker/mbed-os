/*
 * Copyright (c) 2018-2019, Arm Limited. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

/***************************************************************************/
/*                             DRAFT UNDER REVIEW                          */
/*   These APIs are still evolving and are meant as a prototype for review.*/
/*   The APIs will change depending on feedback and will be firmed up      */
/*   to a stable set of APIs once all the feedback has been considered.    */
/***************************************************************************/

#ifndef __PSA_ATTEST_PLATFORM_SPE_H__
#define __PSA_ATTEST_PLATFORM_SPE_H__

#include "crypto.h"
#include <stdint.h>
#include <string.h>

#ifdef   __cplusplus
extern "C"
{
#endif

/** psa_crypto_ipc_asymmetric_s struct used for asymmetric
 * PSA Crypto APIs that need psa_key_slot_t and psa_algorithm_t arguments
 * and in order to use the existing infrastructure of the SPM-IPC we provide a struct to
 * pack them together.
 */
typedef struct psa_attest_ipc_inject_s {
    psa_key_type_t type;
    psa_algorithm_t alg;
} psa_attest_ipc_inject_t;


#ifdef   __cplusplus
}
#endif

#endif /* __PSA_ATTEST_PLATFORM_SPE_H__ */
