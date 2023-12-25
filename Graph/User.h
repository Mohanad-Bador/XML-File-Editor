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
    void print_user();

    ~User();

    User(const string& id, const string& name);
    void addFollower(User* follower);
};

#endif
