```plantuml
@startuml

package maintec {
    [BringUp] ..> [API]
    [HttpProcessor] ..> [API]
    [BringUp] --> IProcessor
    IProcessor - [HttpProcessor]
    
    component Celix {
        [BringUp] ..> [ShellCxx]
        [remote_shell]
    }
}

@enduml
```