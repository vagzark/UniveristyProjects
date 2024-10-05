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
snr_db = np.linspace(0, 24, 300)  # Reduced number of points for faster simulation
snr_linear = 10**(snr_db / 10)


def generate_spike_qam(base_size, num_spikes, d_min, E_avg):
    side_length = int(np.sqrt(base_size))
    step_size = d_min / np.sqrt(2)  # diagonal distance
    x_coords = np.linspace(-step_size * (side_length // 2), step_size * (side_length // 2), side_length)
    y_coords = np.linspace(-step_size * (side_length // 2), step_size * (side_length // 2), side_length)
    xx, yy = np.meshgrid(x_coords, y_coords)
    base_qam_points = xx.flatten() + 1j * yy.flatten()
    
    half_diagonal = np.sqrt((max(x_coords) ** 2) + (max(y_coords) ** 2))
    sum_f_distances = np.sum(np.abs(base_qam_points) ** 2) - min(num_spikes, 4) * (half_diagonal ** 2)
    total_energy_budget = base_size * E_avg
    remaining_energy_for_spikes = total_energy_budget - sum_f_distances

    if remaining_energy_for_spikes <= 0:
        raise ValueError("Not enough energy budget for spikes, increase E_avg or reduce base_size")

    spike_energy_per_spike = remaining_energy_for_spikes / min(num_spikes, 4)  # Energy per spike
    spike_distance = np.sqrt(spike_energy_per_spike)  # Distance from the origin for each spike

    corner_indices = [
        0,  # Bottom-left
        side_length - 1,  # Bottom-right
        len(base_qam_points) - side_length,  # Top-left
        len(base_qam_points) - 1  # Top-right
    ]

    for i in range(min(num_spikes, 4)):  # Ensure we do not exceed the four corners
        index = corner_indices[i]
        angle = np.angle(base_qam_points[index])
        base_qam_points[index] += np.exp(1j * angle) * spike_distance

    return base_qam_points, spike_distance


def generate_cqam_radii(dmin, M, N, E_avg):
    n = M // N
    radii = np.zeros(N)
  
    R1 = dmin / (2 * np.sin(np.pi / n))
    radii[0] = R1
    if N > 1:
        radii[1] = np.sqrt(dmin**2 + R1**2 - 2 * R1 * dmin * np.cos(2 * np.pi / n))

    for i in range(2, N):
        R_prev = radii[i-1]
        R_prev_2 = radii[i-2]
        angle_diff = 2 * np.pi / n
        R_next_from_prev = np.sqrt(dmin**2 + R_prev**2 - 2 * R_prev * dmin * np.cos(angle_diff))
        angle_offset = (np.pi / n) * ((i % 2) * 2 - (i % 2))
        R_next_from_prev_2 = np.sqrt(dmin**2 + R_prev_2**2 - 2 * R_prev_2 * dmin * np.cos(2 * angle_diff + angle_offset))
        radii[i] = max(R_next_from_prev, R_next_from_prev_2)

    if N > 1:
        radii[N-1] = np.sqrt(N * E_avg - np.sum(radii[:N-1]**2))

    return radii


def calculate_ser_spike_qam(M, num_spikes, d_min, PAPR):
    snr_linear = 10**(snr_db / 10)
    gama = M - num_spikes * (np.sqrt(PAPR) ** 2)
    gama = gama / (M - 1)
    N0 = 1 / snr_linear
    dmid = np.sqrt(3 / (M - 1) / 2) * np.sqrt(2 * M - 8 * np.sqrt(M) + 8)
    pmax = Q((np.sqrt(PAPR) - dmid) / np.sqrt(2 * N0))
    ser1 = 2 * (1 - 1/np.sqrt(M)) * Q(np.sqrt(3 * gama * snr_linear / (M - 1)))
    ser2 = 1 - (1 - ser1) ** 2 
    ser = (M - num_spikes) / M * ser2 + num_spikes / M * pmax
    return ser


def calculate_ser_cqam(symbols, R, harvested_energy):
    num_neighbors = [4, 2, 1, 1]
    ser = 0
    for i, r in enumerate(R):
        n_neigh = num_neighbors[i]
        epsilon = harvested_energy
        effective_power = r**2 - epsilon * r**2
        Q_arg = np.sqrt(effective_power * snr_linear *2)* np.sin(np.pi / 4)
        ser += n_neigh * Q(Q_arg)
    return ser / len(R)
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

# Generate CQAM radii
cqam_radii = generate_cqam_radii(d_min, M, N, 1)

# Place symbols on the CQAM constellation
cqam_symbols = place_cqam_symbols(cqam_radii, M, N)
ser_cqam = calculate_ser_cqam(cqam_symbols, cqam_radii,  0)
ser_spikeqam1 = calculate_ser_spike_qam(16,1, d_min, 10.3)


plt.figure()
plt.semilogy(snr_db, ser_cqam, label='16-c-QAM ')
plt.semilogy(snr_db, ser_spikeqam1, label='16-spike QAM', linestyle='--')

plt.xlabel('Es/No (dB)')
plt.ylabel('Symbol Error Rate (SER)')
plt.title('SER vs. SNR for 16-c-QAM')
plt.grid(True)
plt.legend()

# Set the y-axis limit to display down to 10^-6
#plt.ylim([1e-6, 1])

plt.show()
