find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)
# 寻找 Qt 相关的包
find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)
# 寻找其他包

# TODO 手动指定安装位置
set(ACore_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../ACore/build/ACore")
set(ACore_DIR_LIB ${ACore_DIR}/bin/libacore.dll)
set(ACore_DIR_INCLUDE ${ACore_DIR}/include)

message("dir --- " ${ACore_DIR_LIB})

find_package(ACore REQUIRED)
find_package(OpenCV REQUIRED)
