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
#include "GenerateEulerColors.h"

#include <limits>

#include "DREAM3DLib/Common/EbsdColoring.hpp"
#include "DREAM3DLib/Common/MatrixMath.h"

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
GenerateEulerColors::GenerateEulerColors() :
  AbstractFilter(),
  m_CellEulerAnglesArrayName(DREAM3D::CellData::EulerAngles),
  m_CellEulerColorsArrayName(DREAM3D::CellData::EulerColor),
  m_CellEulerAngles(NULL),
  m_CellEulerColors(NULL)
{
  setupFilterParameters();
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
GenerateEulerColors::~GenerateEulerColors()
{
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void GenerateEulerColors::setupFilterParameters()
{
  std::vector<FilterParameter::Pointer> parameters;
  setFilterParameters(parameters);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void GenerateEulerColors::writeFilterParameters(AbstractFilterParametersWriter* writer)
{
  /* Place code that will write the inputs values into a file. reference the
   AbstractFilterParametersWriter class for the proper API to use. */
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void GenerateEulerColors::dataCheck(bool preflight, size_t voxels, size_t fields, size_t ensembles)
{
  setErrorCondition(0);
  std::stringstream ss;
  VoxelDataContainer* m = getVoxelDataContainer();
  if (NULL == m)
  {
    ss.str("");
    ss << getHumanLabel() << "The VoxelDataContainer was NULL and this is NOT allowed. There is an error in the programming. Please contact the developers";
    setErrorCondition(-1);
    addErrorMessage(getHumanLabel(), ss.str(), -1);
    return;
  }

  GET_PREREQ_DATA(m, DREAM3D, CellData, CellEulerAngles, ss, -300, float, FloatArrayType, voxels, 3)

  CREATE_NON_PREREQ_DATA(m, DREAM3D, CellData, CellEulerColors, ss, uint8_t, UInt8ArrayType, 0, voxels, 3)
}


// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void GenerateEulerColors::preflight()
{
  /* Place code here that sanity checks input arrays and input values. Look at some
  * of the other DREAM3DLib/Filters/.cpp files for sample codes */
  dataCheck(true, 1, 1, 1);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void GenerateEulerColors::execute()
{
  int err = 0;
  std::stringstream ss;
  setErrorCondition(err);
  VoxelDataContainer* m = getVoxelDataContainer();
  if(NULL == m)
  {
    setErrorCondition(-999);
    notifyErrorMessage("The Voxel DataContainer Object was NULL", -999);
    return;
  }
  int64_t totalPoints = m->getTotalPoints();
  size_t totalFields = m->getNumFieldTuples();
  size_t totalEnsembles = m->getNumEnsembleTuples();
  dataCheck(false, totalPoints, totalFields, totalEnsembles);
  if (getErrorCondition() < 0)
  {
    return;
  }

  size_t index = 0;


  #if 0
 float minEuler[3] = { std::numeric_limits<float >::max(), std::numeric_limits<float >::max(), std::numeric_limits<float >::max() };
 float maxEuler[3] = { std::numeric_limits<float >::min(), std::numeric_limits<float >::min(), std::numeric_limits<float >::min() };

  for (int i = 0; i < totalPoints; ++i)
  {
    index = i * 3;
    if (m_CellEulerAngles[index] < minEuler[0]) { minEuler[0] = m_CellEulerAngles[index]; }
    if (m_CellEulerAngles[index] > maxEuler[0]) { maxEuler[0] = m_CellEulerAngles[index]; }

    if (m_CellEulerAngles[index + 1] < minEuler[1]) { minEuler[1] = m_CellEulerAngles[index + 1]; }
    if (m_CellEulerAngles[index + 1] > maxEuler[1]) { maxEuler[1] = m_CellEulerAngles[index + 1]; }

    if (m_CellEulerAngles[index + 2] < minEuler[2]) { minEuler[2] = m_CellEulerAngles[index + 2]; }
    if (m_CellEulerAngles[index + 2] > maxEuler[2]) { maxEuler[2] = m_CellEulerAngles[index + 2]; }
  }
  #else
   float minEuler[3] = { 0.0f, 0.0f, 0.0f };
   float maxEuler[3] = { 2.0*M_PI, M_PI, 2.0*M_PI };

  #endif


  float delta[3] = { maxEuler[0] - minEuler[0], maxEuler[1] - minEuler[1], maxEuler[2] - minEuler[2]};



  // Write the Euler Coloring Cell Data
  for (int i = 0; i < totalPoints; ++i)
  {
    index = i * 3;
    m_CellEulerColors[index] =    static_cast<unsigned char>((m_CellEulerAngles[index] - minEuler[0])/(delta[0]) * 255.0f);
    m_CellEulerColors[index + 1] = static_cast<unsigned char>((m_CellEulerAngles[index + 1] - minEuler[1])/(delta[1]) * 255.0f);
    m_CellEulerColors[index + 2] = static_cast<unsigned char>((m_CellEulerAngles[index + 2] - minEuler[2])/(delta[2]) * 255.0f);
  }

  /* Let the GUI know we are done with this filter */
  notifyStatusMessage("Complete");
}