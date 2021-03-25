FROM ubuntu:18.04

RUN apt-get update && \
    apt-get install -y redis wget libssl-dev vim && \
    apt-get clean

RUN apt-get install -yq --no-install-recommends \
    build-essential \
    curl \
    uuid-dev \
    git \
    libjansson-dev \
    libcurl4-openssl-dev \
    default-jdk \
    cmake \
    libffi-dev \
    libxml2-dev && \
    apt-get install -yq --no-install-recommends \
    libczmq-dev && \
    apt-get install -yq --no-install-recommends \
    libcpputest-dev

WORKDIR /opt

RUN wget https://github.com/Kitware/CMake/releases/download/v3.18.6/cmake-3.18.6.tar.gz && \
    tar -zxvf cmake-3.18.6.tar.gz && \
    cd cmake-3.18.6 && \
    ./bootstrap && \
    make && \
    make install && \
    cd .. && \
    rm -Rf cmake-3.18.6*

RUN git clone --single-branch --branch master https://github.com/apache/celix.git && \
    cd celix && \
    mkdir build && \
    cd build && \
    cmake -DCMAKE_BUILD_TYPE=RelWithDebInfo .. && \
    make && \
    make install && \
    cd ../.. && \
    rm -Rf celix

RUN git clone --branch remote https://github.com/sjgarani/maintec.git && \
    cd maintec && \
    mkdir build && \
    cd build && \
    cmake .. && \
    make

EXPOSE 6666
