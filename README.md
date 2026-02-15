# 🌍 Traveling Salesperson Problem (TSP) Optimizer

![C](https://img.shields.io/badge/C-99%25-blue?style=flat-square&logo=c)
![Algorithms](https://img.shields.io/badge/Algorithms-NP--Hard-red?style=flat-square)
![Memory](https://img.shields.io/badge/Memory-Leak--Free-brightgreen?style=flat-square)

A high-performance C solver for the NP-Hard Traveling Salesperson Problem (TSP) utilizing a Backtracking algorithm enhanced with **Branch and Bound** optimization.

This project demonstrates proficiency in handling NP-Hard combinatorial problems, advanced memory management, and abstract data types (Opaque Pointers).

---

## 🚀 Technical Highlights
- **Branch & Bound Pruning:** Dynamically cuts suboptimal branches during the recursive state-space tree exploration, drastically reducing time complexity compared to brute-force permutations ($O(n!)$).
- **Symbol Table (Hash Table):** Implements a custom Symbol Table with Linear Probing hashing to map string keys (City names) to internal graph indices in $O(1)$ average time.
- **Opaque ADTs:** Uses First-Class Abstract Data Types for both the `Item` (City) and the `Symbol Table`, encapsulating data and hiding internal structures from the client.

---

## 💻 Usage & Compilation

You can compile the project using standard GCC. No external dependencies are required.

```bash
# 1. Compile the source code
gcc -Wall -Wextra -O3 -o tsp_solver main.c Graph.c Item.c ST.c

# 2. Run the executable with the provided routing file
./tsp_solver input.txt

$ ./tsp_solver input.txt
Loading City Network from input.txt...
Network loaded successfully!

Initializing Branch & Bound Optimizer...

--- TSP OPTIMAL PATH FOUND ---
Minimum Distance: 2030 km
Route: Torino -> Milano -> Venezia -> Napoli -> Roma -> Torino

Optimization report:
Pruned branches: 20

Memory successfully freed. Program terminated.

# Valgrind memory check command
valgrind --leak-check=full ./tsp_solver input.txt

# Expected Result:
# All heap blocks were freed -- no leaks are possible
