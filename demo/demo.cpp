#include <iostream>
#include <mutex>
#include <string>
#include <thread>
#include "log.h"
#include "readwrite.h"

constexpr int routine_steps = 10;

std::mutex running_mutex;

void reader_running() {
    for (int t = 0; t < 3; t++) {
        readwrite::READ_LOCK_GUARD_;
        for (int i = 0; i < routine_steps; i++) {
            std::lock_guard<std::mutex> lock(running_mutex);
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    }
    return;
}

void writer_running() {
    readwrite::WRITE_LOCK_GUARD_;
    for (int i = 0; i < 50; i++) {
        std::lock_guard<std::mutex> lock(running_mutex);
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    return;
}

void multi_reader() {
    std::thread p1(reader_running);
    std::thread p2(reader_running);
    std::thread p3(reader_running);
    std::thread p4(reader_running);
    std::thread p5(reader_running);

    p1.join();
    p2.join();
    p3.join();
    p4.join();
    p5.join();
    return;
}

void multi_writer() {
    std::thread p1(writer_running);
    std::thread p2(writer_running);
    std::thread p3(writer_running);
    std::thread p4(writer_running);
    std::thread p5(writer_running);

    p1.join();
    p2.join();
    p3.join();
    p4.join();
    p5.join();
    return;
}

void multi_writer_reader() {
    std::thread p1(reader_running);
    std::thread p2(writer_running);
    std::thread p3(reader_running);
    std::thread p4(writer_running);
    std::thread p5(reader_running);

    p1.join();
    p2.join();
    p3.join();
    p4.join();
    p5.join();
    return;
}

void writer_first() {
    std::thread p1(reader_running);
    std::thread p2(reader_running);
    std::thread p3(writer_running);

    p1.join();
    p2.join();
    p3.join();
    return;
}

int main() {
    multi_reader();
    multi_writer();
    multi_writer_reader();
    writer_first();
    return 0;
}
