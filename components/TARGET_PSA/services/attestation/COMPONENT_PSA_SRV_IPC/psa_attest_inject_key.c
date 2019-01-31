/*
 * Copyright (c) 2018-2019, Arm Limited. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include "psa_attest_inject_key.h"
#include "psa_attest_platform_spe.h"
#include "crypto.h"
#include "psa_defs.h"
#include "spm_client.h"

#define MINOR_VER 1

psa_status_t
psa_attestation_inject_key(const uint8_t *key_data,
                           size_t key_data_length,
                           psa_key_type_t type,
                           psa_algorithm_t alg,
                           uint8_t *public_key_data,
                           size_t public_key_data_size,
                           size_t *public_key_data_length)
{
    psa_handle_t handle = PSA_NULL_HANDLE;    
    psa_error_t call_error = PSA_SUCCESS;
    psa_attest_ipc_inject_t psa_attest_ipc = { 0, 0 };
    psa_invec_t in_vec[2];
    psa_outvec_t out_vec[2];

    psa_attest_ipc.type = type;
    psa_attest_ipc.alg = alg;

    in_vec[0] = (psa_invec_t) {
        &psa_attest_ipc,
        sizeof(psa_attest_ipc_inject_t)
    };
    in_vec[1] = (psa_invec_t) {
        key_data, key_data_length
    };
    out_vec[0] = (psa_outvec_t) {
        public_key_data, public_key_data_size
    };
    out_vec[1] = (psa_outvec_t) {
        public_key_data_length, sizeof(*public_key_data_length)
    };

    handle = psa_connect(PSA_ATTEST_INJECT_KEY_ID, MINOR_VER);
    if (handle <= 0) {
        return (PSA_ERROR_COMMUNICATION_FAILURE);
    }

    call_error = psa_call(handle, in_vec, 2, out_vec, 2);

    psa_close(handle);

    if (call_error < 0) {
        call_error = (psa_error_t) PSA_ERROR_COMMUNICATION_FAILURE;
    }
    return ((psa_status_t)call_error);
}
