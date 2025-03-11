# ASP1_DZ3
Detonacija Mina (Mine denotation game) Graph Simulation\\
(Treci domaci zadatak iz ASPa1 - 2023. godine)\\
Overview
This project is a graph-based simulation of mines represented by vertices with circular properties. Each vertex (mine) is characterized by its coordinates (x, y) and radius r. The simulation allows you to add and remove vertices (mines), connect them via edges (directed), and delete edges. The goal is to manage a set of mines, each represented as a node in the graph, and interact with them using a series of operations.

Features
Graph Representation: The graph uses an adjacency list to represent connections between mines (vertices). Each vertex holds a Node struct containing information about the mine's coordinates and radius.
Operations:
Add a mine (vertex) to the graph.
Remove a mine (vertex) from the graph.
Add an edge (detonation path) between two mines.
Remove an edge (detonation path) between two mines.
Print the graph in an adjacency list format.
Delete the entire graph from memory.
Perform a breadth-first search (BFS) to find all reachable mines from a given starting mine.
Installation
Requirements
C Compiler (e.g., GCC)
Standard C libraries (stdlib.h, stdio.h, math.h, time.h)

Upon running the program, you will be presented with a main menu. The available options are:

Create a Graph: Create a graph where nodes represent mines. You can define the number of mines and add or remove them.
Detonacija Mina (Mine Detonation Game): Simulate the detonation of mines by performing operations on the graph.
Operations
Add Vertex: Adds a mine (vertex) with specified coordinates (x, y) and radius r to the graph.
Remove Vertex: Removes a mine (vertex) from the graph by specifying its coordinates (x, y) and radius r.
Add Edge: Creates a directed edge between two mines. An edge represents one mine being able to detonate another.
Remove Edge: Removes a directed edge between two mines.
Print Graph: Prints the graph in adjacency list format, displaying all the vertices and their connected edges.
Delete Graph: Deletes the entire graph, freeing all memory.
Example
To create a graph:

Choose option 1 to create a graph.
Enter the number of mines to be added.
Select from options to add vertices, remove vertices, and add/remove edges.
To simulate detonations:

Perform operations to connect and disconnect vertices as the simulation runs.
Functions
createGraph()
Creates an empty graph with a specified number of mines.

addVertex()
Adds a new mine to the graph, checking if a mine with the same properties already exists.

removeVertex()
Removes a specified mine from the graph.

addEdge()
Adds a directed edge between two mines (vertices) in the graph.

removeEdge()
Removes a directed edge between two mines.

detonira()
Checks if two mines are within detonation range (i.e., if one mine can detonate another).

BFS()
Performs a breadth-first search to find all reachable vertices (mines) from a starting point.

Conclusion
This program simulates the dynamics of mine detonations within a graph structure, providing functionality for adding and removing mines and edges, and simulating interactions between them. It offers a way to model the behavior of mines, including detonation ranges, adjacency relationships, and connected components.
