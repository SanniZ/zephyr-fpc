# SPDX-License-Identifier: Apache-2.0
set(TAC_DIR ${PROJECT_SOURCE_DIR}/fingerprint_tac)

add_definitions(-DFPC_REE_DEVICE_ALIAS_FILE="modalias")
add_definitions(-DFPC_REE_DEVICE_NAME="fpc_irq")
add_definitions(-DFPC_REE_DEVICE_PATH="/sys/bus/platform/devices")


include_directories(${TAC_DIR}/interface
                    ${TAC_DIR}/normal/inc
                    ${TAC_DIR}/normal/inc/kpi
                    ${TAC_DIR}/normal/platform/zephyr/inc
                    ${TAC_DIR}/normal/src/test)
aux_source_directory(${TAC_DIR}/normal/src app_sources)
aux_source_directory(${TAC_DIR}/normal/src/kpi app_sources)
aux_source_directory(${TAC_DIR}/normal/src/hw_auth app_sources)
aux_source_directory(${TAC_DIR}/normal/src/test app_sources)
aux_source_directory(${TAC_DIR}/normal/platform/zephyr/src app_sources)
aux_source_directory(${TAC_DIR}/normal/platform/zephyr/src/hw_auth app_sources)
