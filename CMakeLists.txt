cmake_minimum_required(VERSION 3.10)

project(Filter)

find_package(Git QUIET)

if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
    execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                    RESULT_VARIABLE GIT_SUBMOD_RESULT)
    if(NOT GIT_SUBMOD_RESULT EQUAL "0")
        message(FATAL_ERROR "git submodule update --init --recursive failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
    endif()
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_executable(Filtering Source/devel.cpp)
    install(TARGETS Filtering 
        DESTINATION ${PROJECT_SOURCE_DIR}/Devel/)     
elseif(CMAKE_BUILD_TYPE STREQUAL "Releas")
    add_executable(Filtering Source/main.cpp)
    install(TARGETS Filtering 
        DESTINATION ${PROJECT_BINARY_DIR}) 
endif()

add_compile_definitions(NOT_ROOT_USE=true)

target_link_libraries(Filtering Filter GenLib INI_File)
target_link_libraries(Filtering -static)


target_include_directories(Filtering PUBLIC
                          "${PROJECT_BINARY_DIR}"
                          "${PROJECT_SOURCE_DIR}/Source/"                     
                          )

add_subdirectory(Source)
add_subdirectory(Source/INI_File/Source)
add_subdirectory(Source/INI_File/Source/GenLib/Source)
