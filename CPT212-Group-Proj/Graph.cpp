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

void Graph::generateRandomEdge()
{
	srand(time(0));
	int source{}, destination{};
	while (source == destination) {
		source = rand() % ((int)myList.size());
		destination = rand() % ((int)myList.size());

	}
	addEdge(source, destination);
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
	cout << "The graph currently looks like this:\n";
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

void Graph::reset() {
	initialize();
}





// function for debugging
void Graph::loopover(vector<node>& v, int num) {

	if (!v.empty()) {
		cout << endl << CITY_NAMES[num];
		for (node n : v)
			cout << " --> " << CITY_NAMES[n.num] << "(" << n.edgeLen << ")";
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
	AdjList reversedList{ myList.size() };
	for (int vertexNum = 0; vertexNum < (int)myList.size(); vertexNum++)
	{
		// Recur for all the vertices adjacent to this vertex
		for (int i = 0; i < myList[vertexNum].size(); ++i)
		{
			node nieghborVertex = myList[vertexNum][i];
			reversedList[nieghborVertex.num].push_back(node(vertexNum, nieghborVertex.edgeLen));
		}
	}

	return reversedList;
}

// The main function that returns true if graph is strongly connected
bool Graph::isStronglyConnected()
{
	// Step 1: Mark all the vertices as not visited (For first DFS)
	int size = (int)myList.size();
	bool* visited = new bool[size] {0};
	// Step 2: Do DFS traversal starting from first vertex.
	DFSearch(0, visited);
	// If DFS traversal doesn�t visit all vertices,then return false.
	for (int i = 0; i < size; i++)
		if (visited[i] == false)
			return false;

	// Step 3: Create a reversed graph
	AdjList reversedList = getReverse();
	Graph reversedGraph(reversedList);

	// Step 4: Mark all the vertices as not visited (For second DFS)
	for (int i = 0; i < size; i++)
		visited[i] = false;

	// Step 5: Do DFS for reversed graph starting from first vertex. Starting Vertex must be same starting
	// point of first DFS
	reversedGraph.DFSearch(0, visited);


	// If all vertices are not visited in second DFS, then return false
	for (int i = 0; i < size; i++)
		if (visited[i] == false)
			return false;

	delete visited, visited = NULL;

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
	cout << "The Graph is not strongly connected....we will generate edges until it becomes so.\n"
		<< "Please wait...";
	while (!strongly) {
		generateRandomEdge();
		strongly = isStronglyConnected();
	}
	cout << "\nDone generating random edges and the graph is strongly connected.\n"
		<< "The new graph looks like this:\n";
	print();

}

void Graph::removeEdge(int u, int v)
{
	for (int i = 0; i < myList[u].size(); i++) {
		if (myList[u][i] == v) {
			myList[u].erase(myList[u].begin() + i);
			break;
		}
	}

}

void Graph::shortestPath(int startnode, int destination) {
	int max = 5;
	int n = (int)myList.size(),
		* distance = new int[max],
		* pred = new int[max];
	bool* visited = new bool[max] {0};
	int count, mindistance, nextnode;
	int INF = 999999;
	//making all the distance INF and pred of all nodes startnode
	for (int i = 0; i < n; i++) {
		distance[i] = INF;
		pred[i] = startnode;
	}
	// inserting the adjacent nodes' distances in the ditance array
	for (node nd : myList[startnode]) {
		distance[nd.num] = nd.edgeLen;
	}
	//initial condition for the algorithm
	distance[startnode] = 0;
	visited[startnode] = true;
	count = 1;
	int i = 0, j = 0;
	//algorithm to find the shortest path
	while (count < n - 1) {
		mindistance = INF;
		for (i = 0; i < n; i++) {
			if (distance[i] < mindistance && !visited[i]) {
				mindistance = distance[i];
				nextnode = i;
			}
		}
		visited[nextnode] = true;
		for (node nd : myList[nextnode]) {
			if (!visited[nd.num]) {
				if (mindistance + nd.edgeLen < distance[nd.num])
				{
					distance[nd.num] = mindistance + nd.edgeLen;
				}
			}
		}
		count++;
	}
	// printing shortest path to all the vertices
	for (i = 0; i < n; i++)
		if (i != startnode && i == destination) {
			cout << "\nDistance of node " << i << "= " << distance[i];
			cout << "\nPath = " << i;
			j = i;
			do {
				j = pred[j];
				cout << " <--- " << j;
			} while (j != startnode);
		}
	cout << endl;
}


// A function to recieve a subgraph to apply MST on
void Graph::selectEdgesForMST()
{
	AdjList userList{ 5 };
	Graph subgraph(userList);
	int sourceVertex;
	int neighborVertex;
	char again = 'y';
	while (again == 'y' || again == 'Y') {

		//printing all vertices that have children
		vector<int> parents = getParentVertices();
		for (int i : parents)
			cout << i << ". " << CITY_NAMES[i] << endl;
		cout << "Please enter the number of parent vertex from list above: ";
		cin >> sourceVertex;

		//printing all nieghbors from selected vertex
		cout << "-----------------------------------------------\n";
		vector<int> neighbors = getNeighbors(sourceVertex);
		for (int i : neighbors)
			cout << i << ". " << CITY_NAMES[i] << endl;
		cout << "Please enter the number of neighbor vertex from list above: ";
		cin >> neighborVertex;

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

void Graph::selectEdgeToRemove()
{
	int sourceVertex, neighborVertex;
	//printing all vertices that have children
	vector<int> parents = getParentVertices();
	for (int i : parents)
		cout << i << ". " << CITY_NAMES[i] << endl;
	cout << "Please enter the number of parent vertex from list above: ";
	cin >> sourceVertex;

	//printing all nieghbors from selected vertex
	cout << "-----------------------------------------------\n";
	vector<int> neighbors = getNeighbors(sourceVertex);
	for (int i : neighbors)
		cout << i << ". " << CITY_NAMES[i] << endl;
	cout << "Please enter the number of neighbor vertex from list above: ";
	cin >> neighborVertex;

	removeEdge(sourceVertex, neighborVertex);
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
	//To make the graph strongly connected so we can have an MST
	while (!isStronglyConnected())
		generateRandomEdge();
	const int V = myList.size();
	// Array to store constructed MST
	int* parent = new int[V];
	// Key values used to pick minimum weight edge in cut
	int* key = new int[V];

	// To represent set of vertices included in MST
	bool* mstSet = new bool[V] { 0 };

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
int Graph::getMinKey(int key[], bool mstSet[]) {
	// Initialize min value
	int min = INT_MAX, min_index{};
	const int V = (int)myList.size();
	for (int v = 0; v < V; v++)
		if (mstSet[v] == false && key[v] < min)
			min = key[v], min_index = v;

	return min_index;
}
void Graph::printMST(int parent[]) {
	int sum = 0;
	cout << "The MST edges are:\n";
	for (int i = 0; i < 5; i++) {
		if (parent[i] != -1) {
			cout << CITY_NAMES[parent[i]] << " ---> " << CITY_NAMES[i] << "  " << "(" << DISTANCES[parent[i]][i] << ")" << endl;
			sum += DISTANCES[parent[i]][i];
		}
	}
	cout << "And the sum of the wieghts is: " << sum << endl;
}
