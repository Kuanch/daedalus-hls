#include "tlm_memory/ExampleMem.h"

ExampleMem::ExampleMem(sc_core::sc_module_name name) :
    sc_core::sc_module(name),
    target_socket("target_socket"),
    mMemory("mMemory", MEMORY_SIZE >> 2)
{
    p_adaptor = scml2::target_port_adaptor::create("p_adaptor", &target_socket);
    (*p_adaptor)(mMemory);
}
