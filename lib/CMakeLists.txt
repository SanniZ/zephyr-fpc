# SPDX-License-Identifier: Apache-2.0
set(LIB_DIR ${PROJECT_SOURCE_DIR}/lib)

# get name of lib.
string(REPLACE "lib" "" lib_name ${lib_name})
string(REPLACE ".a" "" lib_name ${lib_name})
# build lib.
file(GLOB lib_sources ${LIB_DIR}/src/*.c)
add_library(${lib_name} STATIC ${lib_sources})
target_link_libraries(app PUBLIC ${lib_name})
