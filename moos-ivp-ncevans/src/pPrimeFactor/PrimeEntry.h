/************************************************************/
/*    NAME: Craig Evans                                              */
/*    ORGN: MIT, Cambridge MA                               */
/*    FILE: PrimeEntry.h                                          */
/*    DATE: March 4th, 2021                             */
/************************************************************/
#ifndef PrimeEntry_HEADER
#define PrimeEntry_HEADER


// File: PrimeEntry.h

 #include <string> 
 #include <vector> 
 #include <cstdint>

 class PrimeEntry
 {
 public:

   PrimeEntry();
   ~PrimeEntry();

   void setOriginalVal(unsigned long int v);
   void setReceivedIndex(unsigned int v)    {m_received_index=v;};
   void setCalculatedIndex(unsigned int v)  {m_calculated_index=v;};
   void setDone(bool v)                     {m_done=v;};
   void setStartIndex(unsigned long int v) {m_start_index=v;};
   void setStartTime(double v) {m_start_time=v;};
   void setTotalTime(double v);
   double getTotalTime() {return(m_total_time);};

   bool   done() {return(m_done);};

   bool   factor(unsigned long int max_steps);

   std::string  getReport();

 protected:
   uint64_t      m_start_index;
   uint64_t      m_orig;
   bool          m_done;
   unsigned int  m_received_index;
   unsigned int  m_calculated_index;
   uint64_t  m_current_int;
   double m_total_time;
   double m_start_time;

   std::vector<uint64_t> m_factors;
 };
 #endif 
