/************************************************************/
/*    NAME: Craig Evans                                              */
/*    ORGN: MIT, Cambridge MA                               */
/*    FILE: PrimeEntry.cpp                                          */
/*    DATE: March 4th, 2021                             */
/************************************************************/


#include "ACTable.h"
#include "PrimeFactor.h"
#include <cstdint>
#include <sstream>
#include <list>
#include <string>

using namespace std;

//---------------------------------------------------------
// Constructor
PrimeEntry::PrimeEntry()
{
  m_start_index=2;
  m_received_index=0;
  m_done=false;
  m_calculated_index=0;
  m_orig=0;
  m_total_time=0;
  //m_factors(0)=0;

}
PrimeEntry::~PrimeEntry()
{
}
//Sets the incoming variable to m_orig
void PrimeEntry::setOriginalVal(unsigned long int num)
{
  m_orig=num;
  m_current_int=num;
}
bool PrimeEntry::factor(unsigned long int max_steps)
{
  bool done=true;
  uint64_t thistime=1;
  uint64_t p=sqrt(m_orig)+1;

  //Calculate the actual prime factors
  if(m_orig>3){
    for (unsigned long int i=m_start_index; i<=p; i++){
      if (m_current_int%i==0){
        m_factors.push_back(i);
        m_current_int=m_current_int/i;
        i=i-1;
      }
      //This if check if we met the limit for checks
      if(thistime==max_steps){
        setStartIndex(i);
        setDone(false);
        done=false;
        break;
      }
      thistime++;
    }
  }

  if (m_current_int!=m_orig&&m_current_int!=1&&done){
    if(m_factors.back()!=m_current_int){
      m_factors.push_back(m_current_int);
    }
  }
  //Set it to done if thr for loop completed 
  if (done){
    setDone(true);
    return true;
  }
  else{
    return true;
  }
}
void PrimeEntry::setTotalTime(double final_time)
{
  m_total_time=m_total_time+(final_time-m_start_time);
}
//Piece together all the elements of PrimeEntry for report
std::string PrimeEntry::getReport()
{
  stringstream my_note_string;
  my_note_string<<"orig="<<m_orig<<",";
  my_note_string<<"reveived="<<m_received_index;
  my_note_string<<",calculated="<<m_calculated_index;
  my_note_string<<",Time_calculating_factor "<<getTotalTime();
  my_note_string<<",primes=";
  if (m_factors.size()!=0){
    for (int i=0; i<m_factors.size(); i++){
      if(i!=m_factors.size()-1){
      my_note_string<<m_factors[i]<<":";
      }
      else{
        my_note_string<<m_factors[i];
      }
    }
  }
  else{
    my_note_string<<m_orig<<" HAS_NO_FACTORS";
  }
  my_note_string<<",username=Craig";
  string note=my_note_string.str();
  return note;
}
