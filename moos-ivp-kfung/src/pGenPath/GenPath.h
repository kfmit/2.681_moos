/************************************************************/
/*    NAME: Kat Fung                                              */
/*    ORGN: MIT, Cambridge MA                               */
/*    FILE: GenPath.h                                          */
/*    DATE: April 8, 2021                             */
/************************************************************/

#ifndef GenPath_HEADER
#define GenPath_HEADER

#include "MOOS/libMOOS/Thirdparty/AppCasting/AppCastingMOOSApp.h"
#include "XYPoint.h"
#include "XYSegList.h"
#include <list>
#include <vector>
#include <iostream>


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

   // For Generating Path
   bool ConvertPoint();
   bool FindShortestPath();
   bool NotifyTSPUpdates();

    // For REGenerating path
   bool CheckPoints();
   bool NotifyRegenUpdates();

   // Well this doesn't even get used anymore
   double DistanceCalc(XYPoint point1, XYPoint point2);

 protected:
   void registerVariables();

 private: // Configuration variables
  string m_startpos;
  int m_point_index;              // numerator to count up the points passed
  vector<string> m_tsppoints;     // to hold initial point order
  vector<XYPoint> m_xypointsort;  //to store numbers PRE sort
  XYSegList m_sorted;        // to hold post sort order

  XYSegList m_seglist;          // to hold final point order
  double m_min;                 // a value to compare against
  double m_xnext;               // holds the nextpoint to traverse to
  double m_ynext;
  bool m_allpointsreceived;
  vector<int> m_sorted_index;

  // For Augmentation
  bool m_regenerate;
  double m_xpoint;
  double m_ypoint;
  XYSegList m_not_explored;
  XYSegList m_explored;

 private: // State variables
};

#endif
