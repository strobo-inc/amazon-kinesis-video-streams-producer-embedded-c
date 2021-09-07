/*
 * Copyright 2021 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License").
 * You may not use this file except in compliance with the License.
 * A copy of the License is located at
 *
 *  http://aws.amazon.com/apache2.0
 *
 * or in the "license" file accompanying this file. This file is distributed
 * on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied. See the License for the specific language governing
 * permissions and limitations under the License.
 */

#ifndef SAMPLE_CONFIG_H
#define SAMPLE_CONFIG_H

#include "kvs/mkv_generator.h"

/* KVS general configuration */
#define AWS_ACCESS_KEY                  "xxxxxxxxxxxxxxxxxxxx"
#define AWS_SECRET_KEY                  "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"

/* KVS stream configuration */
#define KVS_STREAM_NAME                 "kvs_example_camera_stream"
#define AWS_KVS_REGION                  "us-east-1"
#define AWS_KVS_SERVICE                 "kinesisvideo"
#define AWS_KVS_HOST                    AWS_KVS_SERVICE "." AWS_KVS_REGION ".amazonaws.com"

/* KVS optional configuration */
#define ENABLE_AUDIO_TRACK              1
#define ENABLE_IOT_CREDENTIAL           0
#define ENABLE_RING_BUFFER_MEM_LIMIT    1

#define VIDEO_CODEC_NAME                "V_MPEG4/ISO/AVC"
#define VIDEO_TRACK_NAME                "kvs video track"

/* Audio configuration */
#if ENABLE_AUDIO_TRACK
#define AUDIO_CODEC_NAME                "A_AAC"
#define AUDIO_TRACK_NAME                "kvs audio track"
#define AUDIO_MPEG_OBJECT_TYPE          AAC_LC
#define AUDIO_FREQUENCY                 16000
#define AUDIO_CHANNEL_NUMBER            2
#endif /* ENABLE_AUDIO_TRACK */

/* IoT credential configuration */
#if ENABLE_IOT_CREDENTIAL
#define CREDENTIALS_HOST                "xxxxxxxxxxxxxx.credentials.iot.us-east-1.amazonaws.com"
#define ROLE_ALIAS                      "KvsCameraIoTRoleAlias"
#define THING_NAME                      KVS_STREAM_NAME

#define ROOT_CA \
"-----BEGIN CERTIFICATE-----\n" \
"......\n" \
"-----END CERTIFICATE-----\n"

#define CERTIFICATE \
"-----BEGIN CERTIFICATE-----\n" \
"......\n" \
"-----END CERTIFICATE-----\n"

#define PRIVATE_KEY \
"-----BEGIN RSA PRIVATE KEY-----\n" \
"......\n" \
"-----END RSA PRIVATE KEY-----\n"
#endif

#if ENABLE_RING_BUFFER_MEM_LIMIT
/* Buffering options */
#define RING_BUFFER_MEM_LIMIT           (2 * 1024 * 1024)
#endif /* ENABLE_RING_BUFFER_MEM_LIMIT */

#ifdef KVS_USE_POOL_ALLOCATOR

/**
 * KVS LIB and its 3rd party dependencies use 48K bytes which is measured on RPi. Make it 128K for safety.
 */
#define POOL_ALLOCATOR_SIZE_FOR_KVS     (128 * 1024)

/**
 * This sample use 1M measured on T31. Make it 1.5M for safety. Please increase it depends on real application.
 */
#define POOL_ALLOCATOR_SIZE_FOR_APP     (1536 * 1024)

/**
 * Get the size of stream buffer.  If there is no buffer limit, then assume it's 2M bytes.
 */
#ifdef ENABLE_RING_BUFFER_MEM_LIMIT
#define BUFFER_MEM_LIMIT        RING_BUFFER_MEM_LIMIT
#else
#define BUFFER_MEM_LIMIT        (2 * 1024 * 1024)
#endif

/**
 * Total size for pool equals the sum of KVS and its libraries usage, the stream buffer usage, and application usage.
 */
#define POOL_ALLOCATOR_SIZE     (BUFFER_MEM_LIMIT + POOL_ALLOCATOR_SIZE_FOR_KVS + POOL_ALLOCATOR_SIZE_FOR_APP)

#endif /* KVS_USE_POOL_ALLOCATOR */

#endif /* SAMPLE_CONFIG_H */
