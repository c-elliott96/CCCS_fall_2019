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

  Rect rect;
  Point topLeft;
  Point botRight;
  
  int depth;
  int maxDepth;
  int threshold;
  std::vector< Point > objs;
  QTNode * topLTree;
  QTNode * topRTree;
  QTNode * botLTree;
  QTNode * botRTree;
  QTNode * parent;

  void insert(Point);
  bool inBoundary(Point);
  bool hasChildren();
  //int getDepth(QTNode * parent);

  QTNode() // this will only be called for very first node
    {
      rect.x = 0;
      rect.y = 0;
      rect.w = 800;
      rect.h = 800;
      //depth = 0;
      maxDepth = 10;
      threshold = 5;
      topLTree = NULL;
      topRTree = NULL;
      botLTree = NULL;
      botRTree = NULL;
      parent = NULL;
      objs.clear();
    }

  QTNode(Point topL, Point botR, QTNode * parent_)
    {
      rect.x = topL.x;
      rect.y = topL.y;
      rect.w = botR.x - topL.x;
      rect.h = botR.y - topL.y;
      
      topLeft = topL;
      botRight = botR;
      
      //depth = getDepth(parent);
      maxDepth = 10;
      threshold = 5;
      
      topLTree = NULL;
      topRTree = NULL;
      botLTree = NULL;
      botRTree = NULL;
      parent = parent_;
      objs.clear();
    }
};


void QTNode::insert(Point p)
{
  if (!inBoundary(p))
    {
      std::cout << "Exited after check 1\n";
      return;
    }

  if (objs.size() < threshold)
    {
      objs.push_back(p);
      std::cout << "Exited after check 2\n";
      return;
    }

  // here we need to check if the node we're in has children
  if (!this->hasChildren() && objs.size() >= threshold)
    {
      this->topLTree = new QTNode(Point(topLeft.x, topLeft.y),
				  Point((topLeft.x + botRight.x) / 2,
					(topLeft.y + botRight.y) / 2),
				  this);
      
      this->topRTree = new QTNode(Point((topLeft.x + botRight.x) / 2,
					topLeft.y),
				  Point(botRight.x, (topLeft.y + botRight.y) / 2),
				  this);
      
      this->botLTree = new QTNode(Point(topLeft.x, (topLeft.y + botRight.y) / 2),
				  Point((topLeft.x + botRight.x) / 2,
				  botRight.y),
				  this);

      this->botRTree = new QTNode(Point((topLeft.x + botRight.x) / 2,
				  (topLeft.y + botRight.y) / 2),
				  Point(botRight.x, botRight.y),
				  this);

      std::cout << "Recursive function call ... \n";
      
      if (topLTree->inBoundary(p))
	{
	  topLTree->insert(p);
	}

      if (topRTree->inBoundary(p))
	{
	  topRTree->insert(p);
	}

      if (botLTree->inBoundary(p))
	{
	  botLTree->insert(p);
	}
      if (botRTree->inBoundary(p))
	{
	  botRTree->insert(p);
	}
    }
  else
    {
      if (this->topLTree->inBoundary(p))
  	{
  	  this->topLTree->insert(p);
  	}

      else if (this->topRTree->inBoundary(p))
  	{
  	  this->topRTree->insert(p);
  	}

      else if (this->botLTree->inBoundary(p))
  	{
  	  this->botLTree->insert(p);
  	}
      else if (this->botRTree->inBoundary(p))
  	{
  	  this->botRTree->insert(p);
  	}
    }
}


bool QTNode::inBoundary(Point p)
{
  return (p.x >= topLeft.x &&
	  p.x <= botRight.x &&
	  p.y >= topLeft.y &&
	  p.y <= botRight.y);
}



bool QTNode::hasChildren()
{
  return (topRTree != NULL || topLTree != NULL ||
	  botRTree != NULL || botLTree != NULL);
}


std::ostream & operator<<(std::ostream & cout, QTNode & n)
{
  cout << "Hello World\n";
  return cout;
}


// std::ostream & operator<<(std::ostream & cout, const std::vector< Point * > & p)
// {
  
// }




#endif
