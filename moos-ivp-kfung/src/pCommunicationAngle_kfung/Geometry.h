/************************************************************/
/*    NAME: Kat Fung                                              */
/*    ORGN: MIT, Cambridge MA                               */
/*    FILE: Geometry.h                                        */
/*    DATE: The night before its due out of confusion                           */
/************************************************************/

#include <iterator>
#include "MBUtils.h"
#include "ACTable.h"
#include <math.h> // needed for NaN
#include <cmath>
#include "CommunicationAngle_kfung.h"
#include <iostream>
#include <sstream> //needed for stringstream
#include <string>
#include <tgmath.h>
#define _USE_MATH_DEFINES

#ifndef GEOMETRY_HEADER
#define GEOMETRY_HEADER

using namespace std;

 class Geometry
 {
 public: // I made everything public because I planned to use it in both 
        //Geometry and the original file if Geometrey doesn't woek

   Geometry();
   ~Geometry() {};
  // These are the Configuration Parameters for determining Ray Tracing
  
  // Environmental Parameters
  double m_surfacess;
  void setSurfaceSpeed(double v)    {m_surfacess = v;};

  double m_ssgrad;
  void setSSGrad(double v)    {m_ssgrad = v;};

  double m_wdepth;
  void setWaterDepth(double v)    {m_wdepth = v;};
  
  string m_vehicle_name;
  void setvehiclename(string str)    {m_vehicle_name = str;};
  
  
// Own Ship Information
  double m_nav_x;
  void setNAVX(double v)    {m_nav_x = v;};
  double m_nav_y;
  void setNAVY(double v)    {m_nav_y =v;};
  double m_nav_depth;
  void setNAVDEPTH(double v)  {m_nav_depth=v;};
  double m_nav_heading;
  void setNAVHEAD(double v)  {m_nav_heading=v;};
  double m_nav_speed;
  void setNAVSPEED(double v)  {m_nav_speed=v;};

// Collaborator
  double m_colnav_x;
  void setCOLNAVX(double v)  {m_colnav_depth=v;};
  double m_colnav_y;
  void setCOLNAVY(double v)  {m_colnav_y=v;};
  double m_colnav_depth;
  void setCOLNAVDEPTH(double v)  {m_colnav_depth=v;};
  double m_colnav_heading;
  void setCOLNAVHEAD(double v)  {m_colnav_heading=v;};
  double m_colnav_speed;
  void setCOLNAVSPEED(double v)  {m_colnav_speed=v;};

  // Has S to denote string, set in Communication header file
  string m_collaborator_name;
  string m_Scolnav_x;
  string m_Scolnav_y;
  string m_Scolnav_depth;
  string m_Scolnav_heading;
  string m_Scolnav_speed;

  // report strings
  string m_acoustic_report;
  string  get_AReport();
  string m_connect_report;
  string  get_CReport();

  // Time related member variables
  double m_testtime;  // need to tell it to make this calculation every t secs
  void setTestTime(double v)  {m_testtime=v;};

// Functions for actually calculating the angles
   //void setDone(bool v)                     {m_done=v;};

   //bool   done() {return(m_done);};
  
   bool   findangle(); //calculate initial path here
   bool   pathfound(bool works); // test for path found 
   bool   findnewpath(); // find new path here

   // For saving output
    double m_newNAV_X;
    double m_newNAV_Y;
    double m_newDEPTH;
    double m_goodangle;
    double m_tloss;
    double m_theta0;
    double m_dist;
    double m_zmax;

 protected:

 };
 #endif 
