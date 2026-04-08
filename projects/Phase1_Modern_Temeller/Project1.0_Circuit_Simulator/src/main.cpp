#include <iostream>
#include <fstream>
#include "CircuitSimulator.hpp"

int main() {
    std::cout << "[Meta-Engineering] Otonom Urun Gelistirici - Proje 1.0" << std::endl;
    std::cout << "--------------------------------------------------------" << std::endl;
    std::cout << "Starting RLC Circuit Numerical Simulation (RK4 Method)..." << std::endl;

    // Component Parameters: R = 10 Ohms, L = 0.1 Henry, C = 0.001 Farad
    double R = 10.0;
    double L = 0.1;
    double C = 0.001;
    
    // Simulation Parameters
    double dt = 0.0001; // 100 microseconds logic step
    double total_time = 0.5; // Simulate for 0.5 seconds
    double V_in = 5.0; // 5V Step Input Signal

    std::cout << "Parameters -> R: " << R << " Ohm | L: " << L << " H | C: " << C << " F" << std::endl;
    std::cout << "Input Voltage: " << V_in << " V | Time Step: " << dt << " s" << std::endl;

    RLC_Circuit circuit(R, L, C, dt);
    
    // Run the Math Engine
    auto results = circuit.simulate(total_time, V_in);

    // Export Data Pipeline
    std::string filename = "simulation_results.csv";
    std::ofstream file(filename);
    file << "Time(s),Current(A),CapacitorVoltage(V)\n";
    for (const auto& res : results) {
        file << res.time << "," << res.current << "," << res.capacitorVoltage << "\n";
    }
    file.close();

    std::cout << "Simulation Complete. Results written to: " << filename << std::endl;
    std::cout << "Siradaki Gorev: Bu CSV dosyasini Python ile gorsellestirmek." << std::endl;
    
    return 0;
}
