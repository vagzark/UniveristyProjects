import numpy as np
import matplotlib.pyplot as plt
from scipy.special import erfc

def Q(x):
    return 0.5 * erfc(x / np.sqrt(2))

# Parameters
M = 16
num_spikes = 1
d_min = 0.4
E_avg = 1
PAPR = 10.3
N = 4

# SNR range in dB
snr_db = np.linspace(0, 25, 10)  # Reduced number of points for faster simulation
snr_linear = 10**(snr_db / 10)


def generate_cqam_radii(dmin, M, N, E_avg):
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
       radii[N-1] = np.sqrt(N * E_avg - np.sum(radii[:N-1]**2))

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
            symbol = r * np.exp(1j * angle)
            symbols.append(symbol)

    return np.array(symbols)

def calculate_ser_cqam(symbols, R, harvested_energy):
    num_neighbors = [5, 2, 1, 0]
    ser = 0
    R0= R[0]
    for i, r in enumerate(R):
        n_neigh = num_neighbors[i]
        epsilon = harvested_energy
        effective_power = R0**2 - epsilon * R0**2
        Q_arg = np.sqrt(effective_power *2  * snr_linear)* np.sin(np.pi /4)
        ser += n_neigh * Q(Q_arg)
    return ser / len(R)
#from nearest neighbor approximation
#def calculate_ser_cqam(symbols, R, harvested_energy):
    num_neighbors = 5
    ser = 0
    R0= R[0]
    epsilon = harvested_energy
    effective_power = R0**2 - epsilon * R0**2
    Q_arg = np.sqrt(effective_power * 2* snr_linear)* np.sin(np.pi /4)
    ser = num_neighbors * Q(Q_arg)
    return ser

#def calculate_ser_cqam(symbols, R, harvested_energy):
    num_neighbors = [4, 2, 1, 1]
    ser = 0
    R0=R[0]
    for i, r in enumerate(R):
        n_neigh = num_neighbors[i]
        epsilon = harvested_energy
        effective_power = R0**2 - epsilon * R0**2
        if i<4:
         Q_arg = np.sqrt(effective_power *2* snr_linear )* np.sin(np.pi / 4)
         ser += n_neigh * Q(Q_arg)
        if i==4:
         Q_arg = np.sqrt( snr_linear / 2 )*(r-r[1])
         ser += n_neigh * Q(Q_arg)   
    return ser / len(R)
#def calculate_ser_cqam(symbols, R, harvested_energy):
    num_neighbors = [5, 2, 1, 1]
    ser = 0
    for i, r in enumerate(R):
        n_neigh = num_neighbors[i]
        epsilon = harvested_energy
        effective_power = r**2 - epsilon * r**2
        Q_arg = np.sqrt(np.sqrt(effective_power)* snr_linear * np.sin(np.pi / 4))
        ser += n_neigh * Q(Q_arg)
    return ser / len(R)
#def calculate_ser_cqam(symbols, R, harvested_energy):
    num_neighbors = [5, 2, 1, 1]
    ser = 0
    for i, r in enumerate(R):
        n_neigh = num_neighbors[i]
        epsilon = harvested_energy
        effective_power = r**2 - epsilon * r**2
        Q_arg = np.sqrt(effective_power*2* snr_linear) * np.sin(np.pi / 4)
        ser += n_neigh * Q(Q_arg)
    return ser / len(R)
#def calculate_ser_cqam(symbols, R, harvested_energy):
    num_neighbors = [5, 2, 1, 1]
    ser = 0
    for i, r in enumerate(R):
        n_neigh = num_neighbors[i]
        epsilon = harvested_energy
        effective_power = r**2 - epsilon * r**2
        Q_arg = np.sqrt(np.sqrt(effective_power)* snr_linear * np.sin(np.pi / 4))
        ser += n_neigh * Q(Q_arg)
    return ser / len(R)
def ml_detection(received_symbols, constellation_points):
    detected_symbols = []
    for symbol in received_symbols:
        distances = np.abs(symbol - constellation_points)
        detected_symbols.append(constellation_points[np.argmin(distances)])
    return np.array(detected_symbols)

def monte_carlo_simulation(M, constellation_points, snr_linear, num_symbols=100000):
    ser_mc = np.zeros(len(snr_linear))
    
    for idx, snr in enumerate(snr_linear):
        errors = 0
        noise_variance = 1 / (2*snr)
        
        for _ in range(num_symbols // M):
            transmitted_symbols = np.random.choice(constellation_points, M)
            noise = np.sqrt(noise_variance) * (np.random.randn(M) + 1j * np.random.randn(M))
            received_symbols = transmitted_symbols + noise
            detected_symbols = ml_detection(received_symbols, constellation_points)
            errors += np.sum(transmitted_symbols != detected_symbols)
        
        ser_mc[idx] = errors / num_symbols
    
    return ser_mc

# Generate CQAM radii and symbols
cqam_radii = generate_cqam_radii(d_min, M, N, E_avg)
cqam_symbols = place_cqam_symbols(cqam_radii, M, N)

# Monte Carlo simulation for SER
ser_mc_cqam = monte_carlo_simulation(M, cqam_symbols, snr_linear, 100000)

# Analytical SER calculation
ser_analytical_cqam = calculate_ser_cqam(cqam_symbols, cqam_radii, 0)

# Plot the results
plt.figure()
plt.semilogy(snr_db, ser_mc_cqam, 'o-', label='Monte Carlo CQAM')
plt.semilogy(snr_db, ser_analytical_cqam, 'x-', label='Analytical CQAM')
plt.xlabel('SNR (dB)')
plt.ylabel('Symbol Error Rate (SER)')
plt.title('SER vs. SNR for CQAM')
plt.grid(True)
plt.legend()
plt.show()
