/************************************************************/
/*    NAME: ncevans                                              */
/*    ORGN: MIT, Cambridge MA                               */
/*    FILE: PrimeFactor.cpp                                        */
/*    DATE: December 29th, 1963                             */
/************************************************************/

#include <iterator>
#include "MBUtils.h"
#include "ACTable.h"
#include "PrimeFactor.h"
#include <cstdint>
#include <sstream>
#include <list>
#include <string>
#include "PrimeEntry.h"

using namespace std;

//---------------------------------------------------------
// Constructor

PrimeFactor::PrimeFactor()
{
  m_incoming_seq=1;
  m_outgoing_pos=1;
}

//---------------------------------------------------------
// Destructor

PrimeFactor::~PrimeFactor()
{
}

//---------------------------------------------------------
// Procedure: OnNewMail

bool PrimeFactor::OnNewMail(MOOSMSG_LIST &NewMail)
{
  AppCastingMOOSApp::OnNewMail(NewMail);

  MOOSMSG_LIST::iterator p;
  for(p=NewMail.begin(); p!=NewMail.end(); p++) {
    CMOOSMsg &msg = *p;
    string key    = msg.GetKey();
    string sval  = msg.GetString();
    cout<<"THIS is the sval"<<sval<<endl;
    uint64_t value=0;

    //Take the incoming and create instance of PrimeEntry
     if(key == "NUM_VALUE"){
       value= strtoul(sval.c_str(),NULL, 0);
       PrimeEntry new_entry;
       new_entry.setOriginalVal(value);
       new_entry.setReceivedIndex(m_incoming_seq);
       new_entry.setStartTime(MOOSTime());
       m_incoming_seq++;
       m_prime_entry_list.push_back(new_entry);
     }
     if(key != "NUM_VALUE") // handled by AppCastingMOOSApp
       reportRunWarning("Unhandled Mail: " + key);
  }
	
   return(true);
}

//---------------------------------------------------------
// Procedure: OnConnectToServer

bool PrimeFactor::OnConnectToServer()
{
   registerVariables();
   return(true);
}

//---------------------------------------------------------
// Procedure: Iterate()
//            happens AppTick times per second

bool PrimeFactor::Iterate()
{
  AppCastingMOOSApp::Iterate();
   list<PrimeEntry>::iterator p;
   for(p=m_prime_entry_list.begin(); p!=m_prime_entry_list.end();){
      //Here we limit the for loop to x in factor(x)
      //This prevents blocking on one computation
      bool done=p->factor(100000);
      //If the factor is completed post and delete
      if(p->done()){
        p->setCalculatedIndex(m_outgoing_pos);
        m_outgoing_pos++;
        p->setTotalTime(MOOSTime());
        string str=p->getReport();
        Notify("PRIME_RESULT",str);
        p=m_prime_entry_list.erase(p);
      }
      else{
        ++p;
      }
    }
  AppCastingMOOSApp::PostReport();
  return(true);
}

//---------------------------------------------------------
// Procedure: OnStartUp()
//            happens before connection is open

bool PrimeFactor::OnStartUp()
{
  AppCastingMOOSApp::OnStartUp();

  STRING_LIST sParams;
  m_MissionReader.EnableVerbatimQuoting(false);
  if(!m_MissionReader.GetConfiguration(GetAppName(), sParams))
    reportConfigWarning("No config block found for " + GetAppName());

  STRING_LIST::iterator p;
  for(p=sParams.begin(); p!=sParams.end(); p++) {
    string orig  = *p;
    string line  = *p;
    string param = tolower(biteStringX(line, '='));
    string value = line;

    bool handled = false;
    if(param == "NUM_VALUE") {
      handled = true;
    }
    else if(param == "bar") {
      handled = true;
    }

    if(!handled)
      reportUnhandledConfigWarning(orig);

  }
  
  registerVariables();	
  return(true);
}

//---------------------------------------------------------
// Procedure: registerVariables

void PrimeFactor::registerVariables()
{
  AppCastingMOOSApp::RegisterVariables();
  Register("NUM_VALUE", 0);
}


//------------------------------------------------------------
// Procedure: buildReport()

bool PrimeFactor::buildReport() 
{
  m_msgs << "============================================+" << endl;
  m_msgs << "Show the number of NUM_VALUEs left to compute:" << endl;
  m_msgs << "============================================+" << endl;
  int a=m_incoming_seq-m_outgoing_pos;
  stringstream ss1;
  ss1 << a;
  string str1 = ss1.str();
  ACTable actab(1);
  actab << str1;
  actab.addHeaderLines();
  actab << str1;
  m_msgs << actab.getFormattedString();

  return(true);
}




