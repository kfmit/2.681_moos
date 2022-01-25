/************************************************************/
/*    NAME: Craig Evans                                              */
/*    ORGN: MIT                                             */
/*    FILE: BHV_FrontSearch.h                                      */
/*    DATE:                                                 */
/************************************************************/

#ifndef FrontSearch_HEADER
#define FrontSearch_HEADER

#include <vector>
#include <string>
#include <CSimAnneal.h>
#include <CFrontSim.h>
#include "IvPBehavior.h"
#include "ZAIC_PEAK.h"
class BHV_FrontSearch : public IvPBehavior {
public:
  BHV_FrontSearch(IvPDomain);
  ~BHV_FrontSearch() {};
  
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
  bool         findFront();
  IvPFunction* buildFunctionWithZAIC();
  void getParameters();
protected: // Configuration parameters

protected: // State variables
  CSimAnneal anneal;
  vector<CMeasurement> m_measurements_vec;
  string m_measurement;
  double m_osx;
  double m_osy;
  double m_slope;
  double m_intercept;
  double m_angle;
  double m_min_temp;
  double m_max_temp;
  int m_high_indice;
  int m_low_indice;
  string m_name;
  bool m_done_first;
  string m_done1;
  string m_done2;
  double m_desired_course;
  double m_desired_speed;
  double m_current_time;
  double m_start_time;
  double m_start_angle;
  string m_report;
  double m_offset;
  double m_amplitude;
  bool m_got_params;
  double m_shift1;
  double m_shift2;
  bool m_north;
  double m_bound;
  bool m_first_buff;
  double m_period;
};

#define IVP_EXPORT_FUNCTION

extern "C" {
  IVP_EXPORT_FUNCTION IvPBehavior * createBehavior(std::string name, IvPDomain domain) 
  {return new BHV_FrontSearch(domain);}
}
#endif
