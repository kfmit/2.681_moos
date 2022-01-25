// File: PrimeEntry.cpp
// Kat Fung
// March 04 2021 - 10MAR21
// Lab 05

#include "PrimeEntry.h"
#include <iterator>
#include "MBUtils.h"
#include "ACTable.h"
#include <cmath>
#include <string>
#include <cstdlib>
#include <list> //using lists here
#include <iostream>
#include <cstdint>
#include <sstream> //needed for stringstream

using namespace std;

//---------------------------------------------------------
// Constructor
PrimeEntry::PrimeEntry()
 // here, we are creating the math and stuff behiind the variable in PrimeEntry.h
 // so that it can be saved and called in getReport when we want to Notify
  
{ 

  /*
   uint64_t      m_start_index; //holds where we start and come back to continue factoring in for loop
   uint64_t      m_orig;        //
   bool          m_done;
   unsigned int  m_received_index; // where we left off the last time we tried the loop
   unsigned int  m_calculated_index; // the calculated new N

   std::vector<uint64_t> m_factors; */
  

  m_start_index=2;      //starting at 2 ONLY on the first round

}

// this is the setOriginalVal function
void PrimeEntry::setOriginalVal(unsigned long int v)
{
  m_orig = v;              // set the original value to v, passed in OnNewMail
  m_currentval = m_orig;   // value for testing prime, saves the divided val, doesn't overwrite orig  (Thank you Craig!)
  return;
}

// this is the factor function
bool PrimeEntry::factor(unsigned long int max_steps)
{ // v is an ORIGINAL INPUT that changes with each round as we put numbers in
  // this function will actually do the process of finding the factor of m_orig
  // set max steps: 100k to 1mil in Iterate loop
  
  unsigned long int x;                                   // creating integer x for division purposes
  bool isPrime=true;                                     // logical to indicate if prime or not
       

  for(x=m_start_index; x<=max_steps; x++)               //from 2 to the max amount of steps we set goes through all factors of a number
    {	    
       
      
      if(m_currentval%x==0)                          // if v has no remainder, x is a factor of v
	{
	  m_currentval=m_currentval/x;               //divide current val by x, gets smaller each time	
	
	  if(isPrime==true)                          // if the true flag is still up, add factor x to the list
	    {
	      m_factors.push_back(x);                // add the prime factor of x into the vector m_factors
	      cout<<"added factor"<<endl;            // if that worked, should see added factor
	                                             // this x is the last prime factor we landed on, updates through loop
	      x = x-1;                               // tests for doubles of a prime factor
	    
	    // Test for finished factoring
	      if(m_currentval == 1)                  // if we can't divide it anymore and m_calculated_index is one
		{
		  m_done = true;                    // set done as true
		  //m_calculated_index = y;          // the step which it was calculated at   
		  //y++;
		  break;                            // if it is done, get out of for loop
		} //end of if=1
	      else                                  // if the divided current value is not 1 
		{
		m_start_index = x;                  //set the start to the last x if we need to come back through the for loop again
		
		m_done = false;                    // we are NOT DONE keep factoring, start over
		                                    // flag done as false and return false
		} //end of else
	    
	    } // end of if prime true
	} //end of if m_current%x=0 

      // If no x factors except itself, then this number is prime already (STILL INSIDE FOR LOOP)
      
      else if(x==max_steps && m_done==false)           // if on the last step AND done isnt true and no prime factors found
	{
	 m_factors.push_back(m_orig);               // then the number is already prime, add the original number to the list
	 m_done = true;
	} //end of else
      
    } // end of for loop  

  return m_done;
	  
	  } //end of factor function



// this is the getReport function
      
string PrimeEntry::getReport()
  
{
  // needs to contain all the info from calcualting the prime numbers
  stringstream ss_report;                                    //create a stringstream of strings
  // convert from unsigned long int to string within each or print as var?
  ss_report<<"original number:"<<m_orig<<"; ";               // original value
  ss_report<<"received index:"<<m_received_index<<"; ";      // received index
  ss_report<<"calculated index:"<<m_calculated_index<<"; ";  // calculated index
  ss_report<<"prime factors are:";                           // show the prime factors using if and for loop
  if (m_factors.size()==0)                                // if there are NO primes
    {
      ss_report<<"none,"<<m_orig<<" is already a prime number";
    }
    else // if there are factors in m_factor
      {
       for(int ii=0; ii<m_factors.size(); ii++)
	 {
	   ss_report<<m_factors[ii]<<", "; //index into m_factors list and put those numbers into report
	 }
      }
  string big_report=ss_report.str(); //put it all together

  return big_report; // ----------------do i need // end of string
}



  /*

we have a number, N
N has factors x, which is an array of numbers
x is prime if ony=ly x and 1 are factors of x
from y = 2 to sqrt(N)
 if x is divisible by y it is not prime

so for those xvalues that are not divisble by any y's that are not themselves, 
save the x as a prime factor of N

   */
