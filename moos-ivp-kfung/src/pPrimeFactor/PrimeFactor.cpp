/************************************************************/
/*    NAME: Kat Fung                                              */
/*    ORGN: MIT, Cambridge MA                               */
/*    FILE: PrimeFactor.cpp                                        */
/*    DATE: March 02 2021                             */
/************************************************************/

#include <iterator>
#include "MBUtils.h"
#include "ACTable.h"
#include "PrimeFactor.h"
#include <cmath>
#include <string>   // may not need
#include <cstdlib>
#include <list>     // may not need
#include <cstdint>
#include <stdlib.h>

using namespace std;

//---------------------------------------------------------
// Constructor

PrimeFactor::PrimeFactor()
{
  m_test_num = 0;
  m_index = 0;     //starting at 0th
  m_incoming = 0;  // will increase as we add numbers
  m_outgoing = 0;  // wil increase as we add numbers
  //m_primelist; this is the name of the list established in the .h file
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
    string key    = msg.GetKey(); //key from mail
    string sval  = msg.GetString(); //because our input number is processed as a string at first
    
#if 0 // Keep these around just for template
    //string comm  = msg.GetCommunity();
    //double dval  = msg.GetDouble();
    //string msrc  = msg.GetSource();
    //double mtime = msg.GetTime();
    //bool   mdbl  = msg.IsDouble();
    //bool   mstr  = msg.IsString();
#endif
    
    /* This is going to build a list of received mail, convert to numbers, save as PrimeEntry classes, and index them*/     
    
    if(key == "NUM_VALUE"); //if the key is the var we are registering for is NUM_VALUE
    {
      unsigned long int numba = strtoul(sval.c_str(),NULL,0);  // convert the sval to an unisgned long int
      PrimeEntry newnum;                                       // create variable newnum of class PrimeEntry
      newnum.setOriginalVal(numba);                            //set the numba as setOriginalVal from PrimeEntry
      newnum.setReceivedIndex(m_index);                        //set the index of numba as setReceivedIndex from PrimeEntry
      m_index++;                                               // increment index so it moves one each time
      
      // add the newnum to a list of PrimeEntrys
      m_primelist.push_back(newnum);                            // add NUM_VALUE to the list for processing
 
    } //end of if for processing mail

    
    
    // ---------------- ORIGINAL STUFF------------------ 
    //if(key == "FOO") 
       //cout << "great!";

       // else if(key != "APPCAST_REQ") // handled by AppCastingMOOSApp
       //reportRunWarning("Unhandled Mail: " + key);
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

  /* This will use PrimeEntry to find the prime factors of newnum and report back with all the information saved*/

  list<PrimeEntry>::iterator p; //using p to iterate through list of PrimeEntries and check if they are complete
  for(p=m_primelist.begin(); p!=m_primelist.end(); ) //find and delete done entries
    {
      p->factor(100000); // pointer p, factor with max steps of "100,000"
      if(p->done())       // if done is true for that p
	{
      
      p->setCalculatedIndex(m_outgoing);   //set the outgoing index of this p
      m_outgoing++;                        //up one outgoing
      string big_report2=p->getReport();   //get the big_report string from PrimeEntry
      Notify("PRIME_RESULT",big_report2);    //Notify the MOOS with big_report
      p=m_primelist.erase(p);              // and erase that p so we don't look at it again
	}
      else    // if p isn't done
	{
	  p++; //try another p until we get one that works
	}

    }
  
  /* --------------- ODD/EVEN FINDING ---------------

  // Create a loop to look at the list and check if odd or even
  list<string>::iterator p;
  for(p=m_primelist.begin(); p!=m_primelist.end(); )
    {
       string nval = *p; //the string nval is the pth entry of mprimelist [KEEP if inputs are STRINGS]
      
       m_test_num = atoi(nval.c_str()); //convert from string to int original [KEEP if inputs are STRINGS]

       // m_test_num = *p; //set m_test_num to pth entry of m_primelist
    
    if(m_test_num % 2 == 0)
      { //odd = false;
      Notify("NUM_RESULT","even");
      }
    else
      {
      Notify("NUM_RESULT","odd");
      }
    p = m_primelist.erase(p);
    //++p; the above suffices to move on
    
    }

  ---------------------------------------------------*/
  // Do your (above) thing here!
  
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
    if(param == "foo") {
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
  // Register("FOOBAR", 0);
  Register("NUM_VALUE", 0);
}


//------------------------------------------------------------
// Procedure: buildReport()

bool PrimeFactor::buildReport() 
{
  m_msgs << "============================================" << endl;
  m_msgs << "File:                                       " << endl;
  m_msgs << "============================================" << endl;

  ACTable actab(4);
  actab << "Here are the Prime Factors:";
  actab.addHeaderLines();
  actab <<"PRIME_RESULT"<<"big_report2"; // << "two";
  m_msgs << actab.getFormattedString();

  return(true);
}




