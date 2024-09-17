## Leading Question 
We will be using the flight data set. We can learn how to write graphing algorithms and how to actually develop products that are applicable to everyday life. More specifically we will be able to answer the question of the shortest path between airports in the world given a start and end point.
We will develop a shortest path algorithm given the flights and the airports with weights depending on distance and maybe frequency of flights. We will then return the path between the airports. If we have more time we may try to display the flight path visually.
For the algorithms, we may try several to determine the best one, for example Dijkstra’s, BFS, DFS, etc. 

## Dataset Acquisition
Source of the dataset is the flight data: https://openflights.org/data.html

## Data Format
Specifically we will be looking at the airport data and the routes data. The input format are .dat files but we can expand this to be string, text file, etc. as we see fit. The data is quite large, estimate about 10000 routes. We estimate to use most of the data, but we may not need specific country data. We plan to store the data likely in an array for each node representing airports which would store the airport information and routes information.

## Data Correction
We will parse the input data from a text file, with each line representing new data. The information in each line is separated by commas, so we can check for commas to see what information is what. Since each new data is on a new line, if there are missing information for one specific datum, then that information will have a NULL value. Then when we run algorithms, we will make sure to constantly check for NULL values. Alternatively we may just ignore data that has missing information to simplify the process.

## Data Storage
We will store the data using directed graphs and arrays (vectors). The graph will have each node as an airport, and each node will store connections to other nodes through the routes information. It is a directed graph so we can only go in one direction. Given n airports and m routes, we estimate to store about O(n+m) or more specifically O(n+2m) (each route may produce two data points: airport to airport and weights information). 

## Algorithm 
For the algorithms, we plan to use BFS to implement Dijkstra’s and pagerank, and also store runtime information just so we can see the most efficient algorithm.
For each algorithm, expected inputs are starting airport and ending airport. No other inputs are needed, everything else is stored in the graph.
For the output, we expect to print the path found as well as the distance that was found. If extra time allows we may try to show the path visually on a map of the world, so that users can visually see the output path.

Big O storage for all algorithms should be O(n+m), since everything will be stored in the graph. We may use queue and stack extra storage, but that doesn’t impact the Big O size.
Estimate of the Big O for time will be O(n+mlogn), assuming that n is airports and m is routes for Dijkstra’s algorithm.
Big O time for pagerank should be O(n+m) where n is airports and m is routes. This is because we should need to visit each node and edge at least once.

## Timeline
Data acquisition- Week 1
Data processing- Week 2 (parsing data, putting into a readable format)
Data storage- Week 3 (putting data into graph and programming nodes)
Completion of each individual algorithm - Week 4-5 (programming algorithms, making sure its correct, outputing correct value, etc.)
Production of final deliverables- Week 6 (final week) (ensuring correct algorithm, correct output, etc., maybe trying to implement visuals if time allows).
