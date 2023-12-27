#include <vector>
#include <iostream>
#include <string>
#define OMAR_DEBUG false
enum tree_data_type {
    INT, TEXT, NODATA
};

class TreeNode
{
private:
    std::string name;
    std::string str_value;
    int int_value;
    int datatype;
    int level_in_tree;
    std::vector<TreeNode*> children;
    TreeNode* parent;
    TreeNode* next_sibling;
public:
    TreeNode(std::string name, int tree_level, TreeNode* parent);
    TreeNode(std::string name, int tree_level);
    ~TreeNode();
    void add_child(std::string name);
    TreeNode* get_parent();
    TreeNode* get_next_sibling();
    std::string get_name();
    std::string get_string();
    int get_int();
    int set_value(std::string text = "");
    std::vector<TreeNode*> get_children();
    int get_datatype();
};

/*
    @param name Node name
    @param tree_level level in tree (integer)
    @param parent Parent node
*/
TreeNode::TreeNode(std::string node_name, int tree_level, TreeNode* node_parent)
    : name(node_name), level_in_tree(tree_level), parent(node_parent), next_sibling(nullptr)
{
    if (OMAR_DEBUG) std::cout << "Created TreeNode with name " << name << std::endl;
    if (parent) {
        parent->children.push_back(this);
        if (parent->children.size() > 1) {
            parent->children[parent->children.size() - 2]->next_sibling = this;
        }
    }
}


TreeNode::TreeNode(std::string node_name, int tree_level)
    : name(node_name), level_in_tree(tree_level), parent(nullptr), next_sibling(nullptr)
{
        if (parent)
            parent->children.push_back(this);
}

TreeNode::~TreeNode()
{
    for (TreeNode* child:children) {
        delete child;
    }
}

void TreeNode::add_child(std::string child_name) {
    TreeNode* new_node = new TreeNode(child_name,this->level_in_tree + 1,this);
    if (!(this->children.empty()))
        this->children.back()->next_sibling = new_node;
    this->children.push_back(new_node);
}

TreeNode* TreeNode::get_parent() {
    return parent;
}

TreeNode* TreeNode::get_next_sibling() {
    return next_sibling;
}

std::string TreeNode::get_name() {
    if (OMAR_DEBUG) std::cout << "Returned TreeNode name " << name << std::endl;
    return name;
}

std::string TreeNode::get_string() {
    return str_value;
}

int TreeNode::get_int() {
    return int_value;
}

int TreeNode::set_value(std::string text) {
    try {
        int_value = std::stoi(text);
        datatype = INT;
    } catch (std::exception &invalid_argument) {
        str_value = text;
        datatype = TEXT;
    }
    return datatype;
}

std::vector<TreeNode*> TreeNode::get_children() {
    return children;
}

int TreeNode::get_datatype() {
    return datatype;
}

class Tree
{
    TreeNode* rootnode;
private:
    
public:
    int level;
    TreeNode* node_cursor;
    TreeNode* get_root();
    void set_root(TreeNode* root);
    Tree();
    ~Tree();
    bool is_empty();
};


Tree::Tree()
{
    level = 0;
    this->rootnode = nullptr;
}

Tree::~Tree()
{
    delete rootnode;
}

TreeNode* Tree::get_root()
{
    return rootnode;
}

bool Tree::is_empty()
{
    return rootnode == nullptr;
}

void Tree::set_root(TreeNode* root) {
    this->rootnode = root;
}