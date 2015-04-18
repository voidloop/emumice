#include <sstream>
#include <iostream>
#include "emumice.hpp"

using namespace std;
using namespace Emumice;

//------------------------------------------------------------------------------

// print program usage and exit
void usage(const string& s) 
{
  cerr << "Usage: " << s << " <x> <y>" << endl;
}

//------------------------------------------------------------------------------

// convert string in T:
template <typename T> T from_string(const char* s) 
{
   istringstream is(s);
   T val;
   is >> val; 
   return val;
}

//------------------------------------------------------------------------------

int main(int argc, char* argv[]) 
{
   const string program_name(argv[0]); // set the program name

   if (argc < 2) {
      usage(program_name);
      exit(1);
   }

   Point p; 
   p.x = from_string<int>(argv[1]);
   p.y = from_string<int>(argv[2]);
 
   mouse_move(p);
}
