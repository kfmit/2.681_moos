/************************************************************/
/*    NAME: Craig Evans                                              */
/*    ORGN: MIT, Cambridge MA                               */
/*    FILE: GenPath.cpp                                        */
/*    DATE: December 29th, 1963                             */
/************************************************************/

#include <iterator>
#include "MBUtils.h"
#include "ACTable.h"
#include "GenPath.h"
#include "XYSegList.h"
#include <sstream>
#include <string>
using namespace std;

//---------------------------------------------------------
// Constructor

GenPath::GenPath()
{
  m_firsttime=true;
  m_send=true;
  m_sx=0;
  m_sy=0;
  m_point_change=false;
  m_current_index=0;
  m_the_index=0;
  m_nav_x=0;
  m_nav_y=0;
  m_not_complete=true;
}

//---------------------------------------------------------
// Destructor

GenPath::~GenPath()
{
}
void GenPath::getVisitPoint()
{
  double idnum=1;
  for(int i=0;i<m_points.size();i++){
 
    string list_item;
    list_item=m_points[i];
    //now we will parse the string up
    if(list_item!="lastpoint"||list_item!="firstpoint"){
 
      vector<string> svector;
      while(list_item != ""){
        svector.push_back(biteStringX(list_item, ','));
      }
      string xval, yval, id;
      for(unsigned int j=0; j<svector.size(); j++) {
        string pair = svector[j];
        string param = biteStringX(pair, '=');
        string value = pair;
        if(param == "x"){
          xval = value;
       
        }
        else if(param == "y")
          yval = value;
        else if(param == "id")
          id=value;
      }     
      if((xval != "") && (yval != "") && id!="") {
        VisitPoint new_entry;
        new_entry.setXVal(stod(xval.c_str()));
        new_entry.setYVal(stod(yval.c_str()));
        new_entry.setID(idnum);
        m_point_vec.push_back(new_entry);
        Notify("MY_X",new_entry.m_x);
        idnum=idnum+1;
      }

    }
    
  }
}
bool GenPath::getPath()
{
 double mini=1000000;
   int i=0;
   string pair=m_startpos;
   string x_st = biteStringX(pair, ',');
   string y_st = pair;
   double startx=m_nav_x;
   double starty=m_nav_y;
   m_sx=startx;
   m_sy=starty;
   int i1=0;
   for(int t=1;t<m_point_vec.size()+1;t++){
     mini=1000000000;
     for(int j=0;j<m_point_vec.size();j++){
       if(t==1){
         double ar1=(startx-m_point_vec[j].m_x)*(startx-m_point_vec[j].m_x);
         double ar2=(starty-m_point_vec[j].m_y)*(starty-m_point_vec[j].m_y);
         double ar=ar1+ar2;
         double distance=sqrt(ar);
         cout<<"this is distance "<<distance<<endl;
         if(distance<mini&&m_point_vec[j].m_point_order==0){
           mini=distance;
           i=int(m_point_vec[j].m_id);
         }
       }
       else{
         double ar1=(m_point_vec[i1].m_x-m_point_vec[j].m_x)*(m_point_vec[i1].m_x-m_point_vec[j].m_x);
         double ar2=(m_point_vec[i1].m_y-m_point_vec[j].m_y)*(m_point_vec[i1].m_y-m_point_vec[j].m_y);
         double ar=ar1+ar2;
         double distance=sqrt(ar);
         cout<<"THIS IS i "<<i1<<"This is j "<<j<<"THIS is dist "<<distance<<endl;
         if(distance<mini&&m_point_vec[j].m_point_order==0&&i1!=j){
           mini=distance;
           i=int(m_point_vec[j].m_id);
         }
       }
     }
     for(int w=0;w<m_point_vec.size();w++){
       int k=0;
       k=int(m_point_vec[w].m_id);
       if(k==i){
         m_point_vec[w].setPointOrder(t);
       }    
     }
     i=i-1;
     i1=i;
   }
    for(int j=0;j<m_point_vec.size();j++){
     cout<<"THIS IS my x "<<m_point_vec[j].m_x<<" THIS IS my y "<<m_point_vec[j].m_y<<" id "<<m_point_vec[j].m_id<<endl;
     cout<<"This is the order to travel "<<m_point_vec[j].m_point_order<<endl;
   }

   for(int k=1;k<m_point_vec.size()+1;k++){
     for(int j=0;j<m_point_vec.size();j++){
       if(m_point_vec[j].m_point_order==k){
         m_point_vec_new.push_back(m_point_vec[j]);
       }
     }
   }


  ///////////////////////////////////////////////////////////////
  unsigned int h=0;
   XYSegList my_seglist;
   if(m_point_vec_new.size()!=0){
   for(int i=0;i<m_point_vec_new.size();i++){

   my_seglist.add_vertex(m_point_vec_new[i].m_x, m_point_vec_new[i].m_y);
   }
   //my_seglist.delete_vertex(h);
   string update_str = "points = ";
   update_str      += my_seglist.get_spec();
   if(m_point_vec_new.size()<4){
     update_str=update_str+"#capture_radius=5.0";
   }
   Notify("UPDATES_VAR_LIST", update_str);  // UPDATES_VAR depends on your config
   }
   return true;
}
//---------------------------------------------------------
// Procedure: OnNewMail
bool GenPath::checkPoint()
{
  //int delete_index=m_current_index+m_the_index;
  for (int i=0;i<m_point_vec_new.size();i++){
    double x= m_point_vec_new[i].m_x;
    double y=  m_point_vec_new[i].m_y;
    double xdelt=(x-m_nav_x)*(x-m_nav_x);
    double ydelt=(y-m_nav_y)*(y-m_nav_y);
    double dist=sqrt(xdelt+ydelt);
    if(dist<5){
      m_point_vec_new.erase (m_point_vec_new.begin()+i);
      m_the_index=m_the_index-1;
      m_point_change=false;
    }
  }
  if(m_point_vec_new.size()<1){
    m_not_complete=false;
    Notify("POINTS_DONE_ALL_DONE", "true");
  }
  return true;
}
bool GenPath::OnNewMail(MOOSMSG_LIST &NewMail)
{
  AppCastingMOOSApp::OnNewMail(NewMail);

  MOOSMSG_LIST::iterator p;
  for(p=NewMail.begin(); p!=NewMail.end(); p++) {
    CMOOSMsg &msg = *p;
    string key    = msg.GetKey();
    if(key=="VISIT_POINT"){
      string sval  = msg.GetString();
      m_points.push_back(sval);
      if(sval=="lastpoint"&&m_points[0]=="firstpoint"&&m_send){
       
        getVisitPoint();
        bool yep=getPath();
        m_send=false;
      }
    }
    else if (key=="NAV_X"){
      double dval= msg.GetDouble();
      m_nav_x=dval;
      if(m_not_complete&&!m_send){
        bool checker=checkPoint();
      }
    }
    else if (key=="NAV_Y"){
      double dval= msg.GetDouble();
      m_nav_y=dval;
      if(m_not_complete&&!m_send){
        bool checker=checkPoint();
      }
    }
    /* else if (key=="WPT_INDEX"){
       cout<<"THIS IS WPT LOOP"<<endl;
       string sval  = msg.GetString();
      m_current_index=(atoi(sval.c_str()));
      cout<<"THIS IS MY current_index "<<m_current_index;
      m_point_change=true;
      }*/
      else if (key=="GENPATH_REGENERATE"){
        string sval  = msg.GetString();
          if (sval=="true"){
            // reportEvent("SVAL is true");
            m_send=true;
            if(m_point_vec_new.size()>0){
            m_point_vec.clear();
           
            //m_point_vec.push_back("firstpoint");
            for(int k=0;k<m_point_vec_new.size();k++){
              //reportEvent("looping through m_point_vec_new");

              m_point_vec.push_back(m_point_vec_new[k]);
              double idd=k+1;
              m_point_vec[k].setID(idd);
              m_point_vec[k].setPointOrder(0);
            }
             m_current_index=m_point_vec.size();
            //m_point_vec.push_back("lastpoint");
            m_point_vec_new.clear();
             reportEvent("Starting genpath");
            bool yep=getPath();
            reportEvent("Ending genpath");

            m_send=false;
            Notify("GENPATH_REGENERATE","false");
            }
          }
    }
     else{
       cout<<"I did not get it"<<endl;
     }
   }
	
   return(true);
}

//---------------------------------------------------------
// Procedure: OnConnectToServer

bool GenPath::OnConnectToServer()
{
   registerVariables();
   return(true);
}

//---------------------------------------------------------
// Procedure: Iterate()
//            happens AppTick times per second

bool GenPath::Iterate()
{
  AppCastingMOOSApp::Iterate();
  if(m_firsttime||m_points.size()<2){
    Notify("VEH_UP","true");
    //Notify("UTS_PAUSE","false");
         m_firsttime=false;
  }
  else if(m_points.back()=="lastpoint"){
    Notify("VEH_UP","false");
  }
  AppCastingMOOSApp::PostReport();
  return(true);
}

//---------------------------------------------------------
// Procedure: OnStartUp()
//            happens before connection is open

bool GenPath::OnStartUp()
{
  AppCastingMOOSApp::OnStartUp();

  STRING_LIST sParams;
  m_MissionReader.EnableVerbatimQuoting(false);
  if(!m_MissionReader.GetConfiguration(GetAppName(), sParams))
    reportConfigWarning("No config block found for " + GetAppName());

  STRING_LIST::iterator p;
  for(p=sParams.begin(); p!=sParams.end(); p++) {
    string line  = *p;
    string param = tolower(biteStringX(line, '='));
    string value = line;

    bool handled = false;
    if(param == "start_posit"){
      m_startpos = value;
    }

  }
  
  registerVariables();	
  return(true);
}

//---------------------------------------------------------
// Procedure: registerVariables

void GenPath::registerVariables()
{
  AppCastingMOOSApp::RegisterVariables();
  Register("VISIT_POINT");
  Register("NAV_X");
  Register("NAV_Y");
  // Register("WPT_INDEX");
  Register("GENPATH_REGENERATE");
}


//------------------------------------------------------------
// Procedure: buildReport()

bool GenPath::buildReport() 
{
  m_msgs << "============================================" << endl;
  m_msgs << "File:                                       " << endl;
  m_msgs << "============================================" << endl;

  ACTable actab(4);
  actab << "Alpha | Bravo | Charlie | Delta";
  actab.addHeaderLines();
  actab << "one" << "two" << "three" << "four";
  m_msgs << actab.getFormattedString()<<endl;
  m_msgs << "This the size of m_point_vec after clear "<< m_current_index<<endl;
  m_msgs << "This is NAV-X "<<m_nav_x<<endl;
  m_msgs << "The size of m_point_vec_new "<< m_point_vec_new.size()<<endl;
  m_msgs << "The size of m_point_vec "<< m_point_vec.size()<<endl;
  if (m_point_vec_new.size()>0){
    for(int i=0;i<m_point_vec_new.size();i++){
      m_msgs <<"x= "<<m_point_vec_new[i].m_x<<" y= "<<m_point_vec_new[i].m_y<<endl;

    }
  }
  return(true);
}




