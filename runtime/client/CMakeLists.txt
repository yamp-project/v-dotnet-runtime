project("v-dotnet-runtime-client" CXX)

link_directories(${CMAKE_SOURCE_DIR}/lib/client)

file(GLOB_RECURSE PROJECT_SOURCE_FILES "src/*.h" "src/*.cpp")
add_library(${PROJECT_NAME} SHARED ${PROJECT_SOURCE_FILES})
