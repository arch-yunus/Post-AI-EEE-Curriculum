#include <iostream>
#include <vector>
#include <iomanip>
#include "EKF.hpp"

int main() {
    std::cout << "[Meta-Engineering] Phase 3.1: Object-Oriented C++ Extended Kalman Filter (EKF)" << std::endl;
    std::cout << "==========================================================================" << std::endl;

    // Init EKF: start pos=0, high initial uncertainty=1000, Process Noise=0.1, Sensor Noise=5.0
    EKF my_ekf(0.0, 1000.0, 0.1, 5.0);

    // Simulated Noisy Lidar / GPS Data
    std::vector<double> noisy_sensor_measurements = {1.2, 2.1, 2.8, 3.7, 4.9, 5.9, 7.1, 8.2};
    double simulated_control_input = 1.0; // Assume we commanded wheel to move 1 unit every step

    std::cout << std::fixed << std::setprecision(3);
    std::cout << "Initial State: " << my_ekf.getState() << " | Initial Covariance (P): " << my_ekf.getCovariance() << std::endl;
    std::cout << "--------------------------------------------------------------------------" << std::endl;

    for(size_t i=0; i<noisy_sensor_measurements.size(); ++i) {
        
        // 1. Predict physics
        my_ekf.predict(simulated_control_input);
        
        // 2. Update with sensor
        my_ekf.update(noisy_sensor_measurements[i]);
        
        std::cout << "Step: " << i+1 
                  << " | Raw Sensor: " << noisy_sensor_measurements[i] 
                  << " | Filtered Truth: " << my_ekf.getState() 
                  << " | Uncertainty (P): " << my_ekf.getCovariance() << std::endl;
    }

    std::cout << "==========================================================================" << std::endl;
    std::cout << "[System] EKF Logic finished. This Class structure can now be injected into ROS2 nodes." << std::endl;

    return 0;
}
