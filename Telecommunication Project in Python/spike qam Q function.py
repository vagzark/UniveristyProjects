import numpy as np
import matplotlib.pyplot as plt
from scipy.special import erfc


def Q(x):
    return 0.5 * erfc(x / np.sqrt(2))


def generate_spike_qam(base_size, num_spikes, d_min, E_avg):
    # Calculate the number of points per side for the square QAM
    side_length = int(np.sqrt(base_size))
    
    # Determine the step size based on d_min
    step_size = d_min / np.sqrt(2)  # diagonal distance
    
    # Generate the base square QAM constellation points
    x_coords = np.linspace(-step_size * (side_length // 2), step_size * (side_length // 2), side_length)
    y_coords = np.linspace(-step_size * (side_length // 2), step_size * (side_length // 2), side_length)
    xx, yy = np.meshgrid(x_coords, y_coords)
    base_qam_points = xx.flatten() + 1j * yy.flatten()
    
    # Calculate the half-diagonal (distance to a corner point)
    half_diagonal = np.sqrt((max(x_coords) ** 2) + (max(y_coords) ** 2))

    # Calculate the sum of squared distances of the points from the origin,
    # excluding the energy contribution from the corner points that will become spikes
    sum_f_distances = np.sum(np.abs(base_qam_points) ** 2) - min(num_spikes, 4) * (half_diagonal ** 2)


    # Calculate the total energy budget based on E_avg and base_size
    total_energy_budget = base_size * E_avg

    # Remaining energy for spikes
    remaining_energy_for_spikes = total_energy_budget - sum_f_distances

    if remaining_energy_for_spikes <= 0:
        raise ValueError("Not enough energy budget for spikes, increase E_avg or reduce base_size")

    # Calculate the spike distance
    spike_energy_per_spike = remaining_energy_for_spikes / min(num_spikes, 4)  # Energy per spike
    spike_distance = np.sqrt(spike_energy_per_spike)  # Distance from the origin for each spike

    # Determine the positions for the corner points to be replaced by spikes
    corner_indices = [
        0,  # Bottom-left
        side_length - 1,  # Bottom-right
        len(base_qam_points) - side_length,  # Top-left
        len(base_qam_points) - 1  # Top-right
    ]
    

    # Replace the corner points with spikes, ensuring they maintain the minimum distance d_min
    for i in range(min(num_spikes, 4)):  # Ensure we do not exceed the four corners
        index = corner_indices[i]
        # Move the corner point outwards by spike_distance to create the spike
        angle = np.angle(base_qam_points[index])
        base_qam_points[index] += np.exp(1j * angle) * spike_distance

    return base_qam_points,spike_distance

def plot_spike_qam(base_size, num_spikes, d_min, E_avg):
    # Generate the QAM constellation with spikes
    qam_points,spike_distance = generate_spike_qam(base_size, num_spikes, d_min, E_avg)

    # Extract x (real part) and y (imaginary part) coordinates from the complex numbers
    x_coords = qam_points.real
    y_coords = qam_points.imag

    # Create a plot
    plt.figure(figsize=(8, 8))
    plt.scatter(x_coords, y_coords, color='blue', marker='o')
    
    # Highlight the spikes with a different color
    corner_indices = [0, int(np.sqrt(base_size)) - 1, len(qam_points) - int(np.sqrt(base_size)), len(qam_points) - 1]
    for i in range(min(num_spikes, 4)):  # Ensure we do not exceed the four corners
        index = corner_indices[i]
        plt.scatter(x_coords[index], y_coords[index], color='red', marker='o', s=100)  # Larger size for spikes

    # Set plot title and labels
    plt.title('Spike QAM Constellation')
    plt.xlabel('In-phase')
    plt.ylabel('Quadrature')
    plt.grid(True)
    plt.axis('equal')  # Equal aspect ratio ensures that the plot is square

    # Show the plot
    plt.show()

# Example parameters
base_size = 16  # Total number of points in the constellation
num_spikes = 4  # Number of spikes to add
d_min = 1  # Minimum distance between constellation points
E_avg = 4  # Desired average energy

# Plot the constellation
plot_spike_qam(base_size, num_spikes, d_min, E_avg)




def generate_ser_spike_qam(base_size, num_spikes, d_min, E_avg):
    base_points,spike_distance=generate_spike_qam(base_size, num_spikes, d_min, E_avg)
    M=16
    k = np.log2(M)  # Bits per symbol
    
# SNR range in dB
    snr_db = np.linspace(0, 25, 100)
    snr_linear = 10**(snr_db / 10)
 
    gama= M-num_spikes*(spike_distance**2)
    gama= gama/(M-1)
    N=1/snr_linear
    dmid=np.sqrt(3/(M-1)/2)*np.sqrt(2*M-8*np.sqrt(M)+8)
    pmax= Q((spike_distance-dmid)/np.sqrt(2*N))

# SER calculation for square M-s-QAM
    ser1 = 2 * (1 - 1/np.sqrt(M)) * Q(np.sqrt(3*gama*snr_linear/(M-1)))
    ser2=1-(1-ser1)**2 
    ser=(M-num_spikes)/M * ser2 + num_spikes/M * pmax
    
# Plot SER vs. SNR
    plt.figure()
    plt.semilogy(snr_db, ser, label='16-sQAM-dmin=0.4 SER')
    plt.xlabel('SNR (dB)')
    plt.ylabel('Symbol Error Rate (SER)')
    plt.title('SER vs. SNR for 16-sQAM')
    plt.grid(True)
    plt.legend()
    plt.show()
  

    # Extract x (real part) and y (imaginary part) coordinates from the complex numbers
   


generate_ser_spike_qam(16, 1, 0.4, 1)
     
def generate_ser_spike_qampapr(M, num_spikes, d_min, PAPR):
  
    k = np.log2(M)  # Bits per symbol
    
# SNR range in dB
    snr_db = np.linspace(0, 24, 100)
    snr_linear = 10**(0.8*snr_db / 10)
 
    gama= M-num_spikes*(np.sqrt(PAPR)**2)
    gama= gama/(M-1)
    N0=1/snr_linear
    dmid=np.sqrt(3/(M-1)/2)*np.sqrt(2*M-8*np.sqrt(M)+8)
    pmax= Q((np.sqrt(PAPR)-dmid)/np.sqrt(2*N0))

# SER calculation for square M-s-QAM
    ser1 = 2 * (1 - 1/np.sqrt(M)) * Q(np.sqrt(3*gama*snr_linear/(M-1)))
    ser2=1-(1-ser1)**2 
    ser=(M-num_spikes)/M * ser2 + num_spikes/M * pmax

# Plot SER vs. SNR
    plt.figure()
    plt.semilogy(snr_db, ser, label='16-sQAM,dmin=0.4,PAPR=10,SER')
    plt.xlabel('SNR (dB)')
    plt.ylabel('Symbol Error Rate (SER)')
    plt.title('SER vs. SNR for 16-sQAM')
    plt.grid(True)
    plt.legend()
    plt.show()
  
generate_ser_spike_qampapr(16, 1, 0.4, 10.3)