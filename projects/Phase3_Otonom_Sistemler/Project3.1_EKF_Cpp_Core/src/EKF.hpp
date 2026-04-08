#pragma once
#include <iostream>

class EKF {
private:
    // Simple 1D EKF State Variables for Demonstration Frame
    double x; // State (Position)
    double P; // Uncertainty Covariance
    double Q; // Process Noise
    double R; // Measurement Noise Sensor
    
public:
    EKF(double initial_x, double initial_p, double process_noise, double measurement_noise);
    
    // Physics Prediction Step
    void predict(double u);
    
    // Sensor Update Step
    void update(double z);
    
    // Getters
    double getState() const;
    double getCovariance() const;
};
