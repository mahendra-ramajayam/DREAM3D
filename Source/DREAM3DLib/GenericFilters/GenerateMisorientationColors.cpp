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
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#include "GenerateMisorientationColors.h"


#include "DREAM3DLib/Math/MatrixMath.h"
#include "DREAM3DLib/Math/OrientationMath.h"
#include "DREAM3DLib/Math/MatrixMath.h"
#include "DREAM3DLib/OrientationOps/CubicOps.h"
#include "DREAM3DLib/OrientationOps/CubicLowOps.h"
#include "DREAM3DLib/OrientationOps/HexagonalOps.h"
#include "DREAM3DLib/OrientationOps/HexagonalLowOps.h"
#include "DREAM3DLib/OrientationOps/TrigonalOps.h"
#include "DREAM3DLib/OrientationOps/TrigonalLowOps.h"
#include "DREAM3DLib/OrientationOps/TetragonalOps.h"
#include "DREAM3DLib/OrientationOps/TetragonalLowOps.h"
#include "DREAM3DLib/OrientationOps/OrthoRhombicOps.h"
#include "DREAM3DLib/OrientationOps/MonoclinicOps.h"
#include "DREAM3DLib/OrientationOps/TriclinicOps.h"
#include "DREAM3DLib/Utilities/ColorTable.h"

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
GenerateMisorientationColors::GenerateMisorientationColors() :
  AbstractFilter(),
  m_QuatsArrayName(DREAM3D::CellData::Quats),
  m_GoodVoxelsArrayName(DREAM3D::CellData::GoodVoxels),
  m_CellPhasesArrayName(DREAM3D::CellData::Phases),
  m_CrystalStructuresArrayName(DREAM3D::EnsembleData::CrystalStructures),
  m_MisorientationColorArrayName(DREAM3D::CellData::MisorientationColor),
  m_CellPhases(NULL),
  m_Quats(NULL),
  m_CrystalStructures(NULL),
  m_MisorientationColor(NULL)
{
  m_ReferenceAxis.x = 0.0f;
  m_ReferenceAxis.y = 0.0f;
  m_ReferenceAxis.z = 1.0f;
  m_ReferenceAngle = 0.0f;

  setupFilterParameters();
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
GenerateMisorientationColors::~GenerateMisorientationColors()
{
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void GenerateMisorientationColors::setupFilterParameters()
{
  FilterParameterVector parameters;
  {
    FilterParameter::Pointer option = FilterParameter::New();

    option->setHumanLabel("Reference Orientation Axis");
    option->setPropertyName("ReferenceAxis");
    option->setWidgetType(FilterParameter::FloatVec3Widget);
    option->setValueType("FloatVec3Widget_t");
    parameters.push_back(option);
  }
  {
    FilterParameter::Pointer option = FilterParameter::New();
    option->setHumanLabel("Reference Orientation Angle");
    option->setPropertyName("ReferenceAngle");
    option->setWidgetType(FilterParameter::DoubleWidget);
    option->setValueType("float");
    option->setCastableValueType("double");
    parameters.push_back(option);
  }
  setFilterParameters(parameters);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void GenerateMisorientationColors::readFilterParameters(AbstractFilterParametersReader* reader, int index)
{
  reader->openFilterGroup(this, index);
  /* Code to read the values goes between these statements */
  /* FILTER_WIDGETCODEGEN_AUTO_GENERATED_CODE BEGIN*/
  setReferenceAxis( reader->readValue("ReferenceAxis", getReferenceAxis() ) );
  setReferenceAngle( reader->readValue("ReferenceAngle", getReferenceAngle() ) );
  /* FILTER_WIDGETCODEGEN_AUTO_GENERATED_CODE END*/
  reader->closeFilterGroup();
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
int GenerateMisorientationColors::writeFilterParameters(AbstractFilterParametersWriter* writer, int index)
{
  writer->openFilterGroup(this, index);

  /* Place code that will write the inputs values into a file. reference the
   AbstractFilterParametersWriter class for the proper API to use. */
  writer->writeValue("ReferenceAxis", getReferenceAxis() );
  writer->writeValue("ReferenceAngle", getReferenceAngle() );
  writer->closeFilterGroup();
  return ++index; // we want to return the next index that was just written to
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void GenerateMisorientationColors::dataCheck(bool preflight, size_t voxels, size_t fields, size_t ensembles)
{
  setErrorCondition(0);
  std::stringstream ss;
  VolumeDataContainer* m = getVolumeDataContainer();
  if (NULL == m)
  {
    std::stringstream ss;
    ss << getHumanLabel() << "The VolumeDataContainer was NULL and this is NOT allowed. There is an error in the programming. Please contact the developers";
    setErrorCondition(-1);
    addErrorMessage(getHumanLabel(), ss.str(), -1);
    return;
  }


  GET_PREREQ_DATA(m, DREAM3D, CellData, CellPhases, -302, int32_t, Int32ArrayType,  voxels, 1)
  GET_PREREQ_DATA(m, DREAM3D, CellData, Quats, -303, float, FloatArrayType, voxels, 4)

  typedef DataArray<unsigned int> XTalStructArrayType;
  GET_PREREQ_DATA(m, DREAM3D, EnsembleData, CrystalStructures, -304, unsigned int, XTalStructArrayType, ensembles, 1)

  CREATE_NON_PREREQ_DATA(m, DREAM3D, CellData, MisorientationColor, uint8_t, UInt8ArrayType, 0, voxels, 3)

}


// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void GenerateMisorientationColors::preflight()
{
  /* Place code here that sanity checks input arrays and input values. Look at some
  * of the other DREAM3DLib/Filters/.cpp files for sample codes */
  dataCheck(true, 1, 1, 1);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void GenerateMisorientationColors::execute()
{
  int err = 0;
  std::stringstream ss;
  setErrorCondition(err);
  VolumeDataContainer* m = getVolumeDataContainer();
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

  bool* m_GoodVoxels;
  BoolArrayType* goodVoxels = NULL;
  bool missingGoodVoxels = false;
  IDataArray::Pointer gvPtr = m->getCellData(m_GoodVoxelsArrayName);

  if (m->getCellData(m_GoodVoxelsArrayName).get() == NULL)
  {
    missingGoodVoxels = true;
  }
  else
  {
    goodVoxels = BoolArrayType::SafePointerDownCast(gvPtr.get());
    m_GoodVoxels = goodVoxels->GetPointer(0);
  }

  int phase;
  size_t index = 0;

  // Make sure we are dealing with a unit 1 vector.
  MatrixMath::Normalize3x1(m_ReferenceAxis.x, m_ReferenceAxis.y, m_ReferenceAxis.z);
  // Create 1 of every type of Ops class. This condenses the code below
  std::vector<OrientationOps::Pointer> ops;
  ops.push_back(HexagonalOps::New());
  ops.push_back(CubicOps::New());
  ops.push_back(HexagonalLowOps::New());
  ops.push_back(CubicLowOps::New());
  ops.push_back(TriclinicOps::New());
  ops.push_back(MonoclinicOps::New());
  ops.push_back(OrthoRhombicOps::New());
  ops.push_back(TetragonalLowOps::New());
  ops.push_back(TetragonalOps::New());
  ops.push_back(TrigonalLowOps::New());
  ops.push_back(TrigonalOps::New());

  QuatF* quats = reinterpret_cast<QuatF*>(m_Quats);

  QuatF refQuat = {m_ReferenceAxis.x * sin(m_ReferenceAngle), m_ReferenceAxis.y * sin(m_ReferenceAngle), m_ReferenceAxis.z * sin(m_ReferenceAngle), cos(m_ReferenceAngle)};
  QuatF cellQuat = {0.0f, 0.0f, 0.0f, 1.0f};
  DREAM3D::Rgb argb = 0x00000000;

  UInt8ArrayType::Pointer notSupported = UInt8ArrayType::CreateArray(13, 1, "NotSupportedArray");
  notSupported->initializeWithZeros();

  // Write the Misorientation Coloring Cell Data
  for (int64_t i = 0; i < totalPoints; i++)
  {
    phase = m_CellPhases[i];
    index = i * 3;
    m_MisorientationColor[index] = 0;
    m_MisorientationColor[index + 1] = 0;
    m_MisorientationColor[index + 2] = 0;
    cellQuat = quats[i];

    if(m_CrystalStructures[phase] != Ebsd::CrystalStructure::Cubic_High)
    {
      uint32_t idx = m_CrystalStructures[phase];
      if(idx == Ebsd::CrystalStructure::UnknownCrystalStructure)
      {
        idx = 12;
      }
      notSupported->SetValue(idx, 1);
      m_MisorientationColor[index] = 0;
      m_MisorientationColor[index + 1] = 0;
      m_MisorientationColor[index + 2] = 0;

    }
    // Make sure we are using a valid Euler Angles with valid crystal symmetry
    else if( (missingGoodVoxels == true || m_GoodVoxels[i] == true)
             && m_CrystalStructures[phase] < Ebsd::CrystalStructure::LaueGroupEnd )
    {
      argb = ops[m_CrystalStructures[phase]]->generateMisorientationColor(cellQuat, refQuat);
      m_MisorientationColor[index] = RgbColor::dRed(argb);
      m_MisorientationColor[index + 1] = RgbColor::dGreen(argb);
      m_MisorientationColor[index + 2] = RgbColor::dBlue(argb);
    }
  }

  for(size_t i = 0; i < notSupported->GetNumberOfTuples() - 1; i++)
  {
    if (notSupported->GetValue(i) == 1)
    {
      std::string msg("The Symmetry of ");
      msg.append(ops[i]->getSymmetryName()).append(" is not currently supported for Misorientation Coloring. Voxels with this symmetry have been set to black.");
      notifyWarningMessage(msg, -500);
    }
  }

  if (notSupported->GetValue(12) == 1)
  {
    std::string msg("There were voxels with an unknown crystal symmetry due most likely being marked as a 'Bad Voxel'. These voxels have been colored black BUT black is a valid color for Misorientation coloring. Please understand this when visualizing your data.");
    notifyWarningMessage(msg, -500);
  }

  /* Let the GUI know we are done with this filter */
  notifyStatusMessage("Complete");
}
