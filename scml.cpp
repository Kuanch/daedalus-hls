/*
 * SCML2 Memory Example
 *
 * Demonstrates TLM2.0 memory model using SCML2 library with target port adaptor
 *
 * Compile with:
 * g++-9 -Wall -I. -I$SYSTEMC_HOME/include -I$SCML_HOME/include \
 *       -L$SYSTEMC_HOME/lib-linux64 -L$SCML_HOME/lib-linux64 \
 *       scml.cpp -lsystemc -lscml2 -o scml
 */
#include <scml2.h>
#include <tlm.h>
#include <systemc>

#include "Memcheck.h"

class ExampleMem : public sc_core::sc_module
{
private:
  static const unsigned int MEMORY_SIZE = 0x10000;

public:
  tlm::tlm_target_socket<32> target_socket;

public:
  SC_HAS_PROCESS(ExampleMem);

  explicit ExampleMem(sc_core::sc_module_name name) :
    sc_core::sc_module(name),
    target_socket("target_socket"),
    mMemory("mMemory", MEMORY_SIZE >> 2)
  {
    p_adaptor = scml2::target_port_adaptor::create("p_adaptor", &target_socket);
    (*p_adaptor)(mMemory);
  }

private:
    scml2::target_port_adaptor *p_adaptor;
    scml2::memory<unsigned int> mMemory;
};


int sc_main(int argc, char* argv[])
{
  MemoryCheck memoryCheck_1("memoryCheck_1");
  ExampleMem exampleMem("exampleMem");

  memoryCheck_1.socket(exampleMem.target_socket);

  sc_core::sc_start();

  return 0;
}

