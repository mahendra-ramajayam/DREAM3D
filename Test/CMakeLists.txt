#--////////////////////////////////////////////////////////////////////////////
#--
#--  Copyright (c) 2009, Michael A. Jackson. BlueQuartz Software
#--  Copyright (c) 2009, Michael Groeber, US Air Force Research Laboratory
#--  All rights reserved.
#--  BSD License: http://www.opensource.org/licenses/bsd-license.html
#--
#-- This code was partly written under US Air Force Contract FA8650-07-D-5800
#--
#--////////////////////////////////////////////////////////////////////////////

project(DREAM3DTest)

set(DREAM3D_DATA_DIR ""  CACHE PATH "The directory where to find test data files")



configure_file(${PROJECT_RESOURCES_DIR}/EbsdTestFiles/EbsdTestFileLocation.h.in
               ${DREAM3DTest_BINARY_DIR}/EbsdTestFileLocation.h @ONLY IMMEDIATE)
configure_file(${DREAM3DTest_SOURCE_DIR}/TestFileLocations.h.in
               ${DREAM3DTest_BINARY_DIR}/TestFileLocations.h @ONLY IMMEDIATE)

include_directories(${DREAM3DTest_BINARY_DIR})
include_directories(${DREAM3DProj_SOURCE_DIR}/Source/Applications)
include_directories(${DREAM3DProj_SOURCE_DIR}/Source/Plugins)
include_directories(${DREAM3DProj_SOURCE_DIR}/Source/QtSupport)
include_directories(${DREAM3DProj_SOURCE_DIR}/Source/FilterWidgets)
# --------------------------------------------------------------------------
#
# --------------------------------------------------------------------------
macro(MXA_ADD_TEST testname Exename)
    if (NOT APPLE)
        ADD_TEST(${testname} ${Exename})
    else()
        if (NOT ${CMAKE_OSX_ARCHITECTURES} STREQUAL "")
        foreach(arch ${CMAKE_OSX_ARCHITECTURES})
            ADD_TEST( ${arch}_${testname} ${CMP_OSX_TOOLS_SOURCE_DIR}/UBTest.sh ${arch} ${Exename} )
        endforeach()
        else()
            ADD_TEST(${testname} ${Exename})
        endif()
    endif()
endmacro()

# --------------------------------------------------------------------------
# FilterPipelineTest
# --------------------------------------------------------------------------
add_executable(FilterPipelineTest FilterPipelineTest.cpp )
target_link_libraries(FilterPipelineTest DREAM3DLib)
add_test(FilterPipelineTest ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/FilterPipelineTest)

# --------------------------------------------------------------------------
# StatsData Test
# --------------------------------------------------------------------------
add_executable(StatsDataTest StatsDataTest.cpp )
target_link_libraries(StatsDataTest DREAM3DLib)
add_test(StatsDataTest ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/StatsDataTest)

# --------------------------------------------------------------------------
# DataContainer Test
# --------------------------------------------------------------------------
add_executable(DataContainerTest DataContainerTest.cpp )
target_link_libraries(DataContainerTest DREAM3DLib)
add_test(DataContainerTest ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/DataContainerTest)

# --------------------------------------------------------------------------
# H5Support Library Testing
# --------------------------------------------------------------------------
add_executable(H5LiteTest ${DREAM3DTest_SOURCE_DIR}/H5LiteTest.cpp)
target_link_libraries(H5LiteTest H5Support MXA)
add_test(H5LiteTest ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/H5LiteTest)

add_executable(H5UtilitiesTest ${DREAM3DTest_SOURCE_DIR}/H5UtilitiesTest.cpp)
target_link_libraries(H5UtilitiesTest H5Support MXA)
add_test(H5UtilitiesTest ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/H5UtilitiesTest)


# --------------------------------------------------------------------------
# DataArray Testing
# --------------------------------------------------------------------------
add_executable(DataArrayTest ${DREAM3DTest_SOURCE_DIR}/DataArrayTest.cpp)
target_link_libraries(DataArrayTest DREAM3DLib)
add_test(DataArrayTest ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/DataArrayTest)

# --------------------------------------------------------------------------
# File Conversion Testing
# --------------------------------------------------------------------------
add_executable(PhIOTest ${DREAM3DTest_SOURCE_DIR}/PhIOTest.cpp)
target_link_libraries(PhIOTest DREAM3DLib)
add_test(PhIOTest ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/PhIOTest)

add_executable(DxIOTest ${DREAM3DTest_SOURCE_DIR}/DxIOTest.cpp)
target_link_libraries(DxIOTest DREAM3DLib)
add_test(DxIOTest ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/DxIOTest)

add_executable(VtkGrainIdIOTest ${DREAM3DTest_SOURCE_DIR}/VtkGrainIdIOTest.cpp)
target_link_libraries(VtkGrainIdIOTest DREAM3DLib)
add_test(VtkGrainIdIOTest ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/VtkGrainIdIOTest)

# --------------------------------------------------------------------------
# Ebsd Data File Testing
# --------------------------------------------------------------------------
add_executable(CtfReaderTest ${DREAM3DTest_SOURCE_DIR}/CtfReaderTest.cpp)
target_link_libraries(CtfReaderTest EbsdLib)
add_test(CtfReaderTest ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/CtfReaderTest)

#add_executable(EbsdImportTest ${DREAM3DTest_SOURCE_DIR}/EbsdImportTest.cpp
#                              ${DREAM3DProj_SOURCE_DIR}/Source/Plugins/EbsdImport/EbsdImport.cpp)
#target_link_libraries(EbsdImportTest DREAM3DLib MXA EbsdLib H5Support)
#add_test(EbsdImportTest ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/EbsdImportTest)




if (NOT ${DREAM3D_DATA_DIR} STREQUAL "")
    message(STATUS "Synthetic Builder Test using ${DREAM3D_DATA_DIR} as data directory.")
    message(STATUS "  Please make sure the proper files are available in that directory")

    # --------------------------------------------------------------------------
    # FindNeighbors Testing
    # --------------------------------------------------------------------------
    add_executable(FindNeighborsTest ${DREAM3DTest_SOURCE_DIR}/FindNeighborsTest.cpp)
    target_link_libraries(FindNeighborsTest DREAM3DLib)
    add_test(FindNeighborsTest ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/FindNeighborsTest)

    # --------------------------------------------------------------------------
    # SyntheticBuilder Test
    # --------------------------------------------------------------------------
    add_executable(SyntheticBuilderTest ${DREAM3DTest_SOURCE_DIR}/SyntheticBuilderTest.cpp)
    target_link_libraries(SyntheticBuilderTest DREAM3DLib)
    add_test(SyntheticBuilderTest ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/SyntheticBuilderTest)
endif()

# --------------------------------------------------------------------------
# Preflight Test
# --------------------------------------------------------------------------
add_executable(PreFlightTest ${DREAM3DTest_SOURCE_DIR}/PreFlightTest.cpp)
target_link_libraries(PreFlightTest DREAM3DLib)
add_test(PreFlightTest ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/PreFlightTest)


# --------
add_executable(GrainDataReaderTest ${DREAM3DTest_SOURCE_DIR}/GrainDataReaderTest.cpp
                                ${DREAM3DTest_SOURCE_DIR}/CSVGrainDataReader.cpp )

# --------
add_executable(ODFTest ${DREAM3DTest_SOURCE_DIR}/ODFTest.cpp)
target_link_libraries(ODFTest DREAM3DLib)

# --------
add_executable(VoxelTest ${DREAM3DTest_SOURCE_DIR}/VoxelTest.cpp)
#target_link_libraries(VoxelTest DREAM3DLib)

# --------
add_executable(TextureTest ${DREAM3DTest_SOURCE_DIR}/TextureTest.cpp)
target_link_libraries(TextureTest DREAM3DLib)

# --------
#add_executable(DxTest ${DREAM3DTest_SOURCE_DIR}/DxTest.cpp 
#                        ${DREAM3DProj_SOURCE_DIR}/Source/Plugins/GrainGenerator/GrainGeneratorFunc.cpp
#                        ${DREAM3DProj_SOURCE_DIR}/Source/Plugins/GrainGenerator/Algorithms/PackGrainsGen3.cpp
#                        ${DREAM3DProj_SOURCE_DIR}/Source/Plugins/GrainGenerator/Algorithms/PackPrimaryPhases.cpp
#                        ${DREAM3DProj_SOURCE_DIR}/Source/Plugins/GrainGenerator/StructureReaders/DXStructureReader.cpp  )
#target_link_libraries(DxTest DREAM3DLib)

# --------
add_executable(SurfaceMeshTest ${DREAM3DTest_SOURCE_DIR}/SurfaceMeshTest.cpp)
target_link_libraries(SurfaceMeshTest DREAM3DLib)

# --------
add_executable(StatsGenTest ${DREAM3DTest_SOURCE_DIR}/StatsGenTest.cpp)
target_link_libraries(StatsGenTest DREAM3DLib)

# --------
add_executable(RNGTest ${DREAM3DTest_SOURCE_DIR}/RNGTest.cpp)
target_link_libraries(RNGTest DREAM3DLib)

# --------
add_executable(ResFixer ${DREAM3DTest_SOURCE_DIR}/ResFixer.cpp)
target_link_libraries(ResFixer EbsdLib MXA DREAM3DLib)
