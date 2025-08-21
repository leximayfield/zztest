add_executable(zzcheck_c)
target_sources(zzcheck_c PRIVATE
    "zzcheck.c"
    "zzcheck.inl")
target_link_libraries(zzcheck_c PRIVATE zztest)

add_executable(zzcheck_cxx)
target_sources(zzcheck_cxx PRIVATE
    "zzcheck.cpp"
    "zzcheck.inl")
target_link_libraries(zzcheck_cxx PRIVATE zztest)
