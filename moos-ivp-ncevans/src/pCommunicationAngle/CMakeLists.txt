#--------------------------------------------------------
# The CMakeLists.txt for:                       pCommunicationAngle
# Author(s):                              Craig Evans
#--------------------------------------------------------

SET(SRC
  CommunicationAngle.cpp
  VehicleComms.cpp
  CommunicationAngle_Info.cpp
  main.cpp
)

ADD_EXECUTABLE(pCommunicationAngle ${SRC})

TARGET_LINK_LIBRARIES(pCommunicationAngle
   ${MOOS_LIBRARIES}
   apputil
   mbutil
   m
   pthread)

