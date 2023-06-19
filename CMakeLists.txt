cmake_minimum_required(VERSION 3.0.0)
project(image-to-ascii-cpp VERSION 0.1.0)

file(GLOB code_src
    "src/*.cc"
)

add_executable(image-to-ascii-cpp ${code_src})

target_include_directories(image-to-ascii-cpp PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

include(CPack)

if(WIN32) # Windows BITMAP struct conflict
    add_definitions(-DNOGDI)
endif(WIN32)

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

install(TARGETS image-to-ascii-cpp DESTINATION bin)
add_custom_target("uninstall" COMMENT "Uninstall installed files")
add_custom_command(
    TARGET "uninstall"
    POST_BUILD
    COMMENT "Uninstall files with install_manifest.txt"
    COMMAND xargs rm -vf < install_manifest.txt || echo Nothing in
            install_manifest.txt to be uninstalled!
)