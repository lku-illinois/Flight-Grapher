# FlightGrapher

CS 225 Final Project

## Introduction

Our final project utilizes the airports and routes data to construct maps and matrixes.
We implement Dijkstra to find the shortest path between airports depending on the 
distance. We also implment pagerank algorithm to find the most pupular airports.

## Github Organization
These files contain different functions for different implementations. Function descriptions
can be found in the individual files.

Parser: Constructing a graph given the airport and routes data
BFS: Implementation of BFS traversal on the graph
Pagerank: Implementation of pagerank algorithm to find the most popular airports
Dijkstra: Implementation of diskstra algorithm to find the shortest path between airports
Main: Multiple test cases for bfs, dijkstra's and pagerank algorithm

The output files can be found in the Outputs folder.
The data files can be found in the data folder.
Any deliverables (report, contract, etc.) can be found in the Deliverables folder.

## Running Instructions
This program can be compiled using (g++ -o main \*.cpp) in the terminal.
This program can be run by using (./main) or (./main.exe) in the terminal.

User Interactions: When running the program, read the console carefully. It will have instructions on how to run test cases or algorithms.

To modify input, you can directly modify .dat files.
