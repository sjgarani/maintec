#${WS}/maintec/CMakeLists.txt

cmake_minimum_required(VERSION 3.4)
project(maintec)

SET(CMAKE_CXX_FLAGS "-std=c++11 -fno-rtti ${CMAKE_CXX_FLAGS}")
SET(CMAKE_CXX_FLAGS_DEBUG "-g -DDEBUG")

find_package(Celix REQUIRED)

add_subdirectory(bundles/maintec_api)
add_subdirectory(bundles/maintec_service)
add_subdirectory(bundles/maintec_endpoint)

add_celix_container(maintec
    COPY
    BUNDLES
        Celix::rsa_discovery_configured
        Celix::rsa_topology_manager
        Celix::rsa_dfi
        Celix::ShellCxx
        Celix::remote_shell
        maintec_service
    PROPERTIES
        RSA_PORT=18888
        DISCOVERY_CFG_SERVER_PORT=10000
        DISCOVERY_CFG_POLL_ENDPOINTS=http://10.5.0.5:10000/org.apache.celix.discovery.configured
)

add_celix_container(endpoint
    COPY
    CXX
    BUNDLES
        Celix::rsa_topology_manager
        Celix::rsa_dfi
        Celix::shell
        Celix::remote_shell
        Celix::rsa_discovery_configured
        maintec_endpoint
    PROPERTIES
        RSA_PORT=28888
        DISCOVERY_CFG_SERVER_PORT=10000
        DISCOVERY_CFG_POLL_ENDPOINTS=http://10.5.0.6:10000/org.apache.celix.discovery.configured
)

# # <------------ add hiredis dependency --------------->
# find_path(HIREDIS_HEADER hiredis)
# target_include_directories(maintec PUBLIC ${HIREDIS_HEADER})
# 
# find_library(HIREDIS_LIB hiredis)
# target_link_libraries(maintec PUBLIC ${HIREDIS_LIB})
# 
# # <------------ add redis-plus-plus dependency -------------->
# # NOTE: this should be *sw* NOT *redis++*
# find_path(REDIS_PLUS_PLUS_HEADER sw)
# target_include_directories(maintec PUBLIC ${REDIS_PLUS_PLUS_HEADER})
# 
# find_library(REDIS_PLUS_PLUS_LIB redis++)
# target_link_libraries(maintec PUBLIC ${REDIS_PLUS_PLUS_LIB})