# 这个页面主要写一些工具函数
function(get_no_sufix_dir OUTPUT_VAR_NO_SUFIC_DIR TARGET_PATH)
    get_filename_component(file_name ${TARGET_PATH} NAME)
    string(REGEX REPLACE "${file_name}" "" no_sufix_file_dir "${TARGET_PATH}")
    set(var "")
    if(no_sufix_file_dir MATCHES ${CMAKE_CURRENT_SOURCE_DIR})
        string(REGEX REPLACE "${CMAKE_CURRENT_SOURCE_DIR}" "" var "${no_sufix_file_dir}")
    elseif(no_sufix_file_dir MATCHES ${CMAKE_CURRENT_BINARY_DIR})
        string(REGEX REPLACE "${CMAKE_CURRENT_BINARY_DIR}\include" "" var "${no_sufix_file_dir}")
    endif()
    set(${OUTPUT_VAR_NO_SUFIC_DIR} ${var} PARENT_SCOPE)
    # message("target file " ${TARGET_PATH} "   " ${OUTPUT_VAR_NO_SUFIC_DIR})
endfunction()

function(link_depends_dir OUTPUT_VAR_LINK_DIR)

endfunction()
