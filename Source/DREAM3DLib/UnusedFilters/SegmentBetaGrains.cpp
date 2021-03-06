/* ============================================================================
 * Copyright (c) 2011 Michael A. Jackson (BlueQuartz Software)
 * Copyright (c) 2011 Dr. Michael A. Groeber (US Air Force Research Laboratories)
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

#include "SegmentBetaGrains.h"

#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int.hpp>
#include <boost/random/variate_generator.hpp>

#include "DREAM3DLib/Common/Constants.h"
#include "DREAM3DLib/Math/DREAM3DMath.h"
#include "DREAM3DLib/Common/MatrixMath.h"
#include "DREAM3DLib/Math/OrientationMath.h"
#include "DREAM3DLib/Utilities/DREAM3DRandom.h"

#include "DREAM3DLib/OrientationOps/CubicOps.h"
#include "DREAM3DLib/OrientationOps/HexagonalOps.h"
#include "DREAM3DLib/OrientationOps/OrthoRhombicOps.h"

#include "DREAM3DLib/GenericFilters/FindCellQuats.h"

#define ERROR_TXT_OUT 1
#define ERROR_TXT_OUT1 1

const static float m_pi = static_cast<float>(M_PI);

static const float unit110 = 1.0 / sqrtf(2.0);
static const float unit111 = 1.0 / sqrtf(3.0);
static const float unit112_1 = 1.0 / sqrtf(6.0);
static const float unit112_2 = 2.0 / sqrtf(6.0);

float burgersCrystalDirections[12][3][3] = {{{unit111, unit112_1, unit110},
    { -unit111, -unit112_1, unit110},
    {unit111, -unit112_2, 0}
  },

  { { -unit111, unit112_1, unit110},
    {unit111, -unit112_1, unit110},
    {unit111, unit112_2, 0}
  },

  { {unit111, -unit112_1, unit110},
    {unit111, -unit112_1, -unit110},
    {unit111, unit112_2, 0}
  },

  { {unit111, unit112_1, unit110},
    {unit111, unit112_1, -unit110},
    { -unit111, unit112_2, 0}
  },

  { {unit111, unit112_1, unit110},
    {unit111, -unit112_2, 0},
    {unit111, unit112_1, -unit110}
  },

  { {unit111, -unit112_1, unit110},
    { -unit111, -unit112_2, 0},
    {unit111, -unit112_1, -unit110}
  },

  { {unit111, -unit112_1, unit110},
    {unit111, unit112_2, 0},
    { -unit111, unit112_1, unit110}
  },

  { { -unit111, -unit112_1, unit110},
    {unit111, -unit112_2, 0},
    {unit111, unit112_1, unit110}
  },

  { {unit111, -unit112_2, 0},
    {unit111, unit112_1, unit110},
    { -unit111, -unit112_1, unit110}
  },

  { {unit111, unit112_2, 0},
    { -unit111, unit112_1, unit110},
    {unit111, -unit112_1, unit110}
  },

  { {unit111, unit112_2, 0},
    {unit111, -unit112_1, unit110},
    {unit111, -unit112_1, -unit110}
  },

  { { -unit111, unit112_2, 0},
    {unit111, unit112_1, unit110},
    {unit111, unit112_1, -unit110}
  }
};

#define NEW_SHARED_ARRAY(var, m_msgType, size)\
  boost::shared_array<m_msgType> var##Array(new m_msgType[size]);\
  m_msgType* var = var##Array.get();



// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
SegmentBetaGrains::SegmentBetaGrains() :
  SegmentGrains(),
  m_GoodVoxelsArrayName(DREAM3D::CellData::GoodVoxels),
  m_CellPhasesArrayName(DREAM3D::CellData::Phases),
  m_QuatsArrayName(DREAM3D::CellData::Quats),
  m_GrainIdsArrayName(DREAM3D::CellData::GrainIds),
  m_ActiveArrayName(DREAM3D::FieldData::Active),
  m_CrystalStructuresArrayName(DREAM3D::EnsembleData::CrystalStructures),
  m_MisorientationTolerance(5.0f),
  m_RandomizeGrainIds(true),
  m_GrainIds(NULL),
  m_Quats(NULL),
  m_CellPhases(NULL),
  m_GoodVoxels(NULL),
  m_Active(NULL),
  m_CrystalStructures(NULL)
{
  m_HexOps = HexagonalOps::New();
  m_OrientationOps.push_back(m_HexOps.get());
  m_CubicOps = CubicOps::New();
  m_OrientationOps.push_back(m_CubicOps.get());
  m_OrthoOps = OrthoRhombicOps::New();
  m_OrientationOps.push_back(m_OrthoOps.get());

  setupFilterParameters();
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
SegmentBetaGrains::~SegmentBetaGrains()
{

}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void SegmentBetaGrains::setupFilterParameters()
{
  FilterParameterVector parameters;
  {
    FilterParameter::Pointer option = FilterParameter::New();
    option->setPropertyName("MisorientationTolerance");
    option->setHumanLabel("Misorientation Tolerance");
    option->setWidgetType(FilterParameter::DoubleWidget);
    option->setValueType("float");
    option->setCastableValueType("double");
    option->setUnits("Degrees");
    parameters.push_back(option);
  }
  {
    FilterParameter::Pointer option = FilterParameter::New();
    option->setHumanLabel("Axis Tolerance");
    option->setPropertyName("AxisTolerance");
    option->setWidgetType(FilterParameter::DoubleWidget);
    option->setValueType("float");
    option->setCastableValueType("double");
    option->setUnits("Degrees");
    parameters.push_back(option);
  }
  {
    FilterParameter::Pointer option = FilterParameter::New();
    option->setHumanLabel("Angle Tolerance");
    option->setPropertyName("AngleTolerance");
    option->setWidgetType(FilterParameter::DoubleWidget);
    option->setValueType("float");
    option->setCastableValueType("double");
    option->setUnits("Degrees");
    parameters.push_back(option);
  }
#if 0
  {
    FilterParameter::Pointer option = FilterParameter::New();
    option->setHumanLabel("Randomly Reorder Generated Grain Ids");
    option->setPropertyName("RandomizeGrainIds");
    option->setWidgetType(FilterParameter::BooleanWidget);
    option->setValueType("bool");
    parameters.push_back(option);
  }
#endif
  setFilterParameters(parameters);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void SegmentBetaGrains::readFilterParameters(AbstractFilterParametersReader* reader, int index)
{
  reader->openFilterGroup(this, index);
  /* Code to read the values goes between these statements */
////!!##
  reader->closeFilterGroup();
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
int SegmentBetaGrains::writeFilterParameters(AbstractFilterParametersWriter* writer, int index)
{
  writer->openFilterGroup(this, index);
  writer->writeValue("MisorientationTolerance", getMisorientationTolerance() );
  writer->writeValue("AxisTolerance", getAxisTolerance() );
  writer->writeValue("AngleTolerance", getAngleTolerance() );
  writer->closeFilterGroup();
  return index; // we want to return the next index that was just written to
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void SegmentBetaGrains::dataCheck(bool preflight, size_t voxels, size_t fields, size_t ensembles)
{
  setErrorCondition(0);
  std::stringstream ss;
  VoxelDataContainer* m = getVoxelDataContainer();
  int err = 0;

  CREATE_NON_PREREQ_DATA(m, DREAM3D, CellData, GoodVoxels, bool, BoolArrayType,  true, voxels, 1)
  GET_PREREQ_DATA(m, DREAM3D, CellData, CellPhases, -302, int32_t, Int32ArrayType,  voxels, 1)

  TEST_PREREQ_DATA(m, DREAM3D, CellData, Quats, err, -303, float, FloatArrayType, voxels, 5)
  if(err == -303)
  {
    setErrorCondition(0);
    FindCellQuats::Pointer find_cellquats = FindCellQuats::New();
    find_cellquats->setObservers(this->getObservers());
    find_cellquats->setVoxelDataContainer(getVoxelDataContainer());
    if(preflight == true) { find_cellquats->preflight(); }
    if(preflight == false) { find_cellquats->execute(); }
  }
  GET_PREREQ_DATA(m, DREAM3D, CellData, Quats, -303, float, FloatArrayType, voxels, 4)


  CREATE_NON_PREREQ_DATA(m, DREAM3D, CellData, GrainIds, int32_t, Int32ArrayType, 0, voxels, 1)
  CREATE_NON_PREREQ_DATA(m, DREAM3D, FieldData, Active, bool, BoolArrayType, true, fields, 1)

  typedef DataArray<unsigned int> XTalStructArrayType;
  GET_PREREQ_DATA(m, DREAM3D, EnsembleData, CrystalStructures, -304, unsigned int, XTalStructArrayType, ensembles, 1)

}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void SegmentBetaGrains::preflight()
{
  dataCheck(true, 1, 1, 1);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void SegmentBetaGrains::execute()
{
  setErrorCondition(0);
  VoxelDataContainer* m = getVoxelDataContainer();
  if(NULL == m)
  {
    setErrorCondition(-999);
    notifyErrorMessage("The DataContainer Object was NULL", -999);
    return;
  }

  int64_t totalPoints = m->getTotalPoints();
  m->resizeFieldDataArrays(1);
  dataCheck(false, totalPoints, m->getNumFieldTuples(), m->getNumEnsembleTuples());
  if (getErrorCondition() < 0)
  {
    return;
  }

  //Convert user defined tolerance to radians.
  m_MisorientationTolerance = m_MisorientationTolerance * m_pi / 180.0f;
  m_AxisTolerance = m_AxisTolerance * m_pi / 180.0f;
  for(int64_t i = 0; i < totalPoints; i++)
  {
    m_GrainIds[i] = 0;
  }

  SegmentGrains::execute();

  if (true == m_RandomizeGrainIds)
  {
    totalPoints = m->getTotalPoints();
    size_t totalFields = m->getNumFieldTuples();

    // Generate all the numbers up front
    const int rangeMin = 1;
    const int rangeMax = totalFields - 1;
    typedef boost::uniform_int<int> NumberDistribution;
    typedef boost::mt19937 RandomNumberGenerator;
    typedef boost::variate_generator < RandomNumberGenerator&,
            NumberDistribution > Generator;

    NumberDistribution distribution(rangeMin, rangeMax);
    RandomNumberGenerator generator;
    Generator numberGenerator(generator, distribution);
    generator.seed(static_cast<boost::uint32_t>( MXA::getMilliSeconds() )); // seed with the current time

    DataArray<int32_t>::Pointer rndNumbers = DataArray<int32_t>::CreateArray(totalFields, "New GrainIds");
    int32_t* gid = rndNumbers->GetPointer(0);
    gid[0] = 0;
    std::set<int32_t> grainIdSet;
    grainIdSet.insert(0);
    for(size_t i = 1; i < totalFields; ++i)
    {
      gid[i] = i; //numberGenerator();
      grainIdSet.insert(gid[i]);
    }

    size_t r;
    size_t temp;
    //--- Shuffle elements by randomly exchanging each with one other.
    for (size_t i = 1; i < totalFields; i++)
    {
      r = numberGenerator(); // Random remaining position.
      if (r >= totalFields)
      {
        continue;
      }
      temp = gid[i];
      gid[i] = gid[r];
      gid[r] = temp;
    }

    // Now adjust all the Grain Id values for each Voxel
    for(int64_t i = 0; i < totalPoints; ++i)
    {
      m_GrainIds[i] = gid[ m_GrainIds[i] ];
    }
  }

  // If there is an error set this to something negative and also set a message
  notifyStatusMessage("Completed");
}


// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
int SegmentBetaGrains::getSeed(size_t gnum)
{
  setErrorCondition(0);
  VoxelDataContainer* m = getVoxelDataContainer();
  if (NULL == m)
  {
    setErrorCondition(-1);
    std::stringstream ss;
    ss << " DataContainer was NULL";
    addErrorMessage(getHumanLabel(), ss.str(), -1);
    return -1;
  }

  int64_t totalPoints = m->getTotalPoints();

  DREAM3D_RANDOMNG_NEW()
  int seed = -1;
  int randpoint = 0;

  // Precalculate some constants
  int64_t totalPMinus1 = totalPoints - 1;

  int counter = 0;
  randpoint = int(float(rg.genrand_res53()) * float(totalPMinus1));
  while (seed == -1 && counter < totalPoints)
  {
    if (randpoint > totalPMinus1) { randpoint = static_cast<int>( randpoint - totalPoints ); }
    if (m_GoodVoxels[randpoint] == true && m_GrainIds[randpoint] == 0 && m_CellPhases[randpoint] > 0) { seed = randpoint; }
    randpoint++;
    counter++;
  }
  if (seed >= 0)
  {
    m_GrainIds[seed] = gnum;
    m->resizeFieldDataArrays(gnum + 1);
    dataCheck(false, totalPoints, m->getNumFieldTuples(), m->getNumEnsembleTuples());
  }
  return seed;
}
// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
bool SegmentBetaGrains::determineGrouping(int referencepoint, int neighborpoint, size_t gnum)
{
  bool group = false;
  float w = 10000.0;
  float n1 = 0.0f, n2 = 0.0f, n3 = 0.0f;
  float r1 = 0.0f, r2 = 0.0f, r3 = 0.0f;
  float q1[5];
  float q2[5];
  unsigned int phase1, phase2;
  int colony = 0;

  if(m_GrainIds[neighborpoint] == 0 && m_GoodVoxels[neighborpoint] == true)
  {
    phase1 = m_CrystalStructures[m_CellPhases[referencepoint]];
    q1[0] = 1;
    q1[1] = m_Quats[referencepoint * 5 + 1];
    q1[2] = m_Quats[referencepoint * 5 + 2];
    q1[3] = m_Quats[referencepoint * 5 + 3];
    q1[4] = m_Quats[referencepoint * 5 + 4];

    phase2 = m_CrystalStructures[m_CellPhases[neighborpoint]];
    q2[0] = 1;
    q2[1] = m_Quats[neighborpoint * 5 + 1];
    q2[2] = m_Quats[neighborpoint * 5 + 2];
    q2[3] = m_Quats[neighborpoint * 5 + 3];
    q2[4] = m_Quats[neighborpoint * 5 + 4];

    //float degToRad = m_pi/180.0;
    //float ea1 = 309.0*degToRad;
    //float ea2 = 42.0*degToRad;
    //float ea3 = 74.0*degToRad;
    //OrientationMath::EulertoQuat(q1, ea1, ea2, ea3);
    //ea1 = 28.0*degToRad;
    //ea2 = 35.0*degToRad;
    //ea3 = 334.0*degToRad;
    //OrientationMath::EulertoQuat(q2, ea1, ea2, ea3);
    //phase1 = 0;
    //phase2 = 1;

//    if (phase1 == phase2 && m_GoodVoxels[referencepoint] == true && m_GoodVoxels[neighborpoint] == true) w = m_OrientationOps[phase1]->getMisoQuat( q1, q2, n1, n2, n3);
    if (m_CellPhases[referencepoint] == m_CellPhases[neighborpoint])
    {
      w = m_OrientationOps[phase1]->getMisoQuat( q1, q2, n1, n2, n3);
      if (w < m_MisorientationTolerance)
      {
        group = true;
        m_GrainIds[neighborpoint] = gnum;
      }
      else if (phase1 == Ebsd::CrystalStructure::Hexagonal)
      {
        OrientationMath::AxisAngletoRod(w, n1, n2, n3, r1, r2, r3);
        m_OrientationOps[phase1]->getMDFFZRod(r1, r2, r3);
        OrientationMath::RodtoAxisAngle(r1, r2, r3, w, n1, n2, n3);
        w = w * (180.0f / m_pi);
        float angdiff1 = fabs(w - 10.53f);
        float axisdiff1 = acosf(fabs(n1) * 0.0000f + fabs(n2) * 0.0000f + fabs(n3) * 1.0000f);
        if(angdiff1 < m_AngleTolerance && axisdiff1 < m_AxisTolerance) { colony = 1; }
        float angdiff2 = fabs(w - 90.00f);
        float axisdiff2 = acosf(fabs(n1) * 0.9958f + fabs(n2) * 0.0917f + fabs(n3) * 0.0000f);
        if(angdiff2 < m_AngleTolerance && axisdiff2 < m_AxisTolerance) { colony = 1; }
        float angdiff3 = fabs(w - 60.00f);
        float axisdiff3 = acosf(fabs(n1) * 1.0000f + fabs(n2) * 0.0000f + fabs(n3) * 0.0000f);
        if(angdiff3 < m_AngleTolerance && axisdiff3 < m_AxisTolerance) { colony = 1; }
        float angdiff4 = fabs(w - 60.83f);
        float axisdiff4 = acosf(fabs(n1) * 0.9834f + fabs(n2) * 0.0905f + fabs(n3) * 0.1570f);
        if(angdiff4 < m_AngleTolerance && axisdiff4 < m_AxisTolerance) { colony = 1; }
        float angdiff5 = fabs(w - 63.26f);
        float axisdiff5 = acosf(fabs(n1) * 0.9549f + fabs(n2) * 0.0000f + fabs(n3) * 0.2969f);
        if(angdiff5 < m_AngleTolerance && axisdiff5 < m_AxisTolerance) { colony = 1; }
        if (colony == 1)
        {
          group = true;
          m_GrainIds[neighborpoint] = gnum;
        }
      }
    }
    else if ((phase1 == Ebsd::CrystalStructure::Hexagonal && phase2 == Ebsd::CrystalStructure::Cubic))
    {
      colony = check_for_burgers(q2, q1);
      if (colony == 1)
      {
        group = true;
        m_GrainIds[neighborpoint] = gnum;
      }
    }
    else if ((phase1 == Ebsd::CrystalStructure::Cubic && phase2 == Ebsd::CrystalStructure::Hexagonal))
    {
      colony = check_for_burgers(q1, q2);
      if (colony == 1)
      {
        group = true;
        m_GrainIds[neighborpoint] = gnum;
      }
    }
  }
  return group;
}

int SegmentBetaGrains::check_for_burgers(float betaQuat[5], float alphaQuat[5])
{
  float dP = 0.0;
  float angle = 0.0;
  float radToDeg = 180.0f / m_pi;

  float gBeta[3][3];
  float gBetaT[3][3];
  OrientationMath::QuattoMat(betaQuat, gBeta);
  //transpose gBeta so the sample direction is the output when
  //gBeta is multiplied by the crystal directions below
  MatrixMath::Transpose3x3(gBeta, gBetaT);

  float gAlpha[3][3];
  float gAlphaT[3][3];
  OrientationMath::QuattoMat(alphaQuat, gAlpha);
  //transpose gBeta so the sample direction is the output when
  //gBeta is multiplied by the crystal directions below
  MatrixMath::Transpose3x3(gAlpha, gAlphaT);

  float mat[3][3];
  float a[3];
  float b[3];
  for(int i = 0; i < 12; i++)
  {
    MatrixMath::Multiply3x3with3x3(gBetaT, burgersCrystalDirections[i], mat);
    a[0] = mat[0][2];
    a[1] = mat[1][2];
    a[2] = mat[2][2];
    b[0] = gAlphaT[0][2];
    b[1] = gAlphaT[1][2];
    b[2] = gAlphaT[2][2];
    dP = MatrixMath::DotProduct(a, b);
    angle = acos(dP);
    if((angle * radToDeg) < m_AngleTolerance || (180.0 - (angle * radToDeg)) < m_AngleTolerance)
    {
      a[0] = mat[0][0];
      a[1] = mat[1][0];
      a[2] = mat[2][0];
      b[0] = gAlphaT[0][0];
      b[1] = gAlphaT[1][0];
      b[2] = gAlphaT[2][0];
      dP = MatrixMath::DotProduct(a, b);
      angle = acos(dP);
      if((angle * radToDeg) < m_AngleTolerance) { return 1; }
      if((180.0 - (angle * radToDeg)) < m_AngleTolerance) { return 1; }
      b[0] = -0.5 * gAlphaT[0][0] + 0.866025 * gAlphaT[0][1];
      b[1] = -0.5 * gAlphaT[1][0] + 0.866025 * gAlphaT[1][1];
      b[2] = -0.5 * gAlphaT[2][0] + 0.866025 * gAlphaT[2][1];
      dP = MatrixMath::DotProduct(a, b);
      angle = acos(dP);
      if((angle * radToDeg) < m_AngleTolerance) { return 1; }
      if((180.0 - (angle * radToDeg)) < m_AngleTolerance) { return 1; }
      b[0] = -0.5 * gAlphaT[0][0] - 0.866025 * gAlphaT[0][1];
      b[1] = -0.5 * gAlphaT[1][0] - 0.866025 * gAlphaT[1][1];
      b[2] = -0.5 * gAlphaT[2][0] - 0.866025 * gAlphaT[2][1];
      dP = MatrixMath::DotProduct(a, b);
      angle = acos(dP);
      if((angle * radToDeg) < m_AngleTolerance) { return 1; }
      if((180.0 - (angle * radToDeg)) < m_AngleTolerance) { return 1; }
    }
  }

  return 0;
}