/*
    The cities number encodeing:
    0. Monaco, Monaco
    1. Mostar, Bosnia and Herzegovina
    2. Madrid, Spain
    3. Yerevan, Armenia
    4. Boston, United States
*/

#include <iostream>
#include <vector>
#include "Graph.h"
using namespace std;
/*
 Menu options
 1. print graph
 2. check if graph is strongly connected
 3. check if there is a cycle
 4. compute the shortest path between two vertices
 5. Find an MST from certain edges
 6. Add an edge
 7. Remove an edge
 8. Reset the graph
 9. Quit program

*/
int main()
{
    //AdjList a{5};
    //a[0].push_back(node(1, 5 ));
    //a[1].push_back(node(2, 6 ));
    //a[2].push_back(node(3, 4 ));
    //a[3].push_back(node(4, 2 ));
    ////a[4].push_back(node(0 ,3 ));
 
    Graph g;
    g.print();
    g.selectEdgesForMST();
    g.print();
    //while (menuChoice != 9) {
    //    //printMenu();
    //    cout << "Please enter your choice : ";
    //    cin >> menuChoice;
    //    switch (menuChoice) {
    //    case 5:
    //        g.print();
    //        g.printAndSelectEdges();
    //        
    //    }
    //}

  
    return 1;
}