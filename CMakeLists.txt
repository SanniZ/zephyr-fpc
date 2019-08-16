# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.13.1)

include($ENV{ZEPHYR_BASE}/cmake/app/boilerplate.cmake NO_POLICY_SCOPE)
project(fingerprint)

# src path
set(SRC_DIR ${PROJECT_SOURCE_DIR}/src)

# lib name
set(lib_name libfpc1028.a) #libfpc1028.a

# features.
set(hw_auth 1)
set(db_blob 1)

# include *.h
include_directories(${SRC_DIR}/interface
                    ${SRC_DIR}/secure/inc
                    ${SRC_DIR}/secure/lib
                    ${SRC_DIR}/secure/inc/hw_auth)
# get *.c
file(GLOB app_sources
     ${SRC_DIR}/secure/src/fpc_ta_router.c
     ${SRC_DIR}/secure/src/fpc_ta_common.c
     ${SRC_DIR}/secure/src/fpc_ta_sensor.c
     ${SRC_DIR}/secure/src/fpc_ta_bio.c
     ${SRC_DIR}/secure/src/fpc_crypto.c
     ${SRC_DIR}/secure/src/fpc_db.c
     ${SRC_DIR}/secure/src/kpi/fpc_ta_kpi.c)
include(${SRC_DIR}/secure/platform/zephyr/CMakeLists.txt)
if (hw_auth)  # enable hw_auth.
add_definitions(-DFPC_CONFIG_HW_AUTH)
aux_source_directory(${SRC_DIR}/secure/src/hw_auth app_sources)
endif()
if (db_blob)  # enable db_blog.
add_definitions(-DFPC_CONFIG_TA_DB_BLOB)
add_definitions(-DFPC_CONFIG_IDENTIFY_AT_ENROL)
aux_source_directory(${SRC_DIR}/secure/src/db_blob app_sources)
endif()
# add dummy heci, lib and fingerprint_tac.
include(${PROJECT_SOURCE_DIR}/heci/CMakeLists.txt)
include(${PROJECT_SOURCE_DIR}/lib/CMakeLists.txt)
include(${PROJECT_SOURCE_DIR}/fingerprint_tac/CMakeLists.txt)
# build source.
target_sources(app PRIVATE ${app_sources})

# link to staic lib.
# add_library(lib STATIC IMPORTED)
# set_property(TARGET lib PROPERTY IMPORTED_LOCATION ${SRC_DIR}/secure/lib/${lib_name})
# target_link_libraries(app PUBLIC lib)
