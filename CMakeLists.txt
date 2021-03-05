#${WS}/maintec/CMakeLists.txt

cmake_minimum_required(VERSION 3.4)
project(maintec CXX)

SET(CMAKE_CXX_FLAGS "-std=c++11 -fno-rtti ${CMAKE_CXX_FLAGS}")
SET(CMAKE_CXX_FLAGS_DEBUG "-g -DDEBUG")

find_package(Celix REQUIRED)

add_subdirectory(libs/nlohmann_json)

add_subdirectory(bundles/maintec)

add_celix_container(maintec
    COPY
    CXX
    BUNDLES
        Celix::ShellCxx
        Celix::shell_tui
        MaintecBundle
        HttpProcessorBundle
        BringUpBundle
)

# Celix::shell_tui <- Celix::remote_shell

# <------------ add hiredis dependency --------------->
find_path(HIREDIS_HEADER hiredis)
target_include_directories(maintec PUBLIC ${HIREDIS_HEADER})

find_library(HIREDIS_LIB hiredis)
target_link_libraries(maintec PUBLIC ${HIREDIS_LIB})

# <------------ add redis-plus-plus dependency -------------->
# NOTE: this should be *sw* NOT *redis++*
find_path(REDIS_PLUS_PLUS_HEADER sw)
target_include_directories(maintec PUBLIC ${REDIS_PLUS_PLUS_HEADER})

find_library(REDIS_PLUS_PLUS_LIB redis++)
target_link_libraries(maintec PUBLIC ${REDIS_PLUS_PLUS_LIB})