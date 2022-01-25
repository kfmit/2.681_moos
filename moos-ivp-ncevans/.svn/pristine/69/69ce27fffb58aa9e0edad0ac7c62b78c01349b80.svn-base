/************************************************************/
/*    NAME: Craig Evans                                              */
/*    ORGN: MIT, Cambridge MA                               */
/*    FILE: CommunicationAngle.cpp                                        */
/*    DATE: March 11th, 2021                            */
/************************************************************/

#include <iterator>
#include "MBUtils.h"
#include "ACTable.h"
#include <sstream>
#include <list>
#include <string>
#include <math.h>
#include "VehicleComms.h"
#include <iostream>



using namespace std;

VehicleComms::VehicleComms()
{
  m_collab_xval=0;
  m_collab_yval=0;
  m_collab_depthval=0;
  m_collab_speedval=0;
  m_collab_headval=0;
  m_os_x=0;
  m_os_y=0;
  m_os_depth=0;
  m_os_heading=0;
  m_os_speed=0;
  m_deltaz=0;
  m_omega=0;
  m_transd=0;
  m_transx=0;
  m_transy=0;
  m_nav_r=0;
  m_no_chance=false;
  m_old_r=0;
}
VehicleComms::~VehicleComms()
{
}


bool VehicleComms::getMessage(bool nan)
{
  bool done=false;
  stringstream path;
  stringstream location;
  if(nan){
    path<<"elev_angle="<<m_omega<<",transmission_loss=";
    path<<m_TL<<",id=ncevans@mit.edu.";
    m_acoustic_path=path.str();
    location<<"x="<<m_transx<<",y="<<m_transy;
    location<<",depth="<<m_transd<<",id=ncevans@mit.edu";
    m_connectivity_loc=location.str();
    done=true;
  }
  else if(!m_no_chance){
    path<<"elev_angle=NaN,transmission_loss=";
    path<<"NaN,id=ncevans@mit.edu.";
    m_acoustic_path=path.str();
    location<<"x="<<m_transx<<",y="<<m_transy;
    location<<",depth="<<m_transd<<",id=ncevans@mit.edu";
    m_connectivity_loc=location.str();
    done=true;
  }
  else{
    path<<"elev_angle=NaN,transmission_loss=";
    path<<"NaN,id=ncevans@mit.edu.";
    m_acoustic_path=path.str();
    location<<"x=NaN,y=NaN";
    location<<",depth=NaN,id=ncevans@mit.edu";
    m_connectivity_loc=location.str();
    done=true;
  }
  return done;
}
double VehicleComms::getCircleRadius()
{
  double c0=1480;
  double g=0.016;
  double dep1=m_os_depth;
  double dep2=m_collab_depthval;
  double deltaz=dep2-dep1;
  double cz=c0 +dep1*g;
  double zc=-1*c0/g;
  double z_tot=abs(zc)+dep1;
  m_z_TOT=z_tot;
 
  double r3=.5*m_nav_r;
  double gamma=atan2(deltaz,m_nav_r);;
  double zd3=.5*(deltaz);
  double z3=z_tot+zd3;
  double delta_rc=(deltaz/m_nav_r)*(z3);
  double rc=delta_rc+r3;
  double Radius=sqrt((rc*rc)+(z_tot*z_tot));
  m_old_zeta=asin(r3/Radius);

  return Radius;
}
double VehicleComms::calcAngle(double Radius)
{
  double c0=1480;
  double g=0.016;
  double zc=-1*c0/g;
  double z_tot=abs(zc)+m_os_depth;
  double angle=-1*acos(z_tot/Radius)*180/M_PI;
  

  
  return angle;
}
bool VehicleComms::getOmega()
{
  m_deltaz=0;
  m_omega=0;
  m_transd=0;
  m_transx=0;
  m_transy=0;
  m_nav_r=0;
  m_no_chance=false;
  m_old_r=0;
  double c0=1480;
  double g=0.016;
  double zc=-1*c0/g;
  bool got_it=false;
  //calculate the r value from os to collab
  m_nav_r=sqrt(((m_collab_xval-m_os_x)*(m_collab_xval-m_os_x))+((m_collab_yval-m_os_y)*(m_collab_yval-m_os_y)));
  //get the radius of the circle
  double Radius=getCircleRadius();
  m_old_r=Radius;
  //check if there is bottom bounce if not good position
  if(Radius<(abs(zc)+6000)){

    //calculate launch angle
    m_omega=calcAngle(Radius);
    m_transd=m_os_depth;
    m_transx=m_os_x;
    m_transy=m_os_y;
    bool g_tl=getTransmissionLoss();
    m_no_chance=false;
    return true;
  }
  //If there is bottom bounce find a new location
  else{
    //calculates r value for collab current position by finding circle
    double zs_tot=abs(zc)+m_collab_depthval;
    Radius=abs(zc)+5999;
    double delta_rc=(sqrt((Radius*Radius)-(zs_tot*zs_tot)));
    cout<<"THIS IS THE DELTA_C"<<delta_rc<<endl;
    double circ_cent=m_nav_r-delta_rc;
    double ztot= abs(zc)+m_os_depth;
    double distance_os=sqrt((circ_cent*circ_cent)+(ztot*ztot));
    double r1=distance_os-Radius;
    cout <<"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"<<endl;
    cout<<"THIS IS MY LITTLE R DIST  "<<r1<<endl;
    double alpha=acos(circ_cent/distance_os);
    double new_r=cos(alpha)*r1;
    cout <<"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"<<endl;
    cout<<"THIS IS MY NEW R VALUE TO TRANSIT "<<new_r<<endl;
 
     got_it=true;
     
   
    
    
    if(got_it){

      //solve for the location of connectivity
      m_transd=(sin(alpha)*Radius)-abs(zc);
      double phi= asin((m_collab_yval-m_os_y)/(m_nav_r));
      double d_r=new_r;
      m_transx=m_os_x+(cos(phi)*d_r);
      m_transy=m_os_y+(sin(phi)*d_r);

      double NEW_R=sqrt(((m_collab_xval-m_transx)*(m_collab_xval-m_transx))+((m_collab_yval-m_transy)*(m_collab_yval-m_transy)));
      cout<<"THIS IS WHAT I GOT FOR MY NEW R "<<NEW_R<<endl;
      //if we have a good depth
      if(m_transd<6000&&m_transd>0){
        //if the vehicles are not moving give good loc
        cout<<"this is the first speed "<<m_collab_speedval<<endl;
        cout<<"this is the first speed "<<m_os_speed<<endl;
        if(m_collab_speedval==0){
          m_no_chance=false;
          bool g_tl=getTransmissionLoss();
          return false;
        }
        //if they are moving then find transit point


        else{
          //assumes the collab is moving away
          if(got_it){
            double speed_excess=m_os_speed-m_collab_speedval;
            double time_to_get_there=d_r/speed_excess;
            double dist_move=m_collab_speedval*time_to_get_there;
            m_transy=cos(m_collab_headval*M_PI/180)*dist_move;
            m_transx=sin(m_collab_headval*M_PI/180)*dist_move;
            cout<<"IM IN THE SPEED LOOP"<<endl;
            m_no_chance=false;
            bool g_tl=getTransmissionLoss();
            return false;
          }
          else{
            //for right now if we do not have excess speed no location
            m_no_chance=true;
            return false;

          }

        }
      }
      else{
        m_no_chance=true;
        return false;
      }
    }
     
     
  }

    return false;
}
bool VehicleComms::getTransmissionLoss()
{
  double d_theta=.00000001;
  //Here calculate the r value for an omega +.1
  double NEW_RAD=m_z_TOT/cos((m_omega+d_theta)*M_PI/180);
  double c0=1480;
  double g=0.016;
  double zc=-1*c0/g;
  double zs_tot=m_collab_depthval+abs(zc);
  double theta_received=acos(zs_tot/m_old_r);
  double s=m_old_r*(m_omega*M_PI/180-(theta_received));
  double czs=1480+m_collab_depthval*.016;
  double cos_omeg=cos(m_omega*M_PI/180);
  double cz0=1480+m_os_depth*.016;
  double rs1=m_old_r*(sin(m_omega*M_PI/180)+sin(s/m_old_r-(m_omega*M_PI/180)));
  double rs2=NEW_RAD*(sin((m_omega+d_theta)*M_PI/180)+sin(s/NEW_RAD-((m_omega+d_theta)*M_PI/180)));
  double delta_r=(rs2-rs1);
  //Jtakes the finite difference between r's
  double J=delta_r/((M_PI/180)*d_theta);
  //double theta_received=-(s/NEW_RAD)+(M_PI/180*(m_omega));
  double coef=rs1/sin(theta_received);
  J=J*coef;
  double ps=(czs*cos_omeg)/(cz0*J);
  ps=sqrt(abs(ps));
  m_TL= -20*log10(ps);

  
  return true;
}
