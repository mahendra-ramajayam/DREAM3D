
#include "FindBasalLoadingFactor.h"

#include "DREAM3DLib/Math/MatrixMath.h"
#include "DREAM3DLib/Math/DREAM3DMath.h"
#include "DREAM3DLib/Common/Constants.h"
#include "DREAM3DLib/GenericFilters/FindGrainPhases.h"
#include "DREAM3DLib/StatisticsFilters/FindAvgOrientations.h"
#include "DREAM3DLib/GenericFilters/FindCellQuats.h"
#include "DREAM3DLib/StatisticsFilters/FindAvgCAxes.h"

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
FindBasalLoadingFactor::FindBasalLoadingFactor() :
  AbstractFilter(),
  m_AvgQuatsArrayName(DREAM3D::FieldData::AvgQuats),
  m_BasalLoadingFactorArrayName(DREAM3D::FieldData::BasalLoadingFactor),
  m_FieldPhasesArrayName(DREAM3D::FieldData::Phases),
  m_CrystalStructuresArrayName(DREAM3D::EnsembleData::CrystalStructures),
  m_BasalLoadingFactor(NULL),
  m_FieldPhases(NULL),
  m_AvgQuats(NULL)
{
  m_LoadingDir.x = 1.0f;
  m_LoadingDir.y = 1.0f;
  m_LoadingDir.z = 1.0f;
  m_OrientationOps = OrientationOps::getOrientationOpsVector();

  setupFilterParameters();
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
FindBasalLoadingFactor::~FindBasalLoadingFactor()
{
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void FindBasalLoadingFactor::setupFilterParameters()
{
  FilterParameterVector parameters;
  {
    FilterParameter::Pointer option = FilterParameter::New();

    option->setHumanLabel("Loading Direction");
    option->setPropertyName("LoadingDir");
    option->setWidgetType(FilterParameter::FloatVec3Widget);
    option->setValueType("FloatVec3Widget_t");
    option->setUnits("");
    parameters.push_back(option);
  }
  setFilterParameters(parameters);
}
// -----------------------------------------------------------------------------
void FindBasalLoadingFactor::readFilterParameters(AbstractFilterParametersReader* reader, int index)
{
  reader->openFilterGroup(this, index);
  /* Code to read the values goes between these statements */
  /* FILTER_WIDGETCODEGEN_AUTO_GENERATED_CODE BEGIN*/
  setLoadingDir( reader->readValue("LoadingDir", getLoadingDir() ) );
  /* FILTER_WIDGETCODEGEN_AUTO_GENERATED_CODE END*/
  reader->closeFilterGroup();
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
int FindBasalLoadingFactor::writeFilterParameters(AbstractFilterParametersWriter* writer, int index)
{
  writer->openFilterGroup(this, index);
  writer->writeValue("LoadingDirection", getLoadingDir() );
  writer->closeFilterGroup();
  return ++index; // we want to return the next index that was just written to
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void FindBasalLoadingFactor::dataCheck(bool preflight, size_t voxels, size_t fields, size_t ensembles)
{
  setErrorCondition(0);
  std::stringstream ss;
  VolumeDataContainer* m = getVolumeDataContainer();

  GET_PREREQ_DATA(m, DREAM3D, FieldData, AvgQuats, -301, float, FloatArrayType, fields, 4)

  CREATE_NON_PREREQ_DATA(m, DREAM3D, FieldData, BasalLoadingFactor, float, FloatArrayType, 0, fields, 1)

  GET_PREREQ_DATA(m, DREAM3D, FieldData, FieldPhases, -302, int32_t, Int32ArrayType, fields, 1)

  typedef DataArray<unsigned int> XTalStructArrayType;
  GET_PREREQ_DATA(m, DREAM3D, EnsembleData, CrystalStructures, -305, unsigned int, XTalStructArrayType, ensembles, 1)
}


// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void FindBasalLoadingFactor::preflight()
{
  dataCheck(true, 1, 1, 1);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void FindBasalLoadingFactor::execute()
{
  VolumeDataContainer* m = getVolumeDataContainer();
  if(NULL == m)
  {
    setErrorCondition(-999);
    notifyErrorMessage("The DataContainer Object was NULL", -999);
    return;
  }
  setErrorCondition(0);

  dataCheck(false, m->getTotalPoints(), m->getNumFieldTuples(), m->getNumEnsembleTuples());
  if (getErrorCondition() < 0)
  {
    return;
  }

  //int ss = 0;
  QuatF q1;
  QuatF* avgQuats = reinterpret_cast<QuatF*>(m_AvgQuats);

  float sampleLoading[3];
  typedef DataArray<unsigned int> XTalType;

  float w;
  float g1[3][3];
  float g1t[3][3];
  float caxis[3] = {0, 0, 1};
  float c1[3];

  sampleLoading[0] = m_LoadingDir.x;
  sampleLoading[1] = m_LoadingDir.y;
  sampleLoading[2] = m_LoadingDir.z;
  MatrixMath::Normalize3x1(sampleLoading);

  size_t numgrains = m->getNumFieldTuples();
  for (size_t i = 1; i < numgrains; i++)
  {
    QuaternionMathF::Copy(avgQuats[i], q1);
    OrientationMath::QuattoMat(q1, g1);
    //transpose the g matricies so when caxis is multiplied by it
    //it will give the sample direction that the caxis is along
    MatrixMath::Transpose3x3(g1, g1t);
    MatrixMath::Multiply3x3with3x1(g1t, caxis, c1);
    //normalize so that the magnitude is 1
    MatrixMath::Normalize3x1(c1);
    if(c1[2] < 0) { MatrixMath::Multiply3x1withConstant(c1, -1); }
    w = MatrixMath::CosThetaBetweenVectors(c1, sampleLoading);
    w = acos(w);
    w *= DREAM3D::Constants::k_180OverPi;
    m_BasalLoadingFactor[i] = w;
  }

  notifyStatusMessage("FindBasalLoadingFactor Completed");
}
