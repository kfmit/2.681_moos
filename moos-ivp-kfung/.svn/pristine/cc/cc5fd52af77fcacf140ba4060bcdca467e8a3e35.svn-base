/************************************************************/
/*    NAME: Greg Burgess                                    */
/*    ORGN: MIT                                             */
/*    FILE: BHV_ZigLeg.cpp                                  */
/*    DATE: 29 April 2021                                   */
/************************************************************/

#include <iterator>
#include <cstdlib>
#include "MBUtils.h"
#include "BuildUtils.h"
#include "BHV_ZigLeg.h"
#include "XYRangePulse.h"
#include "ZAIC_PEAK.h"

using namespace std;

//---------------------------------------------------------------
// Constructor

BHV_ZigLeg::BHV_ZigLeg(IvPDomain domain) :
  IvPBehavior(domain)
{
  // Provide a default behavior name
  IvPBehavior::setParam("name", "defaultname");

  // Declare the behavior decision space
  m_domain = subDomain(m_domain, "course,speed");

  // Add any variables this behavior needs to subscribe for
  addInfoVars("NAV_X, NAV_Y, WPT_INDEX, NAV_HEADING", "no_warning");

  //Init Variables
  m_wpt_changed_flag = false;
  m_pulse_posted     = true;
  
  
}

//---------------------------------------------------------------
// Procedure: setParam()

bool BHV_ZigLeg::setParam(string param, string val)
{
  // Convert the parameter to lower case for more general matching
  param = tolower(param);

  // Get the numerical value of the param argument for convenience once
  double double_val = atof(val.c_str());
  
  if((param == "zig_angle") && isNumber(val)) {
    m_ZigLeg_angle = double_val;
    return(true);
  }
  else if((param == "zig_duration") && isNumber(val)) {
    m_ZigLeg_duration = double_val;
    return(true);
  }
  else if((param == "pulse_range") && isNumber(val)) {
    m_pulse_range = double_val;
    return(true);
  }
  else if((param == "pulse_duration") && isNumber(val)) {
    m_pulse_duration = double_val;
    return(true);
  }
  else if (param == "bar") {
    // return(setBooleanOnString(m_my_bool, val));
  }

  // If not handled above, then just return false;
  return(false);
}

//---------------------------------------------------------------
// Procedure: onSetParamComplete()
//   Purpose: Invoked once after all parameters have been handled.
//            Good place to ensure all required params have are set.
//            Or any inter-param relationships like a<b.

void BHV_ZigLeg::onSetParamComplete()
{
}

//---------------------------------------------------------------
// Procedure: onHelmStart()
//   Purpose: Invoked once upon helm start, even if this behavior
//            is a template and not spawned at startup

void BHV_ZigLeg::onHelmStart()
{
}

//---------------------------------------------------------------
// Procedure: onIdleState()
//   Purpose: Invoked on each helm iteration if conditions not met.

void BHV_ZigLeg::onIdleState()
{
}

//---------------------------------------------------------------
// Procedure: onCompleteState()

void BHV_ZigLeg::onCompleteState()
{
}

//---------------------------------------------------------------
// Procedure: postConfigStatus()
//   Purpose: Invoked each time a param is dynamically changed

void BHV_ZigLeg::postConfigStatus()
{
}

//---------------------------------------------------------------
// Procedure: onIdleToRunState()
//   Purpose: Invoked once upon each transition from idle to run state

void BHV_ZigLeg::onIdleToRunState()
{
}

//---------------------------------------------------------------
// Procedure: onRunToIdleState()
//   Purpose: Invoked once upon each transition from run to idle state

void BHV_ZigLeg::onRunToIdleState()
{
}

//---------------------------------------------------------------
// Procedure: onRunState()
//   Purpose: Invoked each iteration when run conditions have been met.

IvPFunction* BHV_ZigLeg::onRunState()
{
  // Part 1: Build the IvP function
    IvPFunction *ipf = 0;

  // Part 2: Generate ZigLeg

  double local_wpt_idx = m_wpt_idx;

  //Get Needed Info from Buffer
  bool ok1, ok2, ok3, ok4;
  m_curr_time    = getBufferCurrTime();
  m_curr_x       = getBufferDoubleVal("NAV_X", ok1);
  m_curr_y       = getBufferDoubleVal("NAV_Y", ok2);
  m_curr_heading = getBufferDoubleVal("NAV_HEADING", ok4);
  m_wpt_idx      = getBufferDoubleVal("WPT_INDEX", ok3);
  //if(!ok1 || !ok2 || !ok3 || !ok4) {
  //  postWMessage("No NAV_X or NAV_Y or NAV_HEADING or WPT_INDEX info in info_buffer.");
  //  return(0);
  //}

  //Check to see if wpt changed
  if(!m_wpt_changed_flag){
    if(local_wpt_idx != m_wpt_idx) { 
      m_wpt_time         = getBufferCurrTime();
      m_wpt_changed_flag = true;
    }
  }

  if(m_wpt_changed_flag) {
    //Wait 5 seconds and then post ZigLeg
    if((m_curr_time-m_wpt_time) > 5.0 ) {
      if(m_pulse_posted) {
        XYRangePulse Pulse;
        Pulse.set_x(m_curr_x);                
        Pulse.set_y(m_curr_y);                
        Pulse.set_label("bhv_ZigLeg");
        Pulse.set_rad(m_pulse_range);
        Pulse.set_time(m_curr_time);       
        Pulse.set_color("edge", "yellow");
        Pulse.set_color("fill", "yellow");
        Pulse.set_duration(m_pulse_duration);

        string spec = Pulse.get_spec();
        postMessage("VIEW_RANGE_PULSE", spec);
        m_pulse_posted = false;
        m_heading_mark     = m_curr_heading;
      } 
      if((m_curr_time - (m_wpt_time+5)) < m_ZigLeg_duration){
        ipf = buildFunctionWithZAIC();
      }
      else {
        m_wpt_changed_flag = false;
        m_pulse_posted     = true;
      }
    }
  }



      // Part N: Prior to returning the IvP function, apply the priority wt
      // Actual weight applied may be some value different than the configured
      // m_priority_wt, depending on the behavior author's insite.
      if(ipf)
        ipf->setPWT(m_priority_wt);

      return(ipf);
          
}
//-----------------------------------------------------------
// Procedure: buildFunctionWithZAIC

IvPFunction *BHV_ZigLeg::buildFunctionWithZAIC() 
{
  #if 0
  ZAIC_PEAK spd_zaic(m_domain, "speed");
  spd_zaic.setSummit(m_desired_speed);
  spd_zaic.setPeakWidth(0.5);
  spd_zaic.setBaseWidth(1.0);
  spd_zaic.setSummitDelta(0.8);  
  if(spd_zaic.stateOK() == false) {
    string warnings = "Speed ZAIC problems " + spd_zaic.getWarnings();
    postWMessage(warnings);
    return(0);
  }
  #endif

  //double rel_ang_to_wpt = relAng(m_osx, m_osy, m_nextpt.x(), m_nextpt.y());
  double rel_ang_to_wpt = m_heading_mark + m_ZigLeg_angle;
  ZAIC_PEAK crs_zaic(m_domain, "course");
  crs_zaic.setSummit(rel_ang_to_wpt);
  crs_zaic.setPeakWidth(0);
  crs_zaic.setBaseWidth(180.0);
  crs_zaic.setSummitDelta(30);  
  crs_zaic.setValueWrap(true);
  if(crs_zaic.stateOK() == false) {
    string warnings = "Course ZAIC problems " + crs_zaic.getWarnings();
    postWMessage(warnings);
    return(0);
  }

  //IvPFunction *spd_ipf = spd_zaic.extractIvPFunction();
  IvPFunction *crs_ipf = crs_zaic.extractIvPFunction();

  //OF_Coupler coupler;
  //IvPFunction *ivp_function = coupler.couple(crs_ipf, spd_ipf, 50, 50);

  return(crs_ipf);
}
