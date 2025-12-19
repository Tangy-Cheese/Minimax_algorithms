# Minimax Algorithm Analysis

This project investigates the performance characteristics of the minimax algorithm
across a small set of two-player, deterministic, zero-sum games.

The primary goal is not to build a competitive game-playing engine, but to perform
a comparative and statistical analysis of how different optimisation strategies
affect the practical depth and runtime of minimax search.

## Games Considered

The analysis focuses on the following games:

- Tic-Tac-Toe (as a fully solvable baseline)
- A generalised N×N grid game (to study scaling behaviour)
- Chess (used only as a constrained stress test at shallow depths)

Chess is intentionally limited to small search depths and simple evaluation functions,
and is not intended to compete with modern chess engines.

## Analysis Objectives

Two main analyses are performed:

1. **Search Depth vs Runtime**

   We study how increasing the search depth affects runtime and node expansion for
   different games, highlighting the impact of branching factor and game complexity.

2. **Alpha–Beta Pruning vs Parallel Minimax**

   We compare two optimisation strategies:
   - Alpha–beta pruning to reduce the search space
   - Parallel minimax using OpenMP to reduce wall-clock runtime

   The comparison is framed in terms of the maximum achievable search depth under
   fixed computational constraints, rather than raw speed alone.

Most of the project effort is dedicated to implementing these approaches in a clean,
controlled manner to enable fair and reproducible comparisons.
