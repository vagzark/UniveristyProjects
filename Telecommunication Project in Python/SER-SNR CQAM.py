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

def place_cqam_symbols(R, M, N):
    n = M // N  # Symbols per circle
    symbols = []

    for i, r in enumerate(R):
        # Determine if symbols on this circle should be on the axes
        on_axes = (i + 1) % 2 == 0

        # Starting angle: Align with axes for even circles, offset for odd
        start_angle = 0 if on_axes else np.pi / n

        for j in range(n):
            angle = start_angle + j * 2 * np.pi / n
            symbol = np.array([r * np.cos(angle), r * np.sin(angle)])
            symbols.append(symbol)

    return symbols

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
d_min = 0.4
M = 16
N = 4
n= M//N
# Generate CQAM radii
cqam_radii = generate_cqam_radii(d_min, M, N,1)
 # Place symbols on the CQAM constellation
cqam_symbols = place_cqam_symbols(cqam_radii, M, N)


def calculate_ser(symbols, R, num_neighbors, harvested_energy):
    """ Calculate the Symbol Error Rate for CQAM under ML detection. """
   
    ser = 0
    k = np.log2(M)  # Bits per symbol

# SNR range in dB
    snr_db = np.linspace(0, 25, 300)
    snr_linear = 10**(snr_db / 10)
   
    for i, r in enumerate(R):
        n = num_neighbors[i]  # Number of neighbors at the minimum distance at level i
        epsilon = harvested_energy
        effective_power = r**2 - epsilon*r**2  # This should not be negative
    

        Q_arg = np.sqrt(effective_power *2 * snr_linear ) *np.sin(np.pi /4)

        ser += n * Q(Q_arg)
    
    return ser / len(R)  # Average SER over all levels

neighbours = [5,2,1,0]
ser =calculate_ser(cqam_symbols,cqam_radii,neighbours,0) 
snr_db = np.linspace(0, 25, 300)

plt.figure()
plt.semilogy(snr_db, ser, label='16-c-QAM SER')
plt.xlabel('SNR (dB)')
plt.ylabel('Symbol Error Rate (SER)')
plt.title('SER vs. SNR for 16-c-QAM')
plt.grid(True)
plt.legend()
plt.show()
