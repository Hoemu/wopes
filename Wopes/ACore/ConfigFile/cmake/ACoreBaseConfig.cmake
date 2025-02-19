# 当前页面主要写一些函数和宏定义
message(STATUS "Begin ACoreBaseConfig")

include(./ConfigFile/cmake/ACore.cmake)
include(./ConfigFile/cmake/ACorePackageConfig.cmake)
include(./ConfigFile/cmake/ACoreUtil.cmake)
include(./CMakePackageConfigHelpers)
# include(./ConfigFile/cmake/ACoreTargets.cmake)


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


function(generate_head_file target_dir)
    file(GLOB_RECURSE children "${target_dir}/*.h")
    foreach(child ${children})
        string(REGEX REPLACE "${CMAKE_CURRENT_SOURCE_DIR}" "${ACore_INCLUDE_DIRS_CONFIGCMAKE}" head_res "${child}")
        get_filename_component(file_name ${child} NAME)
        string(REGEX REPLACE "${file_name}" "" complete_dir "${head_res}")
        string(REGEX REPLACE "${CMAKE_CURRENT_BINARY_DIR}/include" "" head_dir "${complete_dir}")
        # message("file name is " ${head_dir})
        if(${head_dir} MATCHES "build")
            continue()
        elseif(NOT ${file_name} MATCHES "main.cpp")
            file(COPY ${child} DESTINATION "${complete_dir}")
            # message("Find file " ${file_name})
        elseif(NOT IS_GENERAT_LIBRARY)
            file(COPY ${child} DESTINATION "${complete_dir}")
            # message("Find file " ${file_name})
        endif()
        install(FILES ${child} DESTINATION include/${head_dir})
        # message("${head_dir}")
    endforeach()
endfunction()


function(find_source_code OUTPUT_VAR)
    file(GLOB_RECURSE src "*.cpp" "*.h")
    set(fileList "")
    foreach(child ${src})
        get_no_sufix_dir(file_dir ${child})
        if(NOT ${file_dir} MATCHES "build")
            LIST(APPEND fileList ${child})
            # message("append value " ${file_dir})
        endif()
    endforeach()
    set(${OUTPUT_VAR} ${fileList} PARENT_SCOPE)

    # message(STATUS "[end src] " ${fileList})
endfunction()

# TODO 设置头文件（非 .h 类型）
function(copy_head target_dir OUTPUT_VAR)
    set(${OUTPUT_VAR} ${target_dir} PARENT_SCOPE)
endfunction()

message("Test " ${SRC_T})

include(./ACore)

message(STATUS "End ACoreBaseConfig")
