/*
 * Copyright (c) 2016 Fingerprint Cards AB <tech@fingerprints.com>
 *
 * All rights are reserved.
 * Proprietary and confidential.
 * Unauthorized copying of this file, via any medium is strictly prohibited.
 * Any use is subject to an appropriate license granted by Fingerprint Cards AB.
 */

#include "fpc_external.h"

/*
 * Returns the required size of buffer passed to fpc_common_init.
 *
 * @return required buffer size in bytes.
 */
uint32_t fpc_common_get_info_size(void) {
    return 64;
}

/*
 * Initialize common data used by fpc libraries,
 * buffer needs to be allocated by caller with the size returned by
 * fpc_common_get_info_size.
 *
 * @param[out] buffer, buffer to be used by fpc libraries to store common data.
 * @param[in] size of buffer. Used internally to check allocation size.
 *
 * @return 0 on success, -1 on failure.
 */
int32_t fpc_common_init(void* buffer, uint32_t* size) {
    return 0;
}

/*
 * Returns width and height of sensor.
 *
 * @param[out] width of sensor.
 * @param[out] height of sensor.
 */
void fpc_common_get_sensor_info(uint8_t* width, uint8_t* height) {
    return;
}

/*
 * Returns the size of image_t type.
 *
 * @return size of image_t type in bytes.
 */
size_t fpc_common_get_image_size(void) {
    return 0;
}

/*
 * Initialize internal fields of image_t from allocated buffer.
 *
 * The buffer passed must be allocated by the caller of size returned from
 * fpc_common_get_image_size().
 *
 * @param buffer
 * @param buffer_size
 *
 * @return 'buffer' casted to image_t
 */
image_t *fpc_common_init_default_image(void *buffer, size_t buffer_size) {
    return 0;
}

/*
 * Ask if FPC engineering interface is supported
 *
 * @return -1 if engineering is built in, no that is not a typo. -1 really.
 *          0 if engineering support is built in.
 */
int32_t fpc_common_is_engineering_supported(void) {
    return 0;
}
