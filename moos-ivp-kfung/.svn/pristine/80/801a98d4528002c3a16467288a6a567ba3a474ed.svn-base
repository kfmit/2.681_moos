/************************************************************/
/*    NAME: Kat Fung                                              */
/*    ORGN: MIT, Cambridge MA                               */
/*    FILE: CommunicationAngle_kfung.cpp                                        */
/*    DATE: December 29th, 1963                             */
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

using namespace std;

//---------------------------------------------------------
// Constructor

CommunicationAngle_kfung::CommunicationAngle_kfung()
{
  m_surfacess = 0;
  m_ssgrad = 0;
  m_wdepth = 0;
  m_testtime = 0;
}

//---------------------------------------------------------
// Destructor

CommunicationAngle_kfung::~CommunicationAngle_kfung()
{
}

//---------------------------------------------------------
// Procedure: OnNewMail

bool CommunicationAngle_kfung::OnNewMail(MOOSMSG_LIST &NewMail)
{
  AppCastingMOOSApp::OnNewMail(NewMail);

  MOOSMSG_LIST::iterator p;
  for(p=NewMail.begin(); p!=NewMail.end(); p++) {
    CMOOSMsg &msg = *p;
    string key    = msg.GetKey();
    double dval  = msg.GetDouble();
    string sval  = msg.GetString();

#if 0 // Keep these around just for template
    string comm  = msg.GetCommunity();
    double dval  = msg.GetDouble();
    string sval  = msg.GetString(); 
    string msrc  = msg.GetSource();
    double mtime = msg.GetTime();
    bool   mdbl  = msg.IsDouble();
    bool   mstr  = msg.IsString();
#endif
    //create instance of class Geometry and pass in variables to the class
    Geometry findangle;                     // new class called findangle

    if(key == "surface_sound_speed")       // Time to pick up the mail
    { 
      m_angletest.setSurfaceSpeed(dval);                   // set variable surfacess}
    }
    else if(key == "sound_speed_gradient") // if it's sound_speed_gradient
      {
         m_angletest.setSSGrad(dval);
      }                     // set ssgrad to dval
    else if(key == "water_depth")         // if key is water_depth
      {
          m_angletest.setWaterDepth(dval);
      }
    else if(key == "time_interval")        // if key is time interval
      {
          m_angletest.setTestTime(dval); 
      }                  // set testtime

      //Now looking for all the MOOSDB variables for OwnShip
    else if(key == "VEHICLE_NAME") 
        {
          m_angletest.setvehiclename(sval);
        }
    else if(key == "NAV_X") 
        {
          m_angletest.setNAVX(dval);
        }
    else if(key == "NAV_Y")
        {
          m_angletest.setNAVY(dval);
        }
    else if(key == "NAV_DEPTH")
        {
          m_angletest.setNAVDEPTH(dval);
        }
    else if(key == "NAV_HEADING")
        {
          m_angletest.setNAVHEAD(dval);
          }
    else if(key == "NAV_SPEED")
        {
          m_angletest.setNAVSPEED(dval);
        }

      // Now looking for collab name and register for those
    else if(key == "COLLABORATOR_NAME")
    {
      m_collaborator_name = sval;
     // Set the names for the collab variables
      m_Scolnav_x = m_collaborator_name+"_NAV_X";
      Register(m_Scolnav_x,0);
      m_Scolnav_y = m_collaborator_name+"_NAV_Y";
      Register(m_Scolnav_y,0);
      m_Scolnav_depth = m_collaborator_name+"_NAV_DEPTH";
      Register(m_Scolnav_depth,0);
      m_Scolnav_heading = m_collaborator_name+"_NAV_HEADING";
      Register(m_Scolnav_heading,0);
      m_Scolnav_speed = m_collaborator_name+"_NAV_SPEED";
      Register(m_Scolnav_speed,0);
    }
      // Now looking for the collab variables
    else if(key == m_Scolnav_x)
      {
        m_angletest.setCOLNAVX(dval);
      }
    else if(key == m_Scolnav_y)
      {
        m_angletest.setCOLNAVDEPTH(dval);
      }
    else if(key == m_Scolnav_depth)
      {
        m_angletest.setCOLNAVDEPTH(dval);
      }
    else if(key == m_Scolnav_heading)
     {
       m_angletest.setCOLNAVHEAD(dval);
     }
    else if(key == m_Scolnav_speed)
      {
        m_angletest.setCOLNAVSPEED(dval);
      }


    else if(key != "APPCAST_REQ") // handled by AppCastingMOOSApp
       reportRunWarning("Unhandled Mail: " + key);
   }
	
   return(true);
}

//---------------------------------------------------------
// Procedure: OnConnectToServer

bool CommunicationAngle_kfung::OnConnectToServer()
{
   registerVariables();
   return(true);
}

//---------------------------------------------------------
// Procedure: Iterate()
//            happens AppTick times per second

bool CommunicationAngle_kfung::Iterate()
{
  AppCastingMOOSApp::Iterate();
  // Doing my thing here!

  // First, check if a initial path was made
  m_angletest.findangle();    //run function findangle
  cout<<"Running findangle";
  Notify("DEBUG",1);          // just to check if findangle is running

  if(m_angletest.findangle() == true) // if the first find angle function of geometry works
  {
  cout<<"original position worked"; //this means findangle has run and is called
  m_angletest.pathfound(true);    // run the pathfound function under true
  }


  else // If the originally calculated radius doesnt bottom out
  {
    m_angletest.pathfound(false);   // Run pathfound as FALSE
             //great, works is true

  m_angletest.findnewpath(); // Run find newpath

  }

 // Make a new tloss function or calculate within each thing

  // Call in reports from geometry
  string the_acoustic_report=m_angletest.get_AReport();   // just praying these saved
  string the_connect_report=m_angletest.get_CReport();    // still praying

  // Once a path has or has not been found, notify the MOOS
  // Notify every testtime times

  // line to do time???
  Notify("ACOUSTIC_PATH", the_acoustic_report);
  Notify("CONNECTIVITY_LOCATION", the_connect_report);


  AppCastingMOOSApp::PostReport();
  return(true);
}

//---------------------------------------------------------
// Procedure: OnStartUp()
//            happens before connection is open

bool CommunicationAngle_kfung::OnStartUp()
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

void CommunicationAngle_kfung::registerVariables()
{
  AppCastingMOOSApp::RegisterVariables();
  // Register("FOOBAR", 0);
  // This is where I am registering to pick up vars from MOOS
  Register("VEHICLE_NAME", 0);
  Register("COLLABORATOR_NAME", 0);
  Register("NAV_X", 0);
  Register("NAV_Y", 0);
  Register("NAV_DEPTH", 0);
  Register("NAV_HEADING", 0);
  Register("NAV_SPEED", 0);
  // Register("'collaborator'_NAV_X", 0);
  // Register("'collaborator'_NAV_Y", 0);
  // Register("'collaborator'_NAV_DEPTH", 0);
  // Register("'collaborator'_NAV_HEADING", 0);
  // Register("'collaborator'_NAV_SPEED", 0);
}


//------------------------------------------------------------
// Procedure: buildReport()

bool CommunicationAngle_kfung::buildReport() 
{
  m_msgs << "============================================" << endl;
  m_msgs << "File: CommunicationAngle_kfung                                       " << endl;
  m_msgs << "============================================" << endl;

  ACTable actab(4);
  actab << "Acoustic Path is "<< m_acoustic_report;
  actab << "Connectivity Location is " <<m_connect_report;
  actab.addHeaderLines();

  return(true);
}




