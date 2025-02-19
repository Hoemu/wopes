# 这个页面主要写一些工具函数

function(get_no_sufix_dir OUTPUT_VAR target_path)
    get_filename_component(file_name ${target_path} NAME)
    string(REGEX REPLACE "${file_name}" "" no_sufix_file_dir "${target_path}")
    set(var "")
    if(no_sufix_file_dir MATCHES ${CMAKE_CURRENT_SOURCE_DIR})
        string(REGEX REPLACE "${CMAKE_CURRENT_SOURCE_DIR}" "" var "${no_sufix_file_dir}")
    elseif(no_sufix_file_dir MATCHES ${CMAKE_CURRENT_BINARY_DIR})
        string(REGEX REPLACE "${CMAKE_CURRENT_BINARY_DIR}\include" "" var "${no_sufix_file_dir}")
    endif()
    set(${OUTPUT_VAR} ${var} PARENT_SCOPE)
    # message("target file " ${target_path} "   " ${OUTPUT_VAR})
endfunction()
