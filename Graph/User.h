#ifndef USER_H
#define USER_H

#include<iostream>
#include<string>
#include "Post.h"
using namespace std;

#pragma once
class User
{
public:
    User();
    string name;
    string id;
    vector<User *> followers;
    vector<Post *> posts;

    User(const string& id, const string& name);
    void addFollower(User* follower);
    string printPost(const Post* post) const;
    void printUser();
    string postSearchByWord(const string& word);
    ~User();
};

#endif
