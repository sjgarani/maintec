FROM maintec/node

RUN git clone https://github.com/sjgarani/maintec.git && \
    cd maintec && \
    mkdir build && \
    cd build && \
    cmake .. && \
    make

EXPOSE 6666
EXPOSE 18888
