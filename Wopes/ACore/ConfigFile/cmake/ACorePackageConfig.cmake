set(ACorePackageInfo "配置相关包文件")

if(IS_GOOGLE_TEST)
    set(GOOGLE_TARGET_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../Depends/google-test-env/lib)
    set(GOOGLE_TAEGET_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/../Depends/google-test-env/include)
    include_directories(${GOOGLE_TAEGET_INCLUDE})
    find_static_lib_file(GOOLE_TEST_LIB ${GOOGLE_TARGET_DIR})
    if(DEFINED CTEST) # 可以测试私有成员
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-access-control")
        add_definitions(-DUSE_CTEST)
    endif()
    message(STATUS "GoogleTest starts.")
endif()

