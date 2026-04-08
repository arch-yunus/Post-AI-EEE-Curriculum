#include <iostream>
#include <chrono>
#include <thread>
#include "BMS_Controller.hpp"

// Synthetic function to simulate the physical battery heating up during a high current draw (e.g. Drone Takeoff)
void simulateTakeoff(BMS_Controller& bms) {
    std::cout << "[Drone] Initiating Max Thrust Takeoff..." << std::endl;
    double current_temp1 = 35.0; // Safe
    double current_temp2 = 40.0; // Safe
    
    // Simulate 5 seconds of flight
    for(int i=0; i<5; ++i) {
        if(!bms.isSystemSafe()) {
            std::cout << "[System] Flight Aborted due to Hardware Protection." << std::endl;
            break;
        }
        
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        
        // Heat rises
        current_temp1 += 4.0;
        current_temp2 += 6.5; // Cell 2 is damaged and heating up too fast!
        
        bms.updateCellData(1, 4.0, current_temp1);
        bms.updateCellData(2, 3.9, current_temp2);
        
        std::cout << "Flight T=" << i 
                  << " | Cell 1 Temp: " << current_temp1 << "C"
                  << " | Cell 2 Temp: " << current_temp2 << "C" << std::endl;
                  
        // Hardware Protection Loop catches it instantly
        bms.executeSafetyLoop(); 
    }
}

int main() {
    std::cout << "[Meta-Engineering] Phase 4.1: C++ Battery Management System (BMS) Firmware" << std::endl;
    std::cout << "==========================================================================" << std::endl;

    BMS_Controller bms;
    
    // Pack of 2 Li-ion cells in series (2S Battery)
    bms.addCell(1, 4.1, 25.0);
    bms.addCell(2, 4.1, 25.0);
    
    std::cout << "BMS Initialized. Checking thresholds..." << std::endl;
    bms.executeSafetyLoop();
    
    simulateTakeoff(bms);

    return 0;
}
