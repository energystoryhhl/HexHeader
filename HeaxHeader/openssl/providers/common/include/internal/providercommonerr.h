/*
 * Generated by util/mkerr.pl DO NOT EDIT
 * Copyright 1995-2019 The OpenSSL Project Authors. All Rights Reserved.
 *
 * Licensed under the Apache License 2.0 (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://www.openssl.org/source/license.html
 */

#ifndef HEADER_PROVERR_H
# define HEADER_PROVERR_H

# include <openssl/opensslconf.h>
# include <openssl/symhacks.h>


# ifdef  __cplusplus
extern "C"
# endif
int ERR_load_PROV_strings(void);

/*
 * PROV function codes.
 */
# if !OPENSSL_API_3
#  define PROV_F_AESNI_INIT_KEY                            0
#  define PROV_F_AES_BLOCK_FINAL                           0
#  define PROV_F_AES_BLOCK_UPDATE                          0
#  define PROV_F_AES_CIPHER                                0
#  define PROV_F_AES_DINIT                                 0
#  define PROV_F_AES_DUPCTX                                0
#  define PROV_F_AES_EINIT                                 0
#  define PROV_F_AES_GET_CTX_PARAMS                        0
#  define PROV_F_AES_INIT_KEY                              0
#  define PROV_F_AES_SET_CTX_PARAMS                        0
#  define PROV_F_AES_STREAM_UPDATE                         0
#  define PROV_F_AES_T4_INIT_KEY                           0
#  define PROV_F_BLAKE2_MAC_INIT                           0
#  define PROV_F_BLAKE2_MAC_SET_PARAMS                     0
#  define PROV_F_GMAC_SET_PARAMS                           0
#  define PROV_F_KMAC_SET_PARAMS                           0
#  define PROV_F_POLY1305_SET_PARAMS                       0
#  define PROV_F_PROV_AES_KEY_GENERIC_INIT                 0
#  define PROV_F_TRAILINGDATA                              0
#  define PROV_F_UNPADBLOCK                                0
# endif

/*
 * PROV reason codes.
 */
# define PROV_R_AES_KEY_SETUP_FAILED                      101
# define PROV_R_BAD_DECRYPT                               100
# define PROV_R_CIPHER_OPERATION_FAILED                   102
# define PROV_R_FAILED_TO_GET_PARAMETER                   103
# define PROV_R_FAILED_TO_SET_PARAMETER                   104
# define PROV_R_INVALID_AAD                               108
# define PROV_R_INVALID_CUSTOM_LENGTH                     111
# define PROV_R_INVALID_DATA                              115
# define PROV_R_INVALID_IVLEN                             116
# define PROV_R_INVALID_IV_LENGTH                         109
# define PROV_R_INVALID_KEYLEN                            117
# define PROV_R_INVALID_KEY_LENGTH                        105
# define PROV_R_INVALID_SALT_LENGTH                       112
# define PROV_R_INVALID_TAG                               110
# define PROV_R_INVALID_TAGLEN                            118
# define PROV_R_NOT_XOF_OR_INVALID_LENGTH                 113
# define PROV_R_NO_KEY_SET                                114
# define PROV_R_OUTPUT_BUFFER_TOO_SMALL                   106
# define PROV_R_TAG_NOTSET                                119
# define PROV_R_TAG_NOT_NEEDED                            120
# define PROV_R_WRONG_FINAL_BLOCK_LENGTH                  107

#endif
