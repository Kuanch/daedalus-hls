#include "ahb/Slave.h"

void Slave::slave_thread() {
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
