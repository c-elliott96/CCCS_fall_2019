#ifndef QT_H
#define QT_H

#include <iostream>
#include <vector>

class QT
{
 
};


class Point
{
 public:
  int x;
  int y;

  Point()
    {
      x = 0;
      y = 0;
    }

  Point(int x_, int y_)
    {
      x = x_;
      y = y_;
    }
};


class QTNode
{
 public:

  Point topLeft;
  Point botRight;
  int depth;
  int maxDepth;
  int threshold;
  std::vector< Point * > objs;
  QTNode * topLTree;
  QTNode * topRTree;
  QTNode * botLTree;
  QTNode * botRTree;
  QTNode * parent;

  void insert(Point *);
  bool inBoundary(Point *);
  bool hasChildren();
  int getDepth(QTNode * parent);

  QTNode() // this will only be called for very first node
    {
      topLeft = Point(0,0);
      botRight = Point(0,0);
      depth = 0;
      maxDepth = 10;
      threshold = 5;
      topLTree = NULL;
      topRTree = NULL;
      botLTree = NULL;
      botRTree = NULL;
      parent = NULL;
    }

  QTNode(Point topL, Point botR, QTNode * parent_)
    {
      topLeft = topL;
      botRight = botR;
      depth = getDepth(parent);
      maxDepth = 10;
      threshold = 5;
      topLTree = NULL;
      topRTree = NULL;
      botLTree = NULL;
      botRTree = NULL;
      parent = parent_;
    }
};


void QTNode::insert(Point * p)
{
  if (p == NULL)
    {
      std::cout << "return at point 1!\n";
      return;
    }

  if (!inBoundary(p))
    {
      std::cout << "return at point 2!\n";
      return;
    }

  /* if (depth >= maxDepth) */
  /*   { */
  /*     objs.emplace_back(p); */
  /*     return; */
  /*   } */

  if (objs.size() < threshold)
    {
      objs.emplace_back(p);
      std::cout << "return at point 3!\n";
      return;
    }

  if (objs.size() >= threshold && depth < maxDepth)
    {
      // IF WE ARE HERE, WE NEED TO SUBDIVIDE QTNODE
      if ((topLeft.x + botRight.x) / 2 >= p->x)
	{
	  // if we are HERE, it's left half of parent node
	  if ((topLeft.y + botRight.y) / 2 >= p->y)
	    {
	      if (topLTree == NULL)
		{
		  topLTree = new QTNode(Point(topLeft.x, topLeft.y),
					Point((topLeft.x + botRight.x) / 2,
					      (topLeft.y + botRight.y) / 2),
					this);
		  topLTree->insert(p);
		}
	    }
	  else // if we are HERE, it's bottom left
	    {
	      if (botRTree == NULL)
		{
		  botLTree = new QTNode(Point(topLeft.x,
					      (topLeft.y + botRight.y) / 2),
					Point((topLeft.x + botRight.x) / 2,
					      botRight.y),
					this);
		  botLTree->insert(p);
		}
	    }
	}
      else
	{
	  if ((topLeft.y + botRight.y) / 2 >= p->y)
	    {
	      if (topRTree == NULL)
		{
		  topRTree = new QTNode(Point((topLeft.x) / 2,
					topLeft.y),
					Point(botRight.x,
					      (topLeft.y + botRight.y) / 2),
					this);
		  topRTree->insert(p);
		}
	    }
	  else
	    {
	      if (botRTree == NULL)
		{
		  botRTree = new QTNode(Point((topLeft.x + botRight.x) / 2,
					      (topLeft.y + botRight.y) / 2),
					Point(botRight.x, botRight.y),
					this);
		  botRTree->insert(p);
		}
	    }
	}
    }
}


bool QTNode::inBoundary(Point * p)
{
  return (p->x >= topLeft.x &&
	  p->x <= botRight.x &&
	  p->y >= topLeft.y &&
	  p->y <= botRight.y);
}



int QTNode::getDepth(QTNode * p)
{
  int d = 0;
  QTNode * q = p;
  while (q != NULL)
    {
      ++d;
      q = q->parent;
    }
  return d;
}


bool QTNode::hasChildren()
{
  return (topRTree != NULL || topLTree != NULL ||
	  botRTree != NULL || botLTree != NULL);
}


std::ostream & operator<<(std::ostream & cout, QTNode & n)
{
  cout << "<   Node address: " << &n << '\n'
       << "    has children? " << n.hasChildren() << '\n'
       << "    Depth: " << n.getDepth(n.parent) << '\n'
       << "    objs contains: " << '\n';

  for (int i = 0; i < n.objs.size(); ++i)
    {
      cout << "point [" << i << "] = " << n.objs[i]->x
	   << ", " << n.objs[i]->y << '\n';
    }
  return cout;
}


std::ostream & operator<<(std::ostream & cout, const std::vector< Point * > & p)
{
  cout << "< Points: " << '\n';
  for (int i = 0; i < p.size(); ++i)
    {
      cout << "    point: " << p[i]->x << ", " << p[i]->y << '\n'; 
    }
  cout << ">" << '\n';
  return cout;
}




#endif
