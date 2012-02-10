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

#ifndef _H5STATSDATA_DELEGATE_H_
#define _H5STATSDATA_DELEGATE_H_

#include <string>

#include <hdf5.h>


#include "DREAM3DLib/DREAM3DLib.h"
#include "DREAM3DLib/Common/DREAM3DSetGetMacros.h"
#include "DREAM3DLib/Common/StatsData.h"

/*
 *
 */
class DREAM3DLib_EXPORT H5StatsDataDelegate
{
  public:

    DREAM3D_SHARED_POINTERS(H5StatsDataDelegate)
    DREAM3D_STATIC_NEW_MACRO(H5StatsDataDelegate)
    DREAM3D_TYPE_MACRO(H5StatsDataDelegate)
    virtual ~H5StatsDataDelegate();

    int writeStatsData(StatsData* data, hid_t groupId);
    int readStatsData(StatsData* data, hid_t groupId);

  protected:
    H5StatsDataDelegate();

    int writePhaseFraction(StatsData* data, hid_t groupId);
    int readPhaseFraction(StatsData* data, hid_t pid);

    int writeGrainDiameterInfo(StatsData* data, hid_t groupId);
    int readGrainDiameterInfo(StatsData* data, hid_t groupId);

    int writeGrainSizeDistribution(StatsData* data, hid_t groupId);
    int readGrainSizeDistribution(StatsData* data, hid_t groupId);

    int writeBinNumbers(StatsData* data, hid_t groupId);
    int readBinNumbers(StatsData* data, hid_t groupId);


    int readMDFWeights(hid_t pid, StatsData* data);
    int readODFWeights(hid_t pid, StatsData* data);
    int readAxisODFWeights(hid_t pid, StatsData* data);

    int writeWeightsData(hid_t pid, const std::string &hdf5GroupName,
                                              VectorOfFloatArray colData);

    int writeDistributionData(hid_t pid, const std::string &disType,
                                          const std::string &hdf5GroupName,
                                          VectorOfFloatArray colData);
    int readDistributionData(hid_t pid, const std::string &disType,
                                          const std::string &hdf5GroupName,
                                          VectorOfFloatArray colData);


    int writeVectorOfArrays(hid_t pid, VectorOfFloatArray colData);
    int readVectorOfArrays(hid_t pid, VectorOfFloatArray colData);

    VectorOfFloatArray createDistributionVector(unsigned int distType);

    VectorOfFloatArray createBetaDistributionArrays();

    VectorOfFloatArray createPowerDistributionArrays();

    VectorOfFloatArray createLogNormalDistributionArrays();

  private:
    H5StatsDataDelegate(const H5StatsDataDelegate&); // Copy Constructor Not Implemented
    void operator=(const H5StatsDataDelegate&); // Operator '=' Not Implemented
};

#endif /* _H5STATSDATA_DELEGATE_H_ */