#include "Graph.h"

void Graph::initialize()
{
	// clearing all the contents of the adjacency list
	for (int i = 0; i < myList.size(); ++i)
		myList[i].clear();
	
	myList[0].push_back(node(4, 6125));
	myList[0].push_back(node(1, 839));
	myList[2].push_back(node(4, 5471));
	myList[3].push_back(node(2, 4036));
	myList[3].push_back(node(1, 2232));

}


Graph::Graph() {
	initialize();
}

//function for debugging
void Graph::print() {
	for (int i = 0; i < myList.size(); ++i)
		loopover(myList[i], i);
}

// function for debugging
void Graph::loopover(vector<node>& v, int num) {
	
	if (!v.empty()) {
		cout << endl << num;
		for (node n : v)
			cout << " --> " << n.num << "(" << n.edgeLen << ")";
	}
}

// A recursive function to print DFS starting from v
void Graph::DFSearch(int vertexNum, bool visited[])
{
	// Mark the current node as visited and print it
	visited[vertexNum] = true;
	// Recur for all the vertices adjacent to this vertex
	for (int i = 0; i < (int)myList[vertexNum].size(); ++i) {
		int neighborNum = myList[vertexNum][i].num;
		if (!visited[neighborNum])
			DFSearch(neighborNum, visited);
	}
}

AdjList Graph::getReverse()
{
	AdjList reversedList{myList.size()};
	for (int vertexNum = 0; vertexNum < (int)myList.size(); vertexNum++)
	{
		// Recur for all the vertices adjacent to this vertex
		for (int i = 0; i < myList[vertexNum].size(); ++i)
		{
			node nieghborVertex = myList[vertexNum][i];
			reversedList[nieghborVertex.num].push_back(node(vertexNum,nieghborVertex.edgeLen));
		}
	}
	cout << "===================================\n\t\tRevesed List\n========================\n";
	for (int i = 0; i < reversedList.size(); ++i)
		loopover(reversedList[i], i);
	return reversedList;
}

// The main function that returns true if graph is strongly connected
bool Graph::isStronglyConnected()
{
	// Step 1: Mark all the vertices as not visited (For first DFS)
	int size = (int)myList.size();
	bool* visited = new bool[size]{0};
	// Step 2: Do DFS traversal starting from first vertex.
	DFSearch(0, visited);
	// If DFS traversal doesn�t visit all vertices,then return false.
	for (int i = 0; i < size; i++)
		if (visited[i] == false)
			return false;

	// Step 3: Create a reversed graph
	AdjList reversedList = getReverse();


	// Step 4: Mark all the vertices as not visited (For second DFS)
	for (int i = 0; i < size; i++)
		visited[i] = false;

	// Step 5: Do DFS for reversed graph starting from first vertex. Starting Vertex must be same starting
	// point of first DFS
	DFSearch(0, visited);



	// If all vertices are not visited in second DFS, then return false
	for (int i = 0; i < size; i++)
		if (visited[i] == false)
			return false;

	delete visited;

	return true;
}

void Graph::checkStronglyConnected() {
	bool strongly = isStronglyConnected();
	// Check if the graph is strongly connected
	if (strongly) {
		cout << "The Graph is strongly connected.\n";
		print();
		return;
	}
	cout << "The Graph is not strongly connected....we will generate edges until it becomes so.\n";
	while (!strongly) {
		generateRandomEdge();
		strongly = isStronglyConnected();
	}
	cout << "Done generating random edges and the graph is strongly connected.\n"
		<< "The new graph looks like this:\n";
	print();

}