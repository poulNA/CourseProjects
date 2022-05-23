# Project Proposal

# AIM:
Leading question: 
What is the shortest path between two points through a particular node?
Given the road networks dataset of a region, We’ll convert it into a graph and then generate a general search tool to perform various kinds of operations on it including- finding the shortest path from one node to another, finding shortest path between two nodes going through n other landmarks or traverse the road network to search for a specific node or a feature.
 
# DATA ACQUISITION AND PROCESSING:
We’ll be using the California road network dataset from the following source https://www.cs.utah.edu/~lifeifei/SpatialDataset.htm.

# Data Format:
The dataset clearly describes the format:
 Nodes (Node ID, longitude, latitude)
Edges (Edge ID, start Node ID, end Node ID, distance)
Data correction:
We’ll ensure that the start node ID and end node ID of edges are valid nodes
We’ll also ensure that all the columns are stored as an appropriate data type for example (longitude and latitude should be stored as a data type that supports negative values) while node ID should only be positive.

# Data Storage: 
We’ll use an adjacency list where we store the distance from 1 node to another as a 2-D array. For example vect[1][2] will give the weight of the edge from 1 to 2. If it’s zero it means there is no edge from 1 to 2.
We’ll also store nodes as a vector of Nodes given by the dataset.


# GRAPH ALGORITHMS:
# Graphic Output of graph: Project on to map based on data
	This algorithm will be used to create a map of the road networks in California. Each node and edge between the start and the destination will be printed out on the map. The map of California state will be used as the base sticker and the nodes will be plotted on it along with the lines/paths between them. We will make use of the CS 225 Sticker Sheet code to accomplish this.
# BFS Traversal algorithm
	A BFS traversal is required to find a node in a graph. For this algorithm the input will be the graph and this algorithm will allow us to generate a directed path of vertex and edges and find a wanted vertex.
# Djikstra’s algorithm
	This algorithm will have the SCC graph version as its input. The main objective of this algorithm will be to find the minimum distance between start and end vertices. The output of this algorithm will be a double representing the minimum distance between two points. 

# Function Efficiency: 
# 1.BFS algorithm: 
O(V + E ). V being number of vertices and E being number of edges. It will take O(V+E) memory.

# 2. Dijkstra’s algorithm: 
O((|E| + |V|) log |V|) with a binary heap.

# TIMELINE: 
Week of 28th March: Organize the dataset and load it so that it is ready for use.
Week of 4th April and 11th April: Start making the graphs with the organized data 
Week of 18th April: Apply above mentioned algorithms to find the shortest path.
Week of 25th April: Implement the shortest path through n landmarks.
Week of 2nd May: Complete final optimizations, analyze time complexities, and prepare the documents to be submitted


