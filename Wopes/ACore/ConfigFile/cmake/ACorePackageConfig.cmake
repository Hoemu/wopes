set(ACorePackageInfo "配置相关包文件")

if(NOT IS_GOOGLE_TEST)
    set(GoogleTestLib {CMAKE_CURRENT_SOURCE_DIR}/../../../../env/google-test-env/lib)
    find_lib_file(GTestLib ${GoogleTestLib})
    set(GoogleTestInclude {CMAKE_CURRENT_SOURCE_DIR}/../../../../env/google-test-env/include)
    include_directories(${GoogleTestInclude})
    if(DEFINED CTEST) # 可以测试私有成员
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-access-control")
        add_definitions(-DUSE_CTEST)
    endif()
endif()
