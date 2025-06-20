import numpy as np
import matplotlib.pyplot as plt

data = np.loadtxt("data.txt") 
iterations = data[:, 0]  
capacity = data[:, 1] 
size = data[:, 2]  

plt.figure(figsize=(10, 5))
plt.plot(iterations, capacity,color="#ff69b4", label="Capacity", marker="o", linestyle="--")
plt.plot(iterations, size, color="#ffb6c1", label="Size", marker="s", linestyle="-")


plt.xlabel("Iterations (x1000 elements)")
plt.ylabel("Vector Capacity and Size")
plt.title("Dynamic Resizing of Vector")
plt.legend()
plt.grid(True)

plt.show()