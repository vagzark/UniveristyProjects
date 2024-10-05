import numpy as np
import matplotlib.pyplot as plt

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
    print(f"Sum of distances of all symbols without spikes: {sum_f_distances}")

    # Calculate the total energy budget based on E_avg and base_size
    total_energy_budget = base_size * E_avg

    # Remaining energy for spikes
    remaining_energy_for_spikes = total_energy_budget - sum_f_distances

    if remaining_energy_for_spikes <= 0:
        raise ValueError("Not enough energy budget for spikes, increase E_avg or reduce base_size")

    # Calculate the spike distance
    spike_energy_per_spike = remaining_energy_for_spikes / min(num_spikes, 4)  # Energy per spike
    spike_distance = np.sqrt(spike_energy_per_spike)  # Distance from the origin for each spike
    print(f"Spike distance: {spike_distance}")
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
    total_energy = np.sum(np.abs(base_qam_points) ** 2)
    #print(f"Total energy after spikes: {total_energy}")
    return base_qam_points

def plot_spike_qam(base_size, num_spikes, d_min, E_avg):
    # Generate the QAM constellation with spikes
    qam_points = generate_spike_qam(base_size, num_spikes, d_min, E_avg)

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
base_size = 16# Total number of points in the constellation
num_spikes = 1  # Number of spikes to add
d_min = 0.4 # Minimum distance between constellation points
E_avg = 1 # Desired average energy

# Plot the constellation
plot_spike_qam(base_size, num_spikes, d_min, E_avg)