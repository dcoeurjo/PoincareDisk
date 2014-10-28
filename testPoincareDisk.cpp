/**
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as
 *  published by the Free Software Foundation, either version 3 of the
 *  License, or  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 **/

/**
 * @file testPoincare.cpp
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2010/06/01
 **/



#include <iostream>
#include <complex>
#include "cairoPoincare.h"


struct Point{

  Point(double xx, double yy): myX(xx),myY(yy)
  {}

  Point(std::complex<double> p): myX(p.real()),myY(p.imag())
  {}

  double x() const
  {return myX;}

  double y() const
  {return myY;}


  double myX,myY;
};



/**
 * Explicit Gyrotranslation "z+a".
 * res = (a+z)/(1-z*conj(a))
 */
void mobiusTranslate(double ax, double ay, double zx, double zy, double &resx, double &resy)
{

  std::complex<double> a(ax,ay),z(zx,zy),res, one(1,0);

  res = (a + z)/( one + conj(a)*z);
  resx = res.real();
  resy = res.imag();
}


Point mobiusTranslate(const Point &a, const Point &z)
{
  double rx,ry;
  mobiusTranslate(a.x(),a.y(),z.x(),z.y(), rx,ry);
  return Point(rx,ry);
}



int main()
{

  initPDF("poincare-unit.pdf");
  drawUnitCircle();
  flushPDF();

  initPDF("poincare-edge.pdf");
  drawUnitCircle();
  drawEdge(Point(0.5,0.5), Point(-0.6,0.2),true);
  flushPDF();

  initPDF("poincare-edgeline.pdf");
  drawUnitCircle();
  drawLine(Point(0.5,0.5), Point(-0.6,0.2),true);
  flushPDF();

  initPDF("poincare-example.pdf");
  drawUnitCircle();
  drawLine(Point(std::polar(0.93300,3.19046)), Point(std::polar(0.92440,3.33815)));
  drawLine(Point(std::polar(0.79288,2.58823)), Point(std::polar(0.48261,2.36832)));
  drawLine(Point(std::polar(0.34615,1.09714)), Point(std::polar(0.61119,1.62662)));
  drawLine(Point(std::polar(0.61020,0.79445)), Point(std::polar(0.87224,3.90366)));
  drawLine(Point(std::polar(0.90210,4.08137)), Point(std::polar(0.07962,5.36132)));
  drawLine(Point(std::polar(0.78684,5.16442)), Point(std::polar(0.73969,4.49662)));
  flushPDF();

  initPDF("poincare-triangle.pdf");
  drawUnitCircle();
  drawTriangle(Point(0.8,-0.3),Point(0.2,-0.6), Point(-0.61,-0.6), 1, 0, 0);
  flushPDF();

  initPDF("poincare-triangle2.pdf");
  drawUnitCircle();
  drawTriangle(Point(0.1,0.5),Point(0.2,-0.6), Point(-0.1,-0.6), 1, 0, 0);
  flushPDF();


  initPDF("poincare-triangle3.pdf");
  drawUnitCircle();
  drawTriangle(Point(0.0,1),Point(1,-0.0010), Point(0,0), 1, 0, 0);
  flushPDF();

  initPDF("poincare-triangle4.pdf");
  drawUnitCircle();
  drawTriangle(Point(0.0,1),Point(1,0), Point(-0.866,-0.5), 1, 0, 0);
  flushPDF();


  initPDF("poincare.pdf");
  drawUnitCircle();

  //drawEdge(Point(0.5,0.5), Point(-0.6,-0.6));

  /* drawLine(Point(0.5,0.5), Point(0.8,-0.3));
     drawLine(Point(-0.5,0.2), Point(0.3,-0.1));
     drawLine(Point(0.5,0.5), Point(0.2,0.5));
     drawLine(Point(0.1,0.5), Point(0.2,0.5));
     drawLine(Point(0.25,-0.5), Point(0.9,0.7));
     drawLine(Point(-0.1,0.5), Point(0.2,-0.5));
  */

  /*drawEdge( Point(0.8,-0.3),Point(0.5,0.5));
    drawEdge(Point(-0.5,0.2), Point(0.3,-0.1));
    drawEdge(Point(0.5,0.5), Point(0.2,0.5));
    drawEdge(Point(0.1,0.5), Point(0.2,0.5));
  */

  /* drawTriangle(Point(0.8,-0.3),Point(0.5,0.5), Point(-0.61,-0.6));
     drawTriangle(Point(-0.5,0.3),Point(0.5,0.5), Point(-0.61,-0.6),0,1,0);
     drawTriangle(Point(0.8,-0.3),Point(0.2,-0.6), Point(-0.61,-0.6), 1, 0, 0);
     drawTriangle(Point(0.8,-0.3),Point(0.2,-0.6), Point(-0.61,-0.6), 1, 0, 0);
     drawTriangle(Point(-0.5,-0.76),Point(0.2,-0.6), Point(-0.61,-0.6), 1, 1, 0);
  */

  /*
    int max= 13;
    for(unsigned int k=0; k < (max-1); k++)
    drawTriangle(Point(1,0), Point(cos(k*134/(double)max), sin(k*134/(double)max)),
    Point(cos((k+1)*134/(double)max), sin((k+1)*134/(double)max)),
    0.2, k/(double)max,  (max-k)/(double)max);
  */


  /*
    Point ma=Point(-0.8,+0.3);
    testGyroTranslation(ma,10);
  */

  flushPDF();
}
