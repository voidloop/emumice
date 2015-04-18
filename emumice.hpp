#ifndef EMUMICE_HPP_
#define EMUMICE_HPP_

//------------------------------------------------------------------------------

namespace Emumice {

//------------------------------------------------------------------------------

// a Point on the screen:
struct Point {
   int x, y; 
   Point() :x(0), y(0) { }
   Point(int xx, int yy) :x(xx), y(yy) { }
};

//------------------------------------------------------------------------------

enum Button {
   btn_left,
   btn_right
};

//------------------------------------------------------------------------------

// helper functions: 
int random_range(int a, int b);
int random(int x);
void msleep(int ms);

//------------------------------------------------------------------------------

// simple mouse functions:
Point get_mouse_loc();
void set_mouse_loc(Point p);
void mouse_click(Button b);

//------------------------------------------------------------------------------

// complex mouse functions:
void wind_mouse(Point start, Point end, double gravity, 
                double wind, double min_wait, double max_wait, 
                double max_step, double target_area);
void mouse_move(Point p, int w=0, int h=0, bool laptop=false);
void mouse_move(int x, int y, int w=0, int h=0, bool laptop=false);

//------------------------------------------------------------------------------

}; // namespece Emumice

//------------------------------------------------------------------------------

#endif
