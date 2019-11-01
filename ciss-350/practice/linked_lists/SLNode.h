#ifndef SLNODE_H
#define SLNODE_H

#include <iostream>
#include <cstddef>

class SLNode
{
public:
    SLNode(int key, SLNode * next = NULL)
    : key_(key), next_(next)
    {}

    int key() const 
    {
        return key_;
    }

    SLNode * next() const 
    {
        return next_;
    }

    void set_next(SLNode *next)
    {
        next_ = next; 
    }

private:
    int key_;
    SLNode * next_;
};


std::ostream & operator<<(std::ostream & cout, const SLNode & node)
{
    cout << "<SLNode " << &node
         << ", key: " << node.key()
         << ", next: " << node.next()
         << '>';
    return cout;
}

#endif