# SPDX-License-Identifier: Apache-2.0

file(GLOB lib_sources ${SRC_DIR}/secure/lib/src/*.c)
add_library(fpc STATIC ${lib_sources})
target_link_libraries(app PUBLIC fpc)
