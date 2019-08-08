/**
 * @file
 *
 * @brief Public APIs for the heci.
 */

/*
 * Copyright (c) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "heci.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief
 * register a new HECI client
 * @param client Pointer to the client structure for the instance.
 * @retval 0 If successful.
 */
int heci_register(heci_client_t *client) {
    return 0;
}

/**
 * @brief
 * send HECI message to HOST client with certain connection
 * @param conn_id connection id for sending.
 * @param msg message content pointer to send.
 * @retval 0 If successful.
 */
bool heci_send(uint32_t conn_id, mrd_t *msg) {
    return 1;
}

/**
 * @brief
 * send HECI flow control message to HOST client, indicating that FW client is
 * ready for receiving a new HECI message
 * @param conn_id connection id for sending.
 * @retval 0 If successful.
 */
bool heci_send_flow_control(uint32_t conn_id) {
    return 1;
}

/**
 * @brief
 * complete disconnection between FW client and HOST client, run after
 * receiving a disconnection request from HOST client
 * @param conn_id connection id to disconnect.
 * @retval 0 If successful.
 */
int heci_complete_disconnect(uint32_t conn_id) {
    return 0;
}

#ifdef __cplusplus
}
#endif
