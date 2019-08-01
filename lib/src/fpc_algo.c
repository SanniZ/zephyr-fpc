/*
 * Copyright (c) 2016 Fingerprint Cards AB <tech@fingerprints.com>
 *
 * All rights are reserved.
 * Proprietary and confidential.
 * Unauthorized copying of this file, via any medium is strictly prohibited.
 * Any use is subject to an appropriate license granted by Fingerprint Cards AB.
 */


#include "fpc_algo.h"


/*
 * Get size and initialize memory for this instance.
 *
 * Call this function twice, first with context as NULL to get the required size
 * of context. After this its up to the caller of this function to allocate
 * the requsted memory of size returned in the context_size parameter.
 *
 * Then call this function again with context pointing to a
 * buffer of requested size.
 *
 * @param[in] context, NULL to get required size of context.
 *                     Or buffer of requsted size.
 *
 * @param[out] required size of context allocation in bytes.
 *
 * @return FPC_RESULT_OK
 *         FPC_RESULT_ERROR_MEMORY - if context is null,
 *                                 this is expected on first call to function.
 *         FPC_RESULT_PARAMETER    - if context_size is null.
 */

int fpc_algo_load_configuration(
    algo_context_t *context,
    uint32_t *context_size) {
    return 0;
}

/*
 * Release allocations and clean up this instance.
 * Caller is responsible for finally freeing context.
 *
 * @param[in] context, previously initialized by fpc_algo_load_configuration.
 */
void fpc_algo_cleanup(algo_context_t *context) {
    return 0;
}

/*
 * Begin the enrollment of a new finger.
 *
 * @param[in] context, previously initialized by fpc_algo_load_configuration.
 *
 * @return FPC_RESULT_OK
 *
 */
int fpc_algo_begin_enroll(algo_context_t *algo) {
    return 0;
}


/*
 * Add the image to the current enrollment process.
 *
 * @param[in] context, previously initialized by fpc_algo_load_configuration.
 * @param[in] image, the image to add to the enrollment.
 * @param[out] enroll_data, the data from the enrollment.
 *
 * @return FPC_RESULT_OK
 *         FPC_RESULT_ERROR_PARAMETER - if data is NULL
 *         FPC_RESULT_ERROR_MEMORY - if memory allocation failed during the enrollment
 */

int fpc_algo_enroll(
        algo_context_t *context,
        image_t* img,
        fpc_algo_enroll_data_t *enroll_data) {
    return 0;
}

/*
 * Ends the enrollment and returns the enrolled finger template.
 *
 * @param[in] context, previously initialized by fpc_algo_load_configuration.
 * @param[in] img, image aquired from capture.
 * @param[out] tpl, a buffer with the template data for the enrolled finger.
 *
 * @return FPC_RESULT_OK
 *         FPC_RESULT_ERROR_PARAMETER - if template is NULL or the size of the
 *                                    buffer is too small
 *         FPC_RESULT_ERROR_MEMORY    - if the template extraction failed
 */
int fpc_algo_end_enroll(
        algo_context_t* context,
        fpc_algo_template_t* tpl) {
    return 0;
}

/*
 * Begin identify for the given template candidates.
 *
 * @param[in] context, previously initialized by fpc_algo_load_configuration.
 * @param[in] candidates, the templates of the candidates to verify against
 * @param[in] num_tpl, number of templates in the array.
 *
 * @return FPC_RESULT_OK
 *         FPC_RESULT_ERROR_PARAMETER - if candidates is a NULL pointer, size is
 *         zero or security is an invalid number
 *         FPC_RESULT_ERROR_MEMORY - if memory allocation fails during
 *                                 the identification process
*/
int fpc_algo_begin_identify(
        algo_context_t* context,
        fpc_algo_template_t* candidates,
        uint32_t num_tpl) {
    return 0;
}

/*
 * Use the currently stored image for identification.
 *
 * @param[in] context, previously initialized by fpc_algo_load_configuration.
 * @param[in] img, image aquired from capture.
 * @param[out] Identification data, decision, sensor coverage etc.
 * @param[in] 0 to disable liveness. 1 to use.
 *
 * @return FPC_RESULT_OK
 *         FPC_RESULT_ERROR_PARAMETER - if data is a null pointer
 *         FPC_RESULT_ERROR_MEMORY - if the memory allocation failed during the
 *                                 identification
*/
int fpc_algo_identify(
    algo_context_t *context,
    image_t* img,
    fpc_algo_identify_data_t* data,
    uint8_t liveness) {
    return 0;
}

/*
 * Check if a template update occured.
 *
 * @param[in] context, the current algo context
 * @param[in/out] data, container of the identify result
 *
 * @return FPC_ALGO_OK
 *         FPC_ALGO_ERROR_GENERAL - If there is an error
 */
int fpc_algo_identify_update(algo_context_t *context,
        fpc_algo_identify_data_t* data) {
    return 0;
}

/*
 * End the started identification. If there was a template update during the
 * identification process, the given template struct will be filled with
 * template data. If a null pointer is given the update will be discarded.
 *
 * @param[in] context, previously initialized by fpc_algo_load_configuration.
 *
 * @return FPC_RESULT_OK
 *         FPC_RESULT_ERROR_PARAMETER - if template is NULL or the size of the
 *         buffer too small, (the needed size is returned in the template data)
 */
int fpc_algo_end_identify(
        algo_context_t* context) {
    return 0;
}

/*
 * Called on the image to give a enhanced image, the image is returned in the
 * provided buffer.
 *
 * @param[in] context, previously initialized by fpc_algo_load_configuration.
 * @param[in] image, the capture raw image
 * @param[out] buffer, buffer for the enhanced image
 * @param[in] size, size of the buffer
 *
 * @return FPC_RESULT_OK or,
 *         FPC_RESULT_ERROR_PARAMETER if the image or buffer is null or the size
 *         is too small,
 *         otherwise algo error.
 */
int  fpc_algo_storage_retrieve_enhanced_image(
        algo_context_t* context,
        image_t* image,
        uint8_t* buffer,
        uint32_t size) {
    return 0;
}

/*
 * Qualifies the given image for use with identify and enroll. If the quality
 * of the image is to low this function will return FPC_ALGO_ERROR_BAD_QUALITY.
 *
 * @param[in] image, the image to qualify
 *
 * @return FPC_RESULT_OK - if the image has high enough quality.
 *         FPC_RESULT_BAD_QUALITY - if the image has too low quality
 */
int fpc_algo_qualify_image(image_t* image) {
    return 0;
}

/*
 * Update the given list of template structs will be filled with
 * template data. If a null pointer is given the update will be discarded.
 *
 * @param[in] context, previously initialized by fpc_algo_load_configuration.
 * @param[in/out] templates, a list of buffers for the updated templates
 * @param[in] template_indices, a list of template indices to update template for
 * @param[in] num_tpls, the number of templates to update
 *
 * @return FPC_RESULT_OK
 *         FPC_ERROR_PARAMETER - if templates is NULL or the size of the buffer
 *         is too small, (the needed size is returned in the template data)
 */
int fpc_algo_update_templates(
        algo_context_t *context,
        fpc_algo_template_t** templates,
        uint32_t *template_indices,
        uint32_t num_tpls) {
    return 0;
}

/**
 * Run PN calibration having a finger on the sensor by repeatedly
 * making calls to this function adding one image at a time. When
 * pn_add_image_data->progress reaches 100% the PN image is available
 * by calling fpc_algo_pn_calibrate_finger_end().
 * NOTE:
 * Regardless of the outcome of this function, fpc_algo_pn_calibrate_finger_end()
 * must always be called to release resources.
 *
 * @param[in]  context - Previously initialized by fpc_algo_load_configuration.
 * @param[in]  image   - Image to add to the PN calibration.
 * @param[out] pn_add_image_data - The result from adding 'image'.
 *
 * @return FPC_RESULT_OK - A new call to this function must be made until
 *                         pn_add_image_data->progress reaches 100%.
 *         FPC_RESULT_ERROR_PARAMETER - If any parameter is NULL.
 *         FPC_RESULT_ERROR_...       - Any other error.
 */
int fpc_algo_pn_calibrate_finger(algo_context_t *context,
                                 image_t *image,
                                 fpc_algo_pn_add_image_data_t *pn_add_image_data) {
    return 0;
}

/**
 * End PN calibration started in fpc_algo_pn_calibrate_finger().
 *
 * @param[in]  context - Previously initialized by fpc_algo_load_configuration.
 * @param[in]  image   - Image where the new PN image will be inserted.
 *
 * @return FPC_RESULT_OK - PN image successfully updated in 'image'
 *         FPC_RESULT_ERROR_PARAMETER - If any parameter is NULL.
 *         FPC_RESULT_ERROR_...       - Any other error.
 */
int fpc_algo_pn_calibrate_finger_end(algo_context_t *context,
                                     image_t *image) {
    return 0;
}
