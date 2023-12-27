#include <cstring>
#include <iostream>
#include <stack>
#include "../Structures/Tree.h"
#include "../Structures/XMLtoTree.h"
#define INDENT(X,BUFFER) for (int _ = 0; _ < X; _++) BUFFER += "\t"
using namespace std;
string tree_to_json(Tree& xml_tree);
vector<string> json_arrays(TreeNode& root, vector<string>& arrays);
stack<char> braces_stack;
int indent_size;
string generate_json(TreeNode* rootnode, Tree* tree, string buffer);
bool isArray(TreeNode* node);
bool child_flag = false;