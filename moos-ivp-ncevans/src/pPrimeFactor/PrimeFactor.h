/************************************************************/
/*    NAME: Craig Evans                                     */
/*    ORGN: MIT, Cambridge MA                               */
/*    FILE: PrimeFactor.h                                   */
/*    DATE: March 4th, 2021                                 */
/************************************************************/

#ifndef PrimeFactor_HEADER
#define PrimeFactor_HEADER

#include "MOOS/libMOOS/Thirdparty/AppCasting/AppCastingMOOSApp.h"
#include <list>
#include "PrimeEntry.h"
using namespace std;

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

 protected:
   void registerVariables();
   uint64_t m_incoming_seq;
   uint64_t m_outgoing_pos;
   list<PrimeEntry> m_prime_entry_list;

 private: // Configuration variables

 private: // State variables
};

#endif 
