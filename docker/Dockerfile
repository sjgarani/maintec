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
    git clone https://github.com/redis/hiredis.git && \
    git clone https://github.com/sewenew/redis-plus-plus.git && \
    git clone --branch docker https://github.com/sjgarani/maintec.git


WORKDIR /opt/celix
RUN mkdir build && \
    cd build && \
    cmake -DCMAKE_BUILD_TYPE=RelWithDebInfo .. && \
    make && \
    make install && \
    cd ../.. && \
    rm -Rf celix

WORKDIR /opt/hiredis
RUN make && \
    make install && \
    cd .. && \
    rm -Rf hiredis

WORKDIR /opt/redis-plus-plus
RUN mkdir build && \
    cd build && \
    cmake -DCMAKE_BUILD_TYPE=Release .. && \
    make && \
    make install && \
    cd ../.. && \
    rm -Rf redis-plus-plus

WORKDIR /opt/maintec
RUN git submodule update --init libs/nlohmann_json && \
    mkdir build && \
    cd build && \
    cmake .. && \
    make

COPY data/start_endpoint.sh /opt/start_endpoint.sh
RUN chmod +x /opt/start_endpoint.sh
COPY data/start_maintec.sh /opt/start_maintec.sh
RUN chmod +x /opt/start_maintec.sh

EXPOSE 6666
