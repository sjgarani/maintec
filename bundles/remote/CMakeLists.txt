
add_subdirectory(calculator_api)
add_subdirectory(calculator_service)
add_subdirectory(calculator_shell)

if (BUILD_RSA_DISCOVERY_ETCD AND BUILD_RSA_REMOTE_SERVICE_ADMIN_DFI)
    add_celix_container(remote-services-dfi
        NAME "server"
        GROUP "remote-services/remote-services-dfi"
        BUNDLES
            Celix::rsa_discovery_etcd
            Celix::rsa_topology_manager
            Celix::rsa_dfi
            Celix::shell
            Celix::shell_tui
            Celix::log_admin
            calculator
        PROPERTIES
            RSA_PORT=18888
    )

    add_celix_container(remote-services-dfi-client
        NAME "client"
        GROUP "remote-services/remote-services-dfi"
        BUNDLES
            Celix::rsa_topology_manager
            Celix::rsa_dfi
            Celix::shell
            Celix::shell_tui
            Celix::log_admin
            Celix::rsa_discovery_etcd
            calculator_shell
        PROPERTIES
            RSA_PORT=28888
    )
endif ()