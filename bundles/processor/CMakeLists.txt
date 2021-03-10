add_celix_bundle(HttpProcessorBundle
    VERSION 1.0.0
	SOURCES
        src/HttpProcessorActivator.cc
        src/processor/ChainProcessor.h
        src/processor/HttpMethodProcessor.cc
)

target_link_libraries(HttpProcessorBundle PRIVATE MaintecApi)
target_link_libraries(HttpProcessorBundle PRIVATE nlohmann_json::nlohmann_json)
