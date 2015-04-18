#include <cassert>
#include <CoreFoundation/CoreFoundation.h>
#include <ApplicationServices/ApplicationServices.h>


#include "emumice.hpp"

//------------------------------------------------------------------------------

namespace Emumice {

//------------------------------------------------------------------------------

namespace Detail {

   // this function posts a mouse event in a specified mouse location:
   void mouse_event(CGMouseButton button, CGEventType type, CGPoint location)
   {
      CGEventRef event = CGEventCreateMouseEvent(NULL, type, location, button);
      CGEventSetType(event, type);
      CGEventPost(kCGHIDEventTap, event);
      CFRelease(event);
   }

}; // namespace Detail

//------------------------------------------------------------------------------

// returns current mouse location:
Point get_mouse_loc()
{
   CGEventRef event = CGEventCreate(NULL);
   CGPoint cursor = CGEventGetLocation(event);
   CFRelease(event);
   return Point(cursor.x, cursor.y);
}

//------------------------------------------------------------------------------

// sets mouse location at Point p:
void set_mouse_loc(Point p) 
{
   CGPoint location = CGPointMake(p.x, p.y);
   Detail::mouse_event(kCGMouseButtonLeft, kCGEventMouseMoved, location);
}

//------------------------------------------------------------------------------

// sets mouse button state, if is_press==true the button b is pressed 
// otherwise is released:
void mouse_button(Button b, bool is_press) 
{
   CGEventType type;   
   CGMouseButton button;

   switch (b) {
   case btn_left:   
      type = (is_press ? kCGEventLeftMouseDown : kCGEventLeftMouseUp);
      button = kCGMouseButtonLeft;
      break;
   
   case btn_right:  
      type = (is_press ? kCGEventRightMouseDown : kCGEventRightMouseUp);
      button = kCGMouseButtonRight;
      break;
   };

   CGEventRef event = CGEventCreate(NULL);
   CGPoint location = CGEventGetLocation(event); // current mouse location
   CFRelease(event);

   Detail::mouse_event(button, type, location);
}

//------------------------------------------------------------------------------

// clicks at the current mouse location:
void mouse_click(Button b)
{
   mouse_button(b, true);  // press
   mouse_button(b, false); // release
}

//------------------------------------------------------------------------------

}; // namespace Emumice

//------------------------------------------------------------------------------
