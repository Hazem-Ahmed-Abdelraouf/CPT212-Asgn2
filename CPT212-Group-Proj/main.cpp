/*
    The cities number encodeing:
    0. Monaco, Monaco
    1. Mostar, Bosnia and Herzegovina
    2. Madrid, Spain
    3. Yerevan, Armenia
    4. Boston, United States
*/

#include "Graph.h"
using namespace std;

void menu();
int main()
{
    int menuChoice{}, u,v;

    Graph g;
    while (menuChoice != 9) {
        menu();
        cout << "Please enter your choice : ";
        cin >> menuChoice;
        switch (menuChoice) {
        case 1://print graph
            g.print();
            break;
        case 2://check if graph is strongly connected
             
            break;
        case 3://check if there is a cycle
             
            break;
        case 4://compute the shortest path between two vertices
            
            break;
        case 5://Find an MST from certain edges
            g.print();
            g.selectEdgesForMST();
            break;
        case 6://Add an edge
            
            break;

        case 7://Remove an edge
            g.selectEdgeToRemove();
            break;
        case 8://Reset the graph
            g.reset();
        }
    }


    return 1;
}

void menu() {
    cout << "--------------------------------------------------------------------------" <<
        "\n\t\tMenu options\n\
            1. print graph \n\
            2. check if graph is strongly connected \n\
            3. check if there is a cycle\n\
            4. compute the shortest path between two vertices\n\
            5. Find an MST from certain edges\n\
            6. Add an edge\n\
            7. Remove an edge \n\
            8. Reset the graph\n\
            9. Quit program\n" <<
        "--------------------------------------------------------------------------" << endl;
}
