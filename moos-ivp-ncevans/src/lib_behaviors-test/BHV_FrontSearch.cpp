/************************************************************/
/*    NAME: Craig Evans                                              */
/*    ORGN: MIT                                             */
/*    FILE: BHV_FrontSearch.cpp                                    */
/*    DATE:                                                 */
/************************************************************/

#include <iterator>
#include <cstdlib>
#include "MBUtils.h"
#include "BuildUtils.h"
#include "BHV_FrontSearch.h"
#include <math.h>
#include "OF_Coupler.h"
#include "OF_Reflector.h"
using namespace std;

//---------------------------------------------------------------
// Constructor

BHV_FrontSearch::BHV_FrontSearch(IvPDomain domain) :
  IvPBehavior(domain)
{
  // Provide a default behavior name
  IvPBehavior::setParam("name", "defaultname");

  // Declare the behavior decision space
  m_domain = subDomain(m_domain, "course,speed");
  m_slope=0;
  m_intercept=0;
  m_angle=0;
  m_min_temp=-100;
  m_max_temp=200;
  m_done_first=false;
  m_done1="false";
  m_done2="false";
  m_desired_speed=2;
  m_desired_course=180;
  m_current_time=0;
  m_high_indice=0;
  m_low_indice=0;
  m_got_params=false;
  m_start_angle=180;
  m_start_time=0;
  m_current_time=0;
  m_shift1=0;
  m_shift2=0;
  m_north=true;
  m_bound=0;
  m_first_buff=true;
  m_period=2;
  // Add any variables this behavior needs to subscribe for "UCTD_PARAMETER_ESTIMATE
  addInfoVars("NAV_X, NAV_Y");
  addInfoVars("UCTD_MSMNT_REPORT", "no_warning");
  addInfoVars("DONE_WITH_FIRST_archie", "no_warning");
  addInfoVars("DONE_WITH_FIRST_betty", "no_warning");
  addInfoVars("UCTD_PARAMETER_ESTIMATE", "no_warning");
}

//---------------------------------------------------------------
// Procedure: setParam()

bool BHV_FrontSearch::setParam(string param, string val)
{
  // Convert the parameter to lower case for more general matching
  param = tolower(param);
  if((param == "vname")) {
    m_name=val;
    return(true);
  }
  // Get the numerical value of the param argument for convenience once
 
  


  // If not handled above, then just return false;
  return(false);
}

//---------------------------------------------------------------
// Procedure: onSetParamComplete()
//   Purpose: Invoked once after all parameters have been handled.
//            Good place to ensure all required params have are set.
//            Or any inter-param relationships like a<b.

void BHV_FrontSearch::onSetParamComplete()
{
    postMessage("VNAME", m_name);
    m_start_time=getBufferCurrTime();
    postMessage("TIME_UP1",m_start_time);
}

//---------------------------------------------------------------
// Procedure: onHelmStart()
//   Purpose: Invoked once upon helm start, even if this behavior
//            is a template and not spawned at startup

void BHV_FrontSearch::onHelmStart()
{

}

//---------------------------------------------------------------
// Procedure: onIdleState()
//   Purpose: Invoked on each helm iteration if conditions not met.

void BHV_FrontSearch::onIdleState()
{
}

//---------------------------------------------------------------
// Procedure: onCompleteState()

void BHV_FrontSearch::onCompleteState()
{
}

//---------------------------------------------------------------
// Procedure: postConfigStatus()
//   Purpose: Invoked each time a param is dynamically changed

void BHV_FrontSearch::postConfigStatus()
{
}

//---------------------------------------------------------------
// Procedure: onIdleToRunState()
//   Purpose: Invoked once upon each transition from idle to run state

void BHV_FrontSearch::onIdleToRunState()
{
}

//---------------------------------------------------------------
// Procedure: onRunToIdleState()
//   Purpose: Invoked once upon each transition from run to idle state

void BHV_FrontSearch::onRunToIdleState()
{
}

//---------------------------------------------------------------
// Procedure: onRunState()
//   Purpose: Invoked each iteration when run conditions have been met.

IvPFunction* BHV_FrontSearch::onRunState()
{
  if (m_first_buff){
    m_start_time=getBufferCurrTime();
    m_first_buff=false;
  }
  m_current_time=getBufferCurrTime();
    //Check the time limit
   postMessage("GIVE_ME_UPDATE","YEP");
   postMessage("TIME_UP1",m_start_time);
   postMessage("TIME_UP2",m_current_time);
   
  if(m_current_time-m_start_time>700){
    postMessage("TIME_UP","true");
    postMessage("SURVEY_UNDERWAY", "false");
    postMessage("RETURN","true");
  }
  bool ok1, ok2;
  m_osx = getBufferDoubleVal("NAV_X", ok1);
  m_osy = getBufferDoubleVal("NAV_Y", ok2);
  if(!ok1 || !ok2) {
    postWMessage("No ownship X/Y info in info_buffer.");
    return(0);
  }
  bool okmeas;
    m_measurement = getBufferStringVal("UCTD_MSMNT_REPORT", okmeas);
    //this is where i get the sensor infor
  if(!okmeas) {
    postWMessage("No CTD info_buffer.");
    return(0);
  }
  else{
    string value=m_measurement;
    CMeasurement measure;
    measure = anneal.parseMeas(value);
    m_measurements_vec.push_back(measure);
    postMessage("BHV_EST_TEMPERATURE", measure.temp);
  }

  //Check if done with first search
  bool okf;
  bool oks;
  bool est;
  //string done1;
  //string done2;UCTD_PARAMETER_ESTIMATE
  m_report = getBufferStringVal("UCTD_PARAMETER_ESTIMATE", est);
  if(est){
    getParameters();
  }
  m_done1 = getBufferStringVal("DONE_WITH_FIRST_archie", okf);
  m_done2 = getBufferStringVal("DONE_WITH_FIRST_betty", oks);
  if (m_done1=="true"|| m_done2=="true"){
    m_done_first=true;
    postMessage("INSIDE", "true");
  }

  //Create the Objective Function
  IvPFunction *ipf = 0;
  if (m_done_first&&m_got_params){
    postMessage("SURVEY_UNDERWAY","false");
    if(m_name=="archie"){
      m_bound=m_amplitude*1.1;
      m_desired_speed=m_period/120;
    }
    else{
      m_bound=m_amplitude*.4;
      m_desired_speed=m_period/110;
    }
    if(m_osx>150){
      m_shift1=90;
      m_shift2=270;
    }
    if(m_osx<-30){
      m_shift1=0;
      m_shift2=0;
    }
   
    double dif=m_osy-m_offset;
    double dif2=m_offset+20;
    postMessage("DIF",dif);
    if(m_osy>m_offset+m_bound){
      m_desired_course=180;
      m_north=true;
    }
    else if(m_osy<m_offset-m_bound){
      m_desired_course=0;
      m_north=false;
    }
    else if(m_north==false){
      m_desired_course=45+m_angle+m_shift2;
      postMessage("GIVE_ME_UPDATE","YEP");

    }
    else if(m_north==true){
      m_desired_course=135+m_angle+m_shift1;
      postMessage("GIVE_ME_UPDATE","NOPE");
    }
      ipf = buildFunctionWithZAIC();
    
  }

  // Part N: Prior to returning the IvP function, apply the priority wt
  // Actual weight applied may be some value different than the configured
  // m_priority_wt, depending on the behavior author's insite.
  if(ipf)
    ipf->setPWT(m_priority_wt);

  return(ipf);
}
bool BHV_FrontSearch::findFront()
{
  for (int i =0; i<m_measurements_vec.size(); i++){
    if(m_measurements_vec[i].temp<m_min_temp){
      m_min_temp=m_measurements_vec[i].temp;
      m_low_indice=i;
    }
    if(m_measurements_vec[i].temp>m_max_temp){
      m_max_temp=m_measurements_vec[i].temp;
      m_high_indice=i;
    }

    

  }
    postMessage("BHV_EST_MINX", m_measurements_vec[m_low_indice].x);
    postMessage("BHV_EST_MINY", m_measurements_vec[m_low_indice].y);
    postMessage("BHV_EST_MAXX", m_measurements_vec[m_high_indice].x);
    postMessage("BHV_EST_MAXY", m_measurements_vec[m_high_indice].y);
    return true;
}
IvPFunction *BHV_FrontSearch::buildFunctionWithZAIC()
{
  ZAIC_PEAK  crs_zaic(m_domain,"course");
  crs_zaic.setSummit(m_desired_course);
  crs_zaic.setMinMaxUtil(20, 120);
  crs_zaic.setBaseWidth(20);
  //Now the speed zaic
  ZAIC_PEAK spd_zaic(m_domain, "speed");
  spd_zaic.setSummit(m_desired_speed);
  spd_zaic.setPeakWidth(0.5);
  spd_zaic.setBaseWidth(1.0);
  spd_zaic.setSummitDelta(0.8); 


  IvPFunction *spd_ipf = spd_zaic.extractIvPFunction();
  IvPFunction *crs_ipf = crs_zaic.extractIvPFunction();

  OF_Coupler coupler;
  IvPFunction *ipv = coupler.couple(crs_ipf, spd_ipf, 50, 50);

  return ipv;
}
void BHV_FrontSearch::getParameters()
{
  string a=tokStringParse(m_report, "offset", ',', '=');
  string b=tokStringParse(m_report, "amplitude", ',', '=');
  string c=tokStringParse(m_report, "angle", ',', '=');
  string d=tokStringParse(m_report, "period", ',', '=');
  m_angle=stod(c);
  m_offset=stod(a);
  m_amplitude=stod(b);
  m_period=stod(d);
  postMessage("AMP", m_amplitude);
  postMessage("OFFSET", m_offset);
  postMessage("ANGLE", m_angle);
  m_got_params=true;
}
