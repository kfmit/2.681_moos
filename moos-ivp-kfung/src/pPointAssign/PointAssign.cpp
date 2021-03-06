/************************************************************/
/*    NAME: Kat Fung                                              */
/*    ORGN: MIT, Cambridge MA                               */
/*    FILE: PointAssign.cpp                                        */
/*    DATE: December 29th, 1963                             */
/************************************************************/

#include <iterator>
#include "MBUtils.h"
#include "ACTable.h"
#include "PointAssign.h"
#include "XYPoint.h"
#include <list>
#include <string>

using namespace std;

//---------------------------------------------------------
// Constructor

PointAssign::PointAssign()
{
  //initialize any random variables you plan to use here
  m_assign_by_region = false; //default to NOT assign by region
  m_lastpoint = false;
  m_notified = false;
  m_starttime = MOOSTime();
}

//---------------------------------------------------------
// Destructor

PointAssign::~PointAssign()
{
}

//---------------------------------------------------------
// Procedure: OnNewMail

bool PointAssign::OnNewMail(MOOSMSG_LIST &NewMail)
{
  AppCastingMOOSApp::OnNewMail(NewMail);

  MOOSMSG_LIST::iterator p;
  for (p = NewMail.begin(); p != NewMail.end(); p++)
  {
    CMOOSMsg &msg = *p;
    string key = msg.GetKey();
    //double dval  = msg.GetDouble();
    string sval = msg.GetString();

#if 0 // Keep these around just for template
    string comm  = msg.GetCommunity();
    double dval  = msg.GetDouble();
    string msrc  = msg.GetSource();
    double mtime = msg.GetTime();
    bool   mdbl  = msg.IsDouble();
    bool   mstr  = msg.IsString();
#endif

    // Create a list of generated Visit Points
    if (key == "VISIT_POINT")
    {
      //  // This is a list of STRINGS not INTS
      //  m_pointslist.push_back(sval);
      handleNewPoint(sval);
      if (sval == "lastpoint")
        m_lastpoint = true;
    }

    else if (key != "APPCAST_REQ") // handled by AppCastingMOOSApp
      reportRunWarning("Unhandled Mail: " + key);
  }

  return (true);
}

bool PointAssign::handleNewPoint(string msg)
{
  if (msg == "firstpoint" || msg == "lastpoint")
  {
    // Cool, do nothing
    m_labellist.push_back(msg);
    Notify("VISIT_POINT", msg);
    return (true);
  }

  // This is a list of STRINGS not INTS
  // m_pointslist.push_back(sval);
  // ["x=XX, y=YY, label=@@", "x=XX, y=YY, label=@@"]
  // [XYPoint(XX,YY,@@),XYPoint(XX,YY,@@),XYPoint(XX,YY,@@)]
  else
  {
    string pointstring = msg; // the whole "x=num, y=num, id=num"
    // cout << pointstring << endl;
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
    double x = stod(xstring.c_str());
    double y = stod(ystring.c_str());
    int idnum = stod(idstring.c_str());
    string label = idstring; // he gets to stay a string

    m_labellist.push_back(label);

    //postViewPoint(x, y, label, "red");
    XYPoint point(x, y);
    point.set_label(label);
    m_pointslist.push_back(point);

    // Visual Hint of Points
    if (m_assign_by_region == true)
    {
      // Sort by east and west
      if (x <= 87) // WEST
      {
        // if in the west region, assign to v1
        // Define West as x from (88,200)
        postViewPoint(x, y, label, "blue");
        cout << "Posted West Point" << endl;
      }
      else if (x >= 88) // EAST
      {
        // if in the east region, assign to v2
        // Define EAST as x from (-25,87)
        postViewPoint(x, y, label, "yellow");
      }
    }
    else // DO NOT ASSIGN BY REIGION
    {    // Alternate point assignment

      if (idnum % 2 == 0) // if the number is even, give to vehicle 1
      {
        // Assign Point to Vehicle 1 and Notify
        postViewPoint(x, y, label, "blue");
      }

      else // so for all the odd numbers
      {
        // Assign Point to Vehicle 2 and Notify here?;
        postViewPoint(x, y, label, "yellow");
      }
    }
  }
  return (false);
}

//---------------------------------------------------------
// Procedure: OnConnectToServer

bool PointAssign::OnConnectToServer()
{
  registerVariables();
  return (true);
}

//---------------------------------------------------------
// DECLARE: postViewPoint: a function for sorting points

void PointAssign::postViewPoint(double x, double y, string label, string color)
{
  XYPoint point(x, y);
  point.set_label(label);
  point.set_color("vertex", color);
  point.set_param("vertex_size", "9");

  string spec = point.get_spec(); // gets the string representation of a point
  Notify("VIEW_POINT", spec);     // THIS IS SOMETHING MOOS ALREADY KNOWS HOW TO READ
};

//---------------------------------------------------------
// Procedure: Iterate()
//            happens AppTick times per second

bool PointAssign::Iterate()
{
  AppCastingMOOSApp::Iterate();
  // Do your thing here!
  // Create a report of all the travel points for each vehicle
  // don't Notify until "lastpoint" is received

  int alternate = 0; // variable to alternate between vehicles

  // Name the vehicles
  string bluevehicle1 = "VISIT_POINT_" + m_name1;
  string yellowvehicle2 = "VISIT_POINT_" + m_name2;

  if (m_lastpoint && !m_notified && MOOSTime()-m_starttime > 5)
  {
    // From the m_pointslist, split around the string to get x ,y, and id
    list<XYPoint>::iterator p;
    for (p = m_pointslist.begin(); p != m_pointslist.end(); p++)
    {
      XYPoint point = *p;
      string pointstring = point.get_spec();

      // HOLD OFF AND PUT THESE IN LATER
      // Run postViewPoint with these conditions change color with vehicle assigment
      // STILL INSIDE FOR LOOP: Assign points in manner

      // check if assign by region is true
      double x = point.x();
      double y = point.y();

      if (m_assign_by_region == true) // if it is true, divide into east/west
      {
        Notify("assign_by_region", "true");
        // Sort by east and west

        if (x <= 87) // WEST
        {
          // if in the west region, assign to v1
          // Define West as x from (88,200)
          Notify(bluevehicle1, pointstring);
          cout << "Posted West Point" << endl;
        }
        else if (x >= 88) // EAST
        {
          // if in the east region, assign to v2
          // Define EAST as x from (-25,87)
          Notify(yellowvehicle2, pointstring);
          cout << "Posted East Point" << endl;
        }
        // End of assign by region
      }

      else // DO NOT ASSIGN BY REIGION
      {
        Notify("assign_by_region", "false");
        // Alternate point assignment
        {
          if (alternate % 2 == 0) // if the number is even, give to vehicle 1
          {
            // Assign Point to Vehicle 1 and Notify
            cout << "point assigned to blue" << endl;
            Notify(bluevehicle1, pointstring);
          }

          else // so for all the odd numbers
          {
            // Assign Point to Vehicle 2 and Notify here?
            cout << "point assigned to yellow" << endl;
            Notify(yellowvehicle2, pointstring);
          }
        }
        alternate++; // increments alternate up 1 through next iteration of p
      }
    }
    
    Notify(yellowvehicle2,"lastpoint");
    Notify(bluevehicle1,"lastpoint");
    m_notified = true;
  } // end of XYpoint loop

  AppCastingMOOSApp::PostReport();
  return (true);
}

//---------------------------------------------------------
// Procedure: OnStartUp()
//            happens before connection is open

bool PointAssign::OnStartUp()
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
    string param = tolower(biteStringX(line, '=')); //chops line by =, keeps the right side
    string value = line;

    // PARAM is LEFT, line is the RIGHT side

    bool handled = false;
    if (param == "foo")
    {
      handled = true;
    }
    else if (param == "bar")
    {
      handled = true;
    }

    // Create a list of vehicle names
    else if (param == "vname1")
    {
      //m_namelist.push_back(value);
      m_name1 = toupper(value); // so i don't have to access a list
      handled = true;
    }
    else if (param == "vname2")
    {
      //m_namelist.push_back(value);
      m_name2 = toupper(value); //so i don't have to access a list
      handled = true;
    }

    // Check is assigning by region
    else if (param == "assign_by_region")
    {
      if (value == "false")
      {
        // set m_assign_by_region
        m_assign_by_region = false;
        handled = true;
      }

      else
      {
        m_assign_by_region = true;
        handled = true;
      }
    }

    if (!handled)
      reportUnhandledConfigWarning(orig);
  }

  registerVariables();
  return (true);
}

//---------------------------------------------------------
// Procedure: registerVariables

void PointAssign::registerVariables()
{
  AppCastingMOOSApp::RegisterVariables();
  // Register("FOOBAR", 0);
  // Registering for MOOS Variables
  Register("VISIT_POINT", 0);
  Register("VIEW_POINT,0");
}

//------------------------------------------------------------
// Procedure: buildReport()

bool PointAssign::buildReport()
{
  m_msgs << "============================================" << endl;
  m_msgs << "File: PointAssign.cpp                                      " << endl;
  m_msgs << "============================================" << endl;

  ACTable actab(4);
  actab << "Alpha | Bravo | Charlie | Delta";
  actab.addHeaderLines();
  actab << "one";
  m_msgs << actab.getFormattedString() << m_pointslist.size();

  return (true);
}
