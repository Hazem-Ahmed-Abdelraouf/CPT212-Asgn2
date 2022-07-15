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
	cout << endl;
}

void Graph::addEdge(int source, int destination)
{	// checking if the edge already exists.
	if (find(myList[source].begin(), myList[source].end(), destination)
		== myList[source].end())
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

// Function 2
// Function that returns true if graph contains cycle
bool Graph::isCyclic()
{  
	int size = (int)myList.size();
	bool* visited = new bool[size] {0};

	bool* recStack = new bool[size]{0};
	for (int i = 0; i < size; i++)
	{
		visited[i] = false;
		recStack[i] = false;
	}

	for (int i = 0; i < size; i++)
		if (!visited[i] && DFSearch(i, visited))
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
			 << "Added the edge, do you want to add another ? (Y / N) : ";
		cin >> again;
	}
	// if it returns false, then the selected edges cannot produce MST  
	if (subgraph.findMSTOnce() == false) {
		cout << "The edges don't make an MST, so we are going to produce an MST from the original Graph\n";
		// now we are going to find MST from the original graph rooted at node '0'
		//firsly we need to make sure that the graph is strongly connected
		while (!isStronglyConnected())
			generateRandomEdge();
		//Then we call the findMST function
		findMST(0);
	}
	// else now we know that edges form a strongly connected graph and 
	// can produce atleast one MST without the need to generate random edges
	else {
		cout << "The selected edges can produce at least one MST\n";
		subgraph.findMST(0);
	}

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

bool Graph::findMSTOnce() {
	//If the graph is not strongly connected return false
	return isStronglyConnected();
}

void Graph::findMST(int root) {
	const int V = myList.size();
	// Array to store constructed MST
	int *parent = new int[V];
	// Key values used to pick minimum weight edge in cut
	int *key = new int[V];

	// To represent set of vertices included in MST
	bool *mstSet = new bool[V]{ 0 };

	// Initialize all keys as INFINITE
	for (int i = 0; i < V; i++)
		key[i] = INT_MAX;

	// Always include first 1st vertex in MST.
	// Make key 0 so that root node is picked as first vertex.
	key[root] = 0;
	parent[root] = -1; // root node has no parents in MST

	// The MST will have V vertices
	for (int count = 0; count < V - 1; count++)
	{
		// Pick the minimum key vertex from the not included vertices in MST
		int minVertex = getMinKey(key, mstSet);

		// Add the picked vertex to the MST Set
		mstSet[minVertex] = true;
		// Updating the key value and parent index of the adjacent vertices of
		// the picked vertex. (only nodes that have not been in the MST)
		for (int i = 0; i < (int)myList[minVertex].size(); i++) {
			node current = myList[minVertex][i];
			// If the current neighbor node is not in MST set and its length is less than its key then update them
			if (mstSet[current.num] == false && current.edgeLen < key[current.num]) {
				parent[current.num] = minVertex;
				key[current.num] = current.edgeLen;
			}

		}
	}
	printMST(parent);
	delete key, delete mstSet, delete parent;
}
int Graph:: getMinKey(int key[], bool mstSet[]) {
	// Initialize min value
	int min = INT_MAX, min_index{};
	const int V = (int) myList.size();
	for (int v = 0; v < V; v++)
		if (mstSet[v] == false && key[v] < min)
			min = key[v], min_index = v;

	return min_index;
}
void Graph::printMST(int parent[]) {
	cout << "The MST edges are:\n";
	for (int i = 0; i < 5; i++)
		if (parent[i] != -1)
			cout << parent[i] << " - " << i << endl;
}
/*
// Number of vertices in the graph
#define V 5

// A utility function to find the vertex with
// minimum key value, from the set of vertices
// not yet included in MST
int minKey(int key[], bool mstSet[], int V)
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
	const int V = myList.size();
	// Array to store constructed MST
	int parent[V];

	// Key values used to pick minimum weight edge in cut
	int key[V];

	// To represent set of vertices included in MST
	bool mstSet[V]{0};

	// Initialize all keys as INFINITE
	for (int i = 0; i < V; i++)
		key[i] = INT_MAX;

	// Always include first 1st vertex in MST.
	// Make key 0 so that root node is picked as first vertex.
	key[root] = 0;
	parent[root] = -1; // root node has no parents in MST

	// The MST will have V vertices
	for (int count = 0; count < V - 1; count++)
	{
		// Pick the minimum key vertex from the not included vertices in MST
		int minVertex = minKey(key, mstSet);

		// Add the picked vertex to the MST Set
		mstSet[minVertex] = true;

		------------------------------------------------------------------------
		// Updating the key value and parent index of the adjacent vertices of
		// the picked vertex. (only nodes that have not been in the MST)
		for (int v = 0; v < V; v++)
		
			// graph[u][v] is non zero only for adjacent vertices of m
			// mstSet[v] is false for vertices not yet included in MST
			// Update the key only if graph[u][v] is smaller than key[v]
			if (graph[u][v] && mstSet[v] == false && graph[u][v] < key[v])
				parent[v] = u, key[v] = graph[u][v];
		+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
			// Updating the key value and parent index of the adjacent vertices of
			// the picked vertex. (only nodes that have not been in the MST)
			for (int i = 0; i < (int)myList[minVertex].size()) {
				node current = myList[minVertex][i];
				// If the current neighbor node is not in MST set and its length is less than its key then update them
				if (mstSet[current.num] == false && current.edgelen < key[current.num]) {
					parent[current.num] = minVertex;
					key[current.num] = current.edgeLen;
				}

			}
	
	// print the constructed MST
	printMST(parent, graph);
}
*/
