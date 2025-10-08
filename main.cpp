/*
Compile with:
g++ -I. -I$SYSTEMC_HOME/include -L$SYSTEMC_HOME/lib-linux64 -Wl,-rpath=$SYSTEMC_HOME/lib-linux64 -o main main.cpp tb.cpp -lsystemc -lm
*/
#include <iostream>
#include <systemc.h>

SC_MODULE(Master) {
    sc_out<bool> HWRITE;
    sc_out<sc_uint<32>> HADDR;
    sc_out<sc_uint<32>> HWDATA;
    sc_in<bool> HREADY;
    sc_in<sc_uint<32>> HRDATA;

    void master_thread() {
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
        cout << "Read Data: " << data << endl;
    }

    SC_CTOR(Master) {
        SC_THREAD(master_thread);
    }
};

SC_MODULE(Slave) {
    sc_in<bool> HWRITE;
    sc_in<sc_uint<32>> HADDR;
    sc_in<sc_uint<32>> HWDATA;
    sc_out<bool> HREADY;
    sc_out<sc_uint<32>> HRDATA;

    sc_uint<32> memory[256];

    void slave_thread() {
        while (true) {
            wait();
            HREADY.write(false);
            if (HWRITE.read()) {
                // Write operation
                memory[HADDR.read()] = HWDATA.read();
            } else {
                // Read operation
                HRDATA.write(memory[HADDR.read()]);
            }
            HREADY.write(true);
        }
    }

    SC_CTOR(Slave) {
        SC_THREAD(slave_thread);
        sensitive << HWRITE << HADDR << HWDATA;
    }
};

SC_MODULE(Testbench) {
    sc_out<bool> HWRITE;
    sc_out<sc_uint<32>> HADDR;
    sc_out<sc_uint<32>> HWDATA;
    sc_in<bool> HREADY;
    sc_in<sc_uint<32>> HRDATA;

    void testbench_thread() {
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
        cout << "Read Data: " << data << endl;
    }

    SC_CTOR(Testbench) {
        SC_THREAD(testbench_thread);
    }
};

int sc_main(int argc, char* argv[]) {
    sc_signal<bool> HWRITE;
    sc_signal<sc_uint<32>> HADDR;
    sc_signal<sc_uint<32>> HWDATA;
    sc_signal<bool> HREADY;
    sc_signal<sc_uint<32>> HRDATA;

    Master master("master");
    Slave slave("slave");

    // Connect signals
    master.HWRITE(HWRITE);
    master.HADDR(HADDR);
    master.HWDATA(HWDATA);
    master.HREADY(HREADY);
    master.HRDATA(HRDATA);

    slave.HWRITE(HWRITE);
    slave.HADDR(HADDR);
    slave.HWDATA(HWDATA);
    slave.HREADY(HREADY);
    slave.HRDATA(HRDATA);

    // Start simulation
    sc_start();

    return 0;
}
