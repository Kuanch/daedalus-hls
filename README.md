# Daedalus-HLS

SystemC hardware simulation examples demonstrating various hardware modeling concepts.

## Overview

This repository contains three SystemC examples:

1. **AHB Bus Simulation** (`main.cpp`) - AMBA AHB protocol with Master/Slave modules
2. **FIFO Buffer** (`buffer.cpp`) - Queue-based buffer with testbench
3. **TLM2.0 Memory** (`scml.cpp`, `Memcheck.h`) - Transaction-level memory model using SCML2

## Prerequisites

- SystemC library (set `$SYSTEMC_HOME`)
- SCML2 library (set `$SCML_HOME` for TLM examples)
- g++ compiler (g++-9 or later recommended)

## Building

### AHB Bus Example
```bash
g++ -I. -I$SYSTEMC_HOME/include -L$SYSTEMC_HOME/lib-linux64 \
    -Wl,-rpath=$SYSTEMC_HOME/lib-linux64 \
    -o main main.cpp -lsystemc -lm
```

### Buffer Example
```bash
g++ -I. -I$SYSTEMC_HOME/include -L$SYSTEMC_HOME/lib-linux64 \
    -Wl,-rpath=$SYSTEMC_HOME/lib-linux64 \
    -o buffer buffer.cpp -lsystemc -lm
```

### SCML2 TLM Example
```bash
g++-9 -Wall -I. -I$SYSTEMC_HOME/include -I$SCML_HOME/include \
      -L$SYSTEMC_HOME/lib-linux64 -L$SCML_HOME/lib-linux64 \
      scml.cpp -lsystemc -lscml2 -o scml
```

## Running

Simply execute the compiled binaries:
```bash
./main
./buffer
./scml
```

## Project Structure

- `main.cpp` - AHB bus protocol implementation
- `buffer.cpp` - FIFO buffer with testbench
- `scml.cpp` - SCML2 memory example
- `Memcheck.h` - TLM2.0 memory checker module
- `README.md` - This file
- `.gitignore` - Git ignore rules

## License

See LICENSE file for details.
