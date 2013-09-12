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
#ifndef _FaceArray_H_
#define _FaceArray_H_


#include <string.h>

#include <boost/shared_array.hpp>

#include "DREAM3DLib/DREAM3DLib.h"
#include <QtCore/qset.h>
#include "DREAM3DLib/Common/DREAM3DSetGetMacros.h"
#include "DREAM3DLib/Common/VertexArray.hpp"
#include "DREAM3DLib/Common/DynamicListArray.hpp"



/**
 * @brief The MeshLinks class contains arrays of Faces for each Node in the mesh. This allows quick query to the node
 * to determine what Cells the node is a part of.
 */
class FaceArray
{
  public:

    typedef struct
    {
      size_t verts[3];
    } Face_t;

    typedef QSet<int32_t> UniqueFaceIds_t;

    DREAM3D_SHARED_POINTERS(FaceArray)
    DREAM3D_STATIC_NEW_MACRO(FaceArray)
    DREAM3D_TYPE_MACRO(FaceArray)



    // -----------------------------------------------------------------------------
    //
    // -----------------------------------------------------------------------------
    virtual ~FaceArray(){ }

    // -----------------------------------------------------------------------------
    //
    // -----------------------------------------------------------------------------
    void resizeArray(size_t newSize) { m_Array->Resize(newSize); }

    // -----------------------------------------------------------------------------
    //
    // -----------------------------------------------------------------------------
    int64_t getNumberOfTuples() { return m_Array->getNumberOfTuples(); }
    int64_t count() { return m_Array->getNumberOfTuples(); }


    // -----------------------------------------------------------------------------
    //
    // -----------------------------------------------------------------------------
    static Pointer CreateArray(size_t numElements, const QString &name)
    {
      if (name.isEmpty() == true)
      {
        return NullPointer();
      }
      FaceArray* d = new FaceArray();
      d->resizeArray(numElements);
      Pointer ptr(d);
      return ptr;
    }

    // -----------------------------------------------------------------------------
    //
    // -----------------------------------------------------------------------------
    void getVerts(size_t edgeId, size_t* verts)
    {
      Face_t& Face = *(m_Array->getPointer(edgeId));
      verts[0] = Face.verts[0];
      verts[1] = Face.verts[1];
      verts[2] = Face.verts[2];
    }

    // -----------------------------------------------------------------------------
    //
    // -----------------------------------------------------------------------------
    void setVerts(size_t edgeId, float* verts)
    {
      Face_t& Face = *(m_Array->getPointer(edgeId));
      Face.verts[0] = verts[0];
      Face.verts[1] = verts[1];
      Face.verts[2] = verts[2];
    }

    // -----------------------------------------------------------------------------
    //
    // -----------------------------------------------------------------------------
    void findFacesContainingVert(StructArray<VertexArray::Vert_t>::Pointer Verts,
                               StructArray<Face_t>::Pointer Faces )
    {

      size_t numPts = Verts->getNumberOfTuples();
      size_t numCells = Faces->getNumberOfTuples();

      m_FacesContainingVert = DynamicListArray::New();

      // Allocate the basic structures
      //m_FacesContainingVert->allocate(numCells);
      QVector<uint16_t> linkCount(numCells, 0);
      size_t cellId;
      unsigned short* linkLoc;

      // fill out lists with number of references to cells
      typedef boost::shared_array<unsigned short> SharedShortArray_t;
      SharedShortArray_t linkLocPtr(new unsigned short[numPts]);
      linkLoc = linkLocPtr.get();

      ::memset(linkLoc, 0, numPts*sizeof(unsigned short));


      size_t pts[3];

      //vtkPolyData *pdata = static_cast<vtkPolyData *>(data);
      // traverse data to determine number of uses of each point
      for (cellId=0; cellId < numCells; cellId++)
      {
        getVerts(cellId, pts);
        for (size_t j=0; j < 3; j++)
        {
         // m_FacesContainingVert->incrementLinkCount(pts[j]);
         linkCount[pts[j]]++;
        }
      }

      // now allocate storage for the links
      m_FacesContainingVert->allocateLists(linkCount);

      for (cellId=0; cellId < numCells; cellId++)
      {
        getVerts(cellId, pts);
        for (size_t j=0; j < 3; j++)
        {
          m_FacesContainingVert->insertCellReference(pts[j], (linkLoc[pts[j]])++, cellId);
        }
      }

    }

    // -----------------------------------------------------------------------------
    //
    // -----------------------------------------------------------------------------
    void findFaceNeighbors(StructArray<VertexArray::Vert_t>::Pointer Verts, StructArray<Face_t>::Pointer Faces)
    {

      size_t nFaces = Faces->getNumberOfTuples();

      DynamicListArray::Pointer m_FaceNeighbors = DynamicListArray::New();

      QVector<uint16_t> linkCount(nFaces, 0);

      // Allocate an array of bools that we use each iteration of triangle so that we don't put duplicates into the array
      boost::shared_array<bool> visitedPtr(new bool[nFaces]);
      bool* visited = visitedPtr.get();
      ::memset(visitedPtr.get(), 0, nFaces);

      // Reuse this vector for each loop. Avoids re-allocating the memory each time through the loop
      QVector<int> loop_neighbors(32, 0);

      // Build up the Face Adjacency list now that we have the cell links
      for(size_t t = 0; t < nFaces; ++t)
      {
        //   qDebug() << "Analyzing Face " << t << "\n";
        Face_t& seedFace = *(Faces->getPointer(t));
        for(size_t v = 0; v < 3; ++v)
        {
          //   qDebug() << " vert " << v << "\n";
          int nFs = m_FacesContainingVert->getNumberOfElements(seedFace.verts[v]);
          int* vertIdxs = m_FacesContainingVert->getElementListPointer(seedFace.verts[v]);

          for(int vt = 0; vt < nFs; ++vt)
          {
            if (vertIdxs[vt] == static_cast<int>(t) ) { continue; } // This is the same triangle as our "source" triangle
            if (visited[vertIdxs[vt]] == true) { continue; } // We already added this triangle so loop again
            //      qDebug() << "   Comparing Face " << vertIdxs[vt] << "\n";
            Face_t& vertFace = *(Faces->getPointer(vertIdxs[vt]));
            int vCount = 0;
            // Loop over all the vertex indices of this triangle and try to match 2 of them to the current loop triangle
            // If there are 2 matches then that triangle is a neighbor of this triangle. if there are more than 2 matches
            // then there is a real problem with the mesh and the program is going to assert.
            // Unrolled the loop to shave about 25% of time off the outer loop.
            int seedFaceVert0 = seedFace.verts[0];
            int seedFaceVert1 = seedFace.verts[1];
            int seedFaceVert2 = seedFace.verts[2];
            int trgtFaceVert0 = vertFace.verts[0];
            int trgtFaceVert1 = vertFace.verts[1];
            int trgtFaceVert2 = vertFace.verts[2];

            if (seedFaceVert0 == trgtFaceVert0 || seedFaceVert0 == trgtFaceVert1 || seedFaceVert0 == trgtFaceVert2  )
            {
              vCount++;
            }
            if (seedFaceVert1 == trgtFaceVert0 || seedFaceVert1 == trgtFaceVert1 || seedFaceVert1 == trgtFaceVert2  )
            {
              vCount++;
            }
            if (seedFaceVert2 == trgtFaceVert0 || seedFaceVert2 == trgtFaceVert1 || seedFaceVert2 == trgtFaceVert2  )
            {
              vCount++;
            }

            BOOST_ASSERT(vCount < 3); // No way 2 edges can share both vertices. Something is VERY wrong at this point

            // So if our vertex match count is 2 and we have not visited the triangle in question then add this triangle index
            // into the list of Face Indices as neighbors for the source triangle.
            if (vCount == 2)
            {
              //qDebug() << "       Neighbor: " << vertIdxs[vt] << "\n";
              // Use the current count of neighbors as the index
              // into the loop_neighbors vector and place the value of the vertex triangle at that index
              loop_neighbors[linkCount[t]] = vertIdxs[vt];
              linkCount[t]++;// Increment the count for the next time through
              if (linkCount[t] >= loop_neighbors.size())
              {
                loop_neighbors.resize(loop_neighbors.size() + 10);
              }
              visited[vertIdxs[vt]] = true; // Set this triangle as visited so we do NOT add it again
            }
          }
        }
        BOOST_ASSERT(linkCount[t] > 2);
        // Reset all the visited triangle indexs back to false (zero)
        for(size_t k = 0;k < linkCount[t]; ++k)
        {
          visited[loop_neighbors[k]] = false;
        }
        // Allocate the array storage for the current triangle to hold its Face list
        m_FaceNeighbors->setElementList(t, linkCount[t], &(loop_neighbors[0]));
      }
    }

    /*
     * @brief
     */
    Face_t* getPointer(size_t i)
    {
      return m_Array->getPointer(i);
    }

     /**
     * @brief Returns reference to the Face_t at the index i
     * @param i
     * @return
     */
    inline Face_t& operator[](size_t i)
    {
      return (*m_Array)[i];
    }
     /**
     * @brief Returns reference to the Face_t at the index i
     * @param i
     * @return
     */
    inline Face_t& getFace(size_t i)
    {
      return (*m_Array)[i];
    }


  protected:
    FaceArray();

  private:
    StructArray<Face_t>::Pointer  m_Array;
    DynamicListArray::Pointer m_FacesContainingVert;
    DynamicListArray::Pointer m_FaceNeighbors;

    QString m_Name;

    FaceArray(const FaceArray&); // Copy Constructor Not Implemented
    void operator=(const FaceArray&); // Operator '=' Not Implemented

};



#endif /* _FaceArray_H_ */
