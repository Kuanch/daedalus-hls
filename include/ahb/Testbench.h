#ifndef AHB_TESTBENCH_H
#define AHB_TESTBENCH_H

#include <systemc.h>

SC_MODULE(Testbench) {
    sc_out<bool> HWRITE;
    sc_out<sc_uint<32>> HADDR;
    sc_out<sc_uint<32>> HWDATA;
    sc_in<bool> HREADY;
    sc_in<sc_uint<32>> HRDATA;

    void testbench_thread();

    SC_CTOR(Testbench) {
        SC_THREAD(testbench_thread);
    }
};

#endif // AHB_TESTBENCH_H
