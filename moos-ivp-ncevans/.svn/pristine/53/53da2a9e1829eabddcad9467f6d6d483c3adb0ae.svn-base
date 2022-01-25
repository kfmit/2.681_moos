/************************************************************/
/*    NAME: Craig Evans                                              */
/*    ORGN: MIT, Cambridge MA                               */
/*    FILE: Odometry.cpp                                        */
/*    DATE: December 29th, 1963                             */
/************************************************************/

#include <iterator>
#include <math.h>
#include "MBUtils.h"
#include "ACTable.h"
#include "Odometry.h"

using namespace std;

//---------------------------------------------------------
// Constructor

Odometry::Odometry()
{
  m_first_reading=true;
  m_current_x=0;
  m_current_y=0;
  m_previous_x=0;
  m_previous_y=0;
  m_total_distance=0;
}

//---------------------------------------------------------
// Destructor

Odometry::~Odometry()
{
}
//The addDistance function calculates distance from every x y
void Odometry::addDistance(double x_point, double y_point)
{
  //
  m_previous_x=m_current_x;
  m_previous_y=m_current_y;
  m_current_x=x_point;
  m_current_y=y_point;
  if(m_first_reading){
    m_first_reading=false;
  }
  else{
    double x_dist=abs(m_current_x-m_previous_x);
    double y_dist=abs(m_current_y-m_previous_y);
    double current_distance=sqrt((y_dist*y_dist)+(x_dist*x_dist));
    m_total_distance=m_total_distance+current_distance;
  }

}
//---------------------------------------------------------
// Procedure: OnNewMail

bool Odometry::OnNewMail(MOOSMSG_LIST &NewMail)
{
  AppCastingMOOSApp::OnNewMail(NewMail);


  bool got_x =false;
  bool got_y =false;
  double current_x=0;
  double current_y=0;
  MOOSMSG_LIST::iterator p;
  for(p=NewMail.begin(); p!=NewMail.end(); p++) {
    CMOOSMsg &msg = *p;
    string key    = msg.GetKey();
    double dval  = msg.GetDouble();
    if (key=="NAV_X"){
      current_x=dval;
      got_x =true;
    }
    else if (key=="NAV_Y"){
      current_y=dval;
      got_y=true;
    }

    else if(key != "APPCAST_REQ") // handled by AppCastingMOOSApp
       reportRunWarning("Unhandled Mail: " + key);
    //if an update for x and y call addDistance
    if (got_x && got_y){
      addDistance(current_x,current_y);
      got_x=false;
      got_y=false;
    }
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
//            happens AppTick times per second

bool Odometry::Iterate()
{
  AppCastingMOOSApp::Iterate();
  //The iterate loop used just for notification of distance
  if (!m_first_reading)
    Notify("ODOMETRY_DIST",m_total_distance);



  
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

  Register("NAV_X",0);
  Register("NAV_Y",0);
}



//------------------------------------------------------------
// Procedure: buildReport()

bool Odometry::buildReport() 
{
  m_msgs << "============================================" << endl;
  m_msgs << "File:                                       " << endl;
  m_msgs << "============================================" << endl;
  //publish the distance for debugging
  ACTable actab(2);
  actab << "Value | Distance";
  actab.addHeaderLines();
  actab << "distance" << m_total_distance;
  m_msgs << actab.getFormattedString();

  return(true);
}




