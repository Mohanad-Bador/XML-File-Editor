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


