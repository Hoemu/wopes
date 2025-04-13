# 编程环境设置
# set(CMAKE_AUTOUIC ON)
# set(CMAKE_AUTOMOC ON)
# set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 显示详细编译过程
# enable_language(RC)
# set(CMAKE_RC_VERBOSE ON)  # 显示详细编译过程
# set(CMAKE_RC_FLAGS "--preprocessor-arg=-v")  # 显示预处理细节

# DeBug output
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG
    ${CMAKE_CURRENT_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG
    ${CMAKE_CURRENT_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG
    ${CMAKE_CURRENT_BINARY_DIR}/bin)

#release output
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE
    ${CMAKE_CURRENT_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE
    ${CMAKE_CURRENT_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE
    ${CMAKE_CURRENT_BINARY_DIR}/bin)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(IS_GENERAT_LIBRARY OFF)   # Debug 模式下启用调试
else()
    set(IS_GENERAT_LIBRARY ON)    # Release 模式关闭调试
endif()

#--------------------------------  以下为手动设置 --------------------------------#

# include(./CMakePackageConfigHelpers)      # NOTE 需要自动定位 ACore_DIRS 时放开注释
set(IS_GENERAT_LIBRARY OFF)                 # 是否生成库/或者是调试模式
set(IS_GOOGLE_TEST ON)                      # 是否开启 googleTest
set(ACORE_LIBRARY_STATUS SHARED)            # 生产静态库 （动态库或者静态库） STATIC/SHARED
set(IS_SPDLOG ON)                           # 启动 spdLog
set(BUILD_PATH "build")                     # 构建路径（相对当前源文件）
set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_BINARY_DIR}/../${PROJECT_NAME}") # 自定义安装位置
set(ACore_LIBS "${CMAKE_INSTALL_PREFIX}/lib/lib${PROJECT_NAME}.dll.a")     # 静态库位置（安装后）
set(ACore_Resource_DIR ${CMAKE_CURRENT_BINARY_DIR})
set(ACore_SHARED_DIRS "${CMAKE_INSTALL_PREFIX}/bin")                       # 动态库位置（安装后）
SET(ACORE_STATIC_DIRS "${CMAKE_INSTALL_PREFIX}/lib")                       # 静态库位置（安装后）
set(ACore_INCLUDE_DIRS "${CMAKE_INSTALL_PREFIX}/include")                  # 头文件位置（安装后）
set(ACore_INCLUDE_DIRS_CONFIGCMAKE "${CMAKE_CURRENT_BINARY_DIR}/include")  # 未定义

# message(STATUS "PROJECT_VERSION = ${PROJECT_VERSION}")

