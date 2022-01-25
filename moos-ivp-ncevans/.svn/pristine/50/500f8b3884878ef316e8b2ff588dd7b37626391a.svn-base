#--------------------------------------------------------
# The CMakeLists.txt for:                  pFrontEstimate
# Author(s):                               Henrik Schmidt
#--------------------------------------------------------

SET(SRC
  FrontEstimate.cpp
  pFrontEstimateMain.cpp
)

ADD_EXECUTABLE(pFrontEstimate ${SRC})
   
TARGET_LINK_LIBRARIES(pFrontEstimate
   ${MOOS_LIBRARIES}
   geometry
   henrik_anneal
   ufield
   apputil
   mbutil
   m
   pthread)
