/*
 *  Joseph Armstrong
 *  To be run with a .txt file that gives nodes and distances between nodes
 *  Utilizes dijkstra's algorithm to parse through a nodes and find the best path
 *
 */


#include <iostream>
#include <fstream>
#include <stdexcept>

#define INFINITY 9999
#define max 30

using namespace std;

int vertArr[30][30];  // initialize the matrix used
int array[30];        // initializes an array to store the building values

void add_edge(int u, int v, int dist) {       //function to add edge into the matrix
    vertArr[u][v] = dist;     // adds the vertices and distance to the matrix
    vertArr[v][u] = dist;     // undirected so it has to be added in both directions
}

int checkNodes(int x)   {     // used to store the building name values and return a value for the matrix
    int check=0;
    int secondCheck = 0;
    int rtrn;
    for(int i = 0; i < 30; i++) {
        if(array[i] == x) {    // checks if the array has already stored the building name
            check++;
            rtrn = i;          // returns a previouslt assigned name
        }
        if(array[i] == 0 && secondCheck == 0 && check < 1)   {  // checks that the array doesn't have the new building
            array[i] = x;        // inserts the new building to the next available spot
            rtrn = i;
            secondCheck = 1;
        }
    }
    return rtrn;      // returns a value the matrix will be able to use
}

int outputNodes(int x)  {    // converts user input to the proper terms for the matrix
    int rtrn;
    for(int i = 0; i<30; i++)   {
        if(array[i] == x)   {    // searches the array and returns the location
            rtrn = i;
        }
    }
    return rtrn;
}

int DNodes(int x)  {     // converts the matrix's outputs to the proper terms used by the user
    int rtrn = 0;
    rtrn = array[x];
    return rtrn;
}

void dijkstra(int G[max][max], int n, int startnode, int endnode) {
    int cost[max][max],distance[max],pred[max];
    int visited[max],count,mindistance,nextnode,i,j;
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            if(G[i][j]==0)
                cost[i][j]=INFINITY;  // sets the cost matrix to a large number
            else
                cost[i][j]=G[i][j];
    for(i=0;i<n;i++) {
        distance[i]=cost[startnode][i];  // sets teh distance array to the updated cost matrix
        pred[i]=startnode;
        visited[i]=0;              // marks nodes as unvisited 
    }
    distance[startnode]=0;    // sets the distance to and from the startnode as 0
    visited[startnode]=1;    // marks the startnode as visited
    count=1;
    while(count<n-1) {
        mindistance=INFINITY;  //initializes the minimum distance to a large number
        for(i=0;i<n;i++)
            if(distance[i]<mindistance&&!visited[i]) {  //checks the distance traversed and that the node hasn't been visited yet
                mindistance=distance[i];        // changes the mindistance to the current's node
                nextnode=i;                     // sets which node to traverse next
            }
        visited[nextnode]=1;          // marks the next node as visited
        for(i=0;i<n;i++)
            if(!visited[i])
                if(mindistance+cost[nextnode][i]<distance[i]) {  
                    distance[i]=mindistance+cost[nextnode][i];    // if the current node is not visited, this changes the distance array
                    pred[i]=nextnode;
                }
        count++;
    }
    for(i=endnode-1;i<endnode;i++)    // displays the information of the path to the user
        if(i!=startnode) {
            cout<<"\nDistance of node "<< DNodes(i) <<"="<<distance[i];  // displays the total distance
            cout<<"\nPath="<< DNodes(i);    // displays the node path ending
            j=i;
            do {
                j=pred[j];
                cout << "<-" << DNodes(j);    // displays the traversal path
            }while(j!=startnode);
        }
}

int main() {
    ifstream inf;
    inf.open("graph.txt");     // opens the file given
    if (inf.fail()) {
        cerr << "Error: Could not open input file\n";
        exit(1);
    }
    inf.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    int vertices = 0;    // initializes the vertices to 0
    while (vertices < 1) {
        try {
            inf >> vertices;    // takes the first input of the file and sets it to the number of vertices
        }
        catch (std::ifstream::failure e) {
            break;
        }
    }

    int u, v, dist;      // initializes the integers used for reading from the file
    while (!inf.eof() > 0) {
        try {
            inf >> u;    // reads the first node
            inf >> v;    // reads the second node
            u = checkNodes(u);    // changes the nodes value to one the matrix can use while also storing the initial value
            v = checkNodes(v);    // changes the nodes value to one the matrix can use while also storing the initial value
            inf >> dist; // reads the distance between the nodes
            add_edge(u, v, dist);    // adds an edge from the file
        }
        catch (std::ifstream::failure e) {
            break;
        }
    }
    inf.close();

    int endNode, startNode;
    cout << "Enter the start building: " << endl;
    cin >> startNode;
    cout << endl << "Enter the end building: " << endl;
    cin >> endNode;

    startNode = outputNodes(startNode);
    endNode = outputNodes(endNode)+1;

    dijkstra(vertArr, vertices, startNode, endNode);

    return 0;
}