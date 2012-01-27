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

#include "DataContainerReader.h"

#include <hdf5.h>

#include "H5Support/H5Lite.h"
#include "H5Support/H5Utilities.h"
#include "DREAM3DLib/HDF5/VTKH5Constants.h"


// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
DataContainerReader::DataContainerReader() :
AbstractFilter()
{
  setupFilterOptions();
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
DataContainerReader::~DataContainerReader()
{
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void DataContainerReader::setupFilterOptions()
{
  std::vector<FilterOption::Pointer> options;
  {
    FilterOption::Pointer option = FilterOption::New();
    option->setHumanLabel("Input File");
    option->setPropertyName("InputFile");
    option->setWidgetType(FilterOption::InputFileWidget);
    option->setValueType("string");
    options.push_back(option);
  }
  setFilterOptions(options);
}
// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void DataContainerReader::dataCheck(bool preflight, size_t voxels, size_t fields, size_t ensembles)
{
  setErrorCondition(0);
  std::stringstream ss;

  if (m_InputFile.empty() == true)
  {
    ss << getNameOfClass() << ": The output file must be set before executing this filter.";
    setErrorCondition(-1);
  }

  setErrorMessage(ss.str());
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void DataContainerReader::preflight()
{
  dataCheck(true, 1, 1, 1);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void DataContainerReader::execute()
{
  DataContainer* m = getDataContainer();
  if (NULL == m)
  {
    setErrorCondition(-1);
    std::stringstream ss;
    ss << getNameOfClass() << " DataContainer was NULL";
    setErrorMessage(ss.str());
    return;
  }
  setErrorCondition(0);
  dataCheck(false, 1, 1, 1);
  int err = 0;
  std::stringstream ss;
  typedef std::list<std::string> NameListType;

  // Clear out everything from the data container before we start.
  int64_t volDims[3] = {0, 0, 0};
  float spacing[3] = {1.0f, 1.0f, 1.0f};
  float origin[3] = {0.0f, 0.0f, 0.0f};
  m->setDimensions(volDims[0], volDims[1], volDims[2]);
  m->setResolution(spacing);
  m->setOrigin(origin);

  m->clearCellData();
  m->clearFieldData();
  m->clearEnsembleData();

  hid_t fileId = H5Utilities::openFile(m_InputFile, false);
  if(fileId < 0)
  {
    ss.str("");
    ss << getNameOfClass() << ": Error opening input file '" << m_InputFile << "'";
    setErrorCondition(-150);
    setErrorMessage(ss.str());
    return;
  }
  hid_t dcGid = H5Gopen(fileId, DREAM3D::HDF5::DataContainerName.c_str(), 0);
  if(dcGid < 0)
  {
    err = H5Utilities::closeFile(fileId);
    ss.str("");
    ss << getNameOfClass() << ": Error opening group '" << DREAM3D::HDF5::DataContainerName << "'";
    setErrorCondition(-150);
    setErrorMessage(ss.str());
    return;
  }


  err = H5Lite::readPointerDataset(dcGid, H5_DIMENSIONS, volDims);
  if(err < 0)
  {
    setErrorMessage("H5ReconVolumeReader Error Reading the Dimensions");
    setErrorCondition(-151);
    err = H5Gclose(dcGid);
    err = H5Fclose(fileId);
    return;
  }
  m->setDimensions(volDims[0], volDims[1], volDims[2]);

  err = H5Lite::readPointerDataset(dcGid, H5_SPACING, spacing);
  if(err < 0)
  {
    setErrorMessage("H5ReconVolumeReader Error Reading the Spacing (Resolution)");
    setErrorCondition(-152);
    err = H5Gclose(dcGid);
    err = H5Fclose(fileId);
    return;
  }
  m->setResolution(spacing);

  err = H5Lite::readPointerDataset(dcGid, H5_ORIGIN, origin);
  if(err < 0)
  {
    setErrorMessage("H5ReconVolumeReader Error Reading the Origin");
    setErrorCondition(-153);
    err = H5Gclose(dcGid);
    err = H5Fclose(fileId);
    return;
  }
  m->setOrigin(origin);


//Read the Voxel Data
  hid_t cellGroupId = H5Gopen(dcGid, H5_CELL_DATA_GROUP_NAME, H5P_DEFAULT );
  if(err < 0)
  {
    ss.str("");
    ss << "Error opening voxel Group " << H5_CELL_DATA_GROUP_NAME << std::endl;
    setErrorCondition(-154);
    setErrorMessage(ss.str());
    return;
  }

  NameListType names;
  H5Utilities::getGroupObjects(cellGroupId, H5Utilities::H5Support_DATASET | H5Utilities::H5Support_GROUP, names);
  std::cout << "Number of Items in CELL Group: " << names.size() << std::endl;
  for (NameListType::iterator iter = names.begin(); iter != names.end(); ++iter )
  {
    std::cout << "Voxel Array: " << *iter << std::endl;
  }
  H5Gclose(cellGroupId); // Close the Cell Group


  //Read the Field Data
  hid_t fieldGroupId = H5Gopen(dcGid, H5_FIELD_DATA_GROUP_NAME, H5P_DEFAULT );
  if(err < 0)
  {
    ss.str("");
    ss << "Error opening Field Data Group " << H5_FIELD_DATA_GROUP_NAME << std::endl;
    setErrorCondition(-154);
    setErrorMessage(ss.str());
    return;
  }

  names.clear();
  H5Utilities::getGroupObjects(fieldGroupId, H5Utilities::H5Support_DATASET | H5Utilities::H5Support_GROUP, names);
  std::cout << "Number of Items in Field Group: " << names.size() << std::endl;
  for (NameListType::iterator iter = names.begin(); iter != names.end(); ++iter )
  {
    std::cout << "Field Array: " << *iter << std::endl;
  }
  H5Gclose(fieldGroupId); // Close the Cell Group


  err = H5Gclose(dcGid);
  err = H5Fclose(fileId);




}