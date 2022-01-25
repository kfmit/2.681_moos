#--------------------------------------------------------
# The CMakeLists.txt for:                       pCommunicationAngle_kfung
# Author(s):                              Kat Fung
#--------------------------------------------------------

SET(SRC
  CommunicationAngle_kfung.cpp
  CommunicationAngle_kfung_Info.cpp
  Geometry.cpp
  main.cpp
)

ADD_EXECUTABLE(pCommunicationAngle_kfung ${SRC})

TARGET_LINK_LIBRARIES(pCommunicationAngle_kfung
   ${MOOS_LIBRARIES}
   apputil
   mbutil
   m
   pthread)

