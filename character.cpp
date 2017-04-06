#include "character.h"

using namespace std;


  Character::Character(){}
  // the first parameter should just be passed in and saved to 
  //  the 'image' data member as in ( image = myimage; )
  Character::Character(unsigned char (*myimage)[256], int ulr, int ulc, int h, int w )
  {
      ul_r = ulr;
      ul_c = ulc;
      height = h;
      width = w;
      image = myimage;
  }
  Character::~Character(){}


  void Character::perform_tests()
  {
     calc_bit_quads();
     calc_area();
     calc_perimeter();
     calc_euler_number();
     calc_spatial_moment(); 
     calc_sym();            
     calc_aspect_ratio();
  }
  void Character::classify()
  {
      if(Euler == -1)
      {
         recognized_char = 8;
      }
      else if(Euler == 1)
      {
         if(aspect >= 1.7)
         {
            recognized_char = 1;
         }
         else if(vert/height < .43)
         {
            recognized_char = 7;
         }
         else if(hor/width >= .575)
         {
            recognized_char = 3;
         }
         else if(vert/ height > .53)
         {
            recognized_char = 2;
         }
         else
         {
            recognized_char = 5;
         }
      }
      else
      {
         if((vert/ height > .48) &&(vert / height < .52)&&(hor/width > .48) && (hor/width < .52) )
         {
            recognized_char = 0;
         }
         else if(hor / width > .55)
         {
            recognized_char = 4;
         }
         else if(vert / height < .495)
         {
            recognized_char = 9;
         }
         else
         {
            recognized_char = 6;
         }
      }
  }
  char Character::get_classification()
  {
      return recognized_char;
  }
  // returns upper-left point and lower-right point of bounding box
  //  DOES NOT compute bounding box...it's already in your data members
  //  just returns the bounding box if a user wants the bounds
  void Character::get_bounding_box(int &ulr, int &ulc, int &lrr, int &lrc)
  {
      ulr = ul_r;
      ulc = ul_c;
      lrr = ul_r +height;
      lrc = ul_c +width;
  }
  void Character::print_calculations()
  {
      cout << "H,W"<< height<< " "<< width<<endl;
      cout << "Q1,Q3,Qd,Q2,Q4"<< Q1<<" "<<Q3<<" "<<Qd<<" "<<Q2<<" "<<Q4<<endl;
      cout << "Euler"<<Euler<<endl;
      cout << "area, per" << area <<" "<< per<<endl;
      cout << "vert, hor, vert_sym, hor_sym, aspect"<<vert<<" "<< hor<<" "<< vert_sym<<" "<< hor_sym<<" "<< aspect<<endl;
  }

 
  //==============
  // Helper Functions to set data members
  //==============

  void Character::calc_bit_quads()
  {
      int ulc,ulr,h,w;
      ulc = ul_c-1;
      ulr = ul_r-1;
      h = height +2;
      w = width +2;
      Q1=0;
      Q3=0;
      Qd=0;
      Q2=0;
      Q4=0;
      //cout << ulr<< ulc << h << w<< endl;
      // look in the four squares and count black
      //use black to calculate Qs
      for(int i = ulr; i< (h+ulr); i++)
      {
         for(int j = ulc; j<(w+ulc); j++)
         {
            int black=0;
            if(image[i][j] == 0)
            {
               //cout<< "done"<<endl;
               black++;
            }
            
            if(image[i][j+1] == 0)
            {
               black++;
            }
          
            if(image[i+1][j] == 0)
            {
               black++;
            }
           
            if(image[i+1][j+1] == 0)
            {
               black++;
            }
            
            if(black == 1)
            {
               Q1++;
            }
            if(black==3)
            {
               Q3++;
            }
            if(black == 2)
            {
               //cout << int (image[i][j]) << " " << int (image[i+1][j+1])<< endl; 
               if(image[i][j] == image[i+1][j+1])
               {
                  Qd++;
               }
               else
               {
                  Q2++;
               }
            }
            if(black==4)
            {
               Q4++;
            }
            
         }
      } 
  }
  void Character::calc_area()
  {
      area = (Q1+2*Q2+2*Qd+3*Q3+4*Q4)/4;
  }
  void Character::calc_perimeter()
  {
      per = Q1+Q2+2*Qd+Q3;
  }
  void Character::calc_euler_number()
  {
      Euler = (Q1 - Q3 -2*Qd)/4;
  }
  void Character::calc_spatial_moment()
  {
      int num = 0;
      int den = 0;
      //follow equation in the assignment
      for(int i = 0 ; i <= height; i++)
      {
         for(int j =0; j<= width; j++)
         {
            if(image[i+ul_r][j+ul_c] == 0)
            {
               num+=i;
               den++;
            }
         }
      }
      vert = double(num)/den;
      num = 0;
      den = 0;
      for(int i = 0 ; i <= height; i++)
      {
         for(int j =0; j<= width; j++)
         {
            if(image[i+ul_r][j+ul_c] == 0)
            {
               num+=j;
               den++;
            }
         }
      }
      hor = double(num)/den;
  } // calcs the horizontal & vertical centroids
  void Character::calc_sym()
  {
      int count =0;
      int total =0;//check vert sym by changing row not col
      for(int i = ul_r; i<= ul_r + height/2; i++)
      {
         for(int j = ul_c; j<ul_c + width; j++)
         {
            //if((image[i][j] == 0) || (image[ul_r +height - i][j] == 0))
            //{
            if(image[i][j] == image[ul_r +height - i][j])
            {
               //cout<< int(image[i][j])<<endl;
               count++;
            }
            total++;
            //}
         }
      }
      vert_sym = double(count)/total;
      count =0;
      total =0;
      for(int i = ul_r; i<= (ul_r + height); i++)
      {
         for(int j = ul_c; j<ul_c + width/2; j++)
         {
            if(image[i][j] == image[i][ul_c + width - j])
            {
               count++;
            }
            total++;
         }
      }
      hor_sym = double(count)/total;
  }            // calcs horizontal and vertical symmetry
  void Character::calc_aspect_ratio()
  {
      aspect = double(height)/width;
  }

