# 🧩 Lightning-Fast Sudoku Solver & Solution Counter

A high-performance Sudoku solver written in C++ that not only completes the grid but exhaustively calculates the **total number of possible valid solutions**. 

Unlike standard implementations that rely on slow, linear searches to validate grid states, this project leverages **Bitmasking and State Tracking** to achieve $O(1)$ validation times, drastically reducing the search space overhead.

---

## ✨ Key Features

* **🧠 Advanced Backtracking & Recursion:** Intelligently explores the solution space, seamlessly rolling back dead-end paths.
* **🔢 Solution Counter:** Doesn't just stop at the first answer—it maps out every single valid configuration for the given board.
* **⚡ Ultra-Optimized Validation (Bitmasking):** Bypasses the traditional $O(N)$ row/column/grid checking loops by utilizing bitwise operations to instantly fetch available numbers.
* **📐 Scalable Logic:** Currently configured for a 4x4 grid (`boardsize = 4`, `cellsize = 2`), but the underlying bitwise logic scales beautifully to standard 9x9 puzzles and beyond.

---

## 🛠️ Under the Hood: The Bitmask Optimization

The core speed of this solver comes from how it tracks the board state. Instead of iterating through arrays to check if a number is safe to place, the board maintains three state arrays:
* `takenrow[]`
* `takencol[]`
* `takengrid[][]`

Each index stores an integer representing a **bitmask** of the currently occupied numbers. 

When the algorithm needs to find valid choices for an empty cell, it simply uses bitwise `OR` and `XOR` operations:
```cpp
// Instantly calculates occupied bits
int taken = (takenrow[row] | takencol[col] | takengrid[row/cellsize][col/cellsize]);

// Flips the bits to reveal available choices in O(1) time
int nottaken = ((1 << (boardsize + 1)) - 1) ^ taken;
