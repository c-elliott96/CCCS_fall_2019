#include <iostream>
#include <vector>


class Objects
{
public:
  int x;
  int y;
  int dx;
  int xy;
}

  
class Node
{
public:
  Node * parent_;
  int maxx;
  int maxy;
  int minx;
  int miny;
  int t;        // threshold
  int maxd;     // max depth --> this avoids infinite loop issues w/ recursion
  std::vector< Object * > objs;
  
private:
}


int main()
{
  std::cout << "Hello World\n";

  return 0;
}
