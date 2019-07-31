# SPDX-License-Identifier: Apache-2.0

# set path
set(SRC_DIR ${PROJECT_SOURCE_DIR}/src)
set(LIB_DIR ${PROJECT_SOURCE_DIR}/src/secure/lib)

# set features.
set(hw_auth 1)
set(db_blob 1)

set(lib_name libfpc1028.a) #libfpc1028.a

# include *.h
include_directories(${SRC_DIR}/interface
                    ${SRC_DIR}/secure/inc
                    ${SRC_DIR}/secure/lib)

# get source.
file(GLOB app_sources
     ${SRC_DIR}/secure/src/fpc_ta_router.c
     ${SRC_DIR}/secure/src/fpc_ta_common.c
     ${SRC_DIR}/secure/src/fpc_ta_sensor.c
     ${SRC_DIR}/secure/src/fpc_ta_bio.c
     ${SRC_DIR}/secure/src/fpc_crypto.c
     ${SRC_DIR}/secure/src/fpc_db.c
     ${SRC_DIR}/secure/src/kpi/fpc_ta_kpi.c)
if (hw_auth)  # enable hw_auth.
add_definitions(-DFPC_CONFIG_HW_AUTH)
include_directories(${SRC_DIR}/secure/inc/hw_auth)
aux_source_directory(${SRC_DIR}/secure/src/hw_auth app_sources)
endif()
if (db_blob)  # enable db_blog.
add_definitions(-DFPC_CONFIG_TA_DB_BLOB)
add_definitions(-DFPC_CONFIG_IDENTIFY_AT_ENROL)
aux_source_directory(${SRC_DIR}/secure/src/db_blob app_sources)
endif()
# get platform source.
include(${SRC_DIR}/secure/platform/zephyr/build/CMakeLists.txt)
# build source.
target_sources(app PRIVATE ${app_sources})

# link to staic lib.
add_library(lib STATIC IMPORTED)
set_property(TARGET lib PROPERTY IMPORTED_LOCATION ${LIB_DIR}/${lib_name})
target_link_libraries(app PUBLIC lib)

#include(${LIB_DIR}/src/CMakeLists.txt) # link to dummy lib.

