``` plantuml
@startuml

package maintec_api {
    interface Laser {
        void setLaser(boolean state)
        boolean getLaser()
    }
}

@enduml
```