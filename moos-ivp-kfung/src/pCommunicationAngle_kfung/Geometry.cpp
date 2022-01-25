/************************************************************/
/*    NAME: Kat Fung                                              */
/*    ORGN: MIT, Cambridge MA                               */
/*    FILE: Geometry.cpp                                        */
/*    DATE: the night before its due out of desparation                           */
/************************************************************/

#include <iterator>
#include "MBUtils.h"
#include "ACTable.h"
#include <math.h> // needed for NaN
#include <cmath>
#include "Geometry.h"
#include <iostream>
#include <sstream> //needed for stringstream
#include <string>
#include <tgmath.h>
#define _USE_MATH_DEFINES

using namespace std;

//---------------------------------------------------------
// Constructor
Geometry::Geometry()
{


}
// Destructor

bool Geometry::findangle()
{
  // NEED TO ACCOUNT FOR HOW much time between tests? how???
  // Math for null line 
  double znull= -m_surfacess/m_ssgrad;              //znull
  double cz = m_surfacess + (m_ssgrad*m_nav_depth); // this is the soundspeed at navdepth
  double nan;


    // variables for use in math

  double s_arc;   // arc length
  bool works;
  
  // Step One: Calculate distance, midpoints, and range
  double dist = sqrt(pow(m_colnav_x-m_nav_x,2)+pow(m_colnav_y-m_nav_y,2)+pow(m_colnav_depth-m_nav_depth,2));
  double xhalf = ((m_nav_x+m_colnav_x)/2);
  double yhalf = ((m_nav_y+m_colnav_y)/2);
  double zhalf = ((m_nav_depth+m_colnav_depth)/2);
  double rhalf = sqrt(pow(xhalf-m_nav_x,2)+pow(yhalf-m_nav_y,2));
  double delta_r = sqrt(pow(m_colnav_x-m_nav_x,2)+pow(m_colnav_y-m_nav_y,2)); //distance in xy plane only
  double delta_z = abs(m_nav_depth-m_colnav_depth);

  // Step two: find the angle between the bisector and vertical, gamma
  double gamma = atan2(delta_z,delta_r);           // gamma calc
  double CM = zhalf/cos(gamma);                    // length from cicle center to bisector
  double Radius = sqrt(pow(dist/2,2)+pow(CM,2));   //Pythagorean for Radius
  cout<< "Radius found:" << Radius;

  // Step three: now that we know Radius, make sure it doesn't hit zmax
  double theta0 = acos((znull+zhalf)/Radius);                          // calculate theta i rad
  double thetadeg = theta0*180/3.14159269;                             // convert to deg, idc pi
  cout<<"angle found: "<< thetadeg;
  m_zmax = (cz/(m_ssgrad*cos(theta0)))-(m_surfacess/m_ssgrad);    // zmax
  m_tloss = 20*log10(dist);                                             //tloss estimate

   if(m_zmax>=m_wdepth)  // now see if we can end here or not
    {
      return false; //set the entirety of findangle to false
    }

    return findangle(); // findangle will be true if the initial value worked, false if not
}

bool Geometry::pathfound(bool works) // this takes the bool works and processes off of that
{
if(works == false)
  { 
    return false;   // that path won't work
    cout<<"No Path Found, runfindnewpath";
    //Notify("ACOUSTIC PATH", nan);
    // Time to calculate a new position using the collaborator's location
  }
  
  else if(works == true)
  {
    return true;
    cout<<"Path Found!";
    m_goodangle = m_theta0;   // set goodangle to theta0
    m_tloss = 20*log10(m_dist);    // calculate tloss (this works for spherical)
    //tloss = 40*log10(dist);     // an appx placeholder
    m_newNAV_X = m_nav_x;         // saves for Creport function
    m_newNAV_Y = m_nav_y;         // saves for Creport function
    m_newDEPTH = m_nav_depth;      // saves for Creport function
  }

    return Geometry::pathfound();
}

bool Geometry::findnewpath()
{
// OKAY SO I DO NOT UNDERSTAND, but.. here we go!
double newRadius = m_zmax;
    // Find the new location of the collaborater
    // Make a radius back from them
    // We know their depth, calculate
    // go find the original theta
return Geometry::findpath();
}

string Geometry::get_AReport()
{
  // Building Acoustic Path string
  stringstream ss_acoustic;                                    //create a stringstream of strings
  ss_acoustic<<"elev_angle="<<m_goodangle<<"; ";
  ss_acoustic<<"transmission_loss="<<m_tloss<<"; ";
  ss_acoustic<<"id=kfung@mit.edu";
  m_acoustic_report=ss_acoustic.str();                   // put it all together
  return m_acoustic_report;

}

string Geometry::get_CReport()
{
  // Building Connetivity location string
  stringstream ss_connect;                                    //create a stringstream of strings
  ss_connect<<"x="<<m_newNAV_X<<"; ";
  ss_connect<<"y="<<m_newNAV_Y<<"; ";
  ss_connect<<"depth="<<m_newDEPTH<<"; ";
  ss_connect<<"id=kfung@mit.edu";
  m_connect_report=ss_connect.str();                   // put it all together
  return m_connect_report;

}

// Should I make ANOTHER Function to handle transmission loss? Or just calculate within