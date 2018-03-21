#include <iostream>
#include <queue>
#include <stdio.h>
#include <stdlib.h>
#include <utility>
#include <vector>
#include <assert.h>

using namespace std;

// might not need this
class Vertex
{
public:
	Vertex(int vertexNum)
	{
		m_vertexNum = vertexNum;
	}

	// Vertex's designated vertex number in Graph
	int m_vertexNum;
};

// might not need this
class Edge
{
public:
	Edge(Vertex vertex1, Vertex vertex2) :
		m_edge({ vertex1, vertex2 })
	{
	}

	// An edge is simply defined as the 2 vertices
	// that it connects
	std::pair<Vertex, Vertex> m_edge;
};

class Graph
{
public:
	Graph(vector<int> input)
	{
		// Assumed: size of input is at least 2 (i.e. at least empty graph)
		assert(input.size() > 2);

		// Allocate memory for 2D, nxn adjacency matrix
		// n = input[0], as shown in example for assignment
		int n = input[0];
		m_adjacencyMatrix = new int*[n];
		for (int i = 0; i < n; i++)
		{
			m_adjacencyMatrix[i] = new int[n];
		}

		// Init adjacency matrix to all zeros
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				m_adjacencyMatrix[i][j] = 0;
			}
		}

		// Init adjacency matrix based on edges given
		// Start at 1 for first edge, as shown in example for assignment
		int i = 1;
		while (i < input.size() && input[i] >= 0)	// Sequence ends with a negative int
		{
			int vertex1 = input[i];
			int vertex2 = input[i + 1];
			m_adjacencyMatrix[vertex1][vertex2] = 1;
			m_adjacencyMatrix[vertex2][vertex1] = 1;
			i = i + 2;	// next edge starts at index after next
		}

		// Alloc memory for m_distanceMatrix, will be initialized with Diameter function
		m_distanceMatrix = new int*[n];
		for (int i = 0; i < n; i++)
		{
			m_distanceMatrix[i] = new int[n];
		}

		m_numVertices = n;
	}

	// 2D adjacency matrix (i.e. an array of int arrays)
	int **m_adjacencyMatrix;
	
	// 2D distance matrix to keep track of distances between each node
	int **m_distanceMatrix;

	int m_numVertices;
};


// For testing
static void PrintDistanceMatrix(Graph G)
{
	for (int i = 0; i < G.m_numVertices; i++)
	{
		for (int j = 0; j < G.m_numVertices; j++)
		{
			int current = G.m_distanceMatrix[i][j];
			cout << current << " ";
		}
		cout << "\n";
	}
}

// TODO: Probably need to implement this as a method to compute the shortest
//		path between two vertices. BFS doesn't always find shortest path,
//		and we want the distances between each vertex to be shortest path
//		between them for computing the diameter of the graph
static void Visit(int v, int distanceFromV, int* distance)
{
	// Record distance for current vertex v from the starting vertex
	distance[v] = distanceFromV;
}

// Output: Distance array, distance that v is from each other vertex
static int* BFS(Graph G, int v)
=======
// TODO: implement Visit method
static int Visit(Graph G, int v, queue<int> *vertexQueue)
{
	for (int i = 0; i < G.m_numVertices; i++)
	{
		if (G.m_adjacencyMatrix[v][i] == 1)
		{
			&vertexQueue.push(i);
		}
	}
}

static int doneVisiting(int[] visited)
{
	for (int i = 0; i < visited.size();i++)
	{
		if (visited(i) == 0)
		{
			return 0;
		}
	}
	return 1;
}


static void BFS(Graph G, int v)
{
	// Init queue of vertices
	queue<int> vertexQueue;
	
	// Alloc memory for visted array to keep track of visited vertices and
	// distance array to keep track of each vertex distance from v
	int numVertices = G.m_numVertices;
	int* visited = new int[numVertices];
	int* distance = new int[numVertices];
	
	for (int i = 0; i < numVertices; i++)
	{
		visited[i] = 0;
		distance[i] = 0;
	}

	// distanceFromV is the distance of the current vertex from v, i.e
	// the iteration we're on in the while loop
	int distanceFromV = 0;

	vertexQueue.push(v);
	visited[v] = 1;
	// Need to implement visit

	Visit(v, distanceFromV, distance);

	while (!vertexQueue.empty())
	{
		// Increment the iteration number, i.e. distance from starting vertex, v
		distanceFromV++;

		int currentVertex = vertexQueue.front();
		vertexQueue.pop();

		// Get row for currentVertex in adjacency matrix to check for its
		// adjacent vertices
		int* currentVertexMatrixRow = G.m_adjacencyMatrix[currentVertex];
		for (int vertex = 0; vertex < numVertices; vertex++)
		{
			if (currentVertexMatrixRow[vertex] == 1)
			{
				// This vertex is adjacent, mark it as visited in the array
				// if it is not already and push onto queue
				if (visited[vertex] == 0)
				{
					vertexQueue.push(vertex);
					visited[vertex] = 1;
					Visit(vertex, distanceFromV, distance);
				}
			}
		}
	}

	return distance;
}

static void InitDistanceMatrix(Graph G)
{
	int numVertices = G.m_numVertices;

	for (int currentVertex = 0; currentVertex < numVertices; currentVertex++)
	{
		int *distancesFromCurrent = BFS(G, currentVertex);
		G.m_distanceMatrix[currentVertex] = distancesFromCurrent;
	}

	// Validate that the matrix is symmetric with the shortest distances from each
	// vertex to each other vertex. BFS doesn't always find shortest path.
	// NOTE: This will probably be unnecessary when we implement Visit to find shortest
	//		path between two vertices
	for (int vertex1 = 0; vertex1 < numVertices; vertex1++)
	{
		for (int vertex2 = 0; vertex2 < numVertices; vertex2++)
		{
			int *distance1 = &G.m_distanceMatrix[vertex1][vertex2];
			int *distance2 = &G.m_distanceMatrix[vertex2][vertex1];

			// If one distance is less than the other, replace larger one
			if (distance1 < distance2)
			{
				*distance2 = *distance1;
			}
			else if (distance2 < distance1)
			{
				*distance1 = *distance2;
			}
		}
	}
}

static int Diameter(Graph G)
{
	InitDistanceMatrix(G);

	// TODO: implement if condition for if graph is not connected

	// Find diameter, i.e. max distance between any 2 vertices in graph
	int diameter = 0;
	for (int i = 0; i < numVertices; i++)
	{
		for (int j = 0; j < numVertices; j++)
		{
			if (G.m_distanceMatrix[i][j] > diameter)
			{
				diameter = G.m_distanceMatrix[i][j];
			}
		}
	}

	// For testing
	PrintDistanceMatrix(G);

	return diameter;
}

int main()
{
	vector<int> input = { 5, 0, 1, 1, 4, 2, 3, 1, 3, 3, 4, -1 };
	Graph graph = Graph(input);

	// test adjacency matrix by printing
	for (int i = 0; i < input[0]; i++)
	{
		for (int j = 0; j < input[0]; j++)
		{
			int current = graph.m_adjacencyMatrix[i][j];
			cout << current << " ";
		}
		cout << "\n";
	}
	cout << "\n";

	// Test with vertex for 0
	BFS(graph, 0);

	Diameter(graph);

	

	return 0;
}
