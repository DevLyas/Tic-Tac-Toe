# 🎮 Tic-Tac-Toe

A simple terminal-based Tic Tac Toe game written in C++, designed for two players with a clear and styled ASCII grid.

## 🖼️ Preview

<pre>
.-----------.
| X | O | X |
:---+---+---:
| O | X | O |
:---+---+---:
| X | O | X |
'-----------'
</pre>

## ✨ Features

- Two-player mode (local)
- Live-updating ASCII grid
- Input validation (bounds & occupied cells)
- Win and draw detection
- Clear terminal screen between turns (ANSI-compatible)

## ⚙️ Requirements

- A C++ compiler (e.g., `g++`, `clang++`)
- Terminal/console that supports ANSI escape codes:
  - ✅ Linux/macOS: works out of the box
  - ✅ Windows 10+: works with ANSI enabled

## 🚀 Getting Started

To compile and run:

```bash
g++ -o tic-tac-toe main.cpp
./tic-tac-toe
```
