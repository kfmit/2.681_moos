/************************************************************/
/*    NAME: Kat Fung                                              */
/*    ORGN: MIT, Cambridge MA                               */
/*    FILE: PrimeFactor.h                                          */
/*    DATE: March, 04 2021                             */
/************************************************************/

#ifndef PrimeFactor_HEADER
#define PrimeFactor_HEADER

#include "MOOS/libMOOS/Thirdparty/AppCasting/AppCastingMOOSApp.h"
#include "PrimeEntry.h"
#include <list>
#include <string>

class PrimeFactor : public AppCastingMOOSApp
{
 public:
   PrimeFactor();
   ~PrimeFactor();

 protected: // Standard MOOSApp functions to overload  
   bool OnNewMail(MOOSMSG_LIST &NewMail);
   bool Iterate();
   bool OnConnectToServer();
   bool OnStartUp();

 protected: // Standard AppCastingMOOSApp function to overload 
  bool buildReport();
  unsigned long int m_test_num;
  unsigned long int m_incoming;
  unsigned long int m_outgoing;
  int m_index;
  std::list<PrimeEntry> m_primelist; //don't use namespace std in header files, can also use
  //std::list<std::string> m_primelist; USE if not converting in Mail

 protected:
   void registerVariables();

 private: // Configuration variables
  int listsize;

  
 private: // State variables
};

#endif 
