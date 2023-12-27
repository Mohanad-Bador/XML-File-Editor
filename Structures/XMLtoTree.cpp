#include "XMLtoTree.h"

/*
    Constructs a tree structure from xml file
    @param file text content of the xml file
    @param xml_tree the Tree object
*/
void xml_to_tree(string file_text, Tree* xml_tree) {
    vector<string> xml_elements = xml_string_to_vec(file_text);
    for (string element : xml_elements) {
        char type;
        if (element[0] == '<' && element[1] != '/') type = 'o';
        else if (element[0] == '<' && element[1] == '/') type = 'c';
        else type = 'd';
        
        add_node_to_tree(type, element, xml_tree);
        
        if (OMAR_DEBUG) cout << "Element: " << element << endl;
    }
}

/*
    Splits an xml file text into a vector with one element per string
    @param xml_text A string containing the xml file's content
    @return `vector<string>` where each item in the vector is a single xml element
*/
vector<string> xml_string_to_vec(string& xml_text)
{
    vector<string> to_return;

    int line_end_index = -1;
    for (int i = 0;; i++) {
        if (xml_text[i] == '\n') {
            string element = xml_text.substr(line_end_index + 1, i - line_end_index - 1);
            trim(element);
            to_return.push_back(element);
            line_end_index = i;
        }
        if (xml_text[i] == '\0') {
            string element = xml_text.substr(line_end_index + 1, i - line_end_index - 1);
            trim(element);
            if (element.size() != 0) to_return.push_back(element);
            break;
        }
    }
    return to_return;
}

/*
    Adds an xml tag to the xml tree
    @param type character representing element type, 'o' for opening tag, 'c' for closing, 'd' for data
    @param element the element itself
    @param tree reference to the tree
*/
void add_node_to_tree(char& type, string& element, Tree* tree) {
    if (type == 'o') {
        
        string tag_name = element.substr(1, element.size() - 2);
        
        
        if (tree->is_empty()) {
            
            TreeNode* rootnode = new TreeNode(tag_name.c_str(),tree->level);
            
            tree->set_root(rootnode);
            
            tree->node_cursor = rootnode;
            
        } else {
            TreeNode* new_node = new TreeNode(tag_name.c_str(), tree->level, tree->node_cursor);
            
            tree->node_cursor = new_node;
            
        }
        tree->level++;
    } else if (type == 'd') {
        
        tree->node_cursor->set_value(element.c_str());
        
    } else if (tree->node_cursor->get_parent() != nullptr) {
        
        tree->node_cursor = tree->node_cursor->get_parent();
        
        tree->level--;
    }
    
}