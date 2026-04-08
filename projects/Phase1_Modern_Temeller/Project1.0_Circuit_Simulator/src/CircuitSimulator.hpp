#ifndef CIRCUIT_SIMULATOR_HPP
#define CIRCUIT_SIMULATOR_HPP

#include <vector>

struct SimulationResult {
    double time;
    double current;
    double capacitorVoltage;
};

class RLC_Circuit {
private:
    double R; // Resistance (Ohm)
    double L; // Inductance (Henry)
    double C; // Capacitance (Farad)
    double dt; // Time step

public:
    RLC_Circuit(double r, double l, double c, double time_step);
    
    // Solves the circuit state equations using Runge-Kutta 4 (RK4)
    // Returns a vector of results over the specified total time
    std::vector<SimulationResult> simulate(double total_time, double input_voltage);
};

#endif
