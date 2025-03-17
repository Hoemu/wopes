cmake_minimum_required(VERSION 3.16)

project(WopeWin VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# set(OpenCV_DIR xxxx) # xxxx目录包含OpenCVConfig.cmake\

include(./WopesConfigFile/WopesConfigPackage.cmake)

# link_directories(${PROJECT_SOURCE_DIR}/../ACore/)
include_directories(${ACore_DIR_INCLUDE}) # 动态变化
include_directories(${OpenCV_INCLUDE_DIRS})

# message(${ACore_INCLUDE_DIRS})
# message(${ACore_SHARED_DIRS})
# message(${ACORE_STATIC_DIRS})
# message(${ACore_LIBS})
# message(${ACore_DIR_LIB})

# message("opencv lib " ${OpenCV_LIBS})

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(WopeWin
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        threadttest.h threadttest.cpp
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET WopeWin APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(WopeWin SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(WopeWin
            ${PROJECT_SOURCES}
        )
    endif()
endif()

# message(STATUS "lib path: ${CMAKE_CURRENT_SOURCE_DIR}/../ACore/lib")
# get_target_property(LIB_PATH ${OpenCV_LIBS} LOCATION)
message(STATUS "lib real path: ${ACore_LIBS}")

link_directories(${ACore_LIBS})
# 链接库
target_link_libraries(WopeWin PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    ${ACore_DIR_LIB}
    ${OpenCV_LIBS}
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.WopeWin)
endif()
set_target_properties(WopeWin PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS WopeWin
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(WopeWin)
endif()
