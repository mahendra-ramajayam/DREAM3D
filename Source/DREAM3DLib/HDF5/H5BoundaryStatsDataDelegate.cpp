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

#include "H5BoundaryStatsDataDelegate.h"

#include "H5Support/H5Lite.h"
#include "H5Support/H5Utilities.h"


// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
H5BoundaryStatsDataDelegate::H5BoundaryStatsDataDelegate()
{

}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
H5BoundaryStatsDataDelegate::~H5BoundaryStatsDataDelegate()
{
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
int H5BoundaryStatsDataDelegate::readBoundaryStatsData(BoundaryStatsData* data, hid_t groupId)
{
  int err = 0;
  //Read the NumFields
  err = readBoundaryArea(data, groupId);

  //Read the PhaseFraction
  err = readPhaseFraction(data, groupId);

  // Read the Parent Phase
  err = readParentPhase(data, groupId);

  return err;
}


// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
int H5BoundaryStatsDataDelegate::writeBoundaryStatsData(BoundaryStatsData* data, hid_t groupId)
{
  if (NULL == data)
  {
    return -1;
  }
  int err = 0;

  // Write the NumFields
  err = writeBoundaryArea(data, groupId);
  if (err < 0)
  {
    return err;
  }

  // Write the PhaseFraction
  err = writePhaseFraction(data, groupId);
  if (err < 0)
  {
    return err;
  }

  // Write the Parent Phase
  err = writeParentPhase(data, groupId);

  return err;
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
int H5BoundaryStatsDataDelegate::writeBoundaryArea(BoundaryStatsData* data, hid_t pid)
{
  float BoundaryArea = data->getBoundaryArea();
  return H5Lite::writeScalarDataset(pid, DREAM3D::HDF5::BoundaryArea, BoundaryArea);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
int H5BoundaryStatsDataDelegate::readBoundaryArea(BoundaryStatsData* data, hid_t pid)
{
  float BoundaryArea = 0.0f;
  int err = H5Lite::readScalarDataset(pid, DREAM3D::HDF5::BoundaryArea, BoundaryArea);
  data->setBoundaryArea(BoundaryArea);
  return err;
}
// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
int H5BoundaryStatsDataDelegate::writePhaseFraction(BoundaryStatsData* data, hid_t pid)
{
  float phaseFraction = data->getPhaseFraction();
  return H5Lite::writeScalarDataset(pid, DREAM3D::HDF5::PhaseFraction, phaseFraction);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
int H5BoundaryStatsDataDelegate::readPhaseFraction(BoundaryStatsData* data, hid_t pid)
{
  float phaseFraction = 0.0f;
  int err = H5Lite::readScalarDataset(pid, DREAM3D::HDF5::PhaseFraction, phaseFraction);
  data->setPhaseFraction(phaseFraction);
  return err;
}
// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
int H5BoundaryStatsDataDelegate::writeParentPhase(BoundaryStatsData* data, hid_t pid)
{
  unsigned int var = static_cast<unsigned int>( data->getParentPhase() );
  return H5Lite::writeScalarDataset(pid, DREAM3D::HDF5::ParentPhase, var);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
int H5BoundaryStatsDataDelegate::readParentPhase(BoundaryStatsData* data, hid_t pid)
{
  unsigned int parentPhase = static_cast<unsigned int>(0.0f);
  int err = H5Lite::readScalarDataset(pid, DREAM3D::HDF5::ParentPhase, parentPhase);
  data->setParentPhase( static_cast<float>(parentPhase) );
  return err;
}
