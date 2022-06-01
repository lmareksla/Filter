cmake_minimum_required(VERSION 3.10)

add_compile_definitions(NOT_ROOT_USE=true)

add_library(Filter STATIC Filter.cpp)

target_include_directories(Filter PUBLIC
                           "${CMAKE_CURRENT_SOURCE_DIR}"
                           "${CMAKE_CURRENT_SOURCE_DIR}/INI_File/Source/"
                           )

target_link_libraries(Filter GenLib INI_File)

install(TARGETS Filter
LIBRARY DESTINATION ${PROJECT_BINARY_DIR}/lib/
ARCHIVE DESTINATION ${PROJECT_BINARY_DIR}/lib/)