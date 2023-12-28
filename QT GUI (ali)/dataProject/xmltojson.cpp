#include "xmltojson.h"
using namespace std;
static string tree_to_json(Tree* xml_tree) {
    string json;
    TreeNode* json_cursor;

    json_cursor = xml_tree->get_root();

    vector<string> array_names;
    array_names = json_arrays(json_cursor, array_names);

    if (xml_tree->is_empty())
        return "";
    
    json += "{\n";
    braces_stack.push('}');
    indent_size++;

    json += generate_json(json_cursor, xml_tree, array_names);

    while (!braces_stack.empty()) {
        json += "\n";
        indent_size--;
        INDENT(indent_size, json);
        json += braces_stack.top();
        braces_stack.pop();
    }
    return json;
}


static vector<string> json_arrays(TreeNode* root, vector<string>& arrays) {
    if (root->get_children().empty()) {
        return arrays;
    }

    if (root->get_children().size() > 1) {
        if (strcmp(root->get_children().front()->get_name().c_str(), root->get_children().back()->get_name().c_str()) == 0) {
            bool array_already_exists = false;
            for (int i = 0; i < arrays.size(); i++) {
                if (strcmp(arrays[i].c_str(), root->get_name().c_str()) == 0) {
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


static string generate_json(TreeNode* root, Tree* tree, vector<string> array_names) {
    // return "debug: disabled generate_json()";
    bool extra_bracket = false;
    string json;
    INDENT(indent_size, json);

    if (root == tree->get_root()) {
        json += "\"";
        json += root->get_name();
        json += "\": ";
    }
    else if (isArray(root->get_parent(), array_names)) {
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
        if (isArray(root, array_names))
            extra_bracket = (root->get_children().size() > 1);
    }

    if (!(root->get_children().empty())) {
        json += "{\n";
        braces_stack.push('}');
        indent_size++;
    }

    // base case
    if (root->get_children().empty()) {
        if (root->get_datatype() == INT) {
            json += to_string(root->get_int());
        } else {
            json += '\"';
            json += root->get_string();
            json += '\"';
        }
        return json;
    } else {
        child_flag = false;
        for (int i = 0; i < root->get_children().size(); i++) {
            json += generate_json(root->get_children()[i], tree, array_names); // recursion
            if (root->get_children().size() == i + 1) {
                json += '\n';
                child_flag = true;
                break;
            }
            json += ",\n";
        }
    }

    if (extra_bracket) {
        indent_size--;
        INDENT(indent_size, json);
        json += braces_stack.top();
        braces_stack.pop();
        json += '\n';
        extra_bracket = false;
    }
    indent_size--;
    INDENT(indent_size, json);
    json += braces_stack.top();
    braces_stack.pop();
    return json;
}

static bool isArray(TreeNode* node, vector<string> array_names) {
    for (int i = 0; i < array_names.size(); i++) {
        if (array_names[i] == node->get_name())
            return true;
    }
    return false;
}

static string read_file(const string& filePath) {
    // Open the file
    ifstream file(filePath);

    // Check if the file is open
    if (!file.is_open()) {
        cerr << "Error: Unable to open file '" << filePath << "'" << endl;
        return ""; // Return an empty string to indicate an error
    }

    // Read the file content into a stringstream
    stringstream buffer;
    buffer << file.rdbuf();

    // Close the file
    file.close();

    // Return the content as a string
    return buffer.str();
}


string convert_to_json(string xml_path) {
    string xml_content = read_file(xml_path);
    regex pattern("<(.*)>(.*)</\\1>");
    string expanded_xml = regex_replace(xml_content, pattern, "<$1>\n$2\n</$1>");
    Tree* xml_tree = new Tree();
    xml_to_tree(expanded_xml, xml_tree);
    string json = tree_to_json(xml_tree);
    delete xml_tree;
    return json;
}
