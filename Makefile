# Makefile for SystemC Examples
# Requires: SYSTEMC_HOME and SCML_HOME environment variables

# Compiler settings
CXX := g++
CXX_SCML := g++-9
CXXFLAGS := -Wall -I./include -I$(SYSTEMC_HOME)/include
LDFLAGS := -L$(SYSTEMC_HOME)/lib-linux64 -Wl,-rpath=$(SYSTEMC_HOME)/lib-linux64
LIBS := -lsystemc -lm

# SCML specific flags
SCML_CXXFLAGS := -Wall -I./include -I$(SYSTEMC_HOME)/include -I$(SCML_HOME)/include
SCML_LDFLAGS := -L$(SYSTEMC_HOME)/lib-linux64 -L$(SCML_HOME)/lib-linux64
SCML_LIBS := -lsystemc -lscml2

# Build directories
BUILD_DIR := build
EXAMPLES_DIR := examples

# Targets
.PHONY: all clean ahb buffer tlm help

all: ahb buffer

help:
	@echo "Available targets:"
	@echo "  all       - Build AHB and Buffer examples (default)"
	@echo "  ahb       - Build AHB bus example"
	@echo "  buffer    - Build FIFO buffer example"
	@echo "  tlm       - Build TLM memory example (requires SCML)"
	@echo "  clean     - Remove all built files"
	@echo ""
	@echo "Environment variables required:"
	@echo "  SYSTEMC_HOME - Path to SystemC installation"
	@echo "  SCML_HOME    - Path to SCML2 installation (for TLM example)"

# AHB Bus Example
ahb: $(BUILD_DIR)/ahb_example

$(BUILD_DIR)/ahb_example: $(EXAMPLES_DIR)/ahb/main.cpp \
                          $(EXAMPLES_DIR)/ahb/Master.cpp \
                          $(EXAMPLES_DIR)/ahb/Slave.cpp \
                          $(EXAMPLES_DIR)/ahb/Testbench.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $^ $(LIBS)
	@echo "Built AHB example: $@"

# Buffer Example
buffer: $(BUILD_DIR)/buffer_example

$(BUILD_DIR)/buffer_example: $(EXAMPLES_DIR)/buffer/main.cpp \
                             $(EXAMPLES_DIR)/buffer/Buffer.cpp \
                             $(EXAMPLES_DIR)/buffer/BufferTestbench.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $^ $(LIBS)
	@echo "Built Buffer example: $@"

# TLM Memory Example (requires SCML)
tlm: $(BUILD_DIR)/tlm_example

$(BUILD_DIR)/tlm_example: $(EXAMPLES_DIR)/tlm_memory/main.cpp \
                          $(EXAMPLES_DIR)/tlm_memory/ExampleMem.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX_SCML) $(SCML_CXXFLAGS) $(SCML_LDFLAGS) -o $@ $^ $(SCML_LIBS)
	@echo "Built TLM example: $@"

# Clean
clean:
	rm -rf $(BUILD_DIR)
	@echo "Cleaned build directory"
