/*
 * Copyright (c) 2018-2019, Arm Limited. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include <stdint.h>
#include <string.h>
#include "attestation.h"
#include "attestation_bootloader_data.h"
#include "tfm_boot_status.h"

enum psa_attest_err_t
attest_get_boot_data(uint8_t major_type, void *ptr, uint32_t len)
{
    // uint8_t *buf_start = ptr;
    struct shared_data_tlv_header *tlv_header;
    struct shared_data_tlv_entry *tlv_entry;
    uintptr_t tlv_end, offset;

    /* Get the boundaries of TLV section */
    tlv_header = (struct shared_data_tlv_header *)BOOT_TFM_SHARED_DATA_BASE;
    if (tlv_header->tlv_magic != SHARED_DATA_TLV_INFO_MAGIC)
    {
        return PSA_ATTEST_ERR_INIT_FAILED;
    }
    tlv_end = (uintptr_t)BOOT_TFM_SHARED_DATA_BASE + (uintptr_t)tlv_header->tlv_tot_len;
    offset  = (uintptr_t)BOOT_TFM_SHARED_DATA_BASE + (uintptr_t)SHARED_DATA_HEADER_SIZE;

    /* Add header to output buffer as well */
    if (len < SHARED_DATA_HEADER_SIZE)
    {
        return PSA_ATTEST_ERR_INIT_FAILED;        
    } else {
        memcpy(ptr, tlv_header, SHARED_DATA_HEADER_SIZE);
        ptr += SHARED_DATA_HEADER_SIZE;
    }

    /* Iterates over the TLV section and copy TLVs with requested major
     * type to the provided buffer.
     */
    for(; offset < tlv_end; offset += tlv_entry->tlv_len)
    {
        tlv_entry = (struct shared_data_tlv_entry *)offset;
        if (GET_MAJOR(tlv_entry->tlv_type) == major_type)
        {
            memcpy(ptr, (const void *)tlv_entry, tlv_entry->tlv_len);
            ptr += tlv_entry->tlv_len;
            tlv_header->tlv_tot_len += tlv_entry->tlv_len;
        }
    }
    return PSA_ATTEST_ERR_SUCCESS;
}