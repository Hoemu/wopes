set(ACorePackageInfo "配置相关包文件")

set(GoogleTestLib {CMAKE_CURRENT_SOURCE_DIR}/../../../../env/google-test-env/lib)
find_lib_file(GTestLib ${GoogleTestLib})
set(GoogleTestInclude {CMAKE_CURRENT_SOURCE_DIR}/../../../../env/google-test-env/include)

# message(${GTestLib})
include_directories(${GoogleTestInclude})
