#--------------------------------------------------------
# The CMakeLists.txt for:                       pFrontEstimate
# Author(s):                              Kat Fung
#--------------------------------------------------------

SET(SRC
  FrontEstimate.cpp
  FrontEstimate_Info.cpp
  main.cpp
)

ADD_EXECUTABLE(pFrontEstimate ${SRC})

TARGET_LINK_LIBRARIES(pFrontEstimate
   ${MOOS_LIBRARIES}
   apputil
   mbutil
   m
   pthread)

