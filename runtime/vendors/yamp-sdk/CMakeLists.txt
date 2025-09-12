cmake_minimum_required(VERSION 3.22)
project("yamp-sdk" C)

file(GLOB_RECURSE CSDK_HEADER_FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h
)

add_library(${PROJECT_NAME} INTERFACE ${CSDK_HEADER_FILES})
add_library(yamp::sdk ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)
#set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE C)