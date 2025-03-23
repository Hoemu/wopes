# 此项目为测试项目（如果要使用此项目，需要单独的 googleTest 依赖）

cmake_minimum_required(VERSION 3.16)

project(QtTestLib LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(LibPath "../Depends/google-test-env")

include_directories("${LibPath}/include/")

file(GLOB_RECURSE fileList "${LibPath}/lib/*.a")

foreach(var ${fileList})
    message(${var})
endforeach()


add_executable(QtTestLib main.cpp
    test_class.h test_class.cpp
    ring_chunk.h ring_chunk.cpp)

target_link_libraries(QtTestLib ${fileList})

include(GNUInstallDirs)
install(TARGETS QtTestLib
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
