#pragma once

#ifndef GRAPH.H

#define GRAPH
#include<vector>
#include <string>
#include <iostream>
using namespace std;
// City names array 
const string CITY_NAMES[5] = { "Monaco, Monaco",
                               "Mostar, Bosnia and Herzegovina",
							   "Madrid, Spain",
                               "Yerevan, Armenia",
                               "Boston, United States"};

// Distances array from each vertex to the rest
const int DISTANCES[5][5] = { {0,839,988,3066,6125},
                              {839,0,1806,2232,6869},
                              {988,1806,0,4036,5471},
                              {3066,2232,4036,0,8783},
                              {6125,6869,5471,8783,0} };



struct node {
	int num{};
	int edgeLen{};
	node(int num = 0, int edgeLen = 0) : num(num), edgeLen(edgeLen){} // constructor
	void operator=(const node& right) {
		this->num = right.num;
		this->edgeLen = right.edgeLen;
	}
	bool operator==(int val) { 
		return this->num == val;
	}


};
/****************************************
   DATA STRUCTURE: Adjacency List
******************************************/
typedef vector<vector<node>> AdjList;

class Graph
{
private:
	AdjList myList{5};
	void initialize();
    void generateRandomEdge() { return; };
	// function to loopover and print each vertex's neighbors
	void loopover(vector<node>& v, int num);
    // A recursive function to DFS starting from a vertex number
    void DFSearch(int vertexNum, bool visited[]);
    // To reverse the graph 
    AdjList getReverse();
	// A function that returns true if the graph is strongly connected
    bool isStronglyConnected();
    // get all parent vertices
    vector<int> getParentVertices();
    // get nieghbors of a vertex
    vector<int> getNeighbors(int source);
    // To get the minimum key 
    int getMinKey(int key[], bool mstSet[]);
    // To print MST
    void printMST(int parent[]);
public:
	Graph();
    Graph(AdjList list);
	void reset();
	void removeEdge(int start, int end);
    void checkStronglyConnected();
	void detectCycle();
	void shortestPath(int start, int end);
    bool findMSTOnce();
	void findMST(int root);
    void printAndSelectEdges();
	//function to print the graph
	void print();
    void addEdge(int source, int destination);

};

#endif

/*
// Number of vertices in the graph
#define V 5

// A utility function to find the vertex with
// minimum key value, from the set of vertices
// not yet included in MST
int minKey(int key[], bool mstSet[])
{
    // Initialize min value
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++)
        if (mstSet[v] == false && key[v] < min)
            min = key[v], min_index = v;

    return min_index;
}

// A utility function to print the
// constructed MST stored in parent[]
void printMST(int parent[], int graph[V][V])
{
    cout<<"Edge \tWeight\n";
    for (int i = 1; i < V; i++)
        cout<<parent[i]<<" - "<<i<<" \t"<<graph[i][parent[i]]<<" \n";
}
// Function to construct and print MST for
// a graph represented using adjacency
// matrix representation
void primMST(int graph[V][V])
{
    // Array to store constructed MST
    int parent[V];

    // Key values used to pick minimum weight edge in cut
    int key[V];

    // To represent set of vertices included in MST
    bool mstSet[V];

    // Initialize all keys as INFINITE
    for (int i = 0; i < V; i++)
        key[i] = INT_MAX, mstSet[i] = false;

    // Always include first 1st vertex in MST.
    // Make key 0 so that this vertex is picked as first vertex.
    key[0] = 0;
    parent[0] = -1; // First node is always root of MST

    // The MST will have V vertices
    for (int count = 0; count < V - 1; count++)
    {
        // Pick the minimum key vertex from the
        // set of vertices not yet included in MST
        int u = minKey(key, mstSet);

        // Add the picked vertex to the MST Set
        mstSet[u] = true;

        // Update key value and parent index of
        // the adjacent vertices of the picked vertex.
        // Consider only those vertices which are not
        // yet included in MST
        for (int v = 0; v < V; v++)

            // graph[u][v] is non zero only for adjacent vertices of m
            // mstSet[v] is false for vertices not yet included in MST
            // Update the key only if graph[u][v] is smaller than key[v]
            if (graph[u][v] && mstSet[v] == false && graph[u][v] < key[v])
                parent[v] = u, key[v] = graph[u][v];
    }

    // print the constructed MST
    printMST(parent, graph);
}

// Driver code
int main()
{
    /* Let us create the following graph
        2 3
    (0)--(1)--(2)
    | / \ |
    6| 8/ \5 |7
    | / \ |
    (3)-------(4)
            9     
int graph[V][V] = { { 0, 2, 0, 6, 0 },
                    { 2, 0, 3, 8, 5 },
                    { 0, 3, 0, 0, 7 },
                    { 6, 8, 0, 0, 9 },
                    { 0, 5, 7, 9, 0 } };

// Print the solution
primMST(graph);

return 0;
}
*/