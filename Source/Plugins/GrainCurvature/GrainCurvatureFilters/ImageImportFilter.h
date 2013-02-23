/*
 * Your License or Copyright Information can go here
 */

#ifndef ImageImportFilter_H_
#define ImageImportFilter_H_

#include <string>

#include "DREAM3DLib/DREAM3DLib.h"
#include "DREAM3DLib/Common/DREAM3DSetGetMacros.h"
#include "DREAM3DLib/Common/IDataArray.h"
#include "DREAM3DLib/Common/AbstractFilter.h"


/**
 * @class ImageImportFilter ImageImportFilter.h ImageImport/Code/ImageImportFilters/ImageImportFilter.h
 * @brief
 * @author
 * @date
 * @version 1.0
 */
class ImageImportFilter : public AbstractFilter
{
  public:
    DREAM3D_SHARED_POINTERS(ImageImportFilter);
    DREAM3D_STATIC_NEW_MACRO(ImageImportFilter);
    DREAM3D_TYPE_MACRO_SUPER(ImageImportFilter, AbstractFilter);

    virtual ~ImageImportFilter();

    /* Place your input parameters here. You can use some of the DREAM3D Macros if you want to
    * DREAM3D_INSTANCE_PROPERTY(float, XRes)
    * DREAM3D_INSTANCE_STRING_PROPERTY(OutputFile)
    */


    /**
    * @brief This returns the group that the filter belonds to. You can select
    * a different group if you want. The string returned here will be displayed
    * in the GUI for the filter
    */
    virtual const std::string getGroupName() { return "GrainCurvature"; }

    /**
    * @brief This returns a string that is displayed in the GUI. It should be readable
    * and understandable by humans.
    */
    virtual const std::string getHumanLabel() { return "ImageImportFilter Filter"; }

    /**
    * @brief This method will instantiate all the end user settable options/parameters
    * for this filter
    */
    virtual void setupFilterParameters();

    /**
    * @brief This method will write the options to a file
    * @param writer The writer that is used to write the options to a file
    */
    virtual void writeFilterParameters(AbstractFilterParametersWriter* writer);

   /**
    * @brief Reimplemented from @see AbstractFilter class
    */
    virtual void execute();

    /**
    * @brief This function runs some sanity checks on the DataContainer and inputs
    * in an attempt to ensure the filter can process the inputs.
    */
    virtual void preflight();

  protected:
    ImageImportFilter();

    /**
    * @brief Checks for the appropriate parameter values and availability of
    * arrays in the data container
    * @param preflight
    * @param voxels The number of voxels
    * @param fields The number of fields
    * @param ensembles The number of ensembles
    */
    void dataCheck(bool preflight, size_t voxels, size_t fields, size_t ensembles);

  private:

    ImageImportFilter(const ImageImportFilter&); // Copy Constructor Not Implemented
    void operator=(const ImageImportFilter&); // Operator '=' Not Implemented
};

#endif /* ImageImportFilter_H_ */