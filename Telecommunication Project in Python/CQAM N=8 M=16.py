import numpy as np
import matplotlib.pyplot as plt

def generate_cqam_radii(dmin, M, N,E_avg):
    # Number of symbols per circle
    n = M // N
    
    # Initialize radii list with R1
    radii = np.zeros(N)
  
    R1 = dmin / (2 * np.sin(np.pi / n))
    radii[0] = R1
    if N > 1:
        radii[1] = np.sqrt(dmin**2-R1**2)

    for i in range(2, N):
       
        R_prev_2 = radii[i-2]
        angle_diff = 2 * np.pi / n

        R_next_from_prev_2 = R_prev_2 + dmin
        radii[i] = R_next_from_prev_2

    if N > 1:
       radii[N-1]= np.sqrt(N - np.sum(radii[:N-1]**2))

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

d_min = 0.3
M = 16
N = 8

# Generate CQAM radii
cqam_radii = generate_cqam_radii(d_min, M, N,1)
 # Place symbols on the CQAM constellation
cqam_symbols = place_cqam_symbols(cqam_radii, M, N)
for i, r in enumerate(cqam_radii, start=1):
    print(f"R{i}: {r}")

# Calculate and print the sum of the squares of the radii
sum_of_squares = np.sum(cqam_radii**2)
print(f"Sum of the squares of the radii: {sum_of_squares}")
# Plotting the constellation
plt.figure(figsize=(6, 6))
for symbol in cqam_symbols:
        plt.plot(symbol[0], symbol[1], 'bo')
for r in cqam_radii:
    circle = plt.Circle((0, 0), r, color='r', fill=False)
    plt.gca().add_artist(circle)
plt.grid(True)
plt.xlabel('In-phase')
plt.ylabel('Quadrature')
plt.title('CQAM Constellation')
plt.axis('equal')
plt.show()

papr_values = []
d_min_values = np.linspace(0, 0.4, 100)
for i in d_min_values:
    rmax = generate_cqam_radii(i, 16,8,1)
    papr = rmax[-1]**2 / 1
    papr_values.append(papr)

plt.figure(figsize=(8, 5))
plt.plot(d_min_values, papr_values, 'r-', label='CQAM, M=16, N=8 (Adjusted)')
plt.grid(True)
plt.xlabel('$d_{min}$')
plt.ylabel('PAPR')
plt.title('PAPR vs $d_{min}$ for CQAM with $M=16$, $N=8$ (Adjusted)')
plt.legend()
plt.show()

    

if __name__ == '__main__':
    main()