# ASP1_DZ3: Detonacija Mina (Mine Detonation Game) - Graph Simulation

## Overview

This project is a graph-based simulation of mines represented by vertices with circular properties. Each vertex (mine) is characterized by its coordinates `(x, y)` and radius `r`. The simulation allows you to add and remove vertices (mines), connect them via directed edges (detonation paths), and delete edges. The goal is to manage a set of mines, each represented as a node in the graph, and interact with them using a series of operations.

## Features

- **Graph Representation**:  
  The graph uses an adjacency list to represent connections between mines (vertices). Each vertex holds a `Node` struct containing information about the mine's coordinates and radius.

### Operations

- Add a mine (vertex) to the graph.
- Remove a mine (vertex) from the graph.
- Add an edge (detonation path) between two mines.
- Remove an edge (detonation path) between two mines.
- Print the graph in an adjacency list format.
- Delete the entire graph from memory.
- Perform a **Breadth-First Search (BFS)** to find all reachable mines from a given starting mine.

## Installation

### Requirements

- **C Compiler** (e.g., GCC)
- Standard C libraries:  
  - `stdlib.h`  
  - `stdio.h`  
  - `math.h`  
  - `time.h`
