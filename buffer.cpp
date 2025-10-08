#include <systemc.h>
#include <queue>

// Buffer Module
SC_MODULE(Buffer) {
    sc_in<bool> clk;
    sc_in<bool> reset;
    sc_in<bool> write_enable;
    sc_in<int> write_data;
    sc_in<bool> read_enable;
    sc_out<int> read_data;
    sc_out<bool> full;
    sc_out<bool> empty;

    std::queue<int> buffer;
    int max_size;

    void buffer_process() {
        if (reset.read()) {
            // Clear the buffer on reset
            while (!buffer.empty()) buffer.pop();
            full.write(false);
            empty.write(true);
            read_data.write(0);
        } else {
            // Write operation
            if (write_enable.read() && !full.read()) {
                buffer.push(write_data.read());
            }
            // Read operation
            if (read_enable.read() && !empty.read()) {
                int data = buffer.front();
                buffer.pop();
                read_data.write(data);
            }
            // Update status flags
            full.write(buffer.size() >= max_size);
            empty.write(buffer.empty());
        }
    }

    SC_CTOR(Buffer) : max_size(16) { // Example buffer size
        SC_METHOD(buffer_process);
        sensitive << clk.pos();
    }
};

// Buffer Testbench
SC_MODULE(BufferTestbench) {
    // Clock and reset signals
    sc_clock clk;
    sc_signal<bool> reset;

    // Buffer interface signals
    sc_signal<bool> write_enable;
    sc_signal<int> write_data;
    sc_signal<bool> read_enable;
    sc_signal<int> read_data;
    sc_signal<bool> full;
    sc_signal<bool> empty;

    // Instantiate the buffer module
    Buffer buffer_inst;

    void test_process() {
        // Initialize signals
        reset.write(true);
        write_enable.write(false);
        read_enable.write(false);
        wait(2, SC_NS);
        reset.write(false);

        // Test write operations
        cout << "Starting write operations..." << endl;
        if (!full.read()) {
            write_enable.write(true);
            write_data.write(0x28);
            wait(clk.posedge_event());
            cout << "Time: " << sc_time_stamp()
                    << " | Written Data: 0x" << hex << 0x28
                    << " | Full: " << full.read()
                    << " | Empty: " << empty.read() << endl;
        } else {
            cout << "Buffer is full at time " << sc_time_stamp() << endl;
            write_enable.write(false);
        }
        write_enable.write(false);

        // Test read operations
        cout << "Starting read operations..." << endl;
        read_enable.write(true);
        while (!empty.read()) {
            wait(clk.posedge_event());
            cout << "Time: " << sc_time_stamp()
                    << " | Read Data: 0x" << hex << read_data.read() << endl;
        }
        read_enable.write(false);

        // Finish simulation
        sc_stop();
    }

    SC_CTOR(BufferTestbench)
        : clk("clk", 10, SC_NS), buffer_inst("buffer_inst") {
        // Connect signals to buffer
        buffer_inst.clk(clk);
        buffer_inst.reset(reset);
        buffer_inst.write_enable(write_enable);
        buffer_inst.write_data(write_data);
        buffer_inst.read_enable(read_enable);
        buffer_inst.read_data(read_data);
        buffer_inst.full(full);
        buffer_inst.empty(empty);

        // Register the test process
        SC_THREAD(test_process);
    }
};

int sc_main(int argc, char* argv[]) {
    BufferTestbench tb("tb");
    sc_start();
    return 0;
}
