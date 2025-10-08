# Daedalus-SystemC

SystemC hardware simulation examples demonstrating various hardware modeling concepts.

## Overview

This repository contains three SystemC examples:

1. **AHB Bus Simulation** - AMBA AHB protocol with Master/Slave modules
2. **FIFO Buffer** - Queue-based buffer with testbench
3. **TLM2.0 Memory** - Transaction-level memory model using SCML2

## Prerequisites

- SystemC library (set `$SYSTEMC_HOME`)
- SCML2 library (set `$SCML_HOME` for TLM examples)
- g++ compiler (g++-9 or later recommended)
- GNU Make

## Project Structure

```
.
├── include/                 # Header files
│   ├── ahb/                # AHB bus modules
│   ├── buffer/             # FIFO buffer modules
│   └── tlm_memory/         # TLM memory modules
├── examples/               # Example implementations
│   ├── ahb/                # AHB bus example
│   ├── buffer/             # Buffer example
│   └── tlm_memory/         # TLM memory example
├── build/                  # Build output directory
├── Makefile                # Build system
├── Dockerfile              # Docker environment
└── docker-compose.yml      # Docker Compose config
```

## Building

### Using Make (Recommended)

```bash
# Build all examples (AHB + Buffer)
make all

# Build specific examples
make ahb        # AHB bus example
make buffer     # FIFO buffer example
make tlm        # TLM memory example (requires SCML)

# Show help
make help

# Clean build artifacts
make clean
```

### Manual Compilation

If you prefer manual compilation:

```bash
# AHB Bus Example
g++ -Wall -I./include -I$SYSTEMC_HOME/include \
    -L$SYSTEMC_HOME/lib-linux64 -Wl,-rpath=$SYSTEMC_HOME/lib-linux64 \
    examples/ahb/*.cpp -lsystemc -lm -o build/ahb_example

# Buffer Example
g++ -Wall -I./include -I$SYSTEMC_HOME/include \
    -L$SYSTEMC_HOME/lib-linux64 -Wl,-rpath=$SYSTEMC_HOME/lib-linux64 \
    examples/buffer/*.cpp -lsystemc -lm -o build/buffer_example

# TLM Memory Example
g++-9 -Wall -I./include -I$SYSTEMC_HOME/include -I$SCML_HOME/include \
    -L$SYSTEMC_HOME/lib-linux64 -L$SCML_HOME/lib-linux64 \
    examples/tlm_memory/*.cpp -lsystemc -lscml2 -o build/tlm_example
```

## Running

Execute the compiled binaries from the build directory:

```bash
./build/ahb_example
./build/buffer_example
./build/tlm_example
```

## Using Docker

Build and run using Docker:

```bash
# Using docker-compose
docker-compose up -d
docker-compose exec systemc-dev bash

# Inside container
make all
./build/ahb_example

# Or using docker directly
docker build -t daedalus-systemc .
docker run -it -v $(pwd):/workspace daedalus-systemc
```

## Examples Description

### 1. AHB Bus Example
Implements AMBA AHB (Advanced High-performance Bus) protocol:
- **Master Module**: Initiates read/write transactions
- **Slave Module**: Responds to master requests with memory operations
- Demonstrates RTL-level modeling with signals and clocks

### 2. FIFO Buffer Example
Queue-based FIFO buffer implementation:
- **Buffer Module**: 16-element queue with full/empty flags
- **Testbench**: Clock-driven verification
- Demonstrates synchronous hardware design

### 3. TLM Memory Example
Transaction-Level Modeling with SCML2:
- **ExampleMem**: 64KB memory with TLM target socket
- **MemoryCheck**: Initiator performing read/write tests
- Demonstrates abstract system-level modeling

## Learning Path

1. Start with **Buffer example** - simplest, demonstrates basic SystemC concepts
2. Move to **AHB example** - learn bus protocols and signal-level design
3. Advance to **TLM example** - abstract transaction-level modeling

## License

See [LICENSE](LICENSE) file for details.
