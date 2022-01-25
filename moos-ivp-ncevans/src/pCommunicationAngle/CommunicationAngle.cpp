/************************************************************/
/*    NAME: Craig Evans                                              */
/*    ORGN: MIT, Cambridge MA                               */
/*    FILE: CommunicationAngle.cpp                                        */
/*    DATE: December 29th, 1963                             */
/************************************************************/

#include <iterator>
#include "MBUtils.h"
#include "ACTable.h"
#include "CommunicationAngle.h"
#include <sstream>
#include <list>
#include <string>
#include <math.h>
#include "VehicleComms.h"

using namespace std;

//---------------------------------------------------------
// Constructor

CommunicationAngle::CommunicationAngle()
{
  VehicleComms m_vehicle_com;
  m_got_new=true;
}

//---------------------------------------------------------
// Destructor

CommunicationAngle::~CommunicationAngle()
{
}






//---------------------------------------------------------
// Procedure: OnNewMail

bool CommunicationAngle::OnNewMail(MOOSMSG_LIST &NewMail)
{
  AppCastingMOOSApp::OnNewMail(NewMail);

  MOOSMSG_LIST::iterator p;
    bool got1=false;
    bool got2=false;
    bool got3=false;
  for(p=NewMail.begin(); p!=NewMail.end(); p++) {
    CMOOSMsg &msg = *p;
    string key    = msg.GetKey();
    double dval  = msg.GetDouble();
 
    if(key == "COLLABORATOR_NAME"){
      string sval  = msg.GetString();
      stringstream name;
      name<<sval<<"_";
      m_collab_name=name.str();
      m_collab_x=m_collab_name+"NAV_X";
      m_collab_y=m_collab_name+"NAV_Y";
      m_collab_depth=m_collab_name+"NAV_DEPTH";
      m_collab_heading=m_collab_name+"NAV_HEADING";
      m_collab_speed=m_collab_name+"NAV_SPEED";
      Register(m_collab_x);
      Register(m_collab_y);
      Register(m_collab_speed);
      Register(m_collab_depth);
      Register(m_collab_heading);          
    }
    else if (key=="NAV_X")
      m_vehicle_com.m_os_x=dval;
    else if (key=="VEHICLE_NAME"){
      string sval  = msg.GetString();
      m_vehicle_com.m_os_name=sval;
    }
    else if (key=="NAV_Y")
      m_vehicle_com.m_os_y=dval;
    else if (key=="NAV_DEPTH")
      m_vehicle_com.m_os_depth=dval;
    else if (key=="NAV_HEADING")
     m_vehicle_com. m_os_heading=dval;
    else if (key=="NAV_SPEED")
      m_vehicle_com.m_os_speed=dval;
    else if (key==m_collab_x){
      got2=true;
      m_vehicle_com.m_collab_xval=dval;
    }
    else if (key==m_collab_y){
      m_vehicle_com.m_collab_yval=dval;
      got3=true;
    }
    else if (key==m_collab_depth){
     m_vehicle_com.m_collab_depthval=dval;
     got1=true;
    }
    else if (key==m_collab_speed)
      m_vehicle_com.m_collab_speedval=dval;
    else if (key==m_collab_heading)
      m_vehicle_com.m_collab_headval=dval; 
    else if(key != "APPCAST_REQ") {// handled by AppCastingMOOSApp
       reportRunWarning("Unhandled Mail: " + key);
    }
      //m_vehicle_com.m_deltaz=m_vehicle_com.getDeltaZ();
    m_got_new=true;

   }

   return(true);
}

//---------------------------------------------------------
// Procedure: OnConnectToServer

bool CommunicationAngle::OnConnectToServer()
{
   registerVariables();
   return(true);
}

//---------------------------------------------------------
// Procedure: Iterate()
//            happens AppTick times per second

bool CommunicationAngle::Iterate()
{
  AppCastingMOOSApp::Iterate();
  // Do your thing here!
  bool got_omega=m_vehicle_com.getOmega();
  bool acoustic_path=m_vehicle_com.getMessage(got_omega); 
  Notify("ACOUSTIC_PATH",m_vehicle_com.m_acoustic_path);
  Notify("CONNECTIVITY_LOCATION",m_vehicle_com.m_connectivity_loc);
  //m_got_new=false;
 
  AppCastingMOOSApp::PostReport();
  return(true);
}

//---------------------------------------------------------
// Procedure: OnStartUp()
//            happens before connection is open

bool CommunicationAngle::OnStartUp()
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
    if(!handled)
      reportUnhandledConfigWarning(orig);

  }
  
  registerVariables();	
  return(true);
}

//---------------------------------------------------------
// Procedure: registerVariables

void CommunicationAngle::registerVariables()
{
  AppCastingMOOSApp::RegisterVariables();
  // Register("FOOBAR", 0);
  Register("VEHICLE_NAME");
  Register("COLLABORATOR_NAME");
  Register("NAV_X");
  Register("NAV_Y");
  Register("NAV_DEPTH");
  Register("NAV_HEADING");
  Register("NAV_SPEED");
}


//------------------------------------------------------------
// Procedure: buildReport()

bool CommunicationAngle::buildReport() 
{
  m_msgs << "============================================" << endl;
  m_msgs << "File:                                       " << endl;
  m_msgs << "============================================" << endl;

  ACTable actab(4);
  actab << "COLLAB | OS_NAME | COLLAB_y | m_nav_r";
  actab.addHeaderLines();
  actab << m_collab_name<< m_os_name << m_collab_y<<m_vehicle_com.m_nav_r;
  m_msgs << actab.getFormattedString();

  return(true);
}




