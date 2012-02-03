/* ============================================================================
 * Copyright (c) 2012 Michael A. Jackson (BlueQuartz Software)
 * Copyright (c) 2012 Dr. Michael A. Groeber (US Air Force Research Laboratories)
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright notice, this
 * list of conditions and the following disclaimer in the documentation and/or
 * other materials provided with the distribution.
 *
 * Neither the name of Michael A. Groeber, Michael A. Jackson, the US Air Force,
 * BlueQuartz Software nor the names of its contributors may be used to endorse
 * or promote products derived from this software without specific prior written
 * permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
 * USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *  This code was written under United States Air Force Contract number
 *                           FA8650-07-D-5800
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */



#include "DREAM3DLib/DREAM3DLib.h"
#include "DREAM3DLib/Common/Observer.h"
#include "DREAM3DLib/Common/FilterPipeline.h"
#include "DREAM3Dlib/GenericFilters/DataContainerWriter.h"
#include "DREAM3DLib/GenericFilters/VtkRectilinearGridWriter.h"
#include "DREAM3DLib/ReconstructionFilters/LoadSlices.h"
#include "DREAM3DLib/ReconstructionFilters/AlignSections.h"
#include "DREAM3DLib/ReconstructionFilters/SegmentGrains.h"
#include "DREAM3DLib/ReconstructionFilters/CleanupGrains.h"

#include "UnitTestSupport.hpp"
#include "TestFileLocations.h"

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void RemoveTestFiles()
{

}



// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void TestFilterPipeline()
{

  // Create our Pipeline object
  FilterPipeline::Pointer pipeline = FilterPipeline::New();

  LoadSlices::Pointer load_slices = LoadSlices::New();
  //  pipeline->pushBack(load_slices);

  AlignSections::Pointer align_sections = AlignSections::New();
  pipeline->pushBack(align_sections);

  SegmentGrains::Pointer segment_grains = SegmentGrains::New();
  pipeline->pushBack(segment_grains);

  CleanupGrains::Pointer cleanup_grains = CleanupGrains::New();
  pipeline->pushBack(cleanup_grains);

  DataContainerWriter::Pointer writer = DataContainerWriter::New();
  pipeline->pushBack(writer);

  VtkRectilinearGridWriter::Pointer vtkWriter = VtkRectilinearGridWriter::New();
  pipeline->pushBack(vtkWriter);

  pipeline->popFront();
  //  pipeline->printFilterNames(std::cout);
  DREAM3D_REQUIRE_EQUAL(4, pipeline->size());

  pipeline->pushFront(align_sections);
  //  pipeline->printFilterNames(std::cout);
  DREAM3D_REQUIRE_EQUAL(5, pipeline->size());

  pipeline->pushFront(load_slices);
  //  pipeline->printFilterNames(std::cout);
  DREAM3D_REQUIRE_EQUAL(6, pipeline->size());

  pipeline->popBack(); // Pop off the vtkwriter
  //  pipeline->printFilterNames(std::cout);
  DREAM3D_REQUIRE_EQUAL(5, pipeline->size());

  pipeline->erase(pipeline->size() - 1); // Erase the data container writer
  //  pipeline->printFilterNames(std::cout);
  DREAM3D_REQUIRE_EQUAL(4, pipeline->size());

  pipeline->insert(pipeline->size(), writer);
  pipeline->insert(pipeline->size(), vtkWriter);
  //  pipeline->printFilterNames(std::cout);
  DREAM3D_REQUIRE_EQUAL(6, pipeline->size());

}

// -----------------------------------------------------------------------------
//  Use test framework
// -----------------------------------------------------------------------------
int main(int argc, char **argv) {
  int err = EXIT_SUCCESS;
#if !REMOVE_TEST_FILES
  DREAM3D_REGISTER_TEST( RemoveTestFiles() );
#endif
  DREAM3D_REGISTER_TEST( TestFilterPipeline() );

#if REMOVE_TEST_FILES
  DREAM3D_REGISTER_TEST( RemoveTestFiles() );
#endif
  PRINT_TEST_SUMMARY();
  return err;
}