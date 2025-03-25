# 此项目为测试项目（如果要使用此项目，需要单独的 googleTest 依赖）

cmake_minimum_required(VERSION 3.16)
project(QtTestLib LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-access-control")
add_definitions(-DUSE_CTEST)

# 通过 FetchContent 自动下载 GTest
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY git@github.com:google/googletest.git
  GIT_TAG release-1.16.0  # 指定稳定版本
)
FetchContent_MakeAvailable(googletest)

# Windows 特殊设置（避免 CRT 冲突）
if(WIN32)
  set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
endif()

add_executable(QtTestLib main.cpp
    test_class.h test_class.cpp
    ring_chunk.h ring_chunk.cpp)

# 链接 GTest 库
target_link_libraries(QtTestLib
  PRIVATE GTest::gtest_main  # 自动包含 main 函数入口
)

# 启用测试并自动发现用例
enable_testing()

# enable_testing()
# add_test(NAME QtTestLib COMMAND QtTestLib)
include(GoogleTest)
include(GNUInstallDirs)
install(TARGETS QtTestLib
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
gtest_discover_tests(QtTestLib)
