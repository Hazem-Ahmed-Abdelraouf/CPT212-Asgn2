#pragma once

#ifndef GRAPH.H

#define GRAPH
#include<vector>
#include <string>
#include <iostream>
#include <ctime>
#include <cstdlib>
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
    void generateRandomEdge();
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
    void selectEdgesForMST();
	//function to print the graph
	void print();
    void addEdge(int source, int destination);

};

#endif
