#ifndef QT_H
#define QT_H

#include <iostream>
#include <vector>


// class QT
// {
// public:
//   QTNode * head;
//   bool is_leaf;

//   QT()
//   {
//     head = NULL;
//     is_leaf = false;
//   }
// };

class Point
{
 public:
  float x;
  float y;
  int r;
  int g;
  int b;
  bool collides = false;
  float dx;
  float dy;
  int radius;
  void move(int x_bound, int y_bound);

  Point()
    {
      x = 0;
      y = 0;
      r = 255;
      g = 255;
      b = 255;
      collides = false;
      dx = float(rand()) / RAND_MAX * 2 - 1;
      dy = float(rand()) / RAND_MAX * 2 - 1;
      radius = 1;
    }

  Point(float x_, float y_)
    {
      x = x_;
      y = y_;
      r = 255;
      g = 255;
      b = 255;
      collides = false;
      dx = float(rand()) / RAND_MAX * 2 - 1;
      dy = float(rand()) / RAND_MAX * 2 - 1;
      radius = 1;
    }
};


void Point::move(int x_bound, int y_bound)
{
  if (x < x_bound - 1 && y < y_bound - 1)
    {
      x += dx;
      y += dy;
    }

  else if (x >= x_bound)
    {
      dx = -dx;
      x += dx;
    }

  else if (y >= y_bound)
    {
      dy = -dy;
      y += dy;
    }
}


class NodeRect
{
public:
  Point topLeft;
  Point topRight;
  Point botLeft;
  Point botRight;

  NodeRect(Rect rect)
  {
    topLeft.x = rect.x;
    topLeft.y = rect.y;

    topRight.x = rect.x + rect.w;
    topRight.y = rect.y;

    botLeft.x = rect.x;
    botLeft.y = rect.y + rect.h;

    botRight.x = rect.x + rect.w;
    botRight.y = rect.y + rect.h;
  }
};


std::ostream & operator<<(std::ostream & cout, NodeRect & n)
{
  cout << "Printing NodeRect values ... \n";
  cout << "topLeft.x = " << n.topLeft.x << " . "
       << "topLeft.y = " <<  n.topLeft.y << '\n'
       << "topRight.x = " << n.topRight.x << " . "
       << "topRight.y = " << n.topRight.y << '\n'
       << "botLeft.x = " << n.botLeft.x << " . "
       << "botLeft.y = " << n.botLeft.y << '\n'
       << "botRight.x = " << n.botRight.x << " . "
       << "botRight.y = " << n.botRight.y << '\n' << '\n';
  return cout;
}



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

  bool is_leaf = false;

  void insert(Point);
  bool inBoundary(Point);
  bool hasChildren();
  void clear_tree(QTNode *);
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

      maxDepth = 10;
      threshold = 5;
      
      topLTree = NULL;
      topRTree = NULL;
      botLTree = NULL;
      botRTree = NULL;
      parent = parent_;
      objs.clear();
    }

  QTNode(Point topL, Point botR, QTNode * parent_, int threshold_)
    {
      rect.x = topL.x;
      rect.y = topL.y;
      rect.w = botR.x - topL.x;
      rect.h = botR.y - topL.y;
      
      topLeft = topL;
      botRight = botR;

      maxDepth = 10;
      threshold = threshold_;
      
      topLTree = NULL;
      topRTree = NULL;
      botLTree = NULL;
      botRTree = NULL;
      parent = parent_;
      objs.clear();
    }
  ~QTNode();
};


QTNode::~QTNode()
{
  // delete topLTree;
  // delete topRTree;
  // delete botLTree;
  // delete botRTree;
}


// void QTNode::clear_tree(QTNode * n)
// {
//   if (n == NULL) return;

//   clear_tree(n->topLTree);
//   clear_tree(n->topRTree);
//   clear_tree(n->botRTree);
//   clear_tree(n->botLTree);

//   delete n;
// }

void QTNode::insert(Point p)
{
  if (!inBoundary(p))
    {
      //std::cout << "Exited after check 1\n";
      return;
    }

  if (objs.size() < threshold)
    {
      objs.push_back(p);
      //std::cout << "Exited after check 2\n";
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

      //std::cout << "Recursive function call ... \n";
      
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
