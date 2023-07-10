# Shortest Path Finder with Dijkstra's Algorithm

This repository contains a basic C program that calculates the shortest path between two cities in a map, using adjacency matrices and minimum heaps. The program reads from an input file to construct the map, provides an adjacency matrix view of the map, and calculates the shortest path between two given cities.

## Input File
The input file should consist of triplets of information representing a city pair and the distance between them. Each triplet is structured as City1-City2-Distance, where City1 and City2 are uppercase single letters representing cities, and Distance is the distance between City1 and City2.

## Adjacency Matrix
The adjacency matrix is a two-dimensional array representation of the map, where the cell at the i-th row and j-th column represents the distance between the i-th city and the j-th city.

## MinHeap
A basic MinHeap data structure is implemented to efficiently select the vertex with the shortest distance during the execution of Dijkstra's algorithm.

## Dijkstra's Algorithm
On inputting a source and a destination vertex, the program calculates and presents the shortest path between them.

## Shortest Path Calculation
The program uses the Dijkstra's algorithm for shortest path calculation. The implementation involves using a minimum heap data structure to hold the nodes, which are sorted by their distance from the source node.

### The main functions of the program are:

- initializeMinHeap: Initializes the min heap with a given capacity.
- insertElementToMinHeap: Inserts a new node into the min heap.
- extractMinElementFromMinHeap: Removes and returns the node with the minimum distance.
- heapify: Ensures the min heap property is maintained after an extraction.
- readInputFile: Reads the map information from an input file and fills the adjacency matrix.
- showAdjacencyMatrix: Displays the adjacency matrix.
- shortestPath: Computes the shortest path between two cities.

## How to Run the Program
Compile the main source file with your preferred C compiler and run the resulting executable. Make sure to prepare an input file with the graph information before running the program. For example, with gcc:
```
gcc main.c -o main
./main
```
