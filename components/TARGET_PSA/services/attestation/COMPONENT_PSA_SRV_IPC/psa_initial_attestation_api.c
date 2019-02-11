/*
 * Copyright (c) 2018-2019, Arm Limited. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include "psa_initial_attestation_api.h"
#include "crypto.h"
#include "psa/client.h"
#include "attestation.h"
#include <string.h>
#include "psa_attest_srv_ifs.h"

#define MINOR_VER 1

enum psa_attest_err_t
psa_initial_attest_get_token(const uint8_t *challenge_obj,
                             uint32_t       challenge_size,
                             uint8_t       *token,
                             uint32_t      *token_size) {
    psa_status_t err_call;
    psa_handle_t handle = PSA_NULL_HANDLE;

    psa_invec in_vec[1] = { { challenge_obj, challenge_size } };
    psa_outvec out_vec[1] = { { token, *token_size } };

    handle = psa_connect(PSA_ATTEST_GET_TOKEN_ID, MINOR_VER);
    if (handle <= 0)
    {
        return (PSA_ATTEST_ERR_GENERAL);
    }

    err_call = psa_call(handle, in_vec, 1, out_vec, 1);
    psa_close(handle);

    if (err_call < 0)
    {
        err_call = PSA_ATTEST_ERR_GENERAL;
    }

    *token_size = out_vec[0].len;

    return ((enum psa_attest_err_t) err_call);
}

enum psa_attest_err_t
psa_initial_attest_get_token_size(uint32_t  challenge_size,
                                  uint32_t *token_size) {
    psa_status_t err_call;

    psa_handle_t handle = PSA_NULL_HANDLE;

    psa_invec in_vec[1] = { { &challenge_size, sizeof(uint32_t) } };
    psa_outvec out_vec[1] = { { token_size, sizeof(uint32_t) } };

    handle = psa_connect(PSA_ATTEST_GET_TOKEN_SIZE_ID, MINOR_VER);
    if (handle <= 0)
    {
        return (PSA_ATTEST_ERR_GENERAL);
    }

    err_call = psa_call(handle, in_vec, 1, out_vec, 1);
    psa_close(handle);

    if (err_call < 0)
    {
        err_call = PSA_ATTEST_ERR_GENERAL;
    }

    return ((enum psa_attest_err_t) err_call);
}
