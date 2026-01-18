cmake_minimum_required(VERSION 3.5...3.31)

project(zztest LANGUAGES C CXX)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

option(ZZTEST_ENABLE_CHECK "Enable selfcheck for zztest")
option(ZZTEST_ENABLE_METATEST "Enable metatest for zztest")

set(ZZTEST_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/include/zztest.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/zztest.c")

add_library(zztest STATIC)
target_sources(zztest PRIVATE ${ZZTEST_SOURCES})
target_include_directories(zztest PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/include")

if(ZZTEST_ENABLE_CHECK)
    add_subdirectory(check)
endif()

if(ZZTEST_ENABLE_METATEST)
    add_subdirectory(metatest)
endif()
