#include "xmltojson.h"

/// TODO: description
string tree_to_json(Tree* xml_tree) {
    string json;
    TreeNode* json_cursor;

    json_cursor = xml_tree->get_root();

    vector<string> arrays;
    arrays = json_arrays(json_cursor, arrays);

    if (xml_tree->is_empty())
        return "";
    
    json += "{\n";
    braces_stack.push('}');
    indent_size++;

    generate_json(json_cursor, xml_tree, json);

    while (!braces_stack.empty()) {
        indent_size--;
        json += "\n";
        INDENT(indent_size, json);
        json += braces_stack.top();
        braces_stack.pop();
    }
}


/// TODO: description
vector<string> json_arrays(TreeNode* root, vector<string>& arrays) {
    if (root->get_children().empty()) {
        return;
    }

    if (root->get_children().size() > 1) {
        if (strcmp(root->get_children().front()->get_name(), root->get_children().back()->get_name()) == 0) {
            bool array_already_exists = false;
            for (int i = 0; i < arrays.size(); i++) {
                if (strcmp(arrays[i].c_str(), root->get_name()) == 0) {
                    array_already_exists = true;
                    break;
                }
            }
            if (!array_already_exists) {
                arrays.push_back(root->get_name());
            }
        }
    }

    for (int i = 0; i < root->get_children().size(); i++) {
        json_arrays(root->get_children()[i], arrays);
    }

    return arrays;
}


/// TODO: description
string generate_json(TreeNode* root, Tree* tree, string buffer) {
    bool extra_pop = false;
    string json;
    INDENT(indent_size, json);

    if (root == tree->get_root()) {
        json += "\"";
        json += root->get_name();
        json += "\": ";
    }
    else if (isArray(root->get_parent())) {
        if (!child_flag) {
            json += '\"';
            json += root->get_name();
            json += "\": ";
            
            if (root->get_parent()->get_children().size() > 1) {
                json += "[\n";
                braces_stack.push('[]');
                indent_size++;
                INDENT(indent_size,json);
            }
            child_flag = true;
        }
    } else {
        json += '\"';
        json += root->get_name();
        json += "\": ";
        if (isArray(root))
            extra_pop = (root->get_children().size() > 1);
    }

    if (!(root->get_children().empty())) {
        json += "{\n";
        braces_stack.push('}');
        indent_size++;
    }

    // base case
    if (root->get_children().empty()) {
        json += '\"';
        if (root->get_datatype() == INT) {
            json += to_string(root->get_int());
        } else {
            json += root->get_string();
        }
        json += '\"';
    } else {
        // TODO
    }
}

bool isArray(TreeNode* node) {
    /// TODO: implement
    return true;
}