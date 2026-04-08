#pragma once
#include <vector>
#include <string>

// Structure mimicking a physically read Li-ion cell data
struct CellData {
    int id;
    double voltage;      // Volts
    double temperature;  // Celsius
};

class BMS_Controller {
private:
    std::vector<CellData> cells;
    bool system_safe;
    
    // Safety Thresholds 
    const double OVERVOLTAGE_LIMIT = 4.25;
    const double UNDERVOLTAGE_LIMIT = 3.20;
    const double OVERTEMP_LIMIT = 60.0;
    
    void triggerKillSwitch(const std::string& reason);

public:
    BMS_Controller();
    
    // Add a cell to the pack
    void addCell(int id, double initial_voltage, double initial_temp);
    
    // Simulates receiving SPI/I2C data from the physical battery balancing ICs
    void updateCellData(int id, double new_voltage, double new_temp);
    
    // Hardware protection loop (Usually runs very fast, e.g. 100 Hz in RTOS)
    void executeSafetyLoop();
    
    bool isSystemSafe() const;
};
