/************************************************************/
/*    NAME: Craig Evans                                              */
/*    ORGN: MIT, Cambridge MA                               */
/*    FILE: VehicleComms.h                                          */
/*    DATE: December 29th, 1963                             */
/************************************************************/
#ifndef VehicleComms_HEADER
#define VehicleComms_HEADER

//File: VehicleComms.h

 #include <string> 
 #include <vector> 
 #include <cstdint>



class VehicleComms
 {
 public:

   VehicleComms();
   ~VehicleComms();

  public:
   bool getOmega();
   bool getMessage(bool nan);
   bool getTransmissionLoss();
   double calcAngle(double Radius);
   double getCircleRadius();
   std::string m_acoustic_path;
   std::string m_connectivity_loc;
   std::string m_os_name;
   bool m_no_chance;
   double m_deltaz;
   double m_omega;
   double m_transx;
   double m_transy;
   double m_transd;
   double m_TL;
   double m_collab_xval;
   double m_collab_yval;
   double m_collab_depthval;
   double m_collab_speedval;
   double m_collab_headval;
   double m_os_x;
   double m_os_y;
   double m_os_depth;
   double m_os_heading;
   double m_os_speed;
   double m_old_zeta;
   double m_old_r;
   double m_z_TOT;
   double m_nav_r;
 };
 #endif 
