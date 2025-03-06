set(ACorePackageInfo "配置相关包文件")

if(NOT IS_GENERAT_LIBRARY)
    set(GoogleTestLib {CMAKE_CURRENT_SOURCE_DIR}/../../../../env/google-test-env/lib)
    find_lib_file(GTestLib ${GoogleTestLib})
    set(GoogleTestInclude {CMAKE_CURRENT_SOURCE_DIR}/../../../../env/google-test-env/include)
    include_directories(${GoogleTestInclude})
endif()
