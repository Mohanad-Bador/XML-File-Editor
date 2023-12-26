#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "User.h"
using namespace std;

class Graph {
private:
    vector<User*> users;
    vector<vector<User*>> adjList;


public:
    Graph();

    Graph(int numVertices,vector<User*> users);

    void addEdge(User* u, User* v);

    void printAdjacencyList() const;

    void buildGraph();

    User* findMostInfluentialUser();

    User* getUserById(const string &userid );

    User* findMostActiveUser();

    vector<User*> findMutualFollowers(const string& ID1, const string& ID2);
    vector<User*> suggest_followers(string id);
};

#endif



/*
#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <string>
#include "User.h"
class Graph {
private:
    unordered_map<string, User*> users;

public:
    Graph() {}

    void addUser(User* user);
    void addFollower(const string& userId, const string& followerId);
    void buildGraph(const vector<User*>& users);
    void printGraph() const;
};


#endif
*/
