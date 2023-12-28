#include "User.h"


User::User()
{
   this->name=" ";
   this->id=" ";
}

void User::printPost(const Post* post) const {
    cout << "Post Body: " << post->body << endl;
    cout << "Topics: ";
    for (const string& topic : post->topics) {
        cout << topic << " ";
    }
    cout << endl;
}

void User :: printUser()
{
   cout<<endl<<"ID: " << " " <<this->id<<endl;
   cout<<"Name:" << " " <<this->name<<endl;
   for(int i=0;i<this->followers.size();i++)
   {
    cout<<"Follower: "<< this->followers[i]->id<<endl;
   }
   cout<<"Posts:"<<endl;
   for(int i=0;i<this->posts.size();i++)
   {
        printPost(posts[i]);
   }

}

string User::postSearchByWord(const string& word) {
    bool found = false;  // Flag to check if there's at least one matching post

    for (const Post* post : posts) {
        // Check if the search term is present in the post body
        if (post->body.find(word) != string::npos) {
            if (!found) {
                cout << "Posts for User " << id << " containing " << word << " :" << endl;
                found = true;  // Set the flag to true after printing the header
            }
            printPost(post);
        } else {
            // Check if the search term is present in any topic
            for (const string& topic : post->topics) {
                if (topic.find(word) != string::npos) {
                    if (!found) {
                        cout << "Posts for User " << id << " containing " << word << " :" << endl;
                        found = true;  // Set the flag to true after printing the header
                    }
                    printPost(post);
                    break; // Break out of the inner loop if a match is found
                }
            }
        }
    }

    if (!found) {
        cout<<"No posts found for User "<<id<<" containing "<<word<<endl;
    }

    return "";  // Empty string to indicate success
}

User::~User() {}

User::User(const string& id, const string& name) : id(id), name(name) {}

void User::addFollower(User* follower) {
    followers.push_back(follower);
}
