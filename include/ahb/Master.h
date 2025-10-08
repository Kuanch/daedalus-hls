#ifndef AHB_MASTER_H
#define AHB_MASTER_H

#include <systemc.h>

SC_MODULE(Master) {
    sc_out<bool> HWRITE;
    sc_out<sc_uint<32>> HADDR;
    sc_out<sc_uint<32>> HWDATA;
    sc_in<bool> HREADY;
    sc_in<sc_uint<32>> HRDATA;

    void master_thread();

    SC_CTOR(Master) {
        SC_THREAD(master_thread);
    }
};

#endif // AHB_MASTER_H
