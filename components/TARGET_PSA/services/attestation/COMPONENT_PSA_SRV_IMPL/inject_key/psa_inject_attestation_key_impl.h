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

#ifndef __PSA_INITIAL_ATTESTATION_IMPL_H__
#define __PSA_INITIAL_ATTESTATION_IMPL_H__

#include "crypto.h"
#include <stdint.h>
#include <string.h>

#ifdef   __cplusplus
extern "C"
{
#endif

/**
 * \brief Generate or import a given key pair and export the public part in a
 *        binary format.
 *        Initial attestation key: Private key for ECDSA-P256 which is used to
 *                                 sign the initial attestation token.
 *                                 Initial attestation service supports elliptic
 *                                 curve signing algorithms.
 *                                 Device maker can decide whether store only
 *                                 the private key on the device or store both
 *                                 (public and private) key.
 *                                 Public key recomputed based on private key.
 *                                 Keys must be provided in raw format, just
 *                                 binary data without any encoding (DER, COSE).
 * 
 *                                 Attestation private key is a persistent key
 *                                 that is saved to persistent storage with
 *                                 persistent storage id = 17.
 *                                 Curve_type indicates to which curve belongs
 *                                 the key.
 *
 * \param[in] key_data      Buffer containing the private key data if given.
 *                          It must contain the format described in the
 *                          documentation of psa_export_public_key() for
 *                          the chosen type.
 *                          In case of generate the private key - NULL will pass.
 * \param key_data_length   Size of the \p data buffer in bytes - if private key
 *                          pass it must be 256 bits.     
 *                          In case of generate the private key -
 *                          key_data_length not treated.
 * \param type              Key type -  must be a ECC key type
 *                          (a \c PSA_KEY_TYPE_ECC_KEYPAIR(PSA_ECC_CURVE_XXX) value).
 * \param alg               The algorithm that the key may be used for -
 *                          must be an ECDSA algorithem.
 * \param[out] data         Buffer where the key data is to be written.
 * \param data_size         Size of the \p data buffer in bytes -  
 *                          needs to be bigger than the max size of the public part.
 * \param[out] data_length  On success, the number of bytes
 *                          that make up the key data.
 *
 * \retval #PSA_SUCCESS
 *         Success.
 * \retval #PSA_ERROR_INVALID_HANDLE
 * \retval #PSA_ERROR_OCCUPIED_SLOT
 *         There is already a key in the specified slot.
 * \retval #PSA_ERROR_NOT_SUPPORTED
 * \retval #PSA_ERROR_INVALID_ARGUMENT
 * \retval #PSA_ERROR_INSUFFICIENT_MEMORY
 * \retval #PSA_ERROR_INSUFFICIENT_ENTROPY
 * \retval #PSA_ERROR_COMMUNICATION_FAILURE
 * \retval #PSA_ERROR_HARDWARE_FAILURE
 * \retval #PSA_ERROR_TAMPERING_DETECTED
 * \retval #PSA_ERROR_BAD_STATE
 *         The library has not been previously initialized by psa_crypto_init().
 *         It is implementation-dependent whether a failure to initialize
 *         results in this error code.
 */

psa_status_t
psa_attestation_inject_key_impl( const uint8_t *key_data,
                                 size_t key_data_length,
                                 psa_key_type_t type,
                                 psa_algorithm_t alg,
                                 uint8_t *public_key_data,
                                 size_t public_key_data_size,
                                 size_t *public_key_data_length);

#ifdef   __cplusplus
}
#endif

#endif /* __PSA_INITIAL_ATTESTATION_IMPL_H__ */
