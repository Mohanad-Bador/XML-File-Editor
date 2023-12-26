#include <vector>

enum tree_data_type {
    INT, TEXT, NODATA
};

class TreeNode
{
private:
    const char *name;
    const char *str_value;
    int int_value;
    int datatype;
    int level_in_tree;
    std::vector<TreeNode*> children;
    TreeNode* next_sibling;
    TreeNode* parent;
public:
    TreeNode(const char* name, int tree_level, TreeNode* parent);
    TreeNode(const char* name, int tree_level);
    ~TreeNode();
    void add_child(const char* name);
    TreeNode* get_parent(); // TODO: implement
    TreeNode* get_next_sibling(); // TODO: implement
    const char* get_name(); // TODO: implement
    const char* get_value(); // TODO: implement
    int set_value(const char* text = ""); // TODO: implement (sets datatype to INT or TEXT or NODATA)
    std::vector<TreeNode*> get_children(); // TODO: implement
};

/*
    @param name Node name
    @param tree_level level in tree (integer)
    @param parent Parent node
*/
TreeNode::TreeNode(const char* name, int tree_level, TreeNode* parent)
    : name(name), level_in_tree(tree_level), parent(parent), next_sibling(nullptr)
{
        if (parent) {
            parent->children.back()->next_sibling = this;
            parent->children.push_back(this);
        }
}

TreeNode::TreeNode(const char* name, int tree_level)
    : name(name), level_in_tree(tree_level), next_sibling(nullptr)
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

void TreeNode::add_child(const char* name) {
    TreeNode* new_node = new TreeNode(name,this->level_in_tree + 1,this);
    if (!(this->children.empty()))
        this->children.back()->next_sibling = new_node;
    this->children.push_back(new_node);
}


class Tree
{
    TreeNode* rootnode;
private:
    
public:
    int level;
    TreeNode* node_cursor;
    TreeNode* get_root();
    void set_root(TreeNode* root); // TODO: implement
    Tree(TreeNode* root);
    ~Tree();
    bool is_empty();
};


Tree::Tree(TreeNode* rootnode)
{
    level = 0;
    this->rootnode = rootnode;
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