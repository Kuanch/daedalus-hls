#include "ahb/Testbench.h"
#include <iostream>

void Testbench::testbench_thread() {
    // Example write operation
    HWRITE.write(true);
    HADDR.write(0x00000010);
    HWDATA.write(0xDEADBEEF);
    wait(HREADY.posedge_event());

    // Example read operation
    HWRITE.write(false);
    HADDR.write(0x00000010);
    wait(HREADY.posedge_event());
    sc_uint<32> data = HRDATA.read();
    std::cout << "Read Data: " << data << std::endl;
}
