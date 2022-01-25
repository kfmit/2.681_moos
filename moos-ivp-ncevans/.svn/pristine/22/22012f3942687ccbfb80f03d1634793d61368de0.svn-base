/************************************************************/
/*    NAME: Craig Evans                                              */
/*    ORGN: MIT                                             */
/*    FILE: BHV_ZigLeg.cpp                                    */
/*    DATE:                                                 */
/************************************************************/

#include <iterator>
#include <cstdlib>
#include "MBUtils.h"
#include "BuildUtils.h"
#include "BHV_ZigLeg.h"

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
  //default values for member variables
  m_osx=0;
  m_osy=0;
  m_zig_duration=10;
  m_zig_angle=20;
  m_current_time=0;
  m_got_first_wpi=false;
  m_wypt_index=0;
  m_offsetting=true;
  
  // Add any variables this behavior needs to subscribe for
  addInfoVars("NAV_X, NAV_Y");
  addInfoVars("WPT_INDEX", "no_warning");
  addInfoVars("NAV_HEADING", "no_warning");
}

//---------------------------------------------------------------
// Procedure: setParam()

bool BHV_ZigLeg::setParam(string param, string val)
{
  // Convert the parameter to lower case for more general matching
  param = tolower(param);

  // Get the numerical value of the param argument for convenience once
  double double_val = atof(val.c_str());
  
  if((param == "zig_angle") && (double_val > 0) && (isNumber(val))) {
    m_zig_angle = double_val;
    return(true);
  }
  else if((param == "zig_duration") && (double_val > 0) && (isNumber(val))) {
    m_zig_duration = double_val;
    return(true);
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

  double NEW_INDEX=0;
  // Get the moos time
  double current_time=getBufferCurrTime();

  // Part 1: Get vehicle position from InfoBuffer and post a 
  // warning if problem is encountered
  bool ok1, ok2;
  m_osx = getBufferDoubleVal("NAV_X", ok1);
  m_osy = getBufferDoubleVal("NAV_Y", ok2);
  if(!ok1 || !ok2) {
    postWMessage("No ownship X/Y info in info_buffer.");
    return(0);
  }
  //Get Heading
  bool okheading;
  m_heading = getBufferDoubleVal("NAV_HEADING", okheading);
  if(!okheading) {
    postWMessage("No heading info in info_buffer.");
    return(0);
  }
  //Get Waypoint Index
  bool newwp;
  NEW_INDEX=getBufferDoubleVal("WPT_INDEX", newwp);
  if  (m_wypt_index!=NEW_INDEX && newwp){
    m_got_first_wpi=true;
    m_current_time=getBufferCurrTime();
    m_wypt_index=NEW_INDEX;
  }


  // Part 1: Build the IvP function
  IvPFunction *ipf = 0;
  if (m_got_first_wpi&&current_time>m_current_time+5&&current_time<m_current_time+m_zig_duration+5){
    if(m_offsetting){
      m_base_heading=m_heading+m_zig_angle;
      m_offsetting=false;
    }
       ZAIC_PEAK  zaic_peak(m_domain,"course");
 
// Step 3 - Configure the ZAIC_PEAK parameters
       zaic_peak.setSummit(m_base_heading);
       zaic_peak.setMinMaxUtil(20, 120);
       zaic_peak.setBaseWidth(0);
       ipf = zaic_peak.extractIvPFunction();

  }
  if (current_time>m_current_time+m_zig_duration+5){
       m_current_time=current_time;
       m_got_first_wpi=false;
       m_offsetting=true;
  }
  // Part N: Prior to returning the IvP function, apply the priority wt
  // Actual weight applied may be some value different than the configured
  // m_priority_wt, depending on the behavior author's insite.
  if(ipf)
    ipf->setPWT(m_priority_wt);

  return(ipf);
}

