#include "User.h"


User::User()
{
   this->name=" ";
   this->id=" ";
}

User::User(const string& id, const string& name) : id(id), name(name) {}

void User::addFollower(User* follower) {
    followers.push_back(follower);
}

string User::printPost(const Post* post) const {
    string s;
    s +="Post Body: " + post->body + '\n' + "Topics: ";
    for (const string& topic : post->topics) {
        s+=topic + " ";
    }
    s+= '\n';
    return s;
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
        cout<<printPost(posts[i]);
   }

}

string User::postSearchByWord(const string& word) {
    bool found = false;  // Flag to check if there's at least one matching post
    string s;
    for (const Post* post : posts) {
        // Check if the search term is present in the post body
        if (post->body.find(word) != string::npos) {
            if (!found) {
                s+="Posts for User " + id + " containing " + word + " :" + '\n';
                found = true;  // Set the flag to true after printing the header
            }
            s+=printPost(post);
        } else {
            // Check if the search term is present in any topic
            for (const string& topic : post->topics) {
                if (topic.find(word) != string::npos) {
                    if (!found) {
                        s+="Posts for User " + id + " containing " + word + " :" + '\n';
                        found = true;  // Set the flag to true after printing the header
                    }
                    s+=printPost(post);
                    break; // Break out of the inner loop if a match is found
                }
            }
        }
    }

    if (!found) {
        s+="No posts found for User "+id+" containing "+word+'\n';
    }

    return s;
}

User::~User() {}
