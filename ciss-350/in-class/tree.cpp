#include <iostream>


int max(int x, int y)
{
    return (x >= y ? x : y);
}
class Node 
{
public: 
    Node(int key, Node * parent = NULL, Node * left = NULL, Node * right = NULL)
        : key_(key), parent_(parent), left_(left), right_(right)
        {}
    int key_;
    Node * parent_;
    Node * left_;
    Node * right_;
};


std::ostream & operator<<(std::ostream & cout, const Node & n)
{
    cout << "<Node " << &n
         << ", key: " << n.key_
         << ", parent: " << n.parent_
         << ", left: " << n.left_
         << ", right: " << n.right_ 
         << '>';
         return cout;
}

int height(Node * n)
{
    if (n == NULL) // base case
    {
        return -1;
    }
    else
    {
        return 1 + max(height(n->left_), height(n->right_));
    }
}


int main()
{
    Node n5(5);
    // ask for code that goes here
    std::cout << "n5: " << n5 << '\n';
    return 0;
}