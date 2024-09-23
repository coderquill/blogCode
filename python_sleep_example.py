import time
import math
import threading

# A function that simulates CPU-bound work
def cpu_bound_work():
    result = 0
    for i in range(1, 10**7):
        result += math.sqrt(i)
    return result

# A function to perform CPU-bound work in a separate thread
def perform_cpu_bound_work():
    for _ in range(3):
        threading.Thread(target=cpu_bound_work).start()

# Record the start time
start_time = time.perf_counter()

# Start CPU-bound work in the background
perform_cpu_bound_work()

# Sleep for 3 seconds
time.sleep(3)

# Record the end time
end_time = time.perf_counter()

# Calculate the actual sleep duration
actual_sleep_duration = end_time - start_time

print(f"Requested sleep: 3 seconds")
print(f"Actual sleep duration: {actual_sleep_duration:.6f} seconds")
