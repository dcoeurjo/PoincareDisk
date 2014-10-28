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
 * @file cairoPoincare.h
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2010/06/01
 **/

#include<cairo.h>
#include<cairo-pdf.h>
#include <math.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


//Size of the cairo board
#define SIZEX 1000
#define SIZEY  1000
//Radius of the "unit" disk
#define RAD 400.0

#define EDGEWIDTH 0.5
#define POINTRADIUS 3


#define EPSILON  0.0001

//Global drawing board
cairo_surface_t *CSglobal;
cairo_t *cairo;



//Functions to map a point from the unit disk to the cairo board
double cX(double x)
{
  return (x*RAD+SIZEX/2.0);
}
double cY(double y)
{
  return (SIZEY-y*RAD) - SIZEY/2.0;
}


/**
 * Draw a point in the Poincaré Disk
 *
 * @param a the point to plot
 * @param r red value
 * @param g green value
 * @param b blue value
 * @param alpha transparency
 */
template <typename Point>
void drawPoint(const Point &a, const double r=0.0, const double g=0.0, const double b=0.0, const double alpha=0.5)
{
  cairo_set_source_rgba (cairo, r, g, b, alpha);
  cairo_set_line_width (cairo, 0.5);
  cairo_arc(cairo, cX(a.x()),cY(a.y()), POINTRADIUS, 0, 2*M_PI);
  cairo_fill (cairo);
  cairo_stroke(cairo);
}



/**
 * Compute the circle containing points a and b, and orthogonal to the
 * unit circle (a.k.a shortest path between a and b in the hyperbolic sense).
 *
 * @param a input point a
 * @param b input point b
 * @param cx abscissa of the circle center
 * @param cy ordiniate of the circle center
 * @param radius radius of the circle
 *
 * @return true if the output is a circle. False if the shortest path
 * is a straight line (diameter of the unit circle).
 */
template <typename Point>
bool computeCircleParameters(const Point &a, const Point &b, double *cx, double *cy, double *radius)
{
  double ax=a.x(), ay=a.y(), bx=b.x(), by=b.y();

  if (fabs(ax*by - ay*bx) < EPSILON )
    return false;

  *cx = (-1/2.0*(ay*bx*bx + ay*by*by
		- (ax*ax + ay*ay + 1)*by + ay)
	/(ax*by -ay*bx));

  *cy = (1/2.0*(ax*bx*bx + ax*by*by
	       - (ax*ax + ay*ay + 1)*bx + ax)
	/(ax*by - ay*bx));


  *radius = (-1/2.0*sqrt(ax*ax*ax*ax*bx*bx + ax*ax*ax*ax*by*by - 2*ax*ax*ax*bx*bx*bx-
			2*ax*ax*ax*bx*by*by + 2*ax*ax*ay*ay*bx*bx + 2*ax*ax*ay*ay*by*by - 2*ax*ax*ay*bx*bx*by
			- 2*ax*ax*ay*by*by*by + ax*ax*bx*bx*bx*bx + 2*ax*ax*bx*bx*by*by + ax*ax*by*by*by*by -
			2*ax*ay*ay*bx*bx*bx - 2*ax*ay*ay*bx*by*by + ay*ay*ay*ay*bx*bx + ay*ay*ay*ay*by*by -
			2*ay*ay*ay*bx*bx*by - 2*ay*ay*ay*by*by*by + ay*ay*bx*bx*bx*bx + 2*ay*ay*bx*bx*by*by + ay*ay*by*by*by*by
			- 2*ax*ax*ax*bx - 2*ax*ax*ay*by + 4*ax*ax*bx*bx - 2*ax*ay*ay*bx + 8*ax*ay*bx*by
			- 2*ax*bx*bx*bx - 2*ax*bx*by*by - 2*ay*ay*ay*by + 4*ay*ay*by*by - 2*ay*bx*bx*by -
			2*ay*by*by*by + ax*ax - 2*ax*bx + ay*ay - 2*ay*by + bx*bx + by*by)
	    /(ax*by -	ay*bx) );

  if ((*radius) < 0.0)
    *radius= 1/2.0*sqrt(ax*ax*ax*ax*bx*bx + ax*ax*ax*ax*by*by - 2*ax*ax*ax*bx*bx*bx
		       - 2*ax*ax*ax*bx*by*by + 2*ax*ax*ay*ay*bx*bx + 2*ax*ax*ay*ay*by*by -
		       2*ax*ax*ay*bx*bx*by - 2*ax*ax*ay*by*by*by + ax*ax*bx*bx*bx*bx + 2*ax*ax*bx*bx*by*by +
		       ax*ax*by*by*by*by - 2*ax*ay*ay*bx*bx*bx - 2*ax*ay*ay*bx*by*by + ay*ay*ay*ay*bx*bx + ay*ay*ay*ay*by*by -
		       2*ay*ay*ay*bx*bx*by - 2*ay*ay*ay*by*by*by + ay*ay*bx*bx*bx*bx + 2*ay*ay*bx*bx*by*by + ay*ay*by*by*by*by
		       - 2*ax*ax*ax*bx - 2*ax*ax*ay*by + 4*ax*ax*bx*bx - 2*ax*ay*ay*bx + 8*ax*ay*bx*by
		       - 2*ax*bx*bx*bx - 2*ax*bx*by*by - 2*ay*ay*ay*by + 4*ay*ay*by*by - 2*ay*bx*bx*by -
		       2*ay*by*by*by + ax*ax - 2*ax*bx + ay*ay - 2*ay*by + bx*bx + by*by)/(ax*by - ay*bx);

  return true;

}


/**
 * Compute the angles of the points (a.k.a., endpoints, ideal points, omega
 * points, etc.) at which the circle meets the boundary of the unit circle,
 * using the circle parameters.
 *
 */
void computeOmegaPoints(const double &cx, const double &cy, const double &r, double *theta1, double *theta2)
{
  double dtheta = atan2(r, 1);
  double theta = std::arg(std::complex<double>(cx, cy));
  if (theta<0) theta+=2*M_PI;
  *theta1 = theta - dtheta;
  *theta2 = theta + dtheta;
}


/**
 * Compute the angles of the intersect points from the perspective of the
 * intersecting circle, since that is the perspective from which cairo_arc()
 * draws.
 *
 */
void computeIntersectAngles(const double &cx, const double &cy, const double &r, double *phi1, double *phi2)
{
  double dphi = atan2(1, r);
  double itheta = std::arg(std::complex<double>(cx, cy));
  if (itheta < 0) itheta += 2*M_PI;
  if (itheta >= M_PI) itheta -= M_PI;
  else if (itheta < M_PI) itheta += M_PI;
  itheta = 2*M_PI - itheta; // convert to Cairo's polar orientation
  *phi1 = itheta - dphi;
  *phi2 = itheta + dphi;
}


/**
 * Draw the hyperbolic line through a and b.
 *
 * @param a first point.
 * @param b second point.
 * @param withPoint true means that  points are also displayed.
 */
template <typename Point>
void drawLine(const Point &a, const Point &b, bool withPoint=true  )
{
  if (withPoint)
    {
      drawPoint(a);
      drawPoint(b);
    }

  double ax=a.x(), ay=a.y(), bx=b.x(), by=b.y();
  double cx,cy,r;

  bool result = computeCircleParameters(a,b,&cx,&cy,&r);

  if (not(result))
    {
      cairo_set_source_rgba (cairo, 0, 0.6, 0, 0.5);
      cairo_set_line_width (cairo, 0.5);

      //We project a and b points onto the unit circle.
      double theta = atan2(ay,ax);
      double theta2 = atan2(by,bx);

      cairo_move_to (cairo, cX(cos(theta)),cY(sin(theta)));
      cairo_line_to (cairo, cX(cos(theta2)),cY(sin(theta2)));
      cairo_stroke(cairo);
    }
  else
    {
      double theta1, theta2;
      computeIntersectAngles(cx, cy, r, &theta1, &theta2);
      cairo_set_source_rgba (cairo, 0, 0.6, 0, 0.5);
      cairo_set_line_width (cairo, EDGEWIDTH);
      cairo_arc(cairo, cX(cx),cY(cy), r*RAD, theta1, theta2);
      cairo_stroke(cairo);
    }
}


/**
 * Internal method for the edge drawing.
 *
 * @param a first point.
 * @param b second point.
 * @param withPoint if true, points are displayed.
 */
template <typename Point>
void internaldrawEdge(const Point &a, const Point &b, bool withPoint )
{
  if (withPoint)
    {
      drawPoint(a);
      drawPoint(b);
    }

  double ax=a.x(), ay=a.y(), bx=b.x(), by=b.y();
  double cx,cy,r;
  bool result  = computeCircleParameters(a,b,&cx,&cy,&r);

  //Near-aligned points -> straight segment.
  if (not(result))
    {
      cairo_move_to (cairo, cX(ax),cY(ay));
      cairo_line_to (cairo, cX(bx),cY(by));
    }
  else
    {
      double theta  = atan2(-ay+cy,ax-cx);
      double theta2 = atan2(-by+cy,bx-cx);

      //We recenter the angles to [0, 2Pi]
      while (theta<0)
	theta += 2*M_PI;
      while (theta2<0)
	theta2 += 2*M_PI;

      if (theta > theta2)
	if ( theta - theta2 > M_PI)
	  cairo_arc(cairo, cX(cx),cY(cy), r*RAD ,theta, theta2);
	else
	  cairo_arc_negative(cairo, cX(cx),cY(cy), r*RAD ,theta, theta2);
      else
	if ( theta2 - theta < M_PI)
	  cairo_arc(cairo, cX(cx),cY(cy), r*RAD ,theta, theta2);
	else
	  cairo_arc_negative(cairo, cX(cx),cY(cy), r*RAD ,theta, theta2);
    }
}



/**
 * Main method to draw an hyperbolic edge between a and b
 *
 * @param a first point
 * @param b second point
 * @param withPoints if true, points are displayed.
 */
template<typename Point>
void drawEdge(const Point &a, const Point &b, const bool withPoints=true)
{
  cairo_set_source_rgba (cairo, 0, 0.0, 1, 0.8);
  cairo_set_line_width (cairo, EDGEWIDTH);

  internaldrawEdge(a,b,withPoints);
  cairo_stroke(cairo);
}


/**
 * Draw an hyperbolic triangle with vertices (a,b,c)..
 *
 * @param a first point
 * @param b second point
 * @param c third point
 * @param r red color for the triangle
 * @param g green color
 * @param bl blue color
 * @param withPoint if true, points are displayed.
 * @param withSupportLines if true, supporting line are displayed.
 */
template<typename Point>
void drawTriangle(const Point &a, const Point &b, const Point &c,
		  const double r= 0, const double g=0, const double bl= 1.0,
		  const bool withPoint=true, const bool withSupportLines=true)
{
  if (withPoint)
    {
      drawPoint(a);
      drawPoint(b);
      drawPoint(c);
    }

  if (withSupportLines)
    {
      drawLine(a,b,false);
      drawLine(b,c,false);
      drawLine(c,a,false);
    }

  cairo_set_source_rgba (cairo, 0, 0.0, 1, 0.8);
  cairo_set_line_width (cairo, EDGEWIDTH);

  cairo_new_path (cairo);
  internaldrawEdge(a,b,false);
  internaldrawEdge(b,c,false);
  internaldrawEdge(c,a,false);


  cairo_set_source_rgba (cairo, r, g, bl, 0.2);
  cairo_fill_preserve(cairo);

  cairo_set_source_rgba (cairo, 0.0, 0.0, 1, 0.8);
  cairo_set_line_width (cairo, EDGEWIDTH);
  cairo_stroke(cairo);
}

/**
 * Draw the unit circle and clip every cairo drawning to it.
 *
 */
void drawUnitCircle()
{
  cairo_arc(cairo, cX(0),cY(0), RAD, 0, 2*M_PI);
  cairo_clip (cairo);
  cairo_new_path (cairo); /* path not consumed by clip()*/

  cairo_set_source_rgba (cairo, 1.0, 0, 0, 0.7);
  cairo_set_line_width (cairo, 10.0);
  cairo_arc(cairo, cX(0),cY(0), RAD, 0, 2*M_PI);

  cairo_stroke(cairo);
}

/**
 * Init the PDF layout.
 *
 * @param fname
 */
void initPDF(const char *fname)
{
  CSglobal=cairo_pdf_surface_create(fname, SIZEX+20, SIZEY+20);
  cairo=cairo_create(CSglobal);
}


/**
 * Terminate the PDF file.
 *
 */
void flushPDF()
{
  cairo_show_page(cairo);
  cairo_destroy(cairo);
  cairo_surface_flush(CSglobal);
  cairo_surface_destroy(CSglobal);
}
