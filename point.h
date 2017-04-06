#ifndef POINT_H
#define POINT_H

class Point
{
 public:
 Point()  
   { r = 0; c = 0; }
 Point(int myr, int myc)
   { r = myr; c = myc; } 
  int r;
  int c;
};

class Point_Comp {
  bool operator() (const Point &lhs, const Point &rhs) const
  { if(lhs.r < rhs.r) return 1;
    else if(lhs.r == rhs.r && lhs.c < rhs.c) return 1;
    else return 0;
  }
};
#endif
