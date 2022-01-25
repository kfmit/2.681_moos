/************************************************************/
/*    NAME: Kat Fung                                              */
/*    ORGN: MIT, Cambridge MA                               */
/*    FILE: CommunicationAngle_kfung.h                                          */
/*    DATE: December 29th, 1963                             */
/************************************************************/

#ifndef CommunicationAngle_kfung_HEADER
#define CommunicationAngle_kfung_HEADER

#include "MOOS/libMOOS/Thirdparty/AppCasting/AppCastingMOOSApp.h"
#include "Geometry.h"
#include <string>

using namespace std;

class CommunicationAngle_kfung : public AppCastingMOOSApp
{
 public:
   CommunicationAngle_kfung();
   ~CommunicationAngle_kfung();
  
  // our class
  Geometry m_angletest;

  // These are the Configuration Parameters for determining Ray Tracing
  double m_surfacess;
  double m_ssgrad;
  double m_wdepth;
  string m_vehicle_name;
  
// Own Ship
  double m_nav_x;
  double m_nav_y;
  double m_nav_depth;
  double m_nav_heading;
  double m_nav_speed;

// Collaborator
  double m_colnav_x;
  double m_colnav_y;
  double m_colnav_depth;
  double m_colnav_heading;
  double m_colnav_speed;
  // Has S to denote string
  string m_collaborator_name;
  string m_Scolnav_x;
  string m_Scolnav_y;
  string m_Scolnav_depth;
  string m_Scolnav_heading;
  string m_Scolnav_speed;

  // report strings
  string m_acoustic_report;
  string m_connect_report;


  // Time related member variables
  double m_testtime;  // need to tell it to make this calculation every t secs

 protected: // Standard MOOSApp functions to overload  
   bool OnNewMail(MOOSMSG_LIST &NewMail);
   bool Iterate();
   bool OnConnectToServer();
   bool OnStartUp();

 protected: // Standard AppCastingMOOSApp function to overload 
   bool buildReport();

 protected:
   void registerVariables();

 private: // Configuration variables

 private: // State variables
};

#endif 
