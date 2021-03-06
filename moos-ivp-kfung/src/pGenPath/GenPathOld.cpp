
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
  m_min = 100000; // initizalize min dist
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
      cout << "Added Visit Point to List" << endl;

      cout << "Size is" << m_tsppoints.size();
      //cout << "sval is:" << sval;

      ConvertPoint(sval);
      cout << "Converting all Visit Points" << endl;
      // this should give us all converted points

      // Run Function FindShortestPath
      if(sval == "lastpoint")
      {
      Notify("FINDPATH_DEBUG", "Mail Complete, running FSP");
      FindShortestPath();
      }
      //cout << "Ran FindShortestPath function" << endl;
    }
    else if (key != "APPCAST_REQ") // handled by AppCastingMOOSApp
      reportRunWarning("Unhandled Mail: " + key);
  }

  return (true);
}

//---------------------------------------------------------
// Procedure: ConvertPoint
bool GenPath::ConvertPoint(string msg)
{
  // vector<string>::iterator jj;
  // for (jj = m_tsppoints.begin(); jj != m_tsppoints.end(); jj++)
  // {
  //   string msg = *jj;
  if (msg == "firstpoint" || msg == "lastpoint")
  {
    // Cool, do nothing
    return (true);
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
  cout << "converted xstring and ystring to doubles" << endl;
  string label = idstring; // he gets to stay a string

  XYPoint point(x, y);
  point.set_label(label);

  // Save that x,y in an unordered list of xy points
  m_xypointsort.push_back(point);
  cout << "Size of XYPointsort is: " << m_xypointsort.size();

  //}
  return (true);
};

// XYPoint GenPath::

//---------------------------------------------------------
// Procedure: FindShortestPath

bool GenPath::FindShortestPath()
{
  //#if 0
  // The purpose of this block is to generate a path of least resistance
  cout << "Running FindShortestPath" << endl;
  // m_xypointsort is a vector of XYpoints passed from Visit Point, UNORDERED

  /*
m_xypointsort = [A, B, C, D, E, F, G]

# iteration 0
m_sorted = []
m_not_explored = m_xypointsort

# iteration 1
m_sorted = [D]
m_not_explored = [B,C,E,F,G]

# iteration 2
m_sorted = [D, C]
m_not_explored = [B,E,F,G]



WE have a list of points
from A to D
calculate A-b, A-C, A-D
compare the distances, save the value of point that gives shortest distance
start the loop again from the saved point
erase the old point
*/

  m_sorted.clear();
  //m_sorted.push_back(m_xypointsort[0]);
  m_xypointsort.erase(m_xypointsort.begin());
  m_not_explored = m_xypointsort;
  m_not_explored.erase(m_not_explored.begin());
  vector<XYPoint>::iterator current = m_xypointsort.begin();
  for (int current_ct = 0; current_ct < m_xypointsort.size()-1; current_ct++)
  {
    double min_distance_to_current = 10e6; //Infinity
    vector<XYPoint>::iterator closest = m_not_explored.begin();
    // for (vector<XYPoint>::iterator next = m_xypointsort.begin(); next != m_xypointsort.end(); next++){
    for (vector<XYPoint>::iterator nextpoint = m_not_explored.begin(); nextpoint != m_not_explored.end(); ++nextpoint)
    {
      // if (nextpoint == current_ct)
      // {
      //   continue; //get outta the loop
      // }

      //else
      //{
        double distance = DistanceCalc(current->x(), nextpoint->x(), current->y(), nextpoint->y());

        if (distance < min_distance_to_current)
        {
          Notify("DISTANCE_DEBUG",distance);
          min_distance_to_current = distance;
          closest = nextpoint;
          // set next as next point from current_ct
          // in sorted ones
        }

      //}
    }
    m_not_explored.erase(closest);

    // if first iteration, append next to m_sorted

      Notify("DISTANCE_DEBUG2", min_distance_to_current);
      m_sorted.push_back(*closest);
      current = m_sorted.end();
  }

  // m_sorted: where the sorted points go
vector<XYPoint>::iterator go;
for(go = m_sorted.begin(); go != m_sorted.end(); go++)
{
  XYPoint point = *go;
  double x1 = point.x();
  double y1 = point.y();

  m_seglist.add_vertex(x1,y1);
}

  // Change to strings
  string updatestring = "points = ";
  updatestring += m_seglist.get_spec();
  Notify("FINDPATH_DEBUG2", "Notified TSP_Updates");

  // Notify TSP_UPDATES
  Notify("TSP_UPDATES", updatestring);

  return (true);

}; //end of class

//---------------------------------------------------------
// Procedure: Distance
double GenPath::DistanceCalc(double x1, double x2, double y1, double y2)
{
  double xdist = pow(x2 - x1, 2);
  double ydist = pow(y2 - y1, 2);
  double dist = sqrt(xdist + ydist);
  return (dist);
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

  AppCastingMOOSApp::PostReport();
  return (true);
}

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
