PoincareDisk
============

The Poincaré disc model is one of the n-d hyperbolic geometry models.

In dimension 2, the disc is defined for points x in the unit disc
equiped with an hyperbolic metric. In this model, straight lines are
circular arcs orthogonal to the unit disc boundary. Hence, the
shortest path between two points is uniquely defined from the circular
arc orthogonal to the boundary containing the two points. Since
triangles are hyperbolic triangles, sum of internal angles of a
triangle is always less or equal to Pi.

This piece of code implements basic drawing functions to display
straight lines, straight segment and hyperbolic triangle in this
model. In order to keep the code as simple as possible, it consists of
a unique C++ header file with quite self explanatory functions. The
PDF export is done by the Cairo library.

Requirements
============

* C/C++ compiler
* cmake
* Cairo/libcairo http://cairographics.org


Examples
========

The syntax is very simple, for example, to draw an hyperbolic segment where vertices are given in polar coordinates:

```initPDF("poincare-edge.pdf");
drawUnitCircle();
drawEdge(Point(0.5,0.5), Point(-0.6,0.2),true);
flushPDF();
```

Note that drawing methods are based on a template parameter “Point”
which implements points in dimension 2. Here you have a very simple
model to construct points on “double” type.

```struct Point{
Point(double xx, double yy): myX(xx),myY(yy)
{}
double x() const
{return myX;}
double y() const
{return myY;}
double myX,myY;
};
```


In the header file, several hyperbolic objects can be displayed:
points
* hyperbolic lines
* hyperbolic segment (with or without support line)
* hyperbolic triangles
