# SPDX-License-Identifier: Apache-2.0
set(PLATFORM_ZEPHYR_DIR ${SRC_DIR}/secure/platform/zephyr)

include_directories(${PLATFORM_ZEPHYR_DIR}/inc)
aux_source_directory(${PLATFORM_ZEPHYR_DIR}/src app_sources)
if (hw_auth)  # enable hw_auth.
aux_source_directory(${PLATFORM_ZEPHYR_DIR}/src/hw_auth app_sources)
endif()
