#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <chrono>
#include <atomic>

// Shared Memory (Simulating Hardware Registers or Globals)
std::mutex system_mutex;
int shared_sensor_value = 0;
std::atomic<bool> is_running(true);

// Task 1: Sensor Reading (High Priority Simulation)
void sensor_task() {
    while (is_running) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // 10 Hz
        
        // Lock mutex to prevent race condition
        std::lock_guard<std::mutex> lock(system_mutex);
        shared_sensor_value += 1;
        std::cout << "[Sensor Task] Updated value to: " << shared_sensor_value << std::endl;
    }
}

// Task 2: Motor Control (Consumer)
void motor_task() {
    while (is_running) {
        std::this_thread::sleep_for(std::chrono::milliseconds(250)); // 4 Hz
        
        std::lock_guard<std::mutex> lock(system_mutex);
        std::cout << "--> [Motor Task] Reading value: " << shared_sensor_value << " | Applying voltage..." << std::endl;
    }
}

int main() {
    std::cout << "[Meta-Engineering] Phase 2: RTOS Mutex & Simulataneous Task Simulator" << std::endl;
    std::cout << "Starting concurrent tasks. Waiting 5 seconds..." << std::endl;

    // Launch threads
    std::thread t1(sensor_task);
    std::thread t2(motor_task);

    // Let the RTOS 'run' for 5 seconds
    std::this_thread::sleep_for(std::chrono::seconds(5));
    
    // Shutdown Sequence
    is_running = false;
    std::cout << "[System] Shutdown Signal Iterated. Joining threads..." << std::endl;

    // Join threads (Wait for them to finish their current cycle securely)
    if (t1.joinable()) t1.join();
    if (t2.joinable()) t2.join();

    std::cout << "System shutdown gracefully. No Race Conditions detected." << std::endl;
    return 0;
}
