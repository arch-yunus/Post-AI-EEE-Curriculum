#include "EKF.hpp"

EKF::EKF(double initial_x, double initial_p, double process_noise, double measurement_noise) {
    x = initial_x;
    P = initial_p;
    Q = process_noise;
    R = measurement_noise;
}

void EKF::predict(double u) {
    // x = F*x + B*u
    // Assuming simple 1D velocity addition for predict step
    x = x + u; 
    
    // P = F*P*F^T + Q
    P = P + Q; // Uncertainty always grows during prediction without sensors
}

void EKF::update(double z) {
    // K = P*H^T * (H*P*H^T + R)^-1
    // Simplification for 1D:
    double S = P + R;
    double K = P / S; // Kalman Gain
    
    // y = z - H*x (Residual)
    double y = z - x;
    
    // x = x + K*y
    x = x + (K * y);
    
    // P = (I - K*H) * P
    P = (1.0 - K) * P;
}

double EKF::getState() const {
    return x;
}

double EKF::getCovariance() const {
    return P;
}
