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
    string getBody();
    vector<string> getTopics();
  

    string body;
    vector <string> topics;
    
      ~Post();
};

#endif