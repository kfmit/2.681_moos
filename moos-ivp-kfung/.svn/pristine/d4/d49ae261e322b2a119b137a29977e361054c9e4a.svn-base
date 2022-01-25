/************************************************************/
/*    NAME: Kat Fung                                              */
/*    ORGN: MIT, Cambridge MA                               */
/*    FILE: PointAssign.h                                          */
/*    DATE: April 1, 2020                                         */
/************************************************************/

#ifndef PointAssign_HEADER
#define PointAssign_HEADER

#include "MOOS/libMOOS/Thirdparty/AppCasting/AppCastingMOOSApp.h"
#include <iostream>
#include <list>
#include"XYPoint.h"

using namespace std;

class PointAssign : public AppCastingMOOSApp
{
 public:
   PointAssign();
   ~PointAssign();

 protected: // Standard MOOSApp functions to overload
   bool OnNewMail(MOOSMSG_LIST &NewMail);
   bool Iterate();
   bool OnConnectToServer();
   bool OnStartUp();

 protected: // Standard AppCastingMOOSApp function to overload
   bool buildReport();

 protected:
   void registerVariables();
   void postViewPoint(double x, double y, string label, string color);
   bool handleNewPoint(string msg);

 private: // Configuration variables
    bool m_assign_by_region;  // parameter for deciding sorting
    list<string> m_namelist;     // a list of vehicle names to add to
    list<XYPoint> m_pointslist;      // making a list for points
    list<string> m_labellist;       // list of labels

    // Instead of making name list,
    string m_name1;
    string m_name2;
    bool m_lastpoint;
    bool m_notified;
    double m_starttime;

 private: // State variables
};

#endif
