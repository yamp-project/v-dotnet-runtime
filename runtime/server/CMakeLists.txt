project("v-dotnet-runtime-server" CXX)

link_directories(${CMAKE_SOURCE_DIR}/lib/server)

file(GLOB_RECURSE PROJECT_SOURCE_FILES "src/*.h" "src/*.cpp")
add_library(${PROJECT_NAME} SHARED ${PROJECT_SOURCE_FILES})

include_directories(${CMAKE_SOURCE_DIR}/vendors/nethost)

target_link_libraries(${PROJECT_NAME} nethost)
