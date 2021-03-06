/*****************************************************************/
/*    NAME: Kat Fung                  */
/*    ORGN: Dept of Mechanical Eng / CSAIL, MIT Cambridge MA     */
/*    FILE: XYRangePulse.ch                                */
/*    DATE: May 5 2021                                */
/*****************************************************************/
 
#ifndef XY_RANGE_PULSE_HEADER
#define XY_RANGE_PULSE_HEADER

#include <string>
#include <vector>
#include <cmath>

#include "IvPBehavior.h"
#include "XYPoint.h"

using namespace std;

// the purpose of this class is to create the ring?
class XYRangePulse
{
public:
  XYRangePulse();
  ~XYRangePulse() {};
  
  
  string  GetReport();  // function for making string
  void  set_x(double v)                     {m_osx=v;};
  void  set_y(double v)                     {m_osy=v;};
  void  set_label(string v)                 {m_label=v;};
  void  set_rad(double v)                   {m_range=v;};
  void  set_time(double v)                  {m_curr_time=v;};
  void  set_color(string type, string color);
  void  set_duration(double v)              {m_pulse_duration=v;};

protected:

protected: // Configuration parameters

protected: // State variables
  double   m_osx;
  double   m_osy;
  string  m_label;
  double m_range;
  double m_curr_time;
  string m_edge_color;
  string m_fill_color;
  double m_moostime;
  double m_edge_size;
  double m_pulse_duration;
};

#ifdef WIN32
	// Windows needs to explicitly specify functions to export from a dll
   #define IVP_EXPORT_FUNCTION __declspec(dllexport) 
#else
   #define IVP_EXPORT_FUNCTION
#endif


#endif









