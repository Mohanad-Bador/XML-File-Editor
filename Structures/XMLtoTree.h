#include <vector>
#include <iostream>
#include <string>
#include "Tree.h"
#include "../Graph/Functions.h"

using namespace std;

/*
    Constructs a tree structure from xml file
    @param file text content of the xml file
    @param xml_tree the Tree object
*/
void xml_to_tree(string file_text, Tree* xml_tree);

/*
    Splits an xml file text into a vector with one element per string
    @param xml_text A string containing the xml file's content
    @return `vector<string>` where each item in the vector is a single xml element
*/
static vector<string> xml_string_to_vec(string& xml_text);

/*
    Adds an xml tag to the xml tree
    @param type character representing element type, 'o' for opening tag, 'c' for closing, 'd' for data
    @param element the element itself
    @param tree reference to the tree
*/
static void add_node_to_tree(char& type, string& element, Tree* tree);
