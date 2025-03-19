cmake_minimum_required(VERSION 3.16)

project(ACore LANGUAGES CXX)

include(./ConfigFile/cmake/ACoreBaseConfig.cmake)
include(./ConfigFile/cmake/ACorePackageConfig.cmake)
# message(STATUS "Generating '${PROJECT_BINARY_DIR}/ConfigFile/ACoreBaseConfig.cmake'")

find_configure_file(${PROJECT_SOURCE_DIR}/ConfigFile)
generate_head_file(${CMAKE_CURRENT_SOURCE_DIR})
find_source_code(SRCS)

message(STATUS "PROJECT_VERSION: ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}.")

if(IS_GENERAT_LIBRARY)
    add_library(ACore SHARED
        ${SRCS}
        ${ACore_Version}
        )
    target_compile_definitions(ACore PRIVATE ACORE_LIBRARY)
    message(STATUS "create lib.")
else()
    add_executable(ACore ${SRCS} main.cpp
        aFileSystem/a_ring_chunk_buffer.h aFileSystem/a_ring_chunk_buffer.cpp)
    target_link_libraries(ACore ${GOOLE_TEST_LIB})
    enable_testing()
    add_test(NAME ACore COMMAND ACore)
    message(STATUS "create exe.")
endif()

set_target_properties(ACore PROPERTIES
    OUTPUT_NAME "acore"          # 修改基础名称，生成 libACore.a
)

# 安装可执行文件到bin目录
install(TARGETS ACore
    EXPORT ACoreTargets
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION bin
)

install(EXPORT ACoreTargets
  FILE ACoreTargets.cmake          # 生成的目标文件名
  NAMESPACE acore::                # 命名空间（推荐格式）
  DESTINATION ./                   # 安装路径
)

# 添加自定义目标实现安装自动触发
# add_custom_target(auto_install
#     DEPENDS all
#     COMMAND "${CMAKE_COMMAND}" --install "${CMAKE_BINARY_DIR}"
#     COMMENT "Auto-installing built targets"
# )


