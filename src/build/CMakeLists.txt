# SPDX-License-Identifier: Apache-2.0

# set path
set(SRC_DIR ${PROJECT_SOURCE_DIR}/src)

# set features.
set(hw_auth 1)
set(db_blob 1)

# lib name
set(lib_name fpc1028) #fpc1028
# path of lib binary
set(lib_binary ${SRC_DIR}/secure/lib/lib${lib_name}.a)

# include *.h
include_directories(${SRC_DIR}/interface
                    ${SRC_DIR}/secure/inc
                    ${SRC_DIR}/secure/lib
                    ${SRC_DIR}/secure/inc/hw_auth)

# get source.
file(GLOB app_sources
     ${SRC_DIR}/secure/src/fpc_ta_router.c
     ${SRC_DIR}/secure/src/fpc_ta_common.c
     ${SRC_DIR}/secure/src/fpc_ta_sensor.c
     ${SRC_DIR}/secure/src/fpc_ta_bio.c
     ${SRC_DIR}/secure/src/fpc_crypto.c
     ${SRC_DIR}/secure/src/fpc_db.c
     ${SRC_DIR}/secure/src/kpi/fpc_ta_kpi.c)
# get platform source.
include(${SRC_DIR}/secure/platform/zephyr/build/CMakeLists.txt)
if (hw_auth)  # enable hw_auth.
add_definitions(-DFPC_CONFIG_HW_AUTH)
aux_source_directory(${SRC_DIR}/secure/src/hw_auth app_sources)
endif()
if (db_blob)  # enable db_blog.
add_definitions(-DFPC_CONFIG_TA_DB_BLOB)
add_definitions(-DFPC_CONFIG_IDENTIFY_AT_ENROL)
aux_source_directory(${SRC_DIR}/secure/src/db_blob app_sources)
endif()
# build source.
target_sources(app PRIVATE ${app_sources})

# link to staic lib.
if (MAKELIB)
set(lib_name ${MAKELIB})
include(${PROJECT_SOURCE_DIR}/lib/CMakeLists.txt)
else()
add_library(lib STATIC IMPORTED)
set_property(TARGET lib PROPERTY IMPORTED_LOCATION ${lib_binary})
target_link_libraries(app PUBLIC lib)
endif()
