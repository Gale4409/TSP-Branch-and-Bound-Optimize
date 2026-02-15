# Traveling Salesperson Problem (TSP) Optimizer

A high-performance C program that solves the NP-Hard Traveling Salesperson Problem (TSP) using a Backtracking algorithm enhanced with **Branch and Bound** optimization. 

This project was built to demonstrate proficiency in handling NP-Hard combinatorial problems, advanced memory management, and abstract data types (Opaque Pointers).

## 🚀 Technical Highlights
- **Branch & Bound Pruning:** Dynamically cuts suboptimal branches during the recursive state-space tree exploration, drastically reducing time complexity compared to brute-force permutations.
- **Symbol Table (Hash Table):** Implements a custom Symbol Table with Linear Probing hashing to map string keys (City names) to internal graph indices in $O(1)$ average time.
- **Opaque ADTs:** Uses First-Class Abstract Data Types for both the `Item` (City) and the `Symbol Table`, perfectly encapsulating data and hiding internal structures from the client.
- **Memory Safety:** Completely memory-leak free, carefully handling dynamic memory allocation for structures, strings, and recursive path arrays.

## 🛠️ Built With
- **Language:** Standard C (C99)
- **Concepts:** NP-Hard Optimization, Backtracking, Graphs (Adjacency Lists), Hashing.
- **Build System:** CMake / GCC

## 💻 How to Run
Compile the project using CMake or standard GCC:
```bash
gcc -Wall -Wextra -o tsp_solver main.c Graph.c Item.c ST.c
