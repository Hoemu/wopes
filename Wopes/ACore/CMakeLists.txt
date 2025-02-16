cmake_minimum_required(VERSION 3.16)

project(ACore LANGUAGES CXX)

include(./ConfigFile/ACoreBaseConfig.cmake)
message(STATUS "Generating '${PROJECT_BINARY_DIR}/ConfigFile/ACoreBaseConfig.cmake'")

find_configure_file(${PROJECT_SOURCE_DIR}/ConfigFile)
generate_head_file(${CMAKE_CURRENT_SOURCE_DIR})

set(HEADERS
    a_core.h
    ACore_global.h
)

set(SOURCES
    a_core.cpp
    main.cpp
)

set(SRCS WIN32
    ${SOURCES}
    ${HEADERS}
)

if(IS_GENERAT_LIBRARY)
    add_library(ACore SHARED
        ${SOURCES} ${HEADERS}
        )
    target_compile_definitions(ACore PRIVATE ACORE_LIBRARY)
    message(STATUS "execute library")
else()
    add_executable(ACore ${SOURCES} ${HEADERS})
    message(STATUS "execute exe")
endif()

set_target_properties(ACore PROPERTIES
    OUTPUT_NAME "acore"          # 修改基础名称，生成 libRenamedLib.a
)

target_link_libraries(ACore PRIVATE Qt${QT_VERSION_MAJOR}::Core)

# 安装可执行文件到bin目录
install(TARGETS ACore DESTINATION bin)
install(TARGETS ACore LIBRARY DESTINATION lib)


