#ifndef POST_H
#define POST_H

#include<iostream>
#include<string>
#include<vector>
using namespace std;

#pragma once

class Post
{
public:
    Post();
    string body;
    vector <string> topics;
  
    string getBody();
    vector<string> getTopics();
    ~Post();
};

#endif