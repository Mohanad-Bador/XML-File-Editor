#include "Graph.h"
using namespace std;
Graph::Graph(){

}

Graph::Graph(int numVertices,vector<User*> users) : adjList(numVertices+1) {
    this->users=users;
}


void Graph::addEdge(User* u, User* v) {
    // Assuming that the User class has an 'id' attribute
    int userId = stoi(u->id);
    int followerId =stoi(v->id);

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

void Graph::buildGraph(){

    // Adding edges based on followers
    for (int i = 0; i < users.size(); ++i) {
        User* currentUser = users[i];
        for (int j = 0; j < currentUser->followers.size(); ++j) {
            User* follower = currentUser->followers[j];
            this->addEdge(currentUser, follower);
        }
       // cout << "User ID: " << currentUser->id << ", Followers: " << currentUser->followers.size() << endl;
    }
}

User* Graph::getUserById(const string &userid)
{
    for(User *user:users){
        if(user->id == userid)
            return user;
    }
    return nullptr;
}

User* Graph::findMostInfluentialUser() {
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
    cout << "User1 ID: " << user1->id <<" " <<user1->name<<endl;
    cout << "User2 ID: " << user2->id << endl;
    // Print followers for debugging
    cout << "Followers of User1 (" << user1->id << "): ";
    for (User* follower : user1->followers) {
             cout << follower->id << " ";
    }
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


vector<User*> Graph::suggest_followers(string id)
{
    vector<bool> v(this->users.size()+1,false);
    User* user=getUserById(id);
    vector<User*> followers=user->followers;
    vector<User*> suggested_followers;

    v[stoi(id)]=true;

    for(User* follower:followers)
    {

       User* u=getUserById(follower->id);
       vector<User *> followers_of_followers=u->followers;
       for(User* f:followers_of_followers){
           if(!v[stoi(f->id)]){
            suggested_followers.push_back(f);
             v[stoi(f->id)]=true;
           }
       }
    }
    if (suggested_followers.empty())
    {
        cout << "No suggested followers." << endl;
    }
    else
    {
      cout<<"suggested followers are: " ;
        for (int i = 0 ; i < suggested_followers.size() ; i++){
            cout<<suggested_followers[i]->id<<" ";
        }
    }


	return suggested_followers;

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
