#include <cstring>
#include <iostream>
#include <stack>
#include "../Structures/XMLtoTree.cpp" // TODO
#define INDENT(X,BUFFER) for (int _ = 0; _ < X; _++) BUFFER += "\t"
using namespace std;
string tree_to_json(Tree* xml_tree);
vector<string> json_arrays(TreeNode* root, vector<string>& arrays);
stack<char> braces_stack;
int indent_size;
string generate_json(TreeNode* rootnode, Tree* tree, vector<string> array_names);
bool isArray(TreeNode* node, vector<string> array_names);
bool child_flag = false;