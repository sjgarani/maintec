#!/bin/bash

redis-server &

CELIX_BUNDLES_PATH=/opt/maintec/build/deploy/maintec/bundles /opt/maintec/build/deploy/maintec/maintec
