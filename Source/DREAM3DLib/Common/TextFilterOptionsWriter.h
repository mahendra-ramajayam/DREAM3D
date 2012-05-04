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
#ifndef TEXTFILTEROPTIONSWRITER_H_
#define TEXTFILTEROPTIONSWRITER_H_

#include <string>


#include "DREAM3DLib/DREAM3DLib.h"
#include "DREAM3DLib/Common/DREAM3DSetGetMacros.h"
#include "DREAM3DLib/Common/AbstractFilter.h"
#include "DREAM3DLib/Common/QualityMetricFilter.h"

#include "AbstractFilterOptionsWriter.h"
/*
 *
 */
class DREAM3DLib_EXPORT TextFilterOptionsWriter : public AbstractFilterOptionsWriter
{
  public:
    DREAM3D_SHARED_POINTERS(TextFilterOptionsWriter);
    DREAM3D_STATIC_NEW_MACRO(TextFilterOptionsWriter);
    DREAM3D_TYPE_MACRO_SUPER(TextFilterOptionsWriter, AbstractFilterOptionsWriter);


    virtual ~TextFilterOptionsWriter();

    virtual int openOptionsGroup(AbstractFilter* filter);
    virtual int closeOptionsGroup();
    virtual int writeValue(const std::string name, const std::string value);

    virtual int writeValue(const std::string name, int8_t value);
    virtual int writeValue(const std::string name, int16_t value);
    virtual int writeValue(const std::string name, int32_t value);
    virtual int writeValue(const std::string name, int64_t value);
    virtual int writeValue(const std::string name, uint8_t value);
    virtual int writeValue(const std::string name, uint16_t value);
    virtual int writeValue(const std::string name, uint32_t value);
    virtual int writeValue(const std::string name, uint64_t value);
    virtual int writeValue(const std::string name, float value);
    virtual int writeValue(const std::string name, double value);

    virtual int writeValue(const std::string name, QualityMetricFilter* f);


  protected:
    TextFilterOptionsWriter();

  private:
    TextFilterOptionsWriter(const TextFilterOptionsWriter&); // Copy Constructor Not Implemented
    void operator=(const TextFilterOptionsWriter&); // Operator '=' Not Implemented
};

#endif /* TEXTFILTEROPTIONSWRITER_H_ */