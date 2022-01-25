/************************************************************/
/*    NAME: Craig Evans                                              */
/*    ORGN: MIT, Cambridge MA                               */
/*    FILE: PointAssign.cpp                                        */
/*    DATE: December 29th, 1963                             */
/************************************************************/

#include <iterator>
#include "MBUtils.h"
#include "ACTable.h"
#include "PointAssign.h"
#include <sstream>
#include <string>
#include "XYPoint.h"  
using namespace std;

//---------------------------------------------------------
// Constructor

PointAssign::PointAssign()
{
  m_first=true;
  m_v1_color="yellow";
  m_v2_color="red";
  m_done=true;
  m_got_1="";
  m_got_2="";
}

//---------------------------------------------------------
// Destructor

PointAssign::~PointAssign()
{
}
bool PointAssign::getPoints()
{
  if (m_assign_by_region_str=="false"){
    m_NAME2points.push_back("firstpoint");
    for(int j=0; j<m_allpoints.size(); j++){
      if(j%2==0){
        m_NAME1points.push_back(m_allpoints[j]);                        
      }
      else{
        m_NAME2points.push_back(m_allpoints[j]);
      }
    }
    m_NAME1points.push_back("lastpoint");
  }
  else{
    double x=0;
    double y=0;
    m_NAME2points.push_back("firstpoint");
    m_NAME1points.push_back("firstpoint");
    for(int i=0;i<m_allpoints.size();i++){
      string list_item;
      list_item=m_allpoints[i];
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
          if(param == "x")
            xval = value;
          else if(param == "y")
            yval = value;
          else if(param == "id")
            id=value;
        }     
        if((xval != "") && (yval != "") && id!="") {
          x=stod(xval.c_str());
          y=stod(yval.c_str());
        }
        if(x<87.5){
          m_NAME1points.push_back(m_allpoints[i]);                          
        }
        else{
          m_NAME2points.push_back(m_allpoints[i]);
        }
      }
    }
    m_NAME1points.push_back("lastpoint");
    m_NAME2points.push_back("lastpoint");
  }
  for(int i=0;i<m_NAME1points.size();i++){
    stringstream name;
    string mes_name;
    name<<"VISIT_POINT_"<<m_vehicle1;
    mes_name=name.str();
    Notify(mes_name,m_NAME1points[i]);
  }
  for(int i=0;i<m_NAME2points.size();i++){
    stringstream name;
    string mes_name;
    name<<"VISIT_POINT_"<<m_vehicle2;
    mes_name=name.str();
    Notify(mes_name,m_NAME2points[i]);
  }
  return true;
}
void PointAssign::getView()
{
   for(int i=0;i<m_NAME1points.size();i++){
    stringstream name;
    string list_item;
    list_item=m_NAME1points[i];
    if(list_item!="lastpoint"||list_item!="firstpoint"){
      vector<string> svector;
      while(list_item != "")
        svector.push_back(biteStringX(list_item, ','));
      string xval, yval, id;

      for(unsigned int j=0; j<svector.size(); j++) {
        string pair = svector[j];
        string param = biteStringX(pair, '=');
        string value = pair;
        if(param == "x")
          xval = value;
        else if(param == "y")
          yval = value;
        else if(param == "id")
          id=value;
      }
      if((xval != "") && (yval != "") && id!="") {
        double x=stod(xval.c_str());
        double y=stod(yval.c_str());
        postViewPoint(x,y,id,m_v1_color);
      }
    }
  
  }
  for(int i=0;i<m_NAME2points.size();i++){
    stringstream name;
    string list_item;
    list_item=m_NAME2points[i];
    if(list_item!="lastpoint"||list_item!="firstpoint"){
      vector<string> svector;
      while(list_item != "")
        svector.push_back(biteStringX(list_item, ','));
      string xval, yval, id;

      for(unsigned int j=0; j<svector.size(); j++) {
        string pair = svector[j];
        string param = biteStringX(pair, '=');
        string value = pair;
        if(param == "x")
          xval = value;
        else if(param == "y")
          yval = value;
        else if(param == "id")
          id=value;
      }
      if((xval != "") && (yval != "") && id!="") {
        double x=stod(xval.c_str());
        double y=stod(yval.c_str());
        postViewPoint(x,y,id,m_v2_color);
      }
    }
  
  }
}
void PointAssign::postViewPoint(double x, double y, string label, string color)
{
   XYPoint point(x, y);
   point.set_label(label);
   point.set_color("vertex", color);
   point.set_param("vertex_size", "2");

   string spec = point.get_spec();    // gets the string representation of a point
   Notify("VIEW_POINT", spec);
}
//---------------------------------------------------------
// Procedure: OnNewMail

bool PointAssign::OnNewMail(MOOSMSG_LIST &NewMail)
{
  AppCastingMOOSApp::OnNewMail(NewMail);

  MOOSMSG_LIST::iterator p;
  for(p=NewMail.begin(); p!=NewMail.end(); p++) {
    CMOOSMsg &msg = *p;
    string key    = msg.GetKey();
    if (key=="VISIT_POINT"){
      reportEvent("I MADE IT TO THE VISIT_POINT");
    string sval  = msg.GetString();
    m_allpoints.push_back(sval);
    }
    else if (key==m_veh1_check){
      string sval  = msg.GetString();
      m_got_1=sval;
    }
    else if (key==m_veh2_check){
      string sval  = msg.GetString();
      m_got_2=sval;
    }
  }
    return(true);
}

//---------------------------------------------------------
// Procedure: OnConnectToServer

bool PointAssign::OnConnectToServer()
{
   registerVariables();
   return(true);
}

//---------------------------------------------------------
// Procedure: Iterate()
//            happens AppTick times per second

bool PointAssign::Iterate()
{
  AppCastingMOOSApp::Iterate();
  if(m_first){
    cout<<"##########################################"<<endl;
    cout<<"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"<<endl;
    Notify("UTS_PAUSE","false");
    m_first=false;
  }
  else{
    if((m_allpoints.size() > 0) && m_allpoints.back()=="lastpoint"&&
       m_got_1=="true"&&m_got_2=="true"){
      // Notify("VISIT_POINT_GILDA","I_MADE_IT");
      bool got=getPoints();
      getView();
      m_done=false;
    }
  }
  AppCastingMOOSApp::PostReport();
  return(true);
}

//---------------------------------------------------------
// Procedure: OnStartUp()
//            happens before connection is open

bool PointAssign::OnStartUp()
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
    cout <<"THIS IS THE LIST OF NAMES"<<endl;
    if(param == "vehicle_name1"){
      m_vehicle1 = value;
      cout<<m_vehicle1<<endl;
      stringstream name;
      name<<"VEH_UP_"<<m_vehicle1;
      m_veh1_check=name.str();

    }
    else if(param == "vehicle_name2"){
      m_vehicle2 = value;
      cout<<m_vehicle2<<endl;
      stringstream name;
      name<<"VEH_UP_"<<m_vehicle2;
      m_veh2_check=name.str();
    }
    else if(param == "assign_by_region"){
      m_assign_by_region_str = value;
      cout<<"ASSIGN"<<m_assign_by_region_str<<endl;
    }
  }


  // if(!handled)
  //  reportUnhandledConfigWarning(orig);

  
  
  registerVariables();	
  return(true);
}

//---------------------------------------------------------
// Procedure: registerVariables

void PointAssign::registerVariables()
{
 
 


  AppCastingMOOSApp::RegisterVariables();
   Register(m_veh1_check);
   Register(m_veh2_check);
   Register("VISIT_POINT");
   //Notify("VISIT_POINT","Iregistered");
  // Register("FOOBAR", 0);
}


//------------------------------------------------------------
// Procedure: buildReport()

bool PointAssign::buildReport() 
{
  m_msgs << "============================================" << endl;
  m_msgs << "File:                                       " << endl;
  m_msgs << "============================================" << endl;

  ACTable actab(4);
  actab << "VIEW_POINT | V1_VIEWPOINT| V2_VIEWPOINT";
  actab.addHeaderLines();
  actab <<"JUST TESTING A THEORY"; //<< m_NAME1points[0]<< m_NAME2points[0];
  m_msgs << m_got_2<<endl;
  m_msgs << m_veh2_check<<endl;
  m_msgs << m_veh1_check<<endl;
  m_msgs << m_first<<endl;
  m_msgs << m_got_2<<endl;
  m_msgs << m_got_1<<endl;

  return(true);
}




