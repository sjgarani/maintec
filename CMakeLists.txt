#${WS}/maintec/CMakeLists.txt

cmake_minimum_required(VERSION 3.4)
project(maintec)

SET(CMAKE_CXX_FLAGS "-std=c++11 -fno-rtti ${CMAKE_CXX_FLAGS}")
SET(CMAKE_CXX_FLAGS_DEBUG "-g -DDEBUG")

find_package(Celix REQUIRED)

add_subdirectory(bundles/maintec_api)
add_subdirectory(bundles/maintec_service)

add_celix_container(maintec
    COPY
    BUNDLES
        Celix::rsa_discovery_etcd
        Celix::rsa_topology_manager
        Celix::rsa_dfi
        Celix::shell
        Celix::remote_shell
        maintec_service
    PROPERTIES
        DISCOVERY_ETCD_SERVER_IP=10.5.0.3
        RSA_PORT=18888
)
