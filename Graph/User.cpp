#include "User.h"


User::User()
{
   this->name=" ";
   this->id=" ";
}
void User :: print_user()
{
   cout<<"ID: " << " " <<this->id<<endl;
   cout<<"Name:" << " " <<this->name<<endl;
   for(int i=0;i<this->followers.size();i++)
   {
    cout<<"Follower: "<< this->followers[i]->id<<endl;
   }
   for(int i=0;i<this->posts.size();i++)
   {
      cout<<"Post Body" << " " <<this->posts[i]->body<<endl;
      for(int j=0;j<this->posts[i]->topics.size();j++)
      {
        cout<<"Topic" << " " <<this->posts[i]->topics[j]<<endl;
      }
   }

}

User::~User() {}

User::User(const string& id, const string& name) : id(id), name(name) {}

void User::addFollower(User* follower) {
    followers.push_back(follower);
}
