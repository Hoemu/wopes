file(GLOB_RECURSE children_h "${CMAKE_CURRENT_SOURCE_DIR}/depends/acore/*.h")
file(GLOB_RECURSE children_cpp "${CMAKE_CURRENT_SOURCE_DIR}/depends/acore/*.cpp")

set(acore_src ${children_h} ${children_cpp})

message("CPP FILE:" ${children_cpp})
