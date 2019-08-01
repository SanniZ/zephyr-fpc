# SPDX-License-Identifier: Apache-2.0

file(GLOB lib_sources ${PROJECT_SOURCE_DIR}/lib/src/*.c)
add_library(${lib_name} STATIC ${lib_sources})
target_link_libraries(app PUBLIC ${lib_name})
