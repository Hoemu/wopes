find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)
# 寻找 Qt 相关的包
find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)
# 寻找其他包

# 手动指定安装位置
set(ACore_DIR "C:/Users/Muiiii/Desktop/generalFile/GitRepertory/wopes/ACore/build/ACore")

find_package(ACore REQUIRED)
find_package(OpenCV REQUIRED)
