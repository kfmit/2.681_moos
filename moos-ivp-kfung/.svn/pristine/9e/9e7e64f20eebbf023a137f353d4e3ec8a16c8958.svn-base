 // File: PrimeEntry.h
 // Kat Fung
 // March 04 2021
 // Taken From Lab 05 Section 4.2
 // Creating a class called Prime Entry to calculate prime values



 #include <string> 
 #include <vector> 
 #include <cstdint>

 #ifndef PRIME_ENTRY_HEADER
 #define PRIME_ENTRY_HEADER

 class PrimeEntry
 {
 public:

   PrimeEntry();
   ~PrimeEntry() {};

   void setOriginalVal(unsigned long int v); //void means no type
   void setReceivedIndex(unsigned int v)    {m_received_index=v;};
   void setCalculatedIndex(unsigned int v)  {m_calculated_index=v;};
   void setDone(bool v)                     {m_done=v;};

    // Time related functions
   void setStartTime(double v)              {m_start_time=v;}
   void setEndTime(double v)                {m_end_time=v;}
   double getElapsedTime();

   bool   done() {return(m_done);};

   bool   factor(unsigned long int max_steps); //calculate primes here

   std::string  getReport(); //output of all the saved info

 protected:
   uint64_t      m_start_index;
   uint64_t      m_orig;
   bool          m_done;
   unsigned long int  m_received_index;
   unsigned long int  m_calculated_index;
   unsigned long int m_currentval;

   std::vector<uint64_t> m_factors;

    // Time related member variables
   double   m_start_time;
   double   m_end_time;
   
 };
 #endif 
