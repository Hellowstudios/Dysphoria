FROM ubuntu:22.04

# install dependencies
RUN apt update && apt install -y \
    build-essential \
    ninja-build \
    cmake \
    git \
    wget \
    python3 \
    python3-pip \
    libx11-dev \
    libxcursor-dev \
    libxrandr-dev \
    libxi-dev \
    libgl1-mesa-dev \
    libglu1-mesa-dev \
    libxinerama-dev \
    libxxf86vm-dev \
    libxext-dev

# install more dependencies
RUN wget https://github.com/Kitware/CMake/releases/download/v3.28.3/cmake-3.28.3-linux-x86_64.sh && \
    chmod +x cmake-3.28.3-linux-x86_64.sh && \
    mkdir -p /opt/cmake-3.28 && \
    ./cmake-3.28.3-linux-x86_64.sh --prefix=/opt/cmake-3.28 --skip-license && \
    ln -s /opt/cmake-3.28/bin/* /usr/local/bin/ && \
    rm cmake-3.28.3-linux-x86_64.sh

# install even more dependencies
RUN pip3 install meson ninja

# working directory for the container
WORKDIR /workspace

# copy the current directory contents into the container at /workspace
COPY . /workspace

# Open docker bash when the container starts
CMD ["/bin/bash"]
