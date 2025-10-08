#ifndef EXAMPLE_MEM_H
#define EXAMPLE_MEM_H

#include <scml2.h>
#include <tlm.h>
#include <systemc>

class ExampleMem : public sc_core::sc_module
{
private:
  static const unsigned int MEMORY_SIZE = 0x10000;

public:
  tlm::tlm_target_socket<32> target_socket;

public:
  SC_HAS_PROCESS(ExampleMem);

  explicit ExampleMem(sc_core::sc_module_name name);

private:
    scml2::target_port_adaptor *p_adaptor;
    scml2::memory<unsigned int> mMemory;
};

#endif // EXAMPLE_MEM_H
