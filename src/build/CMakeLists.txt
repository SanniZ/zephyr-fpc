# SPDX-License-Identifier: Apache-2.0

set(SRC_DIR ${PROJECT_SOURCE_DIR})

# set features.
set(hw_auth 1)  # enable hw_auth.
set(db_blob 1)  # enable db_blog.
set(lib_name libfpc1028.a)  # libfpc1028.a

# include *.h
include_directories(${SRC_DIR}/src/interface
                    ${SRC_DIR}/src/secure/inc
                    ${SRC_DIR}/src/secure/inc/hw_auth
                    ${SRC_DIR}/src/secure/lib)

# get source files.
file(GLOB app_sources
     ${SRC_DIR}/src/secure/src/fpc_ta_router.c
     ${SRC_DIR}/src/secure/src/fpc_ta_common.c
     ${SRC_DIR}/src/secure/src/fpc_ta_sensor.c
     ${SRC_DIR}/src/secure/src/fpc_ta_bio.c
     ${SRC_DIR}/src/secure/src/fpc_crypto.c
     ${SRC_DIR}/src/secure/src/fpc_db.c
     ${SRC_DIR}/src/secure/src/kpi/fpc_ta_kpi.c)
if (hw_auth)  # enable hw_auth.
    add_definitions(-DFPC_CONFIG_HW_AUTH)
    aux_source_directory(${SRC_DIR}/src/secure/src/hw_auth app_sources)
endif()
if (db_blob)  # enable db_blog.
    add_definitions(-DFPC_CONFIG_TA_DB_BLOB)
    add_definitions(-DFPC_CONFIG_IDENTIFY_AT_ENROL)
    aux_source_directory(${SRC_DIR}/src/secure/src/db_blob app_sources)
endif()
# platform source.
include(${SRC_DIR}/src/secure/platform/zephyr/build/CMakeLists.txt)

# build source.
target_sources(app PRIVATE ${app_sources})

# link to lib.
if (lib_name)
    add_definitions(-DFPC_CONFIG_LIB)
    add_library(fp_lib STATIC IMPORTED)
    set_property(TARGET fp_lib PROPERTY IMPORTED_LOCATION ${SRC_DIR}/src/secure/lib/${lib_name})
    target_link_libraries(app PUBLIC fp_lib)
endif()
