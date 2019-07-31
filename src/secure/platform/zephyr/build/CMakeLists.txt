# SPDX-License-Identifier: Apache-2.0

# include *.h
include_directories(${SRC_DIR}/secure/platform/zephyr/inc)

# source *.c
aux_source_directory(${SRC_DIR}/secure/platform/zephyr/src app_sources)
