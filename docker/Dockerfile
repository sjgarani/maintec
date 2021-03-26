FROM maintec/node

RUN git clone --branch remote https://github.com/sjgarani/maintec.git && \
    cd maintec && \
    mkdir build && \
    cd build && \
    cmake .. && \
    make

EXPOSE 6666
EXPOSE 9999
EXPOSE 18888
EXPOSE 28888
