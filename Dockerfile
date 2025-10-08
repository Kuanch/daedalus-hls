FROM ubuntu:22.04

# Avoid interactive prompts during build
ENV DEBIAN_FRONTEND=noninteractive

# Install dependencies
RUN apt-get update && apt-get install -y \
    build-essential \
    g++-9 \
    gcc-9 \
    cmake \
    wget \
    tar \
    git \
    vim \
    && rm -rf /var/lib/apt/lists/*

# Set g++-9 as default
RUN update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-9 90 \
    --slave /usr/bin/g++ g++ /usr/bin/g++-9

# Create working directories
WORKDIR /opt

# Install SystemC 2.3.3
RUN wget https://www.accellera.org/images/downloads/standards/systemc/systemc-2.3.3.tar.gz && \
    tar -xzf systemc-2.3.3.tar.gz && \
    cd systemc-2.3.3 && \
    mkdir build && cd build && \
    ../configure --prefix=/opt/systemc && \
    make -j$(nproc) && \
    make install && \
    cd /opt && \
    rm -rf systemc-2.3.3 systemc-2.3.3.tar.gz

# Install SCML2 (using latest available version)
# Note: SCML2 may require downloading from Accellera or vendor site
# This is a placeholder - adjust URL/version as needed
RUN mkdir -p /opt/scml && \
    echo "Note: SCML2 must be manually installed or obtained from vendor" > /opt/scml/README.txt

# Set environment variables
ENV SYSTEMC_HOME=/opt/systemc
ENV SCML_HOME=/opt/scml
ENV LD_LIBRARY_PATH=$SYSTEMC_HOME/lib-linux64:$SCML_HOME/lib-linux64:$LD_LIBRARY_PATH

# Create workspace
WORKDIR /workspace

# Copy project files
COPY . /workspace/

# Default command
CMD ["/bin/bash"]
