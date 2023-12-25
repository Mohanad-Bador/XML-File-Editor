#include "Graph.h"

Graph::Graph(){}

Graph::Graph(int numVertices) : adjList(numVertices+1) {}


void Graph::addEdge(User* u, User* v) {
    // Assuming that the User class has an 'id' attribute
    int userId = std::stoi(u->id);
    int followerId = std::stoi(v->id);

    // Adding the edge to the adjacency list
    adjList[userId].push_back(v);
}

void Graph::printAdjacencyList() const {
    for (int i = 1; i < adjList.size(); ++i) {
        cout << "User ID " << i << " -> ";
        for (const User* user : adjList[i]) {
            cout << user->id << " ";
        }
        cout << endl;
    }
}

void Graph::buildGraph(const vector<User*>& users){

    // Adding edges based on followers
    for (int i = 0; i < users.size(); ++i) {
        User* currentUser = users[i];
        for (int j = 0; j < currentUser->followers.size(); ++j) {
            User* follower = currentUser->followers[j];
            this->addEdge(currentUser, follower);
        }
        cout << "User ID: " << currentUser->id << ", Followers: " << currentUser->followers.size() << endl;
    }
}

User* Graph::getUserById(const string& userId) const {
    for (const auto& userList : adjList) {
        for (const User* user : userList) {
            if (user->id == userId) {
                    cout<<"USER: "<<user->id<<" NAME: "<<user->name<<endl;
                return const_cast<User*>(user); // Casting away constness, as we know the user exists in the graph
            }
        }
    }
    return nullptr; // Return nullptr if user is not found
}

User* Graph::findMostInfluentialUser() const {
    User* mostInfluentialUser = nullptr;
    int maxFollowers = 0;

    for (int i = 1; i < adjList.size(); ++i) {
        int followersCount = adjList[i].size();
        if (followersCount > maxFollowers) {
            mostInfluentialUser = getUserById(to_string(i));
            maxFollowers = followersCount;
        }
    }
    cout << "The most influential user is: " <<mostInfluentialUser->id<<endl;
    return mostInfluentialUser;
}


User* Graph::findMostActiveUser()
{
	vector<int> activity(adjList.size(), 0);
	for (int i = 0; i < adjList.size(); i++)
	{
		for (const User* follower : adjList[i])
        {
            int loc = std::stoi(follower->id);
            activity[loc]++;
        }
	}
    int max = activity[0];
    int max_loc = 0;

    for (int i = 1; i < activity.size(); i++)
    {
        if (activity[i] > max)
        {
            max = activity[i];
            max_loc = i;
        }
    }
    cout << "The most active user is: " <<max_loc<<endl;
    return getUserById(to_string(max_loc));
}


vector<User*> Graph::findMutualFollowers(const string& ID1, const string& ID2)
{
    User* user1 = getUserById(ID1);
    User* user2 = getUserById(ID2);

    // Print IDs for debugging
    cout << "User1 ID: " << user1->id << endl;
    cout << "User2 ID: " << user2->id << endl;
    // Print followers for debugging
    cout << "Followers of User1 (" << user1->id << "): ";
        cout << user1->followers[0]->id<< " ";
    //for (User* follower : user1->followers) {
    //}
    cout << endl;

    cout << "Followers of User2 (" << user2->id << "): ";
    for (User* follower : user2->followers) {
        cout << follower->id << " ";
    }
    cout << endl;


    vector<User*> mutual_followers;

    // Find mutual followers
    for (User* follower1 : user1->followers)
    {
        for (User* follower2 : user2->followers)
        {
            if (follower1->id == follower2->id)
            {
                mutual_followers.push_back(follower1);
            }
        }
    }

    if (mutual_followers.empty())
    {
        cout << "No mutual followers." << endl;
    }
    else
    {
        cout<<"Mutual followers are: " ;
        for (int i = 0 ; i < mutual_followers.size() ; i++){
            cout<<mutual_followers[i]->id<<" ";
        }
        cout<<endl;
    }
    return mutual_followers;
}


/*void Graph::buildGraph(const vector<User*>& users) {
    // Add users to the graph
    Graph *initGraph = new Graph;
    initGraph

    for (const User* user : users) {

    }

    // Add edges to the graph based on followers
    for (const User* user : users) {
        for (const User* follower : user->followers) {
            //if()
            addFollower(user->id, follower->id);
        }
    }
}
*/





/*
#include "Graph.h"
#include "Functions.h"

void Graph::addUser(User* user) {
    users[user->id] = user;
}

void Graph::addFollower(const string& userId, const string& followerId) {
    if (users.find(userId) != users.end() && users.find(followerId) != users.end()) {
        users[followerId]->addFollower(users[userId]);
    }
}

void Graph::buildGraph(const vector<User*>& users) {
    // Add users to the graph
    for (const User* user : users) {
        addUser(const_cast<User*>(user));  // const_cast to remove const qualifier
    }

    // Add edges to the graph based on followers
    for (const User* user : users) {
        for (const User* follower : user->followers) {
            //if()
            addFollower(user->id, follower->id);
        }
    }
}

void Graph::printGraph() const {
    for (const auto& entry : users) {
        const User* user = entry.second;

        cout << "User ID: " << user->id << endl;
        cout << "Name: " << user->name << endl;
        cout << "Followers: ";
        for (const User* follower : user->followers) {
            cout << follower->id << " ";
        }
        cout << endl;
        cout << "----------------------------------------" << endl;
    }
}
*/
