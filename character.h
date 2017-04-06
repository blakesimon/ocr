#ifndef CHARACTER_H
#define CHARACTER_H
#include <iostream>
using namespace std;


class Character {
 public:
  Character();
  // the first parameter should just be passed in and saved to 
  //  the 'image' data member as in ( image = myimage; )
  Character(unsigned char (*myimage)[256], int ulr, int ulc, int h, int w );
  ~Character();


  void perform_tests();
  void classify();
  char get_classification();
  // returns upper-left point and lower-right point of bounding box
  //  DOES NOT compute bounding box...it's already in your data members
  //  just returns the bounding box if a user wants the bounds
  void get_bounding_box(int &ulr, int &ulc, int &lrr, int &lrc);
  void print_calculations();

 private:
  //==============
  // Helper Functions to set data members
  //==============

  void calc_bit_quads();
  void calc_area();
  void calc_perimeter();
  void calc_euler_number();
  void calc_spatial_moment(); // calcs the horizontal & vertical centroids
  void calc_sym();            // calcs horizontal and vertical symmetry
  void calc_aspect_ratio();

  //==============
  // Data Members
  //==============
 private: 
  char recognized_char;
  unsigned char (*image)[256];
  int ul_r, ul_c;
  int height, width;
  int Euler;
  int Q1,Q3,Qd,Q2,Q4;
  int area, per;
  double vert, hor, vert_sym, hor_sym, aspect;
  
  // feel free to add data members here
  


};

#endif

