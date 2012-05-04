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

SET (SamplingFilters_FILTERS_HDRS
    ${DREAM3DLib_SOURCE_DIR}/SamplingFilters/ChangeResolution.h
    ${DREAM3DLib_SOURCE_DIR}/SamplingFilters/CropVolume.h
)
#-- Add in any addition NON Filter classes here
SET (DREAM3DLib_SamplingFilters_HDRS
    ${SamplingFilters_FILTERS_HDRS}
)

SET (DREAM3DLib_SamplingFilters_SRCS
    ${DREAM3DLib_SOURCE_DIR}/SamplingFilters/ChangeResolution.cpp
    ${DREAM3DLib_SOURCE_DIR}/SamplingFilters/CropVolume.cpp
)
if (NOT DEFINED ONLY_FILTERS)
cmp_IDE_SOURCE_PROPERTIES( "DREAM3DLib/SamplingFilters" "${DREAM3DLib_SamplingFilters_HDRS}" "${DREAM3DLib_SamplingFilters_SRCS}" "0")
endif()
if ( ${PROJECT_INSTALL_HEADERS} EQUAL 1 )
    INSTALL (FILES ${DREAM3DLib_SamplingFilters_HDRS}
            DESTINATION include/DREAM3D/SamplingFilters
            COMPONENT Headers   )
endif()