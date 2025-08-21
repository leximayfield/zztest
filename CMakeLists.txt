cmake_minimum_required(VERSION 3.5...3.31)

project(zztest LANGUAGES C CXX)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

add_library(zztest INTERFACE)
target_include_directories(zztest INTERFACE "include")

add_subdirectory(check)
