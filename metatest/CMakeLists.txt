#
# Metatest is an end-to-end functionality check.  It requires C++14, but
# makes sure the library is functioning properly.
#

include(FetchContent)
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2
    GIT_TAG v3.12.0)
FetchContent_MakeAvailable(Catch2)

add_executable(metatest)
target_sources(metatest PRIVATE
    "metatest.cpp"
    "../include/zztest.h"
    "../src/zztest.c")
target_include_directories(metatest PRIVATE "../include")
target_compile_definitions(metatest PRIVATE "ZZTEST_CONFIG_PRINTF=metatest_printf")
target_link_libraries(metatest PRIVATE Catch2WithMain)
