cmake_minimum_required(VERSION 3.16)

project(Wopes LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# add_subdirectory(./ACore)
add_subdirectory(./Wope)

# cmake --install .
# cmake --build . --target install
# cmake --install . --prefix "../ACore/" --verbose # 明确的安装

# 错误总结：
# 1. 重新设置库文件名称时需要很注意（建议不要重新设置，容易出现奇怪错误）
# 2. 生成库后，安装上，再注释 cmake 语句，重新执行 cmake ，可以找到库，但是会有 ninja 错误
# 3. 修改安装路径，并注释了 message 代码，运行 cmake 并构建，执行 install 进行安装，此时会提示无法找到库，
# 注意，此时 ACore_LIBS 为 acore（小写的），实际上 ACore_LIBS 已经发生改变了，那么只有可能再修改后，缓冲
# 并没有被覆盖（？），此时的状态是可以找到头文件的，但是无法找到库文件
# 最后建议：在 windows 上不要自己写 find_package ，只需要用就可以了
# 4. 什么时候可以 find_package 找得到：默认路径不设置，安装的时候需要使用 cmake --install . 然后删掉 build 整个文件，重新构建，会出现 find_package 找到的那个目录
# 5. 首先把 ACore 单独运行（注意使用右键的执行 CMake），再执行 cmake --install . --prefix "../ACore/" --verbose
# 注释 ACore 项目，右键执行Wopes 执行 CMake（两者其中之一必有被注释），然后还是不行，显示库无法找到。

# 1. Wope 不需要改变，需要改变的是 ACore 中 CMake 部分
# ninja: build stopped: subcommand failed. 的失败有可能是权限的问题（可能）
# 注意：注释 Wope 放开后，一定还是注意把 ACore 本身的库删除，并且改一下 CMakeLists ，重新构建一下
# 注意：出现 multiple 的原因是因为没有删除前面使用 cmd 手动构建的目录
