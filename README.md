# ASP1_DZ3: Detonacija Mina (Mine Detonation Game) - Graph Simulation
Overview
This project is a graph-based simulation of mines represented by vertices with circular properties. Each vertex (mine) is characterized by its coordinates (x, y) and radius r. The simulation allows you to add and remove vertices (mines), connect them via directed edges (detonation paths), and delete edges. The goal is to manage a set of mines, each represented as a node in the graph, and interact with them using a series of operations.

Features
Graph Representation:
The graph uses an adjacency list to represent connections between mines (vertices). Each vertex holds a Node struct containing information about the mine's coordinates and radius.
Operations
Add a mine (vertex) to the graph.
Remove a mine (vertex) from the graph.
Add an edge (detonation path) between two mines.
Remove an edge (detonation path) between two mines.
Print the graph in an adjacency list format.
Delete the entire graph from memory.
Perform a Breadth-First Search (BFS) to find all reachable mines from a given starting mine.
Installation
Requirements
C Compiler (e.g., GCC)
Standard C libraries:
stdlib.h
stdio.h
math.h
time.h
Compilation
Clone or download the repository.

Open a terminal in the project directory.

Compile the program using the following command:

bash
Copy
Edit
gcc -o mine_simulation main.c -lm
Run the compiled program:

bash
Copy
Edit
./mine_simulation
Usage
Main Menu
Upon running the program, you will be presented with a main menu. The available options are:

Create a Graph:
Create a graph where nodes represent mines. Define the number of mines and add or remove them.

Detonacija Mina (Mine Detonation Game):
Simulate the detonation of mines by performing operations on the graph.

Operations
Add Vertex: Adds a mine (vertex) with specified coordinates (x, y) and radius r to the graph.
Remove Vertex: Removes a mine (vertex) from the graph by specifying its coordinates (x, y) and radius r.
Add Edge: Creates a directed edge between two mines, allowing one mine to detonate another.
Remove Edge: Removes a directed edge between two mines.
Print Graph: Prints the graph in adjacency list format, displaying all the vertices and their connected edges.
Delete Graph: Deletes the entire graph and frees all memory.
Example
Creating a Graph
Choose option 1 to create a graph.
Enter the number of mines you want to add.
Select from options to add vertices, remove vertices, and add/remove edges.
Simulating Detonations
Perform operations to connect and disconnect vertices as the simulation runs.
Functions
createGraph():
Creates an empty graph with a specified number of mines.

addVertex():
Adds a new mine to the graph, ensuring that no duplicates exist.

removeVertex():
Removes a specified mine from the graph.

addEdge():
Adds a directed edge between two mines (vertices).

removeEdge():
Removes a directed edge between two mines.

detonira():
Checks if two mines are within detonation range (i.e., if one mine can detonate another).

BFS():
Performs a breadth-first search to find all reachable vertices (mines) from a given starting point.

Conclusion
This program simulates the dynamics of mine detonations within a graph structure. It allows for the management of mines and detonation paths, while simulating interactions such as connecting and disconnecting mines. It also provides a way to model mine behaviors, adjacency relationships, and connected components using graph traversal.
