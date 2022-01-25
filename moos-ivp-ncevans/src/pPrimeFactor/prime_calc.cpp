 /*----------------------------------------------------------------------*/
/************************************************************/
/*    NAME: Craig Evans                                              */
/*    ORGN: MIT, Cambridge MA                               */
/*    FILE: prime_calc.cpp                                          */
/*    DATE: December 29th, 1963                             */
/************************************************************/

 #include <iostream>   // For terminal I/O using cout                     
 #include <cstdlib>    // For converting C-Style string to number with atoi
 #include <sstream>
 #include <vector>
 #include <math.h>
 using namespace std;

 int main(int argc, char **argv)
 {
   if(argc != 2) {
     cout << "Usage: prime_fact NUMBER" << endl;
     exit(1);
   }
   std::vector<uint64_t> m_factors;

   uint64_t m_orig = atof(argv[1]);
   uint64_t m_current_int=m_orig;
   uint64_t p=sqrt(m_orig)+1;


   
   if(m_orig>3){
     for (unsigned long int i=2; i<=p; i++){
       if (m_current_int%i==0){;
         m_factors.push_back(i);
         m_current_int=m_current_int/i;
         i=i-1;
       }
     }
     if (m_current_int!=m_orig&&m_current_int!=1){
       if(m_factors.back()!=m_current_int){
         m_factors.push_back(m_current_int);
       }
     }
   }
   
   cout<<"I am getting out of the loop"<<endl;
   string fact_str="";
   stringstream my_note_string;

   
   if (m_factors.size()!=0){
    for (int i=0; i<m_factors.size(); i++){
      my_note_string<<":"<<m_factors[i];
    }
  }
   fact_str=my_note_string.str();
   cout << "This number "<<m_orig<<" has these factors" << fact_str<<endl;
   return(0);
 }

