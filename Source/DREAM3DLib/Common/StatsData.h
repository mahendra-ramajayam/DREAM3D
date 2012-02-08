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

#ifndef _STATSDATATUPLE_H_
#define _STATSDATATUPLE_H_

#include <hdf5.h>


#include "DREAM3DLib/DREAM3DLib.h"
#include "DREAM3DLib/Common/DREAM3DSetGetMacros.h"
#include "DREAM3DLib/Common/DataArray.hpp"

typedef std::vector<FloatArrayType::Pointer> VectorOfFloatArray;

class DREAM3DLib_EXPORT StatsData
{
  public:
    DREAM3D_SHARED_POINTERS(StatsData);
    DREAM3D_STATIC_NEW_MACRO(StatsData);
    DREAM3D_TYPE_MACRO(StatsData);

    virtual ~StatsData();

    DREAM3D_INSTANCE_PROPERTY(float, PhaseFraction);
    /**
     * @brief The values are encoded into 3 floats: Average, Max, Min
     */
    DREAM3D_INSTANCE_VEC3_PROPERTY(float, GrainDiameterInfo);
    void setAverageGrainDiameter(float v) { m_GrainDiameterInfo[0] = v;}
    float getAverageGrainDiameter() { return m_GrainDiameterInfo[0]; }

    void setMaxGrainDiameter(float v) { m_GrainDiameterInfo[1] = v;}
    float getMaxGrainDiameter() { return m_GrainDiameterInfo[1]; }

    void setMinGrainDiameter(float v) { m_GrainDiameterInfo[2] = v;}
    float getMinGrainDiameter() { return m_GrainDiameterInfo[2]; }

    /**
      * @brief The values are encoded into 2 floats: Average, Standard Deviation
      */
    DREAM3D_INSTANCE_VEC2_PROPERTY(float, GrainSizeDistribution);
    void setGrainSizeAverage(float v) { m_GrainSizeDistribution[0] = v;}
    float getGrainSizeAverage() { return m_GrainSizeDistribution[0]; }

    void setGrainSizeStdDev(float v) { m_GrainSizeDistribution[1] = v;}
    float getGrainSizeStdDev() { return m_GrainSizeDistribution[1]; }


    DREAM3D_INSTANCE_PROPERTY(FloatArrayType::Pointer, BinNumbers);
    /**
     * @breif this will generate the Bin Numbers values;
     */
    FloatArrayType::Pointer generateBinNumbers();
    size_t getNumberOfBins()
    {
      return (m_BinNumbers.get() == NULL) ? 0 : m_BinNumbers->GetSize();
    }

    DREAM3D_INSTANCE_PROPERTY(VectorOfFloatArray, GrainSize_BOverA);
    DREAM3D_INSTANCE_PROPERTY(uint32_t, BOverA_DistType);

    DREAM3D_INSTANCE_PROPERTY(VectorOfFloatArray, GrainSize_COverA);
    DREAM3D_INSTANCE_PROPERTY(uint32_t, COverA_DistType);

    DREAM3D_INSTANCE_PROPERTY(VectorOfFloatArray, GrainSize_COverB);
    DREAM3D_INSTANCE_PROPERTY(uint32_t, COverB_DistType);

    DREAM3D_INSTANCE_PROPERTY(VectorOfFloatArray, GrainSize_Neighbors);
    DREAM3D_INSTANCE_PROPERTY(uint32_t, Neighbors_DistType);

    DREAM3D_INSTANCE_PROPERTY(VectorOfFloatArray, GrainSize_Omegas);
    DREAM3D_INSTANCE_PROPERTY(uint32_t, Omegas_DistType);

    DREAM3D_INSTANCE_PROPERTY(FloatArrayType::Pointer, MisorientationBins);
    /* 3 Vectors: Angles, Axis, Weights */
    DREAM3D_INSTANCE_PROPERTY(VectorOfFloatArray, MDF_Weights);

    DREAM3D_INSTANCE_PROPERTY(FloatArrayType::Pointer, ODF);
    /* 5 Vectors: Euler 1, Euler 2, Euler 3, Sigma, Weights */
    DREAM3D_INSTANCE_PROPERTY(VectorOfFloatArray, ODF_Weights);

    DREAM3D_INSTANCE_PROPERTY(FloatArrayType::Pointer, AxisOrientation);
    /* 5 Vectors: Euler 1, Euler 2, Euler 3, Sigma, Weights */
    DREAM3D_INSTANCE_PROPERTY(VectorOfFloatArray, AxisODF_Weights);

    void initialize();

    int writeHDF5Data(hid_t groupId);
    int readHDF5Data(hid_t groupId);

  protected:
    StatsData();

    int writePhaseFraction(hid_t groupId);
    int writeGrainDiameterInfo(hid_t groupId);
    int writeGrainSizeDistribution(hid_t groupId);
    int writeBinNumbers(hid_t groupId);
    int writeDistributionData(hid_t pid, const std::string &disType,
                                          const std::string &hdf5GroupName,
                                          VectorOfFloatArray colData);
    int writeVectorOfArrays(hid_t pid, const std::string &hdf5GroupName,
                                               VectorOfFloatArray colData);

  private:
    StatsData(const StatsData&); // Copy Constructor Not Implemented
    void operator=(const StatsData&); // Operator '=' Not Implemented
};

#endif /* _STATSDATATUPLE_H_ */