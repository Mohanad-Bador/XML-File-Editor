#include <vector>

class TreeNode
{
private:
public:
    const char *name;
    const char *value;
    std::vector<TreeNode*> children;
    TreeNode* next_sibling;
    TreeNode* parent;
    TreeNode(const char* name, const char* value, TreeNode* parent);
    ~TreeNode();
    void add_child(const char* name, const char* value);
};

TreeNode::TreeNode(const char* name, const char* value, TreeNode* parent)
    : name(name), value(value), parent(parent), next_sibling(nullptr)
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

void TreeNode::add_child(const char* name, const char* value) {
    TreeNode* new_node = new TreeNode(name,value,this);
    this->children.back()->next_sibling = new_node;
    this->children.push_back(new_node);
}


class Tree
{
    TreeNode* rootnode;
private:
    
public:
    TreeNode* root();
    Tree(TreeNode* root);
    ~Tree();
    bool empty();
};


Tree::Tree(TreeNode* root)
{
    this->rootnode = rootnode;
}

Tree::~Tree()
{
    delete rootnode;
}

TreeNode* Tree::root()
{
    return this->rootnode;
}