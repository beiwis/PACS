import matplotlib.pyplot as plt

# Data from the table
steps = [16, 128, 1024, 1048576, 4294967295]
execution_time = [0.00204900000000000004, 0.001529999999999999893, 0.003314000000000000105, 2.160661000000000165, 8848.056034999999611]

# Plotting the data
plt.plot(steps, execution_time, marker='o', linestyle='-', color='b')

# Adding titles and labels
plt.title('Execution time of Sequential π computation with different steps')
plt.xlabel('Steps')
plt.ylabel('Execution time (ms)')

# Show plot 
plt.show()