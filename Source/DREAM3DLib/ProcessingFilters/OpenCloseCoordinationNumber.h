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

#ifndef OpenCloseCoordinationNumber_H_
#define OpenCloseCoordinationNumber_H_

#include <vector>
#include <string>


#include "DREAM3DLib/DREAM3DLib.h"
#include "DREAM3DLib/Common/DREAM3DSetGetMacros.h"
#include "DREAM3DLib/DataArrays/IDataArray.h"

#include "DREAM3DLib/Common/AbstractFilter.h"
#include "DREAM3DLib/DataContainers/VolumeDataContainer.h"
#include "DREAM3DLib/OrientationOps/OrientationOps.h"
#include "DREAM3DLib/DataArrays/NeighborList.hpp"


/**
 * @class OpenCloseCoordinationNumber OpenCloseCoordinationNumber.h DREAM3DLib/ReconstructionFilters/OpenCloseCoordinationNumber.h
 * @brief
 * @author
 * @date Nov 19, 2011
 * @version 1.0
 */
class DREAM3DLib_EXPORT OpenCloseCoordinationNumber : public AbstractFilter
{
  public:
    DREAM3D_SHARED_POINTERS(OpenCloseCoordinationNumber)
    DREAM3D_STATIC_NEW_MACRO(OpenCloseCoordinationNumber)
    DREAM3D_TYPE_MACRO_SUPER(OpenCloseCoordinationNumber, AbstractFilter)

    virtual ~OpenCloseCoordinationNumber();

    //------ Required Cell Data
    DREAM3D_INSTANCE_STRING_PROPERTY(GrainIdsArrayName)

    DREAM3D_INSTANCE_PROPERTY(bool, Loop)
    DREAM3D_INSTANCE_PROPERTY(int, CoordinationNumber)

    virtual const std::string getGroupName() { return DREAM3D::FilterGroups::ProcessingFilters; }
    virtual const std::string getSubGroupName()  { return DREAM3D::FilterSubGroups::CleanupFilters; }
    virtual const std::string getHumanLabel() { return "Smooth Bad Data (Coordination Number)"; }

    virtual void setupFilterParameters();
    /**
    * @brief This method will write the options to a file
    * @param writer The writer that is used to write the options to a file
    */
    virtual int writeFilterParameters(AbstractFilterParametersWriter* writer, int index);

    /**
    * @brief This method will read the options from a file
    * @param reader The reader that is used to read the options from a file
    */
    virtual void readFilterParameters(AbstractFilterParametersReader* reader, int index);


    virtual void execute();
    virtual void preflight();

  protected:
    OpenCloseCoordinationNumber();


  private:
    int32_t* m_Neighbors;

    int32_t* m_GrainIds;

    std::vector<std::vector<int> > voxellists;
    std::vector<int> nuclei;

    void dataCheck(bool preflight, size_t voxels, size_t fields, size_t ensembles);

    OpenCloseCoordinationNumber(const OpenCloseCoordinationNumber&); // Copy Constructor Not Implemented
    void operator=(const OpenCloseCoordinationNumber&); // Operator '=' Not Implemented
};

#endif /* OpenCloseCoordinationNumber_H_ */
