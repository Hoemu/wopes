cmake_minimum_required(VERSION 3.16)

project(Wopes LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(./ACore)
add_subdirectory(./Wope)

# cmake --install .
# cmake --build . --target install
# cmake --install . --prefix "../ACore/" --verbose # 明确的安装
add_subdirectory(TestWin/TestWin)
