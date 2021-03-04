#${WS}/maintec/bundles/maintec/CMakeLists.txt

add_library(ProcessorApi INTERFACE)
target_include_directories(ProcessorApi INTERFACE include)

add_celix_bundle(ProcessorBundle
    VERSION 1.0.0
	SOURCES
        src/ProcessorActivator.cc
)

target_link_libraries(ProcessorBundle PRIVATE ProcessorApi)

add_celix_bundle(HttpProcessorBundle
    VERSION 1.0.0
	SOURCES
        src/HttpProcessorActivator.cc
        src/processor/ChainProcessor.h
        src/processor/HttpMethodProcessor.cc
)

target_link_libraries(HttpProcessorBundle PRIVATE ProcessorApi)

add_celix_bundle(BringUpBundle
    VERSION 1.0.0
	SOURCES
        src/BringUpActivator.cc
)

target_link_libraries(BringUpBundle PRIVATE ProcessorApi)
target_link_libraries(BringUpBundle PRIVATE Celix::shell_api)