 /*----------------------------------------------------------------------*/
/************************************************************/
/*    NAME: Craig Evans                                              */
/*    ORGN: MIT, Cambridge MA                               */
/*    FILE: prime_calc.cpp                                          */
/*    DATE: December 29th, 1963                             */
/************************************************************/

 #include <iostream>   // For terminal I/O using cout                     
 #include <cstdlib>    // For converting C-Style string to number with atoi
 #include <sstream>
 #include <vector>
 #include <math.h>
 #include "VisitPoint.h"
 using namespace std;
 int main(int argc, char **argv)
 {

   vector<VisitPoint> m_point_vec;
   for(int i=0;i<6;i++){
     VisitPoint mypoint;
     mypoint.m_x=i*3;
     mypoint.m_y=i*3;
     mypoint.m_id=i+1;
     m_point_vec.push_back(mypoint);
     }
   m_point_vec[0].m_x=186.725;
   m_point_vec[0].m_y=-172.735;
   m_point_vec[1].m_x=143.008;
   m_point_vec[1].m_y=-107.56;
   m_point_vec[2].m_x=176.465;
   m_point_vec[2].m_y=-47.575;
   m_point_vec[3].m_x=141.523;
   m_point_vec[3].m_y=-99.685;
   m_point_vec[4].m_x=159.748;
   m_point_vec[4].m_y=-118.915;
   m_point_vec[5].m_x=103.07;
   m_point_vec[5].m_y=-53.53;
   double mini=1000000;
   int i=0;
   double startx=0;
   double starty=0;
   int i1=0;
   for(int t=1;t<m_point_vec.size()+1;t++){
     mini=100000;
     for(int j=0;j<m_point_vec.size();j++){
       if(t==1){
         double ar1=(startx-m_point_vec[j].m_x)*(startx-m_point_vec[j].m_x);
         double ar2=(starty-m_point_vec[j].m_y)*(starty-m_point_vec[j].m_y);
         double ar=ar1+ar2;
         double distance=sqrt(ar);
         cout<<"this is distance "<<distance<<endl;
         if(distance<mini&&m_point_vec[j].m_point_order==0){
           mini=distance;
           i=int(m_point_vec[j].m_id);
         }
       }
       else{
         double ar1=(m_point_vec[i1].m_x-m_point_vec[j].m_x)*(m_point_vec[i1].m_x-m_point_vec[j].m_x);
         double ar2=(m_point_vec[i1].m_y-m_point_vec[j].m_y)*(m_point_vec[i1].m_y-m_point_vec[j].m_y);
         double ar=ar1+ar2;
         double distance=sqrt(ar);
         cout<<"THIS IS i "<<i1<<"This is j "<<j<<"THIS is dist "<<distance<<endl;
         if(distance<mini&&m_point_vec[j].m_point_order==0&&i1!=j){
           mini=distance;
           cout<<"MINI"<<mini<<endl;
           i=int(m_point_vec[j].m_id);
         }
       }
     }
     for(int w=0;w<m_point_vec.size();w++){
       int k=0;
       k=int(m_point_vec[w].m_id);
       if(k==i){
         m_point_vec[w].setPointOrder(t);
       }    
     }
     i=i-1;
     i1=i;
   }
   for(int j=0;j<m_point_vec.size();j++){
     cout<<"THIS IS my x "<<m_point_vec[j].m_x<<" THIS IS my y "<<m_point_vec[j].m_y<<" id "<<m_point_vec[j].m_id<<endl;
     cout<<"This is the order to travel "<<m_point_vec[j].m_point_order<<endl;
   }


   vector<VisitPoint> m_point_vec_new;
       for(int k=1;k<m_point_vec.size()+1;k++){
         for(int j=0;j<m_point_vec.size();j++){
           if(m_point_vec[j].m_point_order==k){
             m_point_vec_new.push_back(m_point_vec[j]);
           }
         }
       }
   for(int j=0;j<m_point_vec_new.size();j++){
     cout<<"THIS IS my x "<<m_point_vec_new[j].m_x<<" THIS IS my y "<<m_point_vec_new[j].m_y<<" id "<<m_point_vec_new[j].m_id<<endl;
     cout<<"This is the order to travel "<<m_point_vec_new[j].m_point_order<<endl;
   }
   return(0);
 }

