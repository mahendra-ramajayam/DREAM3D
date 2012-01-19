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

#include "FieldDataCSVWriter.h"

#include "DREAM3DLib/Common/DREAM3DMath.h"
#include "DREAM3DLib/Common/Constants.h"
#include "DREAM3DLib/Common/DREAM3DRandom.h"


const static float m_pi = static_cast<float>(M_PI);


// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
FieldDataCSVWriter::FieldDataCSVWriter() :
AbstractFilter(),
m_PhasesF(NULL),
m_EulerAngles(NULL),
m_EquivalentDiameters(NULL),
m_AspectRatios(NULL),
m_Omega3s(NULL),
m_SurfaceFields(NULL),
m_UnbiasedFields(NULL)
{
  setupFilterOptions();
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
FieldDataCSVWriter::~FieldDataCSVWriter()
{
}
// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void FieldDataCSVWriter::setupFilterOptions()
{
  std::vector<FilterOption::Pointer> options;
  {
    FilterOption::Pointer option = FilterOption::New();
    option->setHumanLabel("Output File");
    option->setPropertyName("FieldDataFile");
    option->setWidgetType(FilterOption::OutputFileWidget);
    option->setValueType("string");
    options.push_back(option);
  }
  setFilterOptions(options);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void FieldDataCSVWriter::preflight()
{

}
// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void FieldDataCSVWriter::execute()
{
  int err = 0;
  setErrorCondition(err);
  DataContainer* m = getDataContainer();
  if(NULL == m)
  {
    setErrorCondition(-1);
    std::stringstream ss;
    ss << getNameOfClass() << " DataContainer was NULL";
    setErrorMessage(ss.str());
    return;
  }

//  int64_t totalPoints = m->totalPoints();
//  int totalFields = m->getTotalFields();

  std::string filename = getFieldDataFile();

  std::ofstream outFile;
  outFile.open(filename.c_str(), std::ios_base::binary);
  char space = DREAM3D::GrainData::Delimiter;
  // Write the total number of grains
  outFile << m->getTotalFields()-1 << std::endl;
  // Get all the names of the arrays from the Data Container
  std::list<std::string> headers = m->getFieldArrayNameList();

  std::vector<IDataArray::Pointer> data;

  // Print the GrainIds Header before the rest of the headers
  outFile << DREAM3D::GrainData::GrainID;
  // Loop throught the list and print the rest of the headers, ignoring those we don't want
  for(std::list<std::string>::iterator iter = headers.begin(); iter != headers.end(); ++iter)
  {
    // Only get the array if the name does NOT match those listed
    if ( (*iter).compare(DREAM3D::FieldData::NeighborList) && (*iter).compare(DREAM3D::FieldData::SharedSurfaceAreaList) )
    {
      IDataArray::Pointer p = m->getFieldData(*iter);
      if (p->GetNumberOfComponents() == 1) {
        outFile << space << (*iter);
      }
      else // There are more than a single component so we need to add multiple header values
      {
        for(int k = 0; k < p->GetNumberOfComponents(); ++k)
        {
          outFile << space << (*iter) << "_" << k;
        }
      }
      // Get the IDataArray from the DataContainer
      data.push_back(p);
    }
  }
  outFile << std::endl;

  // Get the number of tuples in the arrays
  size_t numTuples = data[0]->GetNumberOfTuples();

  // Skip the first grain
  for(size_t i = 1; i < numTuples; ++i)
  {
    std::stringstream ss;
    ss << "Writing Field Data - " << ((float)i/numTuples)*100 << " Percent Complete";
    notify(ss.str(), 0, Observable::UpdateProgressMessage);
    // Print the grain id
    outFile << i;
    // Print a row of data
    for( std::vector<IDataArray::Pointer>::iterator p = data.begin(); p != data.end(); ++p)
    {
      outFile << space;
      (*p)->printTuple(outFile, i, space);
    }
    outFile << std::endl;

  }

#if 0

  outFile << DREAM3D::GrainData::GrainID  << space << DREAM3D::GrainData::PhaseID << space
      << DREAM3D::GrainData::Phi1 << space << DREAM3D::GrainData::PHI<< space << DREAM3D::GrainData::Phi2 << space
      << DREAM3D::GrainData::EquivDiam << space
	  << DREAM3D::GrainData::B_Over_A << space << DREAM3D::GrainData::C_Over_A << space << DREAM3D::GrainData::Omega3
	  << space << DREAM3D::GrainData::SurfaceGrain << space << DREAM3D::GrainData::OutsideBoundingBox << std::endl;

  for (size_t i = 1; i < m->getTotalFields(); i++)
  {
	  outFile << i << space << m_PhasesF[i] << space << m_EulerAngles[3*i] << space << m_EulerAngles[3*i+1] << space << m_EulerAngles[3*i+2] <<
		space << m_EquivalentDiameters[i] << space << m_AspectRatios[2*i] << space << m_AspectRatios[2*i+1] <<
		space << m_Omega3s[i] << space << int(m_SurfaceFields[i]) << space << int(m_UnbiasedFields[i]) << std::endl;
  }
#endif


  outFile.close();

  // If there is an error set this to something negative and also set a message
  notify("FieldDataCSVWriter Completed", 0, Observable::UpdateProgressMessage);

}






