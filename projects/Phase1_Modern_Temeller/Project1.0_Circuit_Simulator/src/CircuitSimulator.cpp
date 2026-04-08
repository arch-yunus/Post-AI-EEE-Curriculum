#include "CircuitSimulator.hpp"

RLC_Circuit::RLC_Circuit(double r, double l, double c, double time_step)
    : R(r), L(l), C(c), dt(time_step) {}

std::vector<SimulationResult> RLC_Circuit::simulate(double total_time, double input_voltage) {
    std::vector<SimulationResult> results;
    
    // Initial Conditions
    double q = 0.0; // Initial charge on capacitor
    double i = 0.0; // Initial current
    
    for (double t = 0.0; t <= total_time; t += dt) {
        // Record current state
        double v_c = (C > 0) ? (q / C) : 0.0;
        results.push_back({t, i, v_c});
        
        // System of ODEs:
        // dq/dt = i
        // di/dt = (V - R*i - q/C) / L
        
        auto f1 = [](double current) { return current; };
        auto f2 = [&](double charge, double current) {
            return (input_voltage - R * current - (1.0 / C) * charge) / L;
        };

        // Runge-Kutta 4th Order Implementation
        double k1_q = f1(i);
        double k1_i = f2(q, i);

        double k2_q = f1(i + 0.5 * dt * k1_i);
        double k2_i = f2(q + 0.5 * dt * k1_q, i + 0.5 * dt * k1_i);

        double k3_q = f1(i + 0.5 * dt * k2_i);
        double k3_i = f2(q + 0.5 * dt * k2_q, i + 0.5 * dt * k2_i);

        double k4_q = f1(i + dt * k3_i);
        double k4_i = f2(q + dt * k3_q, i + dt * k3_i);

        // Update states
        q += (dt / 6.0) * (k1_q + 2.0 * k2_q + 2.0 * k3_q + k4_q);
        i += (dt / 6.0) * (k1_i + 2.0 * k2_i + 2.0 * k3_i + k4_i);
    }
    
    return results;
}
