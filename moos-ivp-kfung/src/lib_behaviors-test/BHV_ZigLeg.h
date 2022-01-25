/************************************************************/
/*    NAME: Greg Burgess                                    */
/*    ORGN: MIT                                             */
/*    FILE: BHV_ZigLeg.h                                    */
/*    DATE: 29 April 2021                                   */
/************************************************************/

#ifndef ZigLeg_HEADER
#define ZigLeg_HEADER

#include <string>
#include "IvPBehavior.h"

class BHV_ZigLeg : public IvPBehavior {
public:
  BHV_ZigLeg(IvPDomain);
  ~BHV_ZigLeg() {};
  
  bool         setParam(std::string, std::string);
  void         onSetParamComplete();
  void         onCompleteState();
  void         onIdleState();
  void         onHelmStart();
  void         postConfigStatus();
  void         onRunToIdleState();
  void         onIdleToRunState();
  IvPFunction* onRunState();

protected: // Local Utility functions
  void         postViewPoint(bool viewable=true);
  IvPFunction* buildFunctionWithZAIC();
  IvPFunction* buildFunctionWithReflector();
protected: // Configuration parameters

double m_ZigLeg_angle;
double m_ZigLeg_duration;
double m_pulse_range;
double m_pulse_duration;

protected: // State variables
bool m_wpt_changed_flag;
bool m_pulse_posted;

double m_wpt_time;
double m_wpt_idx;
double m_heading_mark;

double m_curr_time;
double m_curr_x;
double m_curr_y;
double m_curr_heading;



};

#define IVP_EXPORT_FUNCTION

extern "C" {
  IVP_EXPORT_FUNCTION IvPBehavior * createBehavior(std::string name, IvPDomain domain) 
  {return new BHV_ZigLeg(domain);}
}
#endif
