import matplotlib.pyplot as plt
import numpy as np

# --- Enter your measurement data here ---
r1_values = np.array([2000,  2000, 2000,  6800, 6800,  6800,  33000, 33000, 33000, 47000, 47000, 47000])
r2_values = np.array([47000, 6800, 33000, 2000, 33000, 47000, 6800,  2000,  47000, 2000,  33000,  6800])
adc_readings = np.array([982.2, 817.5, 983.0, 231.0, 849.7, 893.6, 173.4, 59.2, 598.9, 41.0, 423.5, 129.0])
# -----------------------------------------

# Constants
V_REF = 3.3  # Reference voltage (Vdd, Vref) [cite: 8]
ADC_MAX_VALUE = 1023.0  # Maximum ADC value (10bit) [cite: 1, 8]

# 1. Calculate theoretical voltage
# V_theory = V_REF * (R2 / (R1 + R2))
theoretical_voltages = V_REF * (r2_values / (r1_values + r2_values))

# 2. Calculate measured voltage
# V_measured = V_REF * (ADC_reading / ADC_MAX_VALUE)
measured_voltages = V_REF * (adc_readings / ADC_MAX_VALUE)

# 3. Calculate regression line (using numpy.polyfit: 1st degree regression)
# y = mx + c (m: slope, c: intercept)
slope, intercept = np.polyfit(theoretical_voltages, measured_voltages, 1)

# Regression line X-axis data points (from min to max of theoretical voltage)
regression_x = np.array([theoretical_voltages.min(), theoretical_voltages.max()])
# Regression line Y-axis data points
regression_y = slope * regression_x + intercept

# Calculate R^2 value (coefficient of determination) (optional)
correlation_matrix = np.corrcoef(theoretical_voltages, measured_voltages)
correlation_xy = correlation_matrix[0,1]
r_squared = correlation_xy**2

print(f"Regression line: y = {slope:.4f}x + {intercept:.4f}")
print(f"Coefficient of determination (R^2): {r_squared:.4f}")

# 4. Draw graph
plt.figure(figsize=(10, 6))

# Scatter plot of measured points
plt.scatter(theoretical_voltages, measured_voltages, color='blue', label='Measured Points')

# Regression line
plt.plot(regression_x, regression_y, color='red', linestyle='--', label=f'Regression Line\ny={slope:.3f}x+{intercept:.3f}\n$R^2$={r_squared:.3f}')

# Graph decoration
plt.title('Theoretical Voltage vs Measured Voltage (Exercise 2)', fontsize=16)
plt.xlabel('Theoretical Voltage (V)', fontsize=12)  # [cite: 8]
plt.ylabel('Measured Voltage (V)', fontsize=12)  # [cite: 8]
plt.legend(fontsize=10)
plt.grid(True, linestyle=':', alpha=0.7)
plt.axline((0,0), slope=1, color='gray', linestyle=':', label='Ideal Line (y=x)')  # Add ideal y=x line
plt.xlim(left=0, right=V_REF)  # X-axis range from 0V to V_REF (theoretical values won't exceed this)
plt.ylim(bottom=0, top=V_REF)  # Y-axis range from 0V to V_REF (measured values shouldn't exceed this)
plt.gca().set_aspect('equal', adjustable='box')  # Set equal scale for X and Y axes

# Display the graph
plt.show()