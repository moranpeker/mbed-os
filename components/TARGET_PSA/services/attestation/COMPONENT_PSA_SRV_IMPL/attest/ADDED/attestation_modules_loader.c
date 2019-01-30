/*
 * Copyright (c) 2018-2019, Arm Limited. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include <stdint.h>
#include <string.h>
#include <stddef.h>
#include "tfm_plat_boot_seed.h"
#include "attestation_bootloader_data.h"
#include "tfm_attest_hal.h"

#include "psa_initial_attestation_api.h"
#include "attestation.h"

enum psa_attest_err_t attest_get_caller_client_id(int32_t *caller_id)
{
    *caller_id = 0;
    return PSA_ATTEST_ERR_SUCCESS; 
}

/*BOOT SEED IS COMMING FROM BOOTLOADER- TEMP IMPLEMENTATION*/
enum tfm_plat_err_t tfm_plat_get_boot_seed(uint32_t size, uint8_t *buf)
{
    
    memcpy(buf, temp_data, size);
    return PSA_ATTEST_ERR_SUCCESS;
}

enum tfm_plat_err_t tfm_plat_get_instance_id(uint32_t size, uint8_t *buf)
{
    memcpy(buf, temp_data, size);
    return PSA_ATTEST_ERR_SUCCESS;
}

enum tfm_plat_err_t tfm_plat_get_hw_version(uint32_t size, uint8_t *buf)
{
    memcpy(buf, temp_data, size);
    return PSA_ATTEST_ERR_SUCCESS;
}

enum tfm_plat_err_t tfm_plat_get_implementation_id(uint32_t size, uint8_t *buf)
{
    memcpy(buf, temp_data, size);
    return PSA_ATTEST_ERR_SUCCESS;
}

enum tfm_security_lifecycle_t tfm_attest_hal_get_security_lifecycle(void)
{
    return TFM_SLC_PROVISONING;
}


