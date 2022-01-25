/************************************************************/
/*    NAME: Craig Evans                                              */
/*    ORGN: MIT, Cambridge MA                               */
/*    FILE: PointAssign.h                                          */
/*    DATE: December 29th, 1963                             */
/************************************************************/

#ifndef PointAssign_HEADER
#define PointAssign_HEADER

#include "MOOS/libMOOS/Thirdparty/AppCasting/AppCastingMOOSApp.h"
#include <vector>
#include <string>

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
  bool getPoints();
  void postViewPoint(double x, double y, string label, string color);
  void getView();
   bool m_first;
   string m_vehicle1;
   string m_vehicle2;
   string m_assign_by_region_str;
   string m_v1_color;
   string m_v2_color;
   string m_veh1_check;
   string m_veh2_check;
   vector<string> m_allpoints;
   vector<string> m_NAME1points;
   vector<string> m_NAME2points;
   string m_got_1;
   string m_got_2;
  bool m_done;
 private: // Configuration variables

 private: // State variables
};

#endif 
