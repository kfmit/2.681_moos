/************************************************************/
/*    NAME: Craig Evans                                              */
/*    ORGN: MIT, Cambridge MA                               */
/*    FILE: main.cpp, Cambridge MA                          */
/*    DATE: December 29th, 1963                             */
/************************************************************/

#include <string>
#include <iostream>
#include <math.h>
#include <sstream>
#include <vector>
using namespace std;

int main(int argc, char *argv[])
{
  double c0=1480;
  double g=0.016;
  double x=0;
  double y=0;
  double x2=15000;
  double y2=15000;
  double dep1=2000;
  double dep2=1500;
  double deltaz=dep2-dep1;
  double r1=0;
  double as=0;
  double cz=c0 +dep1*g;
  double zc=-1*c0/g;
  cout <<"THIS IS MY zc "<<zc<<endl;
  double zcc=6000+abs(zc);
  cout<<"THIS is my zcc "<<zcc<<endl;
  double z_tot=abs(zc)+dep1;
  double nav_r=sqrt(((x2-x)*(x2-x))+((y2-y)*(y2-y)));
  double r3=.5*nav_r;
  double gamma=atan2(deltaz,nav_r);;
  double zd3=.5*(deltaz);
  double z3=z_tot+zd3;
  double delta_rc=(deltaz/nav_r)*(z3);
  double rc=delta_rc+r3;
  double Radius=sqrt((rc*rc)+(z_tot*z_tot));
  cout<<"this is my Radius "<<Radius<<endl;
  double THETA=-1*acos(z_tot/Radius)*180/M_PI;
  
  
  
  //cout <<"this is k "<<k<<endl;

  cout<<"This is the theta value "<<THETA<<"###################"<<endl;rc=delta_rc+r3;



  
  /*
  for(int h=0; h<8000;h++){
    dep1=h;
    double delta=dep2-dep1;
    double cz = c0+(g*dep1);
    r1=sqrt((delta*delta)+((x2-x)*(x2-x))+((y2-y)*(y2-y)));
    for(int i=-90;i<90;i++){
      for(int j=-90;j<90;j++){
    

        double a=cos(i*3.14/180)/cz;
        double R=1/(a*g);
        double s=R(i-j);
        double R1=R*(sin(i*3.14/180));
        // cout <<"This is R1 "<<R1<<endl;
        double r=R*(sin(i*3.14/180)+sin(((s/R-)i)*3.14/180));
        double z=R*cos(((s/R-)i)*3.14/180)-c0/g;
        //cout<<"This is the r value "<<r<<endl;
        //cout<<"This the z value"<<z<<endl;
        if((r-10)<=r1&&r1<=(r+10)&&(dep2-5)<=z&&z<=(dep2+5)){
          double m_omega=i;
          cout<<"This is th depth of vehicle "<<h<<endl;
          cout<<"This is the r value "<<r<<endl;
          cout<<"This the z value"<<z<<endl;
          cout<<"The angle to launch is "<<m_omega<<endl;
        }
      }

    }
    }*/
  
  return(0);
}

