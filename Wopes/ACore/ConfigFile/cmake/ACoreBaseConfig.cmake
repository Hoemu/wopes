# 当前页面主要写一些函数和宏定义
message(STATUS "Begin ACoreBaseConfig")

include(./ConfigFile/cmake/ACore.cmake)
include(./ConfigFile/cmake/ACoreUtil.cmake)
include(./ConfigFile/cmake/ACoreVersionUtil.cmake)
# include(./ConfigFile/cmake/ACoreTargets.cmake)

# 添加配置文件
function(find_configure_file target_dir)
    file(GLOB_RECURSE children "${target_dir}/*.in")
    set(dirlist "")
    foreach(child ${children})
        get_filename_component(dir_name ${child} NAME)
        string(REGEX REPLACE "\\.in$" "" output_str "${dir_name}")
        set(ACoreAllConfigFile "${CMAKE_CURRENT_BINARY_DIR}/${output_str}")
        # string(REGEX REPLACE "${PROJECT_SOURCE_DIR}" "${PROJECT_BINARY_DIR}" res "${ACoreAllConfigFile}")
        configure_file(${child} "${ACoreAllConfigFile}" @ONLY)
        install(FILES "${ACoreAllConfigFile}" DESTINATION "./")
    endforeach()
endfunction()

# 拷贝头文件
function(generate_head_file target_dir)
    file(GLOB_RECURSE children "${target_dir}/*.h")
    foreach(child ${children})
        string(REGEX REPLACE "${CMAKE_CURRENT_SOURCE_DIR}" "${ACore_INCLUDE_DIRS_CONFIGCMAKE}" binary_include "${child}")
        get_filename_component(file_name ${child} NAME)
        string(REGEX REPLACE "${file_name}" "" complete_dir "${binary_include}")
        string(REGEX REPLACE "${ACore_INCLUDE_DIRS_CONFIGCMAKE}" "" head_dir "${complete_dir}")
        # message("file name is " ${head_dir}) # 不添加某一个文件夹
        if(${head_dir} MATCHES ${BUILD_PATH})
            continue()
        endif()
        file(COPY ${child} DESTINATION "${complete_dir}")
        install(FILES ${child} DESTINATION include/${head_dir})
        # message("${head_dir}")
    endforeach()
endfunction()

# 添加源文件
function(find_source_code OUTPUT_VAR)
    file(GLOB_RECURSE src "*.cpp" "*.h")
    set(fileList "")
    foreach(child ${src})
        get_no_sufix_dir(file_dir ${child})
        get_filename_component(file_name ${child} NAME)
        if(IS_GENERAT_LIBRARY)
            if(${file_name} MATCHES "main.cpp")
                continue()
            endif()
        endif()
        if(NOT ${file_dir} MATCHES ${BUILD_PATH})
            LIST(APPEND fileList ${child})
            # message("append value " ${file_dir})
        endif()
    endforeach()
    set(${OUTPUT_VAR} ${fileList} PARENT_SCOPE)
    # message(STATUS "[end src] " ${fileList})
endfunction()

# 添加依赖文件


include(./ACore)

message(STATUS "End ACoreBaseConfig")
