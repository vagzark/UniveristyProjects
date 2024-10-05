import numpy as np
import matplotlib.pyplot as plt
from scipy.special import erfc



# Number of symbols in PAM constellation
M = 16

# Generate the 16-PAM constellation
# Constellation points are evenly spaced along the real line
symbols = np.arange(-(M-1), M, 2)

# Normalize constellation to unit average power
symbols = symbols / np.sqrt(np.mean(symbols**2))

# Plotting
plt.figure()
plt.plot(np.real(symbols), np.imag(symbols), 'bo')
plt.title('16-PAM Constellation')
plt.xlabel('In-Phase')
plt.ylabel('Quadrature')
plt.grid(True)
plt.axis('equal')
plt.show()



# Calculate PAPR
peak_power = np.max(np.abs(symbols)**2)
average_power = np.mean(np.abs(symbols)**2)
PAPR = peak_power / average_power


# Calculate d_min
d_min = np.min(np.abs(np.diff(symbols)))  # Difference between consecutive symbols

# Display calculated values
print(f'PAPR: {PAPR}')
print(f'd_min: {d_min}')

# Plotting the PAPR against d_min
plt.figure()
plt.plot(d_min, PAPR, 'bo')
plt.xlabel('Minimum Euclidean Distance ($d_{min}$)')
plt.ylabel('Peak-to-Average Power Ratio (PAPR)')
plt.title('PAPR vs. $d_{min}$ for 16-PAM')
plt.grid(True)

# Annotating the plot
plt.text(d_min, PAPR, f'({d_min:.2f}, {PAPR:.2f})', verticalalignment='bottom', horizontalalignment='right')

plt.show()


def Q(x):
    return 0.5 * erfc(x / np.sqrt(2))
# Number of symbols
M = 16

# Generate PSK constellation
angles = np.linspace(0, 2 * np.pi, M, endpoint=False)
psk_symbols = np.exp(1j * angles)  # e^(j*theta)

# Normalize to unit average power
psk_symbols = psk_symbols / np.sqrt(np.mean(np.abs(psk_symbols)**2))

# Plotting
plt.figure()
plt.plot(np.real(psk_symbols), np.imag(psk_symbols), 'bo')
plt.title('16-PSK Constellation')
plt.xlabel('In-Phase')
plt.ylabel('Quadrature')
plt.grid(True)
plt.axis('equal')
plt.show()

# Calculate PAPR
peak_power = np.max(np.abs(psk_symbols)**2)
average_power = np.mean(np.abs(psk_symbols)**2)
PAPR = peak_power / average_power


# Calculate d_min
d_min = np.min(np.abs(np.diff(psk_symbols)))  # Difference between consecutive symbols

# Display calculated values
print(f'PAPR: {PAPR}')
print(f'd_min: {d_min}')

# Plotting the PAPR against d_min
plt.figure()
plt.plot(d_min, PAPR, 'bo')
plt.xlabel('Minimum Euclidean Distance ($d_{min}$)')
plt.ylabel('Peak-to-Average Power Ratio (PAPR)')
plt.title('PAPR vs. $d_{min}$ for 16-PSK')
plt.grid(True)

# Annotating the plot
plt.text(d_min, PAPR, f'({d_min:.2f}, {PAPR:.2f})', verticalalignment='bottom', horizontalalignment='right')

plt.show()




def calculate_papr(symbols):
    """ Calculate the Peak-to-Average Power Ratio of the given constellation. """
    power = np.abs(symbols)**2
    peak_power = np.max(power)
    average_power = np.mean(power)
    return peak_power / average_power

def calculate_dmin(symbols):
    """ Calculate the minimum Euclidean distance for the given constellation. """
    dist_matrix = np.abs(symbols[:, np.newaxis] - symbols)
    np.fill_diagonal(dist_matrix, np.inf)  # Exclude zero distance (symbol to itself)
    return np.min(dist_matrix)

# Generate a standard 16-QAM constellation
M = 16
m = int(np.sqrt(M))
real_part = np.linspace(-m+1, m-1, m)
imag_part = np.linspace(-m+1, m-1, m)
qam_symbols = np.array([x + 1j*y for x in real_part for y in imag_part])

# Normalize constellation to have unit average power
qam_symbols = qam_symbols / np.sqrt(np.mean(np.abs(qam_symbols)**2))

# Calculate PAPR and d_min for QAM
qam_papr = calculate_papr(qam_symbols)
qam_dmin = calculate_dmin(qam_symbols)

# Print PAPR and d_min values
print(f"16-QAM PAPR: {qam_papr:.3f}")
print(f"16-QAM d_min: {qam_dmin:.3f}")



# Plotting QAM constellation
plt.figure()
plt.scatter(np.real(qam_symbols), np.imag(qam_symbols), color='red')
plt.title('16-QAM Constellation')
plt.xlabel('In-Phase (I)')
plt.ylabel('Quadrature (Q)')
plt.grid(True)
plt.axis('equal')
plt.show()

# Plotting PAPR vs d_min
plt.figure(figsize=(5, 3))
plt.scatter(qam_dmin, qam_papr, color='blue')
plt.xlabel('Minimum Euclidean Distance ($d_{min}$)')
plt.ylabel('Peak-to-Average Power Ratio (PAPR)')
plt.title('PAPR vs $d_{min}$ for 16-QAM')
plt.grid(True)
plt.show()