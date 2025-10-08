#ifndef AHB_SLAVE_H
#define AHB_SLAVE_H

#include <systemc.h>

SC_MODULE(Slave) {
    sc_in<bool> HWRITE;
    sc_in<sc_uint<32>> HADDR;
    sc_in<sc_uint<32>> HWDATA;
    sc_out<bool> HREADY;
    sc_out<sc_uint<32>> HRDATA;

    sc_uint<32> memory[256];

    void slave_thread();

    SC_CTOR(Slave) {
        SC_THREAD(slave_thread);
        sensitive << HWRITE << HADDR << HWDATA;
    }
};

#endif // AHB_SLAVE_H
