#include <iostream>
#include "SLNode.h"

int main()
{
    SLNode * n0 = new SLNode(0, NULL);
    SLNode * n1 = new SLNode(1, NULL);
    SLNode * n2 = new SLNode(2, NULL);
    SLNode * n3 = new SLNode(3, NULL);

    n0->set_next(n1);
    n1->set_next(n2);
    n2->set_next(n3);

    SLNode * phead = n0;

    SLNode * p = phead;
    while (p != NULL)
    {
        std::cout << (*p) << std::endl;
        p = p->next();
    }


    // std::cout << n0 << '\n'
    //           << n1 << '\n'
    //           << n2 << '\n'
    //           << n3 << '\n';

    return 0;
}
