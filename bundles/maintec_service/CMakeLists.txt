# Licensed to the Apache Software Foundation (ASF) under one
# or more contributor license agreements.  See the NOTICE file
# distributed with this work for additional information
# regarding copyright ownership.  The ASF licenses this file
# to you under the Apache License, Version 2.0 (the
# "License"); you may not use this file except in compliance
# with the License.  You may obtain a copy of the License at
# 
#   http://www.apache.org/licenses/LICENSE-2.0
# 
# Unless required by applicable law or agreed to in writing,
# software distributed under the License is distributed on an
# "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
# KIND, either express or implied.  See the License for the
# specific language governing permissions and limitations
# under the License.

add_celix_bundle(maintec_service
    SOURCES
        src/process_impl
        src/maintec_service_activator
    SYMBOLIC_NAME "maintec_service"
    VERSION 1.0.0
)

target_include_directories(maintec_service PRIVATE src)
target_link_libraries(maintec_service PRIVATE Celix::rsa_spi maintec_api)

get_target_property(DESCR maintec_api INTERFACE_DESCRIPTOR)
celix_bundle_files(maintec_service ${DESCR} DESTINATION .)
