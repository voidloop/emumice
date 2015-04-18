#include <sstream>
#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <time.h>

#include "emumice.hpp"

//------------------------------------------------------------------------------

namespace Emumice {

//------------------------------------------------------------------------------

// generate a random number in range [a,b]:
int random_range(int a, int b)
{
   int div = b-a;
   if (div<=0) return 0;
   int x = (std::rand() % (div)) + a;
   return x;
}

//------------------------------------------------------------------------------

// generate a random number in range [0,x]:
int random(int x)
{
   return random_range(0, x);
}

//------------------------------------------------------------------------------

// sleeps for milliseconds:
void msleep(int ms)
{
   struct timespec req = { 0 };
   time_t sec = int(ms / 1000);
   ms = ms - (sec * 1000);
   req.tv_sec = sec;
   req.tv_nsec = ms * 1000000L;
   nanosleep(&req, &req);
}

//------------------------------------------------------------------------------

void wind_mouse(Point start, Point end, double gravity, 
                double wind, double min_wait, double max_wait, 
                double max_step, double target_area) 
{
   const double sqrt2 = sqrt(2.0);
   const double sqrt3 = sqrt(3.0);
   const double sqrt5 = sqrt(5.0);
   
   double xs = double(start.x);
   double ys = double(start.y);
   double xe = double(end.x);
   double ye = double(end.y);
   
   double wind_x=0;
   double wind_y=0;
   double velo_x=0; 
   double velo_y=0;

   while (hypot(xs - xe, ys - ye) > 1) {
      double dist = hypot(xs - xe, ys - ye);
      wind = std::min(wind, dist);
      if (dist >= target_area) {
         wind_x = (wind_x/sqrt3) + (random(ceil(wind)*2+1) -wind) / sqrt5;
         wind_y = (wind_y/sqrt3) + (random(ceil(wind)*2+1) -wind) / sqrt5;
      }
      else {
         wind_x = wind_x / sqrt2;
         wind_y = wind_y / sqrt2;
         if (max_step < 3)
            max_step = random(3) + 3.0;
         else 
            max_step = max_step / sqrt5;
      }
      velo_x = velo_x + wind_x;
      velo_y = velo_y + wind_y;
      velo_x = velo_x + gravity * (xe - xs) / dist;
      velo_y = velo_y + gravity * (ye - ys) / dist;
      if (hypot(velo_x, velo_y) > max_step) {
         double random_dist = max_step / 2.0 + (random(ceil(max_step) / 2));
         double velo_mag = sqrt(velo_x * velo_x + velo_y * velo_y);
         velo_x = (velo_x / velo_mag) * random_dist;
         velo_y = (velo_y / velo_mag) * random_dist;
      }
      double last_x = ceil(xs);
      double last_y = ceil(ys);
      xs = xs + velo_x;
      ys = ys + velo_y;
      if (last_x != ceil(xs) || last_y != ceil(ys)) {
         set_mouse_loc(Point(ceil(xs), ceil(ys)));
      }
      double step = hypot(xs - last_x, ys - last_y);
      double s = ceil((max_wait - min_wait) * (step / max_step) + min_wait);
      msleep(s);
      //double last_dist = dist;
   }
   
   if ((ceil(xe) != ceil(xs)) || (ceil(ye) != ceil(ys))) {
      set_mouse_loc(end);
   }
}

//------------------------------------------------------------------------------

void mouse_move(Point p, int w, int h, bool is_laptop)
{
   srandom(time(NULL)); // initialize random number generator

  const double mouse_speed = 18.0;
  const int miss_chance = 0;

  Point cur = get_mouse_loc();
  double rand_speed;

  if (is_laptop) {
     bool miss = random(miss_chance) == 0;
     int e = 0;
     int a = p.x - cur.x;
     int b = p.y - cur.y;
     int c = pow(double(a), 2) + pow(double(b), 2);
     int hypo = round(sqrt(c));

     int seg;
     if (hypo == 0) return;
     else if (hypo >=   1 && hypo <=  225) seg = 1;
     else if (hypo >= 226 && hypo <=  600) seg = random(2) + 1;
     else if (hypo >= 601 && hypo <= 1800) seg = random(3) + 1;
     else seg = 5;
     
     int f = round(a / seg);
     int g = round(b / seg);
     
     for (int e=0; e<seg; ++e) {
	std::cout << "e==" << e << "\n";
	msleep(30 + random(50)); // Pascal Wait?

	rand_speed = (random(mouse_speed) / 2.0 + mouse_speed) / 10.0;
	if (rand_speed == 0.0) rand_speed = 0.1;
	
	cur = get_mouse_loc();
	Point n;
	n.x = (cur.x + (f * e)) + random(w);
	n.y = (cur.y + (g * e)) + random(h);
		
	if (miss) {   
	   n.x = n.x + random_range(w, w * 2);
	   n.y = n.y + random_range(h, h * 2);
	}

	wind_mouse(cur, n, 11.0, 8.0, 10.0/rand_speed, 12.0/rand_speed, 10.0*rand_speed, 10.0*rand_speed);
     }

     cur = get_mouse_loc();

     // is Point outside the rectangle?
     if (!(cur.x > p.x && cur.x < p.x + w && 
	   cur.y > p.y && cur.y < p.y + w)) 
     {
	msleep(30 + random(30));
	Point n(p.x + random(w), p.y + random(h));
	wind_mouse(cur, n, 11.0, 6.0, 10.0/rand_speed, 15.0/rand_speed, 10.0*rand_speed, 10.0*rand_speed);	
     }
  } 
  else {
     rand_speed = (random(mouse_speed) / 2.0 + mouse_speed) / 10.0;
     if (rand_speed == 0.0) rand_speed = 0.1;     
     p.x = p.x + random(w);
     p.y = p.y + random(h);
     wind_mouse(cur, p, 9.0, 3.0, 10.0/rand_speed, 15.0/rand_speed, 10.0*rand_speed, 10.0*rand_speed);
  }
}

//------------------------------------------------------------------------------

void mouse_move(int x, int y, int w, int h, bool is_laptop) 
{
   mouse_move(Point(x,y), w, h, is_laptop);
}

//------------------------------------------------------------------------------

}; // namespace Emumice 
