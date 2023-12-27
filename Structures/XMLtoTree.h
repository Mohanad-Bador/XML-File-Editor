#include <vector>
#include <iostream>
#include <string>
#include "Tree.h"
#include "../Graph/Functions.cpp"

using namespace std;

void xml_to_tree(string file_text, Tree* xml_tree);
vector<string> xml_string_to_vec(string& xml_text);
void add_node_to_tree(char& type, string& element, Tree* tree);
