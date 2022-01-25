
/************************************************************/
/*    NAME: Kat Fung                                              */
/*    ORGN: MIT, Cambridge MA                               */
/*    FILE: GenPath.cpp                                        */
/*    DATE: April 8, 2021                            */
/************************************************************/

#include <iterator>
#include "MBUtils.h"
#include "ACTable.h"
#include "GenPath.h"
#include "XYSegList.h"
#include "VisitPoint.h"
#include "XYPoint.h"
#include <cmath>
#include <algorithm>
#include <iostream>
#include <vector>
#include <iterator>
#include <string>
#include <stdlib.h>

using namespace std;

//---------------------------------------------------------
// Constructor

GenPath::GenPath()
{
  m_min = 1000000; // initizalize min dist
  m_allpointsreceived = false;
  m_regenerate = false;
}

//---------------------------------------------------------
// Destructor

GenPath::~GenPath()
{
}

//---------------------------------------------------------
// Procedure: OnNewMail

bool GenPath::OnNewMail(MOOSMSG_LIST &NewMail)
{
  AppCastingMOOSApp::OnNewMail(NewMail);

  MOOSMSG_LIST::iterator p;
  for (p = NewMail.begin(); p != NewMail.end(); p++)
  {
    CMOOSMsg &msg = *p;
    string key = msg.GetKey();
    string sval = msg.GetString();
    double dval = msg.GetDouble();

#if 0 // Keep these around just for template
    string comm  = msg.GetCommunity();
    double dval  = msg.GetDouble();
    string sval  = msg.GetString();
    string msrc  = msg.GetSource();
    double mtime = msg.GetTime();
    bool   mdbl  = msg.IsDouble();
    bool   mstr  = msg.IsString();
#endif

    if (key == "FOO")
      cout << "great!";

    else if (key == "VISIT_POINT")
    {
      // the first entry of tsppoints is the startpos

      m_tsppoints.push_back(sval); // these are strings, initial order
      //cout << "sval is:" << sval;

      // this should give us all converted points

      // Run Function FindShortestPath
      if (sval == "lastpoint")
      {
        m_allpointsreceived = true;
        ConvertPoint();
        cout << "Lastpoint received" << endl;
      }
    }

    else if (key == "NAV_X")
    {
      m_xpoint = dval;
      
    }
    else if (key == "NAV_Y")
    {
      m_ypoint = dval;
      
    }

    else if (key == "GENPATH_REGENERATE")
    {
      if (sval == "true")
      {
        m_regenerate = true;
      }

      else if (sval == "false")
      {
        m_regenerate = false;
      }
    }
    else if (key != "APPCAST_REQ") // handled by AppCastingMOOSApp
      reportRunWarning("Unhandled Mail: " + key);
  }

  return (true);
}

//---------------------------------------------------------
// Procedure: ConvertPoint (Works to convert String to integers)
bool GenPath::ConvertPoint()
{
  vector<string>::iterator jj;
  for (jj = m_tsppoints.begin(); jj != m_tsppoints.end(); jj++)
  {
    string msg = *jj;
    if (msg == "firstpoint" || msg == "lastpoint")
    {
      // Cool, do nothing
      return (true);
      continue; //move on
    }

    // This is a list of STRINGS not INTS

    string pointstring = msg; // the whole "x=num, y=num, id=num"

    // use biteStringX to break up around commas
    // saves the front half as xstring, pointstring is now "y=num, id=num"
    string xstring = biteStringX(pointstring, ','); // pointstring left with "y=num, id=num"
    string ystring = biteStringX(pointstring, ','); // pointstring left with "id=num"
    string idstring = pointstring;                  // set the last piece to idstring

    // use bitStringX to break up around = sign
    string xstr = biteStringX(xstring, '=');   //xstring now contains the num
    string ystr = biteStringX(ystring, '=');   //ystring now contains the num
    string idstr = biteStringX(idstring, '='); //idstring now contains the num

    // turn the strings into doubles, variables defined above
    //cout<<xstring<<endl;
    //cout<<ystring<<endl;
    double x = atof(xstring.c_str());
    double y = atof(ystring.c_str());
    int idnum = atof(idstring.c_str());
    //cout << "converted xstring and ystring to doubles" << endl;
    string label = idstring; // he gets to stay a string

    XYPoint point(x, y);
    point.set_label(label);

    // Save that x,y in an unordered list of xy points
    m_xypointsort.push_back(point);
    m_seglist.add_vertex(point, label);
    //cout << "Size of XYPointsort is: " << m_xypointsort.size();
  }
  return (true);
};

//---------------------------------------------------------
// Procedure: OnConnectToServer

bool GenPath::OnConnectToServer()
{
  registerVariables();
  return (true);
}

//---------------------------------------------------------
// Procedure: Iterate()
//            happens AppTick times per second

bool GenPath::Iterate()
{
  AppCastingMOOSApp::Iterate();
  // Do your thing here!
  int s;
  int next;
  XYSegList seglist_copy = m_seglist;
  if (m_allpointsreceived == true)
  {
    for (s = 0; s < seglist_copy.size(); s++)
    {
      double x1 = seglist_copy.get_vx(s);
      double y1 = seglist_copy.get_vy(s);
      int index = seglist_copy.closest_vertex(x1, y1);
      Notify("DISTANCE_DEBUG", index);
      m_sorted_index.push_back(index);
    }

    // Run the function that allocates index to XYseglist points
    FindShortestPath();

    // Run the function that converts to sorted to
    // string and notifies waypoints variable
    NotifyTSPUpdates();
    m_allpointsreceived = false; // reset our flag to false
  }

  // Continuously Run CheckPoints to see if points are passed
  CheckPoints();

  // Check for Regeneration
  if (m_regenerate == true)
  {

    // Notify Regen Updates
    NotifyRegenUpdates();

    // endflag to stop from doing
    m_regenerate = false;
  }
  // When loop is done, then run the notify

  AppCastingMOOSApp::PostReport();
  return (true);
}

//---------------------------------------------------------
// Procedure: FindShortestPath (Doesn't Work But WHATEVER i wasted 2 weeks on it)

bool GenPath::FindShortestPath()
{
  // The purpose of this block is to generate a path of least resistance
  cout << "Running FindShortestPath" << endl;
  // ORIGINAL XYPoint: m_xypointsort / XYSegList m_seglist
  // FINAL XYSeglist: m_sorted
  // m_sorted: where the sorted points go

  //distance , shortest (holds shortest path)
  // output m_sorted to the seglist

  for (int ii = 0; ii < m_sorted_index.size(); ii++)
  {
    int num = m_sorted_index[ii];
    double x1 = m_seglist.get_vx(num);
    double y1 = m_seglist.get_vy(num);
    m_sorted.add_vertex(x1, y1);
    Notify("DISTANCE_DEBUG", "in FindShortestPath");
  }

  m_not_explored = m_sorted;
  return (true);

}; //end of class

//---------------------------------------------------------
// Procedure: Distance
double GenPath::DistanceCalc(XYPoint point1, XYPoint point2)
{
  double x1 = point1.x();
  double y1 = point1.y();
  double x2 = point2.x();
  double y2 = point2.y();
  double xdist = pow(x2 - x1, 2);
  double ydist = pow(y2 - y1, 2);
  double dist = sqrt(xdist + ydist);
  return (dist);
};

//---------------------------------------------------------
// Procedure: NotifyTSPUpdates
bool GenPath::NotifyTSPUpdates()
{
  // pass the FINAL order to m_sorted
  // Change to strings
  string updatestring = "points = ";
  updatestring += m_sorted.get_spec();
  Notify("FINDPATH_DEBUG2", "Notified TSP_Updates");

  // Notify TSP_UPDATES
  Notify("TSP_UPDATES", updatestring);

  return (true);
};

//---------------------------------------------------------
// Procedure: CheckPoints()
bool GenPath::CheckPoints()
{
  cout << "regenerating path" << endl;
  double visit_radius = 5;
  bool pointfound = false;
  int indextodelete;

  for (int ii = 0; ii < m_not_explored.size(); ii++)
  {
    // Get the x and y point from pPointAssign
    double x1 = m_not_explored.get_vx(ii);
    double y1 = m_not_explored.get_vy(ii);
    
    double dist = sqrt(pow(x1-m_xpoint,2)+pow(y1-m_ypoint,2));

    if (dist < 5) // if the differnce between ys is less than five
    {
      //point passed
      pointfound = true;
      indextodelete = ii;
    }

    Notify("DISTANCE_DEBUG", "Added Point to Regen list");
  }
  
      // if neither value was found during above for loops
    if (pointfound = true)
    {
      m_not_explored.delete_vertex(indextodelete);
    }

  return (true);
};

//---------------------------------------------------------
// Procedure: NotifyRegenUpdates()
bool GenPath::NotifyRegenUpdates()
{
  // pass the FINAL order to m_sorted
  // Change to strings
  if (m_not_explored.size() == 0)
  {
    Notify("FINDPATH_DEBUG2", "All points passed");
  }

  else
  {
    string updatestring = "points = ";
    updatestring += m_not_explored.get_spec();
    Notify("FINDPATH_DEBUG2", "Notified REGEN_Updates");

    // Notify TSP_UPDATES
    Notify("REGEN_UPDATES", updatestring);
  }

  return (true);
};

//---------------------------------------------------------
// Procedure: OnStartUp()
//            happens before connection is open

bool GenPath::OnStartUp()
{
  AppCastingMOOSApp::OnStartUp();

  STRING_LIST sParams;
  m_MissionReader.EnableVerbatimQuoting(false);
  if (!m_MissionReader.GetConfiguration(GetAppName(), sParams))
    reportConfigWarning("No config block found for " + GetAppName());

  STRING_LIST::iterator p;
  for (p = sParams.begin(); p != sParams.end(); p++)
  {
    string orig = *p;
    string line = *p;
    string param = tolower(biteStringX(line, '='));
    string value = line;

    bool handled = false;
    if (param == "foo")
    {
      handled = true;
    }
    else if (param == "bar")
    {
      handled = true;
    }
    else if (param == "start_pos")
    {
      // WHY IS THE OTHER VEHICLE GOING HERE (0,0)
      m_startpos = value;                       //save the start position
      string xstring = biteStringX(value, ','); // value keeps the y value
      double x = atof(xstring.c_str());
      double y = atof(value.c_str());
      XYPoint point(x, y);
      m_xypointsort.push_back(point);
      m_seglist.add_vertex(x, y);

      handled = true;
    }

    if (!handled)
      reportUnhandledConfigWarning(orig);
  }

  registerVariables();
  return (true);
}

//---------------------------------------------------------
// Procedure: registerVariables

void GenPath::registerVariables()
{
  AppCastingMOOSApp::RegisterVariables();
  // Register("FOOBAR", 0);
  // There should be one generated for EACH vehicle
  Register("VISIT_POINT", 0);
  Register("NAV_X", 0);
  Register("NAV_Y", 0);
  Register("GENPATH_REGENERATE", 0);
}

//------------------------------------------------------------
// Procedure: buildReport()

bool GenPath::buildReport()
{
  m_msgs << "============================================" << endl;
  m_msgs << "File: GenPath.cpp                                      " << endl;
  m_msgs << "============================================" << endl;

  ACTable actab(4);
  actab << "Trying to generate a path";
  actab.addHeaderLines();
  actab << "Path Generated!";
  m_msgs << actab.getFormattedString();

  return (true);
}
