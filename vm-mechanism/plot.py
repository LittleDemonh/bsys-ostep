import matplotlib
matplotlib.use('Agg')  # Use the Agg backend for non-interactive plotting
import matplotlib.pyplot as plt
import random

def generate_virtual_addresses(num_addresses, address_space_size, seed):
    random.seed(seed)
    return [random.randint(0, address_space_size - 1) for _ in range(num_addresses)]

def calculate_valid_fraction(addresses, bounds_register):
    valid_addresses = [addr for addr in addresses if addr < bounds_register]
    return len(valid_addresses) / len(addresses)

def main():
    address_space_size = 1000  # Example address space size
    num_addresses = 1000  # Number of addresses to generate
    seeds = [0, 1, 2, 3]  # Different random seeds
    bounds_register_values = range(0, address_space_size + 1, 10)  # Bounds register values

    results = {seed: [] for seed in seeds}

    for seed in seeds:
        for bounds_register in bounds_register_values:
            addresses = generate_virtual_addresses(num_addresses, address_space_size, seed)
            valid_fraction = calculate_valid_fraction(addresses, bounds_register)
            results[seed].append(valid_fraction)

    # Plotting the results
    for seed, fractions in results.items():
        plt.plot(bounds_register_values, fractions, label=f'Seed {seed}')

    plt.xlabel('Bounds Register Value')
    plt.ylabel('Fraction of Valid Addresses')
    plt.title('Fraction of Valid Addresses vs. Bounds Register Value')
    plt.legend()
    plt.grid(True)
    plt.savefig('valid_addresses_plot.png')  # Save the plot to a file

if __name__ == "__main__":
    main()