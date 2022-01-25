/************************************************************/
/*    NAME: Craig Evans                                              */
/*    ORGN: MIT, Cambridge MA                               */
/*    FILE: CommunicationAngle.h                                          */
/*    DATE: December 29th, 1963                             */
/************************************************************/

#ifndef CommunicationAngle_HEADER
#define CommunicationAngle_HEADER

#include "MOOS/libMOOS/Thirdparty/AppCasting/AppCastingMOOSApp.h"
#include <string>
#include "VehicleComms.h"
using namespace std;
class CommunicationAngle : public AppCastingMOOSApp
{
 public:
   CommunicationAngle();
   ~CommunicationAngle();
   VehicleComms m_vehicle_com;

 protected: // Standard MOOSApp functions to overload  
   bool OnNewMail(MOOSMSG_LIST &NewMail);
   bool Iterate();
   bool OnConnectToServer();
   bool OnStartUp();

 protected: // Standard AppCastingMOOSApp function to overload 
   bool buildReport();

 protected:
  void registerVariables();

  string m_collab_name;
  string m_collab_x;
  string m_collab_y;
  string m_collab_depth;
  string m_collab_speed;
  string m_collab_heading;
  string m_os_name;
  bool m_got_new;

  

 private: // Configuration variables

 private: // State variables
};

#endif 
