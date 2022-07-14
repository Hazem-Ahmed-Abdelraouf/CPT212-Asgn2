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

Graph::Graph(AdjList list)
{
	this->myList = list;
}


//function for debugging
void Graph::print() {
	for (int i = 0; i < myList.size(); ++i)
		loopover(myList[i], i);
}

void Graph::addEdge(int source, int destination)
{	// checking if the edge already exists.
	if (find(myList[source].begin(), myList[source].end(), destination)
		!= myList[source].end())
	{
		myList[source].push_back(node(destination, DISTANCES[source][destination]));
	}
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


// A recursive function to print DFS starting from v used by isCyclic()
bool Graph::isCyclicUtil(int vertexNum, bool visited[], bool* recStack)
{
	if (visited[vertexNum] == false)
	{
		visited[vertexNum] = true;
		recStack[vertexNum] = true;

		//list<pair<int,int>>::iterator i;
		for (int i = 0; i < adj[vertexNum].size(); ++i)
		{
			if (!visited[i] && isCyclicUtil(i, visited, recStack))
				return true;
			else if (recStack[i])
				return true;
		}
	}
	recStack[vertexNum] = false; // Remove vertex from recursion stack
	return false;
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
	// If DFS traversal doesn’t visit all vertices,then return false.
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

bool Graph::isCyclic()
{
	bool* visited = new bool[V];
	bool* recStack = new bool[V];
	for (int i = 0; i < V; i++)
	{
		visited[i] = false;
		recStack[i] = false;
	}

	for (int i = 0; i < V; i++)
		if (!visited[i] && isCyclicUtil(i, visited, recStack))
			return true;

	return false;
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
// A function to recieve a subgraph to apply MST on
void Graph::printAndSelectEdges()
{
	AdjList userList{ 5 };
	Graph subgraph(userList);
	int sourceVertex;
	int neighborVertex;
	char again = 'y';
	while (again == 'y' || again == 'Y'){

		//printing all vertices that have children
		vector<int> parents = getParentVertices();
		for (int i : parents)
			cout << i << ". " << CITY_NAMES[i] << endl;
		cout << "Please enter the number of parent vertex from list above: ";
		cin >> sourceVertex;
		/*
		* validate selection from parents vertex
		*/
		//printing all nieghbors from selected vertex
		cout << "-----------------------------------------------\n";
		vector<int> neighbors = getNeighbors(sourceVertex);
		for (int i : neighbors)
			cout << i << ". " << CITY_NAMES[i] << endl;
		cout << "Please enter the number of neighbor vertex from list above: ";
		cin >> neighborVertex;
		/*
		 validate the neigbor from selection
		*/
		subgraph.addEdge(sourceVertex, neighborVertex);
		cout << "--------------------------------------------\n"
			 << "Added the edge, do you want to continue ? (Y / N) : ";
		cin >> again;
	}
	subgraph.findMSTOnce();

}

vector<int> Graph::getParentVertices()
{
	vector<int> parents;
	for (int i = 0; i < (int)myList.size(); ++i)
		if (!myList[i].empty())
			parents.push_back(i);
	return parents;
}
vector<int> Graph::getNeighbors(int source)
{
	vector<int> neighbors;
	for (int i = 0; i < (int)myList[source].size(); i++)
		neighbors.push_back(myList[source][i].num);
	return neighbors;
}
