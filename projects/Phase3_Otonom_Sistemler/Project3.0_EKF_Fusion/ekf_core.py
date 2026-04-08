import numpy as np

print("[Meta-Engineering] Phase 3: 1D Basic Kalman Filter for Sensor Fusion")
print("-" * 50)

# In autonomous systems, we never trust a single sensor.
# A Kalman filter estimates the true state (e.g. position) combining prediction (physics) 
# and update (measurements with noise).

# 1. Initialize State
x = np.array([[0.0]]) # Initial position
P = np.array([[1000.0]]) # High initial uncertainty

# 2. Physics / Process Model (F, Q)
F = np.array([[1.0]]) # State transition matrix (Position remains same without velocity model here for simplicity)
Q = np.array([[0.1]]) # Process noise covariance (Math physics error)

# 3. Measurement Model (H, R)
H = np.array([[1.0]]) # Measurement matrix (Maps state to sensor measurement)
R = np.array([[10.0]]) # Measurement noise covariance (Sensor is noisy!)

# Simulated Noisy Sensor Readings
measurements = [1.2, 2.1, 2.8, 4.3, 5.0, 6.2, 6.8]

print(f"Initial State:\n{x}\n")

for i, z in enumerate(measurements):
    # ==========================
    # STEP 1: PREDICT (PHYSICS)
    # ==========================
    x_pred = np.dot(F, x)
    P_pred = np.dot(F, np.dot(P, F.T)) + Q

    # ==========================
    # STEP 2: UPDATE (SENSOR FUSION)
    # ==========================
    # Calculate Kalman Gain (K)
    S = np.dot(H, np.dot(P_pred, H.T)) + R
    K = np.dot(P_pred, np.dot(H.T, np.linalg.inv(S)))

    # Compute Error (Residual) between sensor measurement and prediction
    y = np.array([[z]]) - np.dot(H, x_pred)

    # Update State with Kalman Gain
    x = x_pred + np.dot(K, y)
    
    # Update Covariance (Uncertainty drops over time)
    I = np.eye(P.shape[0])
    P = np.dot((I - np.dot(K, H)), P_pred)

    print(f"Iter {i+1} | Raw Sensor: {z:.2f} | Filtered True State (x): {x[0][0]:.3f} | Uncertainty (P): {P[0][0]:.3f}")

print("\n[System] Filter converged. Next step: Implement an Extended Kalman Filter (EKF) in ROS2 with C++.")
