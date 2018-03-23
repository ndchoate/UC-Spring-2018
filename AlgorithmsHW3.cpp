#include <queue>
#include <vector>
#include <set>
#include <iostream>
#include <stdlib.h>
//#include <utility>
#include <array>
#include <assert.h>

using namespace std;

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

	//int **m_connectedMatrix;

	int m_numVertices;
};


// For testing
static void PrintDistanceMatrix(Graph G)
{
	int num = G.m_numVertices;
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

static void Visit(int v, int distanceFromV, int* distance)
{
	// Record distance for current vertex v from the starting vertex
	distance[v] = distanceFromV;
}

// Output: Distance array, distance that v is from each other vertex
static vector<int*> BFS(Graph G, int v)
{
	// Init queue of vertices
	queue<int> vertexQueue;

	// Alloc memory for visted array to keep track of visited vertices and
	// distance array to keep track of each vertex distance from v
	int numVertices = G.m_numVertices;
	int* visited = new int[numVertices];
	int* distance = new int[numVertices];

	vector<int*> visitedAndDistance;


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
	visitedAndDistance.push_back(visited);
	visitedAndDistance.push_back(distance);
	return visitedAndDistance;
}

static void InitDistanceMatrix(Graph G)
{
	int numVertices = G.m_numVertices;

	for (int currentVertex = 0; currentVertex < numVertices; currentVertex++)
	{
		vector<int*> visitedAndDistance = BFS(G, currentVertex);
		int *distancesFromCurrent = visitedAndDistance[1];
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
			int distance1 = G.m_distanceMatrix[vertex1][vertex2];
			int distance2 = G.m_distanceMatrix[vertex2][vertex1];

			// If one distance is less than the other, replace larger one
			if (distance1 < distance2)
			{
				G.m_distanceMatrix[vertex2][vertex1] = distance1;
				// distance2 = distance1;
			}
			else if (distance2 < distance1)
			{
				G.m_distanceMatrix[vertex1][vertex2] = distance2;
				// distance1 = distance2;
			}
		}
	}
}

static set<set<int>> Components(Graph G)
{
	int numVertices = G.m_numVertices;
	vector<vector<int>> components;
	set<set<int>> componentsSet;

	for (int i = 0; i < numVertices; i++)
	{
		vector<int*> visitedAndDistance = BFS(G, i);
		vector<int> visitedArray;
		for (int j = 0; j < numVertices; j++)
		{
			visitedArray.push_back(visitedAndDistance[0][j]);
		}

		bool foundEqual = false;
		for (int j = 0; j < components.size(); j++)
		{
			if (visitedArray == components[j])
			{
				foundEqual = true;
			}
		}

		if (!foundEqual)
		{
			components.push_back(visitedArray);
		}
	}

	for (int i = 0; i < components.size(); i++)
	{
		set<int> currentComponent;
		vector<int> component = components[i];
		for (int j = 0; j < numVertices; j++)
		{
			if (component[j] != 0)
			{
				currentComponent.insert(j);
			}
		}

		componentsSet.insert(currentComponent);
	}

	return componentsSet;
}

static int Diameter(Graph G)
{
	InitDistanceMatrix(G);
	int numVertices = G.m_numVertices;

	// Init diameter to 0, if it's empty graph its diameter is 0
	int diameter = 0;

	set<set<int>> connectedComponents = Components(G);
	if (connectedComponents.size() == 1)
	{
		// Entire graph is connected, find diameter
		// Find diameter, i.e. max distance between any 2 vertices in graph
		
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

	}
	else if (connectedComponents.size() > 0)
	{
		// Graph components are not connected, diameter is -1
		diameter = -1;
	}

	return diameter;
}

int main()
{
	vector<int> input = { 5, 0, 1, 1, 4, 2, 3, 1, 3, 3, 4, -1 };
	Graph graph = Graph(input);

	// print adjacency matrix
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

	// print diameter or connected components
	int diameter = Diameter(graph);
	if (diameter != -1)
	{
		cout << diameter << "\n";
	}
	else if (diameter == -1)
	{
		set<set<int>> connectedComponents = Components(graph);
		set<set<int>>::iterator setIt = connectedComponents.begin();
		for (int i = 0; i < connectedComponents.size(); i++)
		{
			setIt++;
			set<int> temp = *setIt++;
			set<int>::iterator secondSetIt = temp.begin();
			for (int j = 0; j < temp.size(); j++)
			{
				cout << *secondSetIt << " ";
			}
			cout << "\n";
		}
	}

	return 0;
}
