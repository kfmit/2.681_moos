/*****************************************************************/
/*    NAME: Kat Fung                                             */
/*    ORGN: Dept of Mechanical Eng / CSAIL, MIT Cambridge MA     */
/*    FILE: BHV_ZigLeg.cpp                                       */
/*    DATE: 06MAY2021                                            */
/*************************************************************** */

#ifndef BHV_ZIGLEG_HEADER
#define BHV_ZIGLEG_HEADER

#include <string>
#include "IvPBehavior.h"
#include "XYPoint.h"
#include "XYRangePulse.h"

class BHV_ZigLeg : public IvPBehavior {
public:
  BHV_ZigLeg(IvPDomain);
  ~BHV_ZigLeg() {};

  bool         setParam(std::string, std::string);
  void         onIdleState();
  IvPFunction* onRunState();

protected:
  //void         postViewPoint(bool viewable=true);
  IvPFunction* buildFunctionWithZAIC();
  IvPFunction* buildFunctionWithReflector();
  void CreatePulse();

protected: // Configuration parameters
  double       m_arrival_radius;
  double       m_desired_speed;
  XYPoint      m_nextpt;
  std::string  m_ipf_type;

protected: // State variables
  double m_zig_duration;
  double m_zig_angle;
  double  m_waypoint_index;
  double  m_waypoint_old;
  double   m_osx;
  double   m_osy;
  double  m_heading;
  double  m_save_heading;
  bool m_heading_saved;

  string  m_label;
  double m_range;
  double m_time_at_index_change;     // time of pulse happen
  string m_edge_color;
  string m_fill_color;
  double m_moos_current_time;      // time of
  double m_edge_size;
  double m_pulse_duration;

};

#ifdef WIN32
	// Windows needs to explicitly specify functions to export from a dll
   #define IVP_EXPORT_FUNCTION __declspec(dllexport)
#else
   #define IVP_EXPORT_FUNCTION
#endif

extern "C" {
  IVP_EXPORT_FUNCTION IvPBehavior * createBehavior(std::string name, IvPDomain domain)
  {return new BHV_ZigLeg(domain);}
}
#endif









