#--////////////////////////////////////////////////////////////////////////////
#--
#--  Copyright (c) 2011, Michael A. Jackson. BlueQuartz Software
#--  Copyright (c) 2011, Michael Groeber, US Air Force Research Laboratory
#--  All rights reserved.
#--  BSD License: http://www.opensource.org/licenses/bsd-license.html
#--
#-- This code was partly written under US Air Force Contract FA8650-07-D-5800
#--
#--////////////////////////////////////////////////////////////////////////////

set(DREAM3DLib_Utilities_HDRS
  ${DREAM3DLib_SOURCE_DIR}/Utilities/ColorTable.h
  ${DREAM3DLib_SOURCE_DIR}/Utilities/ColorUtilities.h
  ${DREAM3DLib_SOURCE_DIR}/Utilities/DREAM3DEndian.h
  ${DREAM3DLib_SOURCE_DIR}/Utilities/DREAM3DRandom.h
  ${DREAM3DLib_SOURCE_DIR}/Utilities/ImageUtilities.h
  ${DREAM3DLib_SOURCE_DIR}/Utilities/PoleFigureUtilities.h
  ${DREAM3DLib_SOURCE_DIR}/Utilities/TimeUtilities.h


)

set(DREAM3DLib_Utilities_SRCS
  ${DREAM3DLib_SOURCE_DIR}/Utilities/ColorTable.cpp
  ${DREAM3DLib_SOURCE_DIR}/Utilities/ColorUtilities.cpp
  ${DREAM3DLib_SOURCE_DIR}/Utilities/DREAM3DRandom.cpp
  ${DREAM3DLib_SOURCE_DIR}/Utilities/ImageUtilities.cpp
  ${DREAM3DLib_SOURCE_DIR}/Utilities/PoleFigureUtilities.cpp

)

cmp_IDE_SOURCE_PROPERTIES( "DREAM3DLib/Utilities" "${DREAM3DLib_Utilities_HDRS}" "${DREAM3DLib_Utilities_SRCS}" "0")
if( ${PROJECT_INSTALL_HEADERS} EQUAL 1 )
    INSTALL (FILES ${DREAM3DLib_Utilities_HDRS}
            DESTINATION include/DREAM3D/Utilities
            COMPONENT Headers   )
endif()



include(${DREAM3DLib_SOURCE_DIR}/Utilities/IO/SourceList.cmake)
#include(${DREAM3DLib_SOURCE_DIR}/Utilities/Mesh/SourceList.cmake)


set(DREAM3DLib_Utilities_HDRS ${DREAM3DLib_Utilities_HDRS} ${DREAM3DLib_Utilities_IO_HDRS})
set(DREAM3DLib_Utilities_SRCS ${DREAM3DLib_Utilities_SRCS} ${DREAM3DLib_Utilities_IO_SRCS})