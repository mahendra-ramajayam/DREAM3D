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

#include "GoldfeatherReader.h"

#include "MXA/Utilities/MXAFileInfo.h"

/**
 * @brief The ScopedFileMonitor class will automatically close an open FILE pointer
 * when the object goes out of scope.
 */
class ScopedFileMonitor
{
  public:
    ScopedFileMonitor(FILE* f) : m_File(f) {}
    virtual ~ScopedFileMonitor() { fclose(m_File);}
  private:
    FILE* m_File;
    ScopedFileMonitor(const ScopedFileMonitor&); // Copy Constructor Not Implemented
    void operator=(const ScopedFileMonitor&); // Operator '=' Not Implemented
};



// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
GoldfeatherReader::GoldfeatherReader() :
  AbstractFilter(),
  m_Principal_Curvature_1ArrayName("Principal_Curvature_1"),
  m_Principal_Curvature_2ArrayName("Principal_Curvature_2"),
  m_Principal_Direction_1ArrayName("Principal_Direction_1"),
  m_Principal_Direction_2ArrayName("Principal_Direction_2"),
  m_SurfaceMeshNodeNormalsArrayName(DREAM3D::VertexData::SurfaceMeshNodeNormals),
  m_SurfaceMeshTriangleLabelsArrayName(DREAM3D::FaceData::SurfaceMeshFaceLabels),
  m_SurfaceMeshTriangleNormalsArrayName(DREAM3D::FaceData::SurfaceMeshFaceNormals),
  m_SurfaceMeshTrianglesArrayName(DREAM3D::FaceData::SurfaceMeshFaces)
{
  setupFilterParameters();
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
GoldfeatherReader::~GoldfeatherReader()
{
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void GoldfeatherReader::setupFilterParameters()
{
  FilterParameterVector parameters;
  /*   For an input file use this code*/
  {
    FilterParameter::Pointer parameter = FilterParameter::New();
    parameter->setHumanLabel("Input File");
    parameter->setPropertyName("InputFile");
    parameter->setWidgetType(FilterParameter::InputFileWidget);
    parameter->setValueType("string");
    parameters.push_back(parameter);
  }

  setFilterParameters(parameters);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void GoldfeatherReader::readFilterParameters(AbstractFilterParametersReader* reader, int index)
{
  reader->openFilterGroup(this, index);
  /* Code to read the values goes between these statements */
////!!##
  reader->closeFilterGroup();
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
int GoldfeatherReader::writeFilterParameters(AbstractFilterParametersWriter* writer, int index)
{
  writer->openFilterGroup(this, index);
  /* Place code that will write the inputs values into a file. reference the
   AbstractFilterParametersWriter class for the proper API to use. */
  writer->writeValue("InputFile", getInputFile() );
  writer->closeFilterGroup();
  return ++index; // we want to return the next index that was just written to
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void GoldfeatherReader::dataCheck(bool preflight, size_t voxels, size_t fields, size_t ensembles)
{
  setErrorCondition(0);
  std::stringstream ss;
  SurfaceDataContainer* sm = getSurfaceDataContainer();

  if (getInputFile().empty() == true)
  {
    ss << ClassName() << " needs the Input File Set and it was not.";
    setErrorCondition(-387);
    addErrorMessage(getHumanLabel(), ss.str(), getErrorCondition());
  }
  else if (MXAFileInfo::exists(getInputFile()) == false)
  {
    ss << "The input file does not exist.";
    setErrorCondition(-388);
    addErrorMessage(getHumanLabel(), ss.str(), getErrorCondition());
  }


  DREAM3D::Mesh::VertListPointer_t vertices = DREAM3D::Mesh::VertList_t::CreateArray(1, DREAM3D::VertexData::SurfaceMeshNodes);
  DREAM3D::Mesh::FaceListPointer_t triangles = DREAM3D::Mesh::FaceList_t::CreateArray(1, DREAM3D::FaceData::SurfaceMeshFaces);

  sm->setVertices(vertices);
  sm->setFaces(triangles);

  DoubleArrayType::Pointer normalsPtr = DoubleArrayType::CreateArray(1, 3, DREAM3D::VertexData::SurfaceMeshNodeNormals);
  //addCreatedCellData( normalsPtr->GetName());
  sm->addVertexData(normalsPtr->GetName(), normalsPtr);

  DoubleArrayType::Pointer pcurv1Ptr = DoubleArrayType::CreateArray(1, 1, "Principal_Curvature_1");
  //addCreatedCellData( pcurv1Ptr->GetName());
  sm->addVertexData(pcurv1Ptr->GetName(), pcurv1Ptr);

  DoubleArrayType::Pointer pcurv2Ptr = DoubleArrayType::CreateArray(1, 1, "Principal_Curvature_2");
// addCreatedCellData( pcurv2Ptr->GetName());
  sm->addVertexData(pcurv2Ptr->GetName(), pcurv2Ptr);

  DoubleArrayType::Pointer pDirection1Ptr = DoubleArrayType::CreateArray(1, 3, "Principal_Direction_1");
// addCreatedCellData( pDirection1Ptr->GetName());
  sm->addVertexData(pDirection1Ptr->GetName(), pDirection1Ptr);

  DoubleArrayType::Pointer pDirection2Ptr = DoubleArrayType::CreateArray(1, 3, "Principal_Direction_2");
//  addCreatedCellData( pDirection2Ptr->GetName());
  sm->addVertexData(pDirection2Ptr->GetName(), pDirection2Ptr);


  DataArray<int32_t>::Pointer faceLabelPtr = DataArray<int32_t>::CreateArray(1, 2, DREAM3D::FaceData::SurfaceMeshFaceLabels);
//  addCreatedFieldData( faceLabelPtr->GetName());
  sm->addFaceData(faceLabelPtr->GetName(), faceLabelPtr);

  DoubleArrayType::Pointer triNormalsPtr = DoubleArrayType::CreateArray(1, 3, DREAM3D::FaceData::SurfaceMeshFaceNormals);
//  addCreatedFieldData( triNormalsPtr->GetName());
  sm->addFaceData(triNormalsPtr->GetName(), triNormalsPtr);

}


// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void GoldfeatherReader::preflight()
{
  /* Place code here that sanity checks input arrays and input values. Look at some
  * of the other DREAM3DLib/Filters/.cpp files for sample codes */
  dataCheck(true, 1, 1, 1);
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void GoldfeatherReader::execute()
{
  int err = 0;
  std::stringstream ss;
  setErrorCondition(err);
  SurfaceDataContainer* m = getSurfaceDataContainer();
  if(NULL == m)
  {
    setErrorCondition(-999);
    notifyErrorMessage("The Voxel DataContainer Object was NULL", -999);
    return;
  }
  setErrorCondition(0);



  FILE* f = fopen(m_InputFile.c_str(), "r");
  if (NULL == f)
  {
    setErrorCondition(-999);
    notifyErrorMessage("Error opening Input file", getErrorCondition());
    return;
  }
  ScopedFileMonitor fileMonitor(f);

  int nNodes = 0;
  fscanf(f, "%d\n", &nNodes);

  dataCheck(false, nNodes, 1, 1);

  // Allocate the Nodes, Normals, curvatures and principal direction vectors
  DREAM3D::Mesh::VertListPointer_t nodesPtr = DREAM3D::Mesh::VertList_t::CreateArray(nNodes, DREAM3D::VertexData::SurfaceMeshNodes);
  nodesPtr->initializeWithZeros();
  DREAM3D::Mesh::Vert_t* nodes = nodesPtr->GetPointer(0);


  DoubleArrayType::Pointer normalsPtr = DoubleArrayType::CreateArray(nNodes, 3, DREAM3D::VertexData::SurfaceMeshNodeNormals);
  double* normals = normalsPtr->GetPointer(0);

  DoubleArrayType::Pointer pcurv1Ptr = DoubleArrayType::CreateArray(nNodes, 1, "Principal_Curvature_1");
  double* pcurv1 = pcurv1Ptr->GetPointer(0);

  DoubleArrayType::Pointer pcurv2Ptr = DoubleArrayType::CreateArray(nNodes, 1, "Principal_Curvature_2");
  double* pcurv2 = pcurv2Ptr->GetPointer(0);

  DoubleArrayType::Pointer pDirection1Ptr = DoubleArrayType::CreateArray(nNodes, 3, "Principal_Direction_1");
  double* pDirection1 = pDirection1Ptr->GetPointer(0);

  DoubleArrayType::Pointer pDirection2Ptr = DoubleArrayType::CreateArray(nNodes, 3, "Principal_Direction_2");
  double* pDirection2 = pDirection2Ptr->GetPointer(0);

  float x, y, z, n0, n1, n2, p1, p2;
  for(int n = 0; n < nNodes; ++n)
  {
    fscanf(f, "%f %f %f %f %f %f %f %f\n", &x, &y, &z, &n0, &n1, &n2, &p1, &p2);
    nodes[n].pos[0] = x;
    nodes[n].pos[1] = y;
    nodes[n].pos[2] = z;
    normals[n * 3 + 0] = n0;
    normals[n * 3 + 1] = n1;
    normals[n * 3 + 2] = n2;
    pcurv1[n] = p1;
    pcurv2[n] = p2;

    // Read the next line of the data which is the principal direction vectors
    fscanf(f, "%f %f %f %f %f %f\n", &x, &y, &z, &n0, &n1, &n2);
    pDirection1[n * 3 + 0] = x;
    pDirection1[n * 3 + 1] = y;
    pDirection1[n * 3 + 2] = z;

    pDirection2[n * 3 + 0] = n0;
    pDirection2[n * 3 + 1] = n1;
    pDirection2[n * 3 + 2] = n2;

  }

  m->setVertices(nodesPtr);
  m->addVertexData(normalsPtr->GetName(), normalsPtr);
  m->addVertexData(pcurv1Ptr->GetName(), pcurv1Ptr);
  m->addVertexData(pcurv2Ptr->GetName(), pcurv2Ptr);
  m->addVertexData(pDirection1Ptr->GetName(), pDirection1Ptr);
  m->addVertexData(pDirection2Ptr->GetName(), pDirection2Ptr);

  int nTriangles = 0;
  err = fscanf(f, "%d\n", &nTriangles);
  if (err < 0)
  {
    off_t fpos;
    fpos = ftell(f);
    setErrorCondition(-876);
    notifyErrorMessage("Error Reading the number of Triangles from the file", getErrorCondition());
    return;
  }

  DREAM3D::Mesh::FaceListPointer_t trianglesPtr = DREAM3D::Mesh::FaceList_t::CreateArray(nTriangles, DREAM3D::FaceData::SurfaceMeshFaces);
  trianglesPtr->initializeWithZeros();
  DREAM3D::Mesh::Face_t* triangles = trianglesPtr->GetPointer(0);

  DataArray<int32_t>::Pointer faceLabelPtr = DataArray<int32_t>::CreateArray(nTriangles, 2, DREAM3D::FaceData::SurfaceMeshFaceLabels);
  faceLabelPtr->initializeWithZeros();
  int32_t* faceLabels = faceLabelPtr->GetPointer(0);

  DoubleArrayType::Pointer triNormalsPtr = DoubleArrayType::CreateArray(nTriangles, 3, DREAM3D::FaceData::SurfaceMeshFaceNormals);
  double* triNormals = triNormalsPtr->GetPointer(0);

  for(int t = 0; t < nTriangles; ++t)
  {
    fscanf(f, "%f %f %f %f %f %f", &x, &y, &z, &n0, &n1, &n2);
    triangles[t].verts[0] = x;
    triangles[t].verts[1] = y;
    triangles[t].verts[2] = z;
    //  triangles[t].tIndex = t;
    faceLabels[t * 2] = 0;
    faceLabels[t * 2 + 1] = 1;
    triNormals[t * 3 + 0] = n0;
    triNormals[t * 3 + 1] = n1;
    triNormals[t * 3 + 2] = n2;
  }

  m->setFaces(trianglesPtr);
  m->addFaceData(faceLabelPtr->GetName(), faceLabelPtr);
  m->addFaceData(triNormalsPtr->GetName(), triNormalsPtr);

  /* Let the GUI know we are done with this filter */
  notifyStatusMessage("Complete");
}











