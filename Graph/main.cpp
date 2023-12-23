#include<iostream>
#include<vector>
#include "Functions.h"
#include "XMLParser.h"
#include "User.h"

using namespace std;
int main()
{
  XMLParser parser;
  vector<User*> users =parser.parseXML("sample.xml");
  for(int i=0;i<users.size();i++)
  {
    users[i]->print_user();
  }
  return 0;
}