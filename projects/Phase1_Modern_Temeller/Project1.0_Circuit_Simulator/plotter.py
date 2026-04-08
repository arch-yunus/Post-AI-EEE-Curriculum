import pandas as pd
import matplotlib.pyplot as plt
import os

print("[Meta-Engineering] Starting Data Visualization Pipeline...")

file_path = "simulation_results.csv"

if not os.path.exists(file_path):
    print(f"Error: {file_path} not found. Please run the C++ simulator first.")
    exit(1)

# Read the CSV data
df = pd.read_csv(file_path)

# Create a figure with two subplots
fig, (ax1, ax2) = plt.subplots(2, 1, figsize=(10, 8))
fig.suptitle('Proje 1.0: RLC Devresi RK4 Simülasyon Analizi', fontsize=16, fontweight='bold')

# Plot 1: Capacitor Voltage over Time
ax1.plot(df['Time(s)'], df['CapacitorVoltage(V)'], color='b', linewidth=2, label='Kapasitör Voltajı (Vc)')
ax1.set_ylabel('Voltage (V)')
ax1.set_title('Kapasitör Voltajı vs Zaman (Damped Oscillation)')
ax1.grid(True, linestyle='--', alpha=0.7)
ax1.legend()

# Plot 2: Current over Time
ax2.plot(df['Time(s)'], df['Current(A)'], color='r', linewidth=2, label='Bobin Akımı (i)')
ax2.set_xlabel('Time (s)')
ax2.set_ylabel('Current (A)')
ax2.set_title('Devre Akımı vs Zaman')
ax2.grid(True, linestyle='--', alpha=0.7)
ax2.legend()

plt.tight_layout()
plt.savefig('rlc_simulation_plot.png', dpi=300)
print("Plotted successfully! Image saved as 'rlc_simulation_plot.png'.")
plt.show()
