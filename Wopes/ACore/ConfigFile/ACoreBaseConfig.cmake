# 当前页面主要写一些函数和宏定义
message(STATUS "Begin ACoreBaseConfig")

set(ACore_INCLUDE_DIRS_CONFIGCMAKE "${CMAKE_CURRENT_BINARY_DIR}/include")
# add_definitions(__ACore_INCLUDE_DIRS )

function(find_configure_file target_dir)
    file(GLOB_RECURSE children "${target_dir}/*.in")
    set(dirlist "")
    foreach(child ${children})
        get_filename_component(dir_name ${child} NAME)
        string(REGEX REPLACE "\\.in$" "" output_str "${dir_name}")
        set(ACoreConfigFile "${CMAKE_CURRENT_BINARY_DIR}/${output_str}")
        # string(REGEX REPLACE "${PROJECT_SOURCE_DIR}" "${PROJECT_BINARY_DIR}" res "${ACoreConfigFile}")
        # message("-- operator " ${ACoreConfigFile})
        configure_file(${child} "${ACoreConfigFile}" @ONLY)
    endforeach()
endfunction()

function(generate_head_file target_dir)
    file(GLOB_RECURSE children "${target_dir}/*.h")
    foreach(child ${children})
        string(REGEX REPLACE "${CMAKE_CURRENT_SOURCE_DIR}" "${ACore_INCLUDE_DIRS_CONFIGCMAKE}" head_res "${child}")
        get_filename_component(dir_name ${child} NAME)
        string(REGEX REPLACE "${dir_name}" "" head_dir "${head_res}")
        string(REGEX REPLACE "${CMAKE_CURRENT_BINARY_DIR}/include" "" head_install "${head_dir}")
        install(FILES ${child} DESTINATION include/${head_install})
        file(COPY ${child} DESTINATION "${head_dir}")
        # message("head -" ${head_install})
    endforeach()
endfunction()

function(find_source_code OUTPUT_VAR)
    file(GLOB_RECURSE src "*.cpp" "*.h")
    set(fileList "")
    foreach(child ${src})
        LIST(APPEND fileList ${child})
        # message("append value " ${child})
    endforeach()
    set(${OUTPUT_VAR} ${fileList} PARENT_SCOPE)
    # message(STATUS "[end src] " ${fileList})
endfunction()

include(./ConfigFile/ACore.cmake)
include(./ConfigFile/ACorePackageConfig.cmake)

message(STATUS "End ACoreBaseConfig")
