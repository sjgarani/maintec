#${WS}/maintec/bundles/maintec/CMakeLists.txt

add_celix_bundle(BringUpBundle
    VERSION 1.0.0
	SOURCES
        src/BringUpActivator.cc
)

target_link_libraries(BringUpBundle PRIVATE Celix::shell_api)