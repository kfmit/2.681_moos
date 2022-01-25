/*****************************************************************/
/*    NAME: Kat Fung                   */
/*    ORGN: Dept of Mechanical Eng / CSAIL, MIT Cambridge MA     */
/*    FILE: XYRangePulse.cpp                               */
/*    DATE: May 6, 2021                                          */
/*****************************************************************/

#include <cstdlib>
#include <math.h>
#include "XYRangePulse.h"
#include <sstream>
#include <iostream>
#include <cstdint>
#include <iterator>
#include "MBUtils.h"
#include "ACTable.h"

using namespace std;

//-----------------------------------------------------------
// Procedure: Constructor

XYRangePulse::XYRangePulse() :
{
}

//-----------------------------------------------
// Procedure:

void XYRangePulse::set_color(string type, string color)
{
if(type == "fill")
{
  m_fill_color = color;
}

else if(type == "edge")
{
  m_edge_color = color;
}

}

//----------------------------------------------------
// getReport

string XYRangePulse::GetReport()
{
  // needs to contain all the info from calcualting the prime numbers
  stringstream ss_report; //create a stringstream of strings
  // convert from unsigned long int to string within each or print as var?
  ss_report << "x=" << m_osx << ", ";              // x
  ss_report << "y=:" << m_osy << ", ";             // y
  ss_report << "radius=" << m_range << ", ";       // radius
  ss_report << "duration="<<m_pulse_duration<< ", ";      // duration
  ss_report << "label="<<m_label<< ", "; 
  ss_report << "edge_color="<<m_edge_color<< ", "; 
  ss_report << "fill_color="<<m_fill_color<< ", "; 
  ss_report << "time="<<m_curr_time<< ", ";
  ss_report << "edge_size="<<m_edge_size<< ", ";
  ss_report << "alpha.moos++" <<; 

  if (m_factors.size != 0)                           // if not empty
  {
    for (int ii = 0; ii < m_factors.size(); ii++)
    {
      ss_report << m_factors[ii] << ", "; // build report
    }
  }
  string big_report = ss_report.str(); //put it all together

  return big_report; // ----------------do i need // end of string
}