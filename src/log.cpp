#include "log.h"

#include <stdio.h>
#include <string>
#include <mutex>
#include <thread>
#include <unordered_map>

namespace {
std::unordered_map<std::thread::id, int> routine_num_map;
int next = 0;
std::mutex log_mutex;
void register_() {
    std::lock_guard<std::mutex> lock(log_mutex);
    if (routine_num_map.find(std::this_thread::get_id()) ==
        routine_num_map.end()) {
        routine_num_map[std::this_thread::get_id()] = next;
    }
    next++;
    return;
}
}  // namespace

void QuickLog(std::string header, std::string log) {
    ::register_();
    std::lock_guard<std::mutex> lock(::log_mutex);
    printf("[%s] %d:%s\n", header.data(), ::routine_num_map[std::this_thread::get_id()], log.data());
    return;
}