# 文件由 CMake 的 install(EXPORT) 自动生成
include(CMakeFindDependencyMacro)
# find_dependency(...)  # 若有依赖其他库

# 导入目标属性
# include(${CMAKE_CURRENT_LIST_DIR}ACoreTargets-release.cmake)

# 创建命名空间目标（推荐）
# add_library(ACore ALIAS ACore)
