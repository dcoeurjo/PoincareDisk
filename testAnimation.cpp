/* COMPILE USING:  g++ -Wextra -o testAnimation `pkg-config --cflags --libs gtk+-3.0` testAnimation.cpp */
#include <gtk/gtk.h>
#include <complex>
//#include <limits>
//#include <iostream>
#include "cairoPoincare.h"

#define WINDOW_WIDTH  1000
#define WINDOW_HEIGHT 1000

static gboolean draw_cb(GtkWidget *widget, cairo_t *cr, gpointer data)
{
  // R code:
  // five2 <- 2*pi / 5
  // angles <- 1:5
  // for (ii in seq(1, 0.2, -0.05)) {
  //   poincare.plot(list(r=ii, rad=five2), list(r=ii, rad=five2*2),T);
  //   for (i in angles) {
  //     poincare.plot(list(r=ii, rad=five2*i), list(r=ii, rad=five2*(i+1)),F);
  //     poincare.plot(list(r=ii, rad=five2*i), list(r=ii, rad=five2*(i+2)),F);
  //   }
  // }
  static const int points = 5;
  //static const double epsilon = std::numeric_limits<double>::epsilon();
  static const double delta = 2*M_PI / points;
  static double r = 1.0;
  static double r_inc = 0.005;
  static const double r_upper = r_inc;
  static const double r_lower = -(r_inc*2);
  static double rot = M_PI/2;
  //static const double rot_inc = r_inc;

  drawUnitCircle(cr, true);

  //if (r == 1.0 || r < 0.2) r_inc = r_inc * -1;
  if (r == 1.0 || r < -1.0) r_inc = r_inc * -1;
  //if (rot > 2*M_PI) rot -= 2*M_PI;

  for (int i = 1; i <= points; ++i) {
    drawLine(cr, Point(std::polar(r,delta*i+rot)), Point(std::polar(r,delta*(i+1)+rot)));
    drawLine(cr, Point(std::polar(r,delta*i+rot)), Point(std::polar(r,delta*(i+2)+rot)));
  }
//std::cout<<"epsilon="<<epsilon<<" r_inc="<<r_inc<<" r="<<r<<" diff="<<fabs(r-0.2)<<" bool="<<(bool)(fabs(r-0.2)>fabs(r_inc))<<" rot="<<rot<<std::endl;

  if (r > r_lower && r <= r_upper) r += r_inc; // skip r ~= 0
  r += r_inc;
  //rot += rot_inc;

  return FALSE;
}

static gboolean draw_trigger(GtkWidget *widget)
{
  if (widget == NULL) return FALSE;

  gtk_widget_queue_draw(widget);

  return TRUE;
}

int main (int argc, char *argv[])
{
   GtkWidget *window;
   GtkWidget *da;

   gtk_init (&argc, &argv);

   window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
   g_signal_connect (window, "destroy", G_CALLBACK (gtk_main_quit), NULL);

   da = gtk_drawing_area_new();
   gtk_widget_set_size_request (da, WINDOW_WIDTH, WINDOW_HEIGHT);
   g_signal_connect (da, "draw", G_CALLBACK(draw_cb),  NULL);

   gtk_container_add (GTK_CONTAINER (window), da);
   gtk_widget_show (da);
   gtk_widget_show (window);

   g_timeout_add (34, (GSourceFunc)draw_trigger, (gpointer)da);

   gtk_main ();

   return 0;
}
