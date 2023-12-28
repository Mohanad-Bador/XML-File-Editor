#include "XMLtoTree.h"
using namespace std ;
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

static vector<string> xml_string_to_vec(string& xml_text)
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
            trim( element);
            if (element.size() != 0) to_return.push_back(element);
            break;
        }
    }
    return to_return;
}

static void add_node_to_tree(char& type, string& element, Tree* tree) {
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
