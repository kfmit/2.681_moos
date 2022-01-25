/*****************************************************************/
/*    NAME: Kat Fung                                             */
/*    ORGN: Dept of Mechanical Eng / CSAIL, MIT Cambridge MA     */
/*    FILE: BHV_Pulse.cpp                               */
/*    DATE: 06MAY2021                                             */
/*****************************************************************/

#include <cstdlib>
#include <math.h>
#include "BHV_Pulse.h"
#include "MBUtils.h"
#include "AngleUtils.h"
#include "BuildUtils.h"
#include "ZAIC_PEAK.h"
#include "OF_Coupler.h"
#include "OF_Reflector.h"
#include "XYRangePulse.h"

using namespace std;

//-----------------------------------------------------------
// Procedure: Constructor

BHV_Pulse::BHV_Pulse(IvPDomain gdomain) : IvPBehavior(gdomain)
{
  IvPBehavior::setParam("name", "pulse");
  //m_domain = subDomain(m_domain, "course,speed");

  // All distances are in meters, all speed in meters per second
  // Default values for configuration parameters
  m_desired_speed = 0;
  m_arrival_radius = 10;
  m_ipf_type = "zaic";

  addInfoVars("NAV_X, NAV_Y, WPT_INDEX", "no_warning");

  m_waypoint_old = 0;
}

//---------------------------------------------------------------
// Procedure: setParam - handle behavior configuration parameters

bool BHV_Pulse::setParam(string param, string val)
{
  // Convert the parameter to lower case for more general matching
  param = tolower(param);

  double double_val = atof(val.c_str());
  if ((param == "pulse_range") && (isNumber(val)))
  {
    //m_nextpt.set_vx(double_val);
    m_range = double_val;
    return (true);
  }
  else if ((param == "pulse_duration") && (isNumber(val)))
  {
    m_pulse_duration = double_val;
    return (true);
  }
  // else if((param == "speed") && (double_val > 0) && (isNumber(val))) {
  //   m_desired_speed = double_val;
  //   return(true);
  // }
  // else if((param == "radius") && (double_val > 0) && (isNumber(val))) {
  //   m_arrival_radius = double_val;
  //   return(true);
  //}

  else if (param == "ipf_type")
  {
    val = tolower(val);
    if ((val == "zaic") || (val == "reflector"))
    {
      m_ipf_type = val;
      return (true);
    }
  }
  return (false);
}

//-----------------------------------------------------------
// Procedure: onIdleState

void BHV_Pulse::onIdleState()
{
  // do nothing
}

//-----------------------------------------------------------
// Procedure: onRunState

IvPFunction *BHV_Pulse::onRunState()
{

  // Part 1: Get vehicle position from InfoBuffer and post a
  // warning if problem is encountered
  bool ok1, ok2, ok3;
  m_osx = getBufferDoubleVal("NAV_X", ok1);
  m_osy = getBufferDoubleVal("NAV_Y", ok2);
  m_waypoint_index = getBufferDoubleVal("WPT_INDEX", ok3);
  m_moos_current_time = getBufferCurrTime();

  // Part 2: Determine if the vehicle has reached a new destination
  // point and if so, make a pulse.
#ifdef WIN32
  double dist = _hypot((m_nextpt.x() - m_osx), (m_nextpt.y() - m_osy));
#else
  //double dist = hypot((m_nextpt.x()-m_osx), (m_nextpt.y()-m_osy));
#endif

  // t=0, waypoint_index=0, m_waypoint_old=0
  // t=1, waypoint_index=1, m_waypoint_old=0, => save time @ index change,

  bool timesave;

  if (ok3 && ok2 && ok1)
  {
    // if the the wpt index is one more than the last time
    if (m_waypoint_index != m_waypoint_old)
    {
      // should only be false when waypoint is changed
      timesave = false;
      if(timesave == false)
      {
      // save that instance of time as curr time
      m_time_at_index_change = m_moos_current_time;
      //m_time_at_index_change = getBufferCurrTime();
      timesave = true;
      }

      // Reset the old index so noly one instance of time is saved
      m_waypoint_old = m_waypoint_index;
    }

    // Wait 5 s, then create pulse
    if (m_moos_current_time = m_time_at_index_change + 5)
    {
      // Run the CreatePulse Function
      CreatePulse();
    }
  }


  // Part 3: Build the IvP function with either the ZAIC tool
  // or the Reflector tool.
  IvPFunction *ipf = 0;
  // if(m_ipf_type == "zaic")
  //   ipf = buildFunctionWithZAIC();
  // else
  //   ipf = buildFunctionWithReflector();
  // if(ipf == 0)
  //   postWMessage("Problem Creating the IvP Function");

  // if(ipf)
  //   ipf->setPWT(m_priority_wt);

  return (ipf);
}

//-----------------------------------------------------------
// Procedure: buildFunctionWithZAIC
#if 0
IvPFunction *BHV_Pulse::buildFunctionWithZAIC()
{
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

  double rel_ang_to_wpt = relAng(m_osx, m_osy, m_nextpt.x(), m_nextpt.y());
  ZAIC_PEAK crs_zaic(m_domain, "course");
  crs_zaic.setSummit(rel_ang_to_wpt);
  crs_zaic.setPeakWidth(0);
  crs_zaic.setBaseWidth(180.0);
  crs_zaic.setSummitDelta(0);
  crs_zaic.setValueWrap(true);
  if(crs_zaic.stateOK() == false) {
    string warnings = "Course ZAIC problems " + crs_zaic.getWarnings();
    postWMessage(warnings);
    return(0);
  }

  IvPFunction *spd_ipf = spd_zaic.extractIvPFunction();
  IvPFunction *crs_ipf = crs_zaic.extractIvPFunction();

  OF_Coupler coupler;
  IvPFunction *ivp_function = coupler.couple(crs_ipf, spd_ipf, 50, 50);

  return(ivp_function);
}

//-----------------------------------------------------------
// Procedure: buildFunctionWithReflector

IvPFunction *BHV_Pulse::buildFunctionWithReflector()
{
  IvPFunction *ivp_function;

  // bool ok = true;
  // AOF_SimpleWaypoint aof_wpt(m_domain);
  // ok = ok && aof_wpt.setParam("desired_speed", m_desired_speed);
  // ok = ok && aof_wpt.setParam("osx", m_osx);
  // ok = ok && aof_wpt.setParam("osy", m_osy);
  // ok = ok && aof_wpt.setParam("ptx", m_nextpt.x());
  // ok = ok && aof_wpt.setParam("pty", m_nextpt.y());
  // ok = ok && aof_wpt.initialize();
  // if(ok) {
  //   OF_Reflector reflector(&aof_wpt);
  //   reflector.create(600, 500);
  //   ivp_function = reflector.extractIvPFunction();
  // }

  return(ivp_function);
}
#endif

// ulimit -c unlimited

//--------------------------------------------------------------
// Procedure: CreatePulse
void BHV_Pulse::CreatePulse()
{
  XYRangePulse pulse;
  pulse.set_x(m_osx); // Presumably m_osx is ownship's x position
  pulse.set_y(m_osy); // Presumably m_osy is ownship's y pbtosition
  pulse.set_label("bhv_pulse");
  pulse.set_rad(m_range);
  // pulse.set_time(m_time_at_index_change);
  pulse.set_time(m_moos_current_time);
  pulse.set_color("edge", "yellow");
  pulse.set_color("fill", "yellow");
  pulse.set_duration(m_pulse_duration);

  string spec = pulse.get_spec();
  postMessage("VIEW_RANGE_PULSE", spec);
}