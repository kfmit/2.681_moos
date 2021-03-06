/************************************************************/
/*    NAME: Craig Evans                                              */
/*    ORGN: MIT, Cambridge MA                               */
/*    FILE: GenPath.h                                          */
/*    DATE: December 29th, 1963                             */
/************************************************************/

#ifndef GenPath_HEADER
#define GenPath_HEADER

#include "MOOS/libMOOS/Thirdparty/AppCasting/AppCastingMOOSApp.h"
#include <vector>
#include <string>
#include "VisitPoint.h"
using namespace std;
class GenPath : public AppCastingMOOSApp
{
 public:
   GenPath();
   ~GenPath();

 protected: // Standard MOOSApp functions to overload  
   bool OnNewMail(MOOSMSG_LIST &NewMail);
   bool Iterate();
   bool OnConnectToServer();
   bool OnStartUp();

 protected: // Standard AppCastingMOOSApp function to overload 
   bool buildReport();

 protected:
  void registerVariables();
  void getVisitPoint();
  bool getPath();
  bool checkPoint();
  vector<string> m_points;
  vector<string> m_pointsordered;
  vector<VisitPoint> m_point_vec;
  vector<VisitPoint> m_point_vec_new;
  bool m_firsttime;
  bool m_send;
  string m_startpos;
  double m_sx;
  double m_sy;
  double m_nav_x;
  double m_nav_y;
  int m_current_index;
  bool m_point_change;
  int m_the_index;
  bool m_not_complete;

 private: // Configuration variables

 private: // State variables
};

#endif 
