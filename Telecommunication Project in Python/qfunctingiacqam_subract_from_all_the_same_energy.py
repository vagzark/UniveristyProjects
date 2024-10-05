import numpy as np
import matplotlib.pyplot as plt
from scipy.special import erfc


def Q(x):
    return 0.5 * erfc(x / np.sqrt(2))

def generate_cqam_radii(dmin, M, N,E_avg):
    # Number of symbols per circle
    n = M // N
    
    # Initialize radii list with R1
    radii = np.zeros(N)
  
    R1 = dmin / (2 * np.sin(np.pi / n))
    radii[0] = R1
    if N > 1:
        radii[1] = np.sqrt(dmin**2 + R1**2 - 2 * R1 * dmin * np.cos(2 * np.pi / n))

    for i in range(2, N):
        R_prev = radii[i-1]
        R_prev_2 = radii[i-2]
        angle_diff = 2 * np.pi / n

        # Calculate radius to maintain dmin with the previous level
        R_next_from_prev = np.sqrt(dmin**2 + R_prev**2 - 2 * R_prev * dmin * np.cos(angle_diff))

        # Calculate radius to maintain dmin with level i-2, taking into account possible angular offset
        angle_offset = (np.pi / n) * ((i % 2) * 2 - (i % 2))
        R_next_from_prev_2 = np.sqrt(dmin**2 + R_prev_2**2 - 2 * R_prev_2 * dmin * np.cos(2 * angle_diff + angle_offset))

        radii[i] = max(R_next_from_prev, R_next_from_prev_2)

    if N > 1:
       radii[N-1]= np.sqrt(N * E_avg - np.sum(radii[:N-1]**2))
    return radii
def adjusted_radii(cqam_radii,energy_harvested):
    
    initial_energies = cqam_radii**2
    adjusted_energies = initial_energies - energy_harvested
    adjusted_energies = np.where(adjusted_energies > 0, adjusted_energies, 0)
    adjusted_radii = np.where(adjusted_energies > 0, np.sqrt(adjusted_energies), 0)
    return adjusted_radii

def main():
    SNR_dB = np.arange(0, 30, 2)  # SNR range in dB
    num_symbols = 10000  # Number of symbols to simulate

def count_neighbors(R, n, d_min):
    """ Count neighbors at d_min for each radius level considering all symbols. """
    neighbors = [0] * len(R)  # Initialize neighbor count list
    points = []

    # Generate all points
    for i, r in enumerate(R):
        for theta in np.linspace(0, 2 * np.pi, n, endpoint=False):
            points.append((r, theta, i))  # Store radius, angle, and circle index

    # Check distances between all pairs of points
    for idx1, (r1, theta1, circle1) in enumerate(points):
        for idx2, (r2, theta2, circle2) in enumerate(points):
            if idx1 != idx2:
                # Calculate distance
                x1, y1 = r1 * np.cos(theta1), r1 * np.sin(theta1)
                x2, y2 = r2 * np.cos(theta2), r2 * np.sin(theta2)
                distance = np.sqrt((x2 - x1)**2 + (y2 - y1)**2)
                if np.isclose(distance, d_min, rtol=1e-5):
                    neighbors[circle1] += 1  # Increment neighbor count for circle1

    # Since each pair is counted twice, divide counts by 2
    neighbors = [int(neigh / 2) for neigh in neighbors]
    return neighbors

def calculate_ser(M, radii, num_neighbors):
    """ Calculate the Symbol Error Rate for CQAM under ML detection. """
    non_zero_radii = np.abs(radii[radii != 0])
    if len(non_zero_radii) == 0:
        return 1.0  # All symbols are zero, maximal error
    
    #return 2 * (1 - 1/M) * Q(d_min / (2 * sigma))
    m=len(non_zero_radii)
    l=len(radii)-m
    ser = 0
    k = np.log2(M)  # Bits per symbol
    snr_linear = 10 ** (20 / 10.0)
   
    for i,r in enumerate(non_zero_radii):
        if(len(non_zero_radii)==1):
           n = num_neighbors # Number of neighbors at the minimum distance at level i
        if(len(non_zero_radii)==4):
           pinakas = [4,2,1,1]
           n=pinakas[i] 
        if(len(non_zero_radii)==3):
           pinakas = [4,2,1]
           n=pinakas[i]
        if(len(non_zero_radii)==2):
           pinakas= [4,2]
           n=pinakas[i]
        effective_power = r**2  # This should not be negative
    

        Q_arg = np.sqrt(np.sqrt(effective_power) *k * snr_linear * np.sin(np.pi /4))

        ser += n * Q(Q_arg)
    ser_final=1/N*(l+ser)
    return ser_final  # Average SER over all levels


d_min = 0.617
M = 16
N = 4
n= M//N
Energy_harvested = np.linspace(0, 4.2, 300)
M = 16
ser_values = []
max_ser = 0  # Initialize the maximum SER observed
cqam_radii = generate_cqam_radii(d_min, M, N,1)
print(cqam_radii)
cqam_radii = np.array(cqam_radii)
cqam_radii=[0.5, 0.75566759, 1.4318229, 1.4518229]
cqam_radii = np.array(cqam_radii)
for Eh in Energy_harvested:
    adjusted_radii1=adjusted_radii(cqam_radii,Eh)
 # Place symbols on the CQAM constellation
    current_ser =calculate_ser(16,adjusted_radii1,3) 
    max_ser = max(max_ser, current_ser)  # Update the maximum SER if the current is higher
    ser_values.append(max_ser)  # Append the maximum SER observed so far

# Plotting
plt.figure(figsize=(10, 6))
plt.plot(Energy_harvested, ser_values, label=f'M={M} CQAM')

plt.xlabel('Energy Harvested')
plt.ylabel('Symbol Error Rate (SER)')
plt.title('SER vs. Energy Harvested for 16-CQAM d_min=max')
plt.grid(True, which='both', linestyle='--', linewidth=0.5)
plt.legend()
plt.show()



d_min=0
M = 16
N = 4
n= M//N
Energy_harvested = np.linspace(0, 4.2, 300)
M = 16
ser_values = []
max_ser = 0  # Initialize the maximum SER observed
cqam_radii = generate_cqam_radii(d_min, M, N,1)
print(cqam_radii)
cqam_radii = np.array(cqam_radii)
for Eh in Energy_harvested:
    adjusted_radii1=adjusted_radii(cqam_radii,Eh)
 # Place symbols on the CQAM constellation
    current_ser =calculate_ser(16,adjusted_radii1,3) 
    max_ser = max(max_ser, current_ser)  # Update the maximum SER if the current is higher
    ser_values.append(max_ser)  # Append the maximum SER observed so far

# Plotting
plt.figure(figsize=(10, 6))
plt.plot(Energy_harvested, ser_values, label=f'M={M} CQAM')

plt.xlabel('Energy Harvested')
plt.ylabel('Symbol Error Rate (SER)')
plt.title('SER vs. Energy Harvested for 16-CQAM d_min=0')
plt.grid(True, which='both', linestyle='--', linewidth=0.5)
plt.legend()
plt.show()
