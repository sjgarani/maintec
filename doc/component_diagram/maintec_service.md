``` plantuml
@startuml

package maintec_service {
    LaserService - [laser_service]

    component Celix {
        [rsa_discovery_configured]
        [rsa_topology_manager]
        [rsa_dfi]
        [shell]
        [remote_shell]
    }
}

@enduml
```