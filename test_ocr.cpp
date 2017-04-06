#include <iostream>
#include <fstream>
#include <vector>
#include <deque>
#include <cstdlib>
#include "character.h"
#include "point.h"
#include "bmplib.h"

using namespace std;

#define THRESH 127

void bfs(Point point, int box[4]);

unsigned char image[SIZE][SIZE];		// Input Image Data Array
unsigned char explored[SIZE][SIZE];		// Explored
//int count =1;


int main(int argc, char *argv[])
{
   if(argc<3)
   {
      cout << "Error not enough inputs"<<endl;
      return 1;
   }
   readGSBMP(argv[1], image);
   //get rid of gray
   for(int i = 0; i<SIZE; i++)
   {
      for(int j = 0; j<SIZE; j++)
      {
         if(image[i][j]< THRESH)
         {
            image[i][j] = 0;
         }
         else
         {
            image[i][j] = 255;
         }
         explored[i][j] = 0;
         
      }
   }
   //find first black find box do tests and print char
   for(int i = 0; i<SIZE; i++)
   {
      
      for(int j = 0; j<SIZE; j++)
      {
         if((image[i][j] == 0) && (explored[i][j] == 0))
         {
            Point point(i,j);
            int box[4];
            bfs(point, box);
            Character character(image,box[0],box[1],box[2], box[3]);
            character.perform_tests();
            character.classify();
            cout << int(character.get_classification()) << " ";
            if(atoi(argv[2]) == 1)
            {
               character.print_calculations();
            }

            
         }
      }
   }
   
  //writeGSBMP("test1", image);
  return 0;
}

void bfs(Point point, int box[4])
{
   deque<Point> queue;
   queue.push_back(point);
   int ulc = point.c;
   int ulr = point.r;
   int lrc = point.c;
   int lrr = point.r;
   
   while(!queue.empty())
   {
      //cout<< ulc <<" "<<ulr <<" "<<lrc <<" "<<lrr <<" "<<endl;
      Point point1;
      point1 = queue.front();
      queue.pop_front();

      if(point1.c < ulc) 
      {
         ulc = point1.c;
      }
      if(point1.r < ulr) 
      {
         ulr = point1.r;
      }
      if(point1.c > lrc) 
      {
         lrc = point1.c;
      }
      if(point1.r > lrr) 
      {
         lrr = point1.r;
      }
      //N
      if((image[point1.r-1][point1.c] == 0) && (explored[point1.r-1][point1.c] ==0))
      {
         Point point2(point1.r-1,point1.c);
         queue.push_back(point2);
         explored[point1.r-1][point1.c] = 1;
         
      }
      //S
      if((image[point1.r+1][point1.c] == 0) && (explored[point1.r+1][point1.c] == 0))
      {
         Point point2(point1.r+1,point1.c);
         queue.push_back(point2);
         explored[point1.r+1][point1.c] = 1;
      }
      //E
      if((image[point1.r][point1.c+1] == 0)&& (explored[point1.r][point1.c+1] == 0))
      {
         Point point2(point1.r,point1.c+1);
         queue.push_back(point2);
         explored[point1.r][point1.c+1] = 1;
      }
      //w
      if((image[point1.r][point1.c-1] == 0)&& (explored[point1.r][point1.c-1] == 0))
      {
         Point point2(point1.r,point1.c-1);
         queue.push_back(point2);
         explored[point1.r][point1.c-1] = 1;
      }
      //NW
      if((image[point1.r-1][point1.c-1] == 0)&& (explored[point1.r-1][point1.c+-1] == 0))
      {
         Point point2(point1.r-1,point1.c-1);
         queue.push_back(point2);
         explored[point1.r-1][point1.c-1] = 1;
      }
      //SW
      if((image[point1.r+1][point1.c-1] == 0)&& (explored[point1.r+1][point1.c-1] == 0))
      {
         Point point2(point1.r+1,point1.c-1);
         queue.push_back(point2);
         explored[point1.r+1][point1.c-1] =1;
      }
      //SE
      if((image[point1.r+1][point1.c+1] == 0) && (explored[point1.r+1][point1.c+1] == 0))
      {
         Point point2(point1.r+1,point1.c+1);
         queue.push_back(point2);
         explored[point1.r+1][point1.c+1] = 1;
      }
      //NE
      if((image[point1.r-1][point1.c+1] == 0)&& (explored[point1.r-1][point1.c+1] == 0))
      {
         Point point2(point1.r-1,point1.c+1);
         queue.push_back(point2);
         explored[point1.r-1][point1.c+1] =1;
      }
      
   }
   box[0] = ulr;
   box[1] = ulc;
   box[2] = lrr-ulr;
   box[3] = lrc-ulc;
  // cout <<box[0]<<box[1]<<box[2]<<box[3]<<endl;
}

           /* for(int a = box[0]; a<box[0]+box[2]; a++)
            {
               for(int b = box[1];b<box[1]+box[3]; b++)
               {
                  // delete
                  if((a==box[0]) || (a==(box[0]+box[2])))
                  {
                     image[a][b] = 128;
                  }
                  if((b==box[1]) || (b==(box[1]+box[3])))
                  {
                     image[a][b] = 128;
                  }
               }
            }*/
