#${WS}/maintec/bundles/maintec/CMakeLists.txt

add_library(ProcessorApi INTERFACE)
target_include_directories(ProcessorApi INTERFACE include)

add_celix_bundle(MaintecBundle
    VERSION 1.0.0
	SOURCES
        src/MaintecActivator.cc
)

target_link_libraries(MaintecBundle PRIVATE ProcessorApi)
target_link_libraries(MaintecBundle PRIVATE nlohmann_json::nlohmann_json)

add_celix_bundle(HttpProcessorBundle
    VERSION 1.0.0
	SOURCES
        src/HttpProcessorActivator.cc
        src/processor/HttpMethodProcessor.cc
)

target_link_libraries(HttpProcessorBundle PRIVATE ProcessorApi)
target_link_libraries(HttpProcessorBundle PRIVATE nlohmann_json::nlohmann_json)

add_celix_bundle(BringUpBundle
    VERSION 1.0.0
	SOURCES
        src/BringUpActivator.cc
)

target_link_libraries(BringUpBundle PRIVATE ProcessorApi)
target_link_libraries(BringUpBundle PRIVATE Celix::shell_api)