# SPDX-License-Identifier: Apache-2.0
set(HECI_DIR ${PROJECT_SOURCE_DIR}/heci)

include_directories(${HECI_DIR}/inc)
aux_source_directory(${HECI_DIR}/src app_sources)
