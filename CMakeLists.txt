# SPDX-License-Identifier: Apache-2.0

set(BOARD qemu_x86)

cmake_minimum_required(VERSION 3.13.1)

include($ENV{ZEPHYR_BASE}/cmake/app/boilerplate.cmake NO_POLICY_SCOPE)
project(fingerprint)

include(src/build/CMakeLists.txt)
