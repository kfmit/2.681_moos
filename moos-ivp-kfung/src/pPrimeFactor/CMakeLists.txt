#--------------------------------------------------------
# The CMakeLists.txt for:                       pPrimeFactor
# Author(s):                              Kat Fung
#--------------------------------------------------------

SET(SRC
  PrimeFactor.cpp
  PrimeEntry.cpp
  PrimeFactor_Info.cpp
  main.cpp
)

ADD_EXECUTABLE(pPrimeFactor ${SRC})

TARGET_LINK_LIBRARIES(pPrimeFactor
   ${MOOS_LIBRARIES}
   apputil
   mbutil
   m
   pthread)

