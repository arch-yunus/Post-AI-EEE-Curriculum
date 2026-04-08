#include "BMS_Controller.hpp"
#include <iostream>

BMS_Controller::BMS_Controller() {
    system_safe = true;
}

void BMS_Controller::triggerKillSwitch(const std::string& reason) {
    if(system_safe) {
        system_safe = false;
        std::cerr << "\n[!] CRITICAL HARDWARE FAULT DETECTED!" << std::endl;
        std::cerr << "[-] Reason: " << reason << std::endl;
        std::cerr << "[!] FIRING CONTACTOR RELAYS --> OPEN (KILL-SWITCH ENGAGED)" << std::endl;
    }
}

void BMS_Controller::addCell(int id, double initial_voltage, double initial_temp) {
    cells.push_back({id, initial_voltage, initial_temp});
}

void BMS_Controller::updateCellData(int id, double new_voltage, double new_temp) {
    for (auto& cell : cells) {
        if (cell.id == id) {
            cell.voltage = new_voltage;
            cell.temperature = new_temp;
            break; // found the cell
        }
    }
}

void BMS_Controller::executeSafetyLoop() {
    if (!system_safe) return; // If already killed, do nothing (LATCHED FAULT)

    for (const auto& cell : cells) {
        if (cell.voltage > OVERVOLTAGE_LIMIT) {
            triggerKillSwitch("Cell " + std::to_string(cell.id) + " OVERVOLTAGE (" + std::to_string(cell.voltage) + "V)");
            return;
        }
        if (cell.voltage < UNDERVOLTAGE_LIMIT) {
            triggerKillSwitch("Cell " + std::to_string(cell.id) + " UNDERVOLTAGE (" + std::to_string(cell.voltage) + "V)");
            return;
        }
        if (cell.temperature > OVERTEMP_LIMIT) {
            triggerKillSwitch("Cell " + std::to_string(cell.id) + " THERMAL RUNAWAY (" + std::to_string(cell.temperature) + "C)");
            return;
        }
    }
    std::cout << "[BMS Loop] All " << cells.size() << " cells nominal." << std::endl;
}

bool BMS_Controller::isSystemSafe() const {
    return system_safe;
}
