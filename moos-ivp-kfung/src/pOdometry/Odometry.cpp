/************************************************************/
/*    NAME: kfung                                              */
/*    ORGN: MIT, Cambridge MA                               */
/*    FILE: Odometry.cpp                                        */
/*    DATE: December 29th, 1963                             */
/************************************************************/

#include <iterator>
#include <cmath>
#include "MBUtils.h"
#include "ACTable.h"
#include "Odometry.h"

using namespace std;

//---------------------------------------------------------
// Constructor

Odometry::Odometry()
{
  // setting initial values for the variables we established in the Odometry.h
  m_first_reading = true; //this is true for the first bit, until we set it to false
  m_current_x = 0;
  m_current_y = 0;
  m_previous_x = 0;
  m_previous_y = 0;
  m_total_distance = 0;
}

//---------------------------------------------------------
// Destructor

Odometry::~Odometry()
{
}

//---------------------------------------------------------
// Procedure: OnNewMail

bool Odometry::OnNewMail(MOOSMSG_LIST &NewMail)
{
  AppCastingMOOSApp::OnNewMail(NewMail);

  MOOSMSG_LIST::iterator p;
  for(p=NewMail.begin(); p!=NewMail.end(); p++) {
    CMOOSMsg &msg = *p;
    // Pull mail and set variables
    
    string key    = msg.GetKey(); //key is key
    
    double dvalue = msg.GetDouble(); //this also exists below, renaming for my clarification
    
    if (key=="NAV_X"){ // if key from msg is NAV_X...
      m_previous_x = m_current_x; //set the current value to the old value
      m_current_x = dvalue; //update to the new value
      }
    else if (key=="NAV_Y"){ // if key from msg is NAV_Y... see above
			     m_previous_y = m_current_y;
			     m_current_y = dvalue;
      }
      
#if 0 // Keep these around just for template
    // string comm  = msg.GetCommunity();
    //double dvalue  = msg.GetDouble();
    //string sval  = msg.GetString(); 
    //string msrc  = msg.GetSource();
    //double mtime = msg.GetTime();
    // bool   mdbl  = msg.IsDouble();
    // bool   mstr  = msg.IsString();
#endif

    // if(key == "FOO") 
    // cout << "great!";

     else if(key != "APPCAST_REQ") // handled by AppCastingMOOSApp
       reportRunWarning("Unhandled Mail: " + key);
   }
	
   return(true);
}

//---------------------------------------------------------
// Procedure: OnConnectToServer

bool Odometry::OnConnectToServer()
{
   registerVariables();
   return(true);
}

//---------------------------------------------------------
// Procedure: Iterate()
//            happens AppTick times per second [Do I control AppTick?]

bool Odometry::Iterate()
{
  AppCastingMOOSApp::Iterate();
  double xdist=0; //creating new variables to make math nice
  double ydist=0;
  double cdist=0;
  
  if(m_first_reading)
    { //so if m_first reading is true
      m_first_reading=false; //now it is not the first reading anymore ever
    }
  else
    {
      xdist = pow(m_current_x-m_previous_x,2);
      ydist = pow(m_current_y-m_previous_y,2);
      cdist = sqrt(xdist+ydist);
      m_total_distance = m_total_distance+cdist;
      Notify("ODOMETRY_DIST",m_total_distance);
    }
  // Do your thing here!
    



    
  AppCastingMOOSApp::PostReport();
  
  return(true);
}

//---------------------------------------------------------
// Procedure: OnStartUp()
//            happens before connection is open

bool Odometry::OnStartUp()
{
  AppCastingMOOSApp::OnStartUp();

  STRING_LIST sParams;
  m_MissionReader.EnableVerbatimQuoting(false);
  if(!m_MissionReader.GetConfiguration(GetAppName(), sParams))
    reportConfigWarning("No config block found for " + GetAppName());

  STRING_LIST::iterator p;
  for(p=sParams.begin(); p!=sParams.end(); p++) {
    string orig  = *p;
    string line  = *p;
    string param = tolower(biteStringX(line, '='));
    string value = line;

    bool handled = false;
    if(param == "foo") {
      handled = true;
    }
    else if(param == "bar") {
      handled = true;
    }

    if(!handled)
      reportUnhandledConfigWarning(orig);

  }
  
  registerVariables();	
  return(true);
}

//---------------------------------------------------------
// Procedure: registerVariables

void Odometry::registerVariables()
{
  AppCastingMOOSApp::RegisterVariables();
  // Register("FOOBAR", 0);
  Register("NAV_X", 0); // THIS HAS TO BE 0 OR IT MESSES UP THE WHOLE THING
 Register("NAV_Y", 0);
  
}


//------------------------------------------------------------
// Procedure: buildReport()

bool Odometry::buildReport() 
{
  m_msgs << "============================================" << endl;
  m_msgs << "File:                                       " << endl;
  m_msgs << "============================================" << endl;

  ACTable actab(2);
  actab << "Value | Distance";
  actab.addHeaderLines();
  actab << "distance" << m_total_distance;
  m_msgs << actab.getFormattedString();

  return(true);
}





