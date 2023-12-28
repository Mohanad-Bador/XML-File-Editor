#include <cstring>
#include <iostream>
#include <stack>
#include <regex>
#include "XMLtoTree.h"

#define INDENT(X,BUFFER) for (int _ = 0; _ < X; _++) BUFFER += "\t"
using namespace std;
static bool isArray(TreeNode* node, vector<string> array_names);
static bool child_flag = false;
static int indent_size;
static stack<char> braces_stack;
static vector<string> json_arrays(TreeNode* root, vector<string>& arrays);
static string generate_json(TreeNode* rootnode, Tree* tree, vector<string> array_names);
static string tree_to_json(Tree* xml_tree);
static string read_file(const string& filePath);

/*
    Convert xml file to json
    @param xml_path Path to xml file
    @return json content as a string
*/
string convert_to_json(string xml_path);
