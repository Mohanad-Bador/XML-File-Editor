#include<iostream>
#include<vector>
#include "Functions.h"
#include "XMLParser.h"
#include "User.h"
#include "Graph.h"
using namespace std;
//Graph graph;

int main()
{
    XMLParser parser;
    vector<User*> users =parser.parseXML("sample.xml");
    for(int i=0;i<users.size();i++)
    {
        users[i]->print_user();
    }

    Graph userGraph(users.size());

    userGraph.buildGraph(users);

    // Print the adjacency list
    userGraph.printAdjacencyList();

    userGraph.findMostInfluentialUser();

    userGraph.findMostActiveUser();

    userGraph.findMutualFollowers("2","3");

/*
    // Create a Graph instance
    Graph userGraph;
    // Add users to the graph

    // Build the graph using the users vector
    userGraph.buildGraph(users);

    // Print the graph
    userGraph.printGraph();
*/
  return 0;
}
