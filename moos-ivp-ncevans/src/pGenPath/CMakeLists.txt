#--------------------------------------------------------
# The CMakeLists.txt for:                       pGenPath
# Author(s):                              Craig Evans
#--------------------------------------------------------

SET(SRC
  GenPath.cpp
  GenPath_Info.cpp
  VisitPoint.cpp
  main.cpp
)

ADD_EXECUTABLE(pGenPath ${SRC})

TARGET_LINK_LIBRARIES(pGenPath
   ${MOOS_LIBRARIES}
   geometry
   apputil
   mbutil
   m
   pthread)

