#${WS}/maintec/CMakeLists.txt

cmake_minimum_required(VERSION 3.4)
project(maintec CXX)

SET(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")
SET(CMAKE_CXX_FLAGS_DEBUG "-g -DDEBUG")

find_package(Celix REQUIRED)

add_subdirectory(bundles/maintec_main)

add_celix_container(maintec
    COPY
    USE_CONFIG
    CXX
    BUNDLES
        Celix::shell
        Celix::remote_shell
        maintec_main
)

celix_container_runtime_properties(maintec
    "CELIX_BUNDLES_PATH=/usr/share/celix/bundles"
)