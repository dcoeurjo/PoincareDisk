PoincareDisk
============
authors: David Coeurjolly


The [Poincaré disk model](http://en.wikipedia.org/wiki/Poincaré_disk_model) is one of the [n-d hyperbolic geometry models](http://en.wikipedia.org/wiki/Hyperbolic_geometry).

In dimension 2, the disc is defined for points x in the unit disc
equiped with an hyperbolic metric. In this model, straight lines are
circular arcs orthogonal to the unit disc boundary. Hence, the
shortest path between two points is uniquely defined from the circular
arc orthogonal to the boundary containing the two points. Since
triangles are hyperbolic triangles, sum of internal angles of a
triangle is always less or equal to pi.

This project implements basic drawing functions to display
straight lines, straight segment and hyperbolic triangle in this
model. In order to keep the code as simple as possible, it consists of
a unique C++ header file with quite self explanatory functions. The
PDF export is done by the Cairo library.

Requirements
============

* C/C++ compiler
* cmake http://www.cmake.org
* Cairo/libcairo http://cairographics.org


Examples
========

The syntax is very simple, for example, to draw an hyperbolic segment where vertices are given in polar coordinates:

    initPDF("poincare-edge.pdf");
    drawUnitCircle();
    drawEdge(Point(0.5,0.5), Point(-0.6,0.2),true);
    flushPDF();


Note that drawing methods are based on a template parameter “Point”
which implements points in dimension 2. Here you have a very simple
model to construct points on “double” type.

    struct Point{
     Point(double xx, double yy): myX(xx),myY(yy)
     {}
     double x() const
     {return myX;}
     double y() const
     {return myY;}
     double myX,myY;
    };

In the header file, several hyperbolic objects can be displayed:
points
* hyperbolic lines
* hyperbolic segment (with or without support line)
* hyperbolic triangles


You can customize colors (method parameters) and width of objects (global variables). Here you have couple of generated figures: Poincaré disc and an hyperbolic segment, hyperbolic triangles (regular one and an ideal one), and hyperbolic uniformization of a polyhedron (a torus with two holes, only one period is displayed).

![](https://raw.github.com/dcoeurjo/PoincareDisk/master/poincare-edgeline.png)
![](https://raw.github.com/dcoeurjo/PoincareDisk/master/poincare-triangle.png)
![](https://raw.github.com/dcoeurjo/PoincareDisk/master/poincare-triangle4.png)
![](https://raw.github.com/dcoeurjo/PoincareDisk/master/2torus.png)
