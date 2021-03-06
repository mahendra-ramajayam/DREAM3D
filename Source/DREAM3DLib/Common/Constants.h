/* ============================================================================
 * Copyright (c) 2010, Michael A. Jackson (BlueQuartz Software)
 * Copyright (c) 2010, Dr. Michael A. Groeber (US Air Force Research Laboratories)
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
#ifndef _DREAM3D_CONSTANTS_H_
#define _DREAM3D_CONSTANTS_H_

#if defined (_MSC_VER)
#define WIN32_LEAN_AND_MEAN   // Exclude rarely-used stuff from Windows headers
#endif



#include <string>

#include "DREAM3DLib/DREAM3DLib.h"

#define DREAM3D_STRING std::string

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
namespace DREAM3D
{

  typedef uint32_t Rgb;
  const Rgb  RGB_MASK    = 0x00ffffff;                // masks RGB values

  namespace FilterGroups
  {
    const DREAM3D_STRING GenericFilters("Generic");
    const DREAM3D_STRING IOFilters("IO");
    const DREAM3D_STRING ProcessingFilters("Processing");
    const DREAM3D_STRING ReconstructionFilters("Reconstruction");
    const DREAM3D_STRING SamplingFilters("Sampling");
    const DREAM3D_STRING StatisticsFilters("Statistics");
    const DREAM3D_STRING CustomFilters("Custom");
    const DREAM3D_STRING SyntheticBuildingFilters("SyntheticBuilding");
    const DREAM3D_STRING SurfaceMeshingFilters("SurfaceMeshing");
    const DREAM3D_STRING SolidMeshingFilters("SolidMeshing");
  }

  namespace FilterSubGroups
  {
    const DREAM3D_STRING EnsembleStatsFilters("Ensemble");
    const DREAM3D_STRING MemoryManagementFilters("Memory/Management");
    const DREAM3D_STRING SpatialFilters("Spatial");
    const DREAM3D_STRING OutputFilters("Output");
    const DREAM3D_STRING InputFilters("Input");
    const DREAM3D_STRING ImageFilters("Image");
    const DREAM3D_STRING CleanupFilters("Cleanup");
    const DREAM3D_STRING ThresholdFilters("Threshold");
    const DREAM3D_STRING RegularizationFilters("Regularization");
    const DREAM3D_STRING ConversionFilters("Conversion");
    const DREAM3D_STRING AlignmentFilters("Alignment");
    const DREAM3D_STRING SegmentationFilters("Segmentation");
    const DREAM3D_STRING GroupingFilters("Grouping");
    const DREAM3D_STRING CropCutFilters("Croping/Cutting");
    const DREAM3D_STRING RotationTransformationFilters("Rotating/Transforming");
    const DREAM3D_STRING ResolutionFilters("Resolution");
    const DREAM3D_STRING MorphologicalFilters("Morphological");
    const DREAM3D_STRING CrystallographicFilters("Crystallographic");
    const DREAM3D_STRING PackingFilters("Packing");
    const DREAM3D_STRING CrystallographyFilters("Crystallography");
    const DREAM3D_STRING GenerationFilters("Generation");
    const DREAM3D_STRING SmoothingFilters("Smoothing");
    const DREAM3D_STRING CurvatureFilters("Curvature");
    const DREAM3D_STRING ConnectivityArrangementFilters("Connectivity/Arrangement");
    const DREAM3D_STRING MiscFilters("Misc");
  }

  namespace CellData
  {
    const DREAM3D_STRING GrainIds("GrainIds");
    const DREAM3D_STRING OldGrainIds("OldGrainIds");
    const DREAM3D_STRING FarFieldZoneIds("FarFieldZoneIds");
    const DREAM3D_STRING FarFieldQuats("FarFieldQuats");
    const DREAM3D_STRING ParentIds("ParentIds");
    const DREAM3D_STRING ParentDensity("ParentDensity");
    const DREAM3D_STRING Phases("Phases");
    const DREAM3D_STRING CellPhases("Phases");
    const DREAM3D_STRING BandContrast("BandContrast");
    const DREAM3D_STRING EulerAngles("EulerAngles");
    const DREAM3D_STRING SurfaceVoxels("SurfaceVoxels");
    const DREAM3D_STRING Quats("Quats");
    const DREAM3D_STRING GoodVoxels("GoodVoxels");
    const DREAM3D_STRING NearestNeighbors("NearestNeighbors");
    const DREAM3D_STRING GBEuclideanDistances("GBEuclideanDistances");
    const DREAM3D_STRING TJEuclideanDistances("TJEuclideanDistances");
    const DREAM3D_STRING QPEuclideanDistances("QPEuclideanDistances");
    const DREAM3D_STRING GrainReferenceMisorientations("GrainReferenceMisorientations");
    const DREAM3D_STRING GrainReferenceCAxisMisorientations("GrainReferenceCAxisMisorientations");
    const DREAM3D_STRING KernelAverageMisorientations("KernelAverageMisorientations");
    const DREAM3D_STRING ImageQualityNoSpace("ImageQuality");
    const DREAM3D_STRING ImageQuality("Image Quality");
    const DREAM3D_STRING ConfidenceIndexNoSpace("ConfidenceIndex");
    const DREAM3D_STRING ConfidenceIndex("Confidence Index");
    const DREAM3D_STRING IPFColor("IPFColor");
    const DREAM3D_STRING MisorientationColor("MisorientationColor");
    const DREAM3D_STRING RodriguesColor("RodriguesColor");
    const DREAM3D_STRING EulerColor("EulerColor");
    const DREAM3D_STRING GlobAlpha("GlobAlpha");
    const DREAM3D_STRING BC("BandContrasts");
    const DREAM3D_STRING ImageData("ImageData");
    const DREAM3D_STRING FlatImageData("FlatImageData");

    const DREAM3D_STRING SolidMeshNodes("SolidMeshNodes");
    const DREAM3D_STRING SolidMeshTetrahedrons("SolidMeshTetrahedrons");
  }

  namespace FieldData
  {
    const DREAM3D_STRING Active("Active");
    const DREAM3D_STRING GoodFields("GoodFields");
    const DREAM3D_STRING Phases("Phases");
    const DREAM3D_STRING FieldPhases("Phases");
    const DREAM3D_STRING F1("F1");
    const DREAM3D_STRING F1spt("F1spt");
    const DREAM3D_STRING F7("F7");
    const DREAM3D_STRING mPrime("mPrime");
    const DREAM3D_STRING EulerAngles("EulerAngles");
    const DREAM3D_STRING NumGrainsPerParent("NumGrainsPerParent");
    const DREAM3D_STRING SurfaceVoxelFractions("SurfaceVoxelFractions");
    const DREAM3D_STRING AxisEulerAngles("AxisEulerAngles");
    const DREAM3D_STRING SurfaceFields("SurfaceFields");
    const DREAM3D_STRING BiasedFields("BiasedFields");
    const DREAM3D_STRING NumNeighbors("NumNeighbors");
    const DREAM3D_STRING RGBs("RGBs");
    const DREAM3D_STRING ElasticStrains("ElasticStrains");
    const DREAM3D_STRING FarFieldOrientations("FarFieldOrientations");
    const DREAM3D_STRING Centroids("Centroids");
    const DREAM3D_STRING NumCells("NumCells");
    const DREAM3D_STRING ParentIds("ParentIds");
    const DREAM3D_STRING Volumes("Volumes");
    const DREAM3D_STRING EquivalentDiameters("EquivalentDiameters");
    const DREAM3D_STRING Schmids("Schmids");
    const DREAM3D_STRING SlipSystems("SlipSystems");
    const DREAM3D_STRING LargestCrossSections("LargestCrossSections");
    const DREAM3D_STRING AspectRatios("AspectRatios");
    const DREAM3D_STRING AxisLengths("AxisLengths");
    const DREAM3D_STRING Omega3s("Omega3s");
    const DREAM3D_STRING AvgCAxes("AvgCAxes");
    const DREAM3D_STRING AvgQuats("AvgQuats");
    const DREAM3D_STRING Poles("Poles");
    const DREAM3D_STRING Neighborhoods("Neighborhoods");
    const DREAM3D_STRING GrainAvgMisorientations("GrainAvgMisorientations");
    const DREAM3D_STRING GrainAvgCAxisMisorientations("GrainAvgCAxisMisorientations");
    const DREAM3D_STRING GrainStdevCAxisMisorientations("GrainStdevCAxisMisorientations");
    const DREAM3D_STRING KernelAvgMisorientations("KernelAvgMisorientations");
    const DREAM3D_STRING NeighborList("NeighborList");
    const DREAM3D_STRING NeighborhoodList("NeighborhoodList");
    const DREAM3D_STRING MisorientationList("MisorientationList");
    const DREAM3D_STRING AvgMisorientations("AvgMisorientations");
    const DREAM3D_STRING SharedSurfaceAreaList("SharedSurfaceAreaList");
    const DREAM3D_STRING LMG("LMG");
    const DREAM3D_STRING BasalLoadingFactor("BasalLoadingFactor");
    const DREAM3D_STRING Clusters("Clusters");
    const DREAM3D_STRING ClusteringList("ClusteringList");
    const DREAM3D_STRING CAxisMisalignmentList("CAxisMisalignmentList");
    const DREAM3D_STRING AvgCAxisMisalignments("AvgCAxisMisalignments");
    const DREAM3D_STRING LocalCAxisMisalignments("LocalCAxisMisalignments");
    const DREAM3D_STRING UnbiasedLocalCAxisMisalignments("UnbiasedLocalCAxisMisalignments");
  }

  namespace EnsembleData
  {
    const DREAM3D_STRING NumFields("NumFields");
    const DREAM3D_STRING VolFractions("VolFractions");
    const DREAM3D_STRING TotalSurfaceAreas("TotalSurfaceAreas");
    const DREAM3D_STRING CrystalStructures("CrystalStructures");
    const DREAM3D_STRING PhaseTypes("PhaseTypes");
    const DREAM3D_STRING BravaisLattice("BravaisLattice");
    const DREAM3D_STRING PrecipitateFractions("PrecipitateFractions");
    const DREAM3D_STRING ShapeTypes("ShapeTypes");
    const DREAM3D_STRING Statistics("Statistics");
    const DREAM3D_STRING PhaseName("PhaseName");
    const DREAM3D_STRING MaterialName("MaterialName");
    const DREAM3D_STRING LatticeConstants("LatticeConstants");
    const DREAM3D_STRING GBCD("GBCD");
    const DREAM3D_STRING GBCDdimensions("GBCDdimensions");
  }


  namespace VertexData
  {
    const DREAM3D_STRING SurfaceMeshNodes("SurfaceMeshNodes");
    const DREAM3D_STRING SurfaceMeshNodeType("SurfaceMeshNodeType");
    const DREAM3D_STRING SurfaceMeshNodeNormals("SurfaceMeshNodeNormals");
    const DREAM3D_STRING SurfaceMeshNodeFaces("SurfaceMeshNodeFaces");
  }

  namespace FaceData
  {
    const DREAM3D_STRING SurfaceMeshFaces("SurfaceMeshFaces");
    const DREAM3D_STRING SurfaceMeshFaceIPFColors("SurfaceMeshFaceIPFColors");
    const DREAM3D_STRING SurfaceMeshFaceMisorientationColors("SurfaceMeshFaceMisorientationColors");
    const DREAM3D_STRING SurfaceMeshFaceLabels("SurfaceMeshFaceLabels");
    const DREAM3D_STRING SurfaceMeshF1s("SurfaceMeshF1s");
    const DREAM3D_STRING SurfaceMeshF1spts("SurfaceMeshF1spts");
    const DREAM3D_STRING SurfaceMeshF7s("SurfaceMeshF7s");
    const DREAM3D_STRING SurfaceMeshmPrimes("SurfaceMeshmPrimes");
    const DREAM3D_STRING SurfaceMeshVoxels("SurfaceMeshVoxels");
    const DREAM3D_STRING SurfaceMeshFaceCentroids("SurfaceMeshFaceCentroids");
    const DREAM3D_STRING SurfaceMeshFaceAreas("SurfaceMeshFaceAreas");
    const DREAM3D_STRING SurfaceMeshTwinBoundary("SurfaceMeshTwinBoundary");
    const DREAM3D_STRING SurfaceMeshTwinBoundaryIncoherence("SurfaceMeshTwinBoundaryIncoherence");
    const DREAM3D_STRING SurfaceMeshTwinBoundarySchmidFactors("SurfaceMeshTwinBoundarySchmidFactors");
    const DREAM3D_STRING SurfaceMeshFaceDihedralAngles("SurfaceMeshFaceDihedralAngles");
    const DREAM3D_STRING SurfaceMeshFaceNormals("SurfaceMeshFaceNormals");
    const DREAM3D_STRING SurfaceMeshGrainFaceId("SurfaceMeshGrainFaceId");
    const DREAM3D_STRING SurfaceMeshGaussianCurvatures("SurfaceMeshGaussianCurvatures");
    const DREAM3D_STRING SurfaceMeshMeanCurvatures("SurfaceMeshMeanCurvatures");
    const DREAM3D_STRING SurfaceMeshPrincipalCurvature1("PrincipalCurvature1");
    const DREAM3D_STRING SurfaceMeshPrincipalCurvature2("PrincipalCurvature2");
    const DREAM3D_STRING SurfaceMeshPrincipalDirection1("PrincipalDirection1");
    const DREAM3D_STRING SurfaceMeshPrincipalDirection2("PrincipalDirection2");
  }

  namespace EdgeData
  {
    const DREAM3D_STRING SurfaceMeshEdges("SurfaceMeshEdges");
    const DREAM3D_STRING SurfaceMeshUniqueEdges("SurfaceMeshUniqueEdges");
    const DREAM3D_STRING SurfaceMeshInternalEdges("SurfaceMeshInternalEdges");
    const DREAM3D_STRING SurfaceMeshTriangleEdges("SurfaceMeshTriangleEdges");
    const DREAM3D_STRING SurfaceMeshEdgeFaces("SurfaceMeshEdgeFaces");
  }


  namespace HDF5
  {
    const DREAM3D_STRING FileVersionName("FileVersion");
    const DREAM3D_STRING FileVersion("5.0");
    const DREAM3D_STRING DataContainerName("DataContainer");

    const DREAM3D_STRING VolumeDataContainerName("VolumeDataContainer");
    const DREAM3D_STRING SurfaceDataContainerName("SurfaceDataContainer");
    const DREAM3D_STRING VertexDataContainerName("VertexDataContainer");
    const DREAM3D_STRING EdgeDataContainerName("EdgeDataContainer");
    const DREAM3D_STRING SurfaceMeshDataContainerName("SurfaceMeshDataContainer");
    const DREAM3D_STRING SolidMeshDataContainerName("SolidMeshDataContainer");
    const DREAM3D_STRING MeshVertLinksName("MeshVertLinks");


    const DREAM3D_STRING VoxelDataName("VoxelData");
    const DREAM3D_STRING PipelineGroupName("Pipeline");
    const DREAM3D_STRING ObjectType("ObjectType");
    const DREAM3D_STRING NumComponents("NumComponents");

    const DREAM3D_STRING VerticesName("Vertices");
    const DREAM3D_STRING FacesName("Faces");
    const DREAM3D_STRING EdgesName("Edges");
    const DREAM3D_STRING MeshLinksName("MeshLinks");
    const DREAM3D_STRING MeshFaceNeighborLists("MeshFaceNeighborLists");

    //  const DREAM3D_STRING Grain_ID("Grain_ID");
    // const DREAM3D_STRING SchmidFactor ("SchmidFactor");
    const DREAM3D_STRING Neighbor_Grain_ID_List( "Neighbor_Grain_ID_List");
    const DREAM3D_STRING KernelAvgDisorientation( "KernelAvgDisorientation");
    const DREAM3D_STRING GrainAvgDisorientation ("GrainAvgDisorientation");
    //  const DREAM3D_STRING ImageQuality( "ImageQuality");

    // const DREAM3D_STRING Phase("Phase");
    const DREAM3D_STRING GBCD("GBCD");
    const DREAM3D_STRING Statistics("Statistics");
    const DREAM3D_STRING AxisOrientation("AxisOrientation");
    const DREAM3D_STRING AxisODFWeights("AxisODF-Weights");
    const DREAM3D_STRING ODF("ODF");
    const DREAM3D_STRING ODFWeights("ODF-Weights");
    const DREAM3D_STRING Euler1("Euler 1");
    const DREAM3D_STRING Euler2("Euler 2");
    const DREAM3D_STRING Euler3("Euler 3");
    const DREAM3D_STRING Weight("Weight");
    const DREAM3D_STRING Sigma("Sigma");
    const DREAM3D_STRING MisorientationBins("MisorientationBins");
    const DREAM3D_STRING MDFWeights("MDF-Weights");
    const DREAM3D_STRING Angle("Angle");
    const DREAM3D_STRING Axis("Axis");
    const DREAM3D_STRING MicroTextureBins("MicroTextureBins");
    const DREAM3D_STRING Stats("Stats");
    const DREAM3D_STRING BoundaryArea("BoundaryArea");
    const DREAM3D_STRING PhaseFraction("PhaseFraction");
    const DREAM3D_STRING CrystalStructure("CrystalStructure");
    const DREAM3D_STRING PhaseType("PhaseType");
    const DREAM3D_STRING PrecipitateBoundaryFraction("Precipitate Boundary Fraction");
    const DREAM3D_STRING ParentPhase("Parent Phase");
    const DREAM3D_STRING Grain_Diameter_Info("Grain_Diameter_Info");
    const DREAM3D_STRING Grain_Size_Distribution("GrainSize Distribution");
    const DREAM3D_STRING Grain_SizeVBoverA_Distributions("GrainSize Vs B Over A Distributions");
    const DREAM3D_STRING Grain_SizeVCoverA_Distributions("GrainSize Vs C Over A Distributions");
    const DREAM3D_STRING Grain_SizeVNeighbors_Distributions("GrainSize Vs Neighbors Distributions");
    const DREAM3D_STRING Grain_SizeVOmega3_Distributions("GrainSize Vs Omega3 Distributions");
    const DREAM3D_STRING StatsType("StatsType");

    const DREAM3D_STRING StatsData("StatsData");
    const DREAM3D_STRING PrimaryStatsData("PrimaryStatsData");
    const DREAM3D_STRING PrecipitateStatsData("PrecipitateStatsData");
    const DREAM3D_STRING BoundaryStatsData("BoundaryStatsData");
    const DREAM3D_STRING MatrixStatsData("MatrixStatsData");
    const DREAM3D_STRING TransformationStatsData("TransformationStatsData");


    const DREAM3D_STRING BinNumber("BinNumber");

    const DREAM3D_STRING Average("Average");
    const DREAM3D_STRING StandardDeviation("Standard Deviation");

    const DREAM3D_STRING Alpha("Alpha");
    const DREAM3D_STRING Beta("Beta");
    const DREAM3D_STRING Exp_k("K");
    const DREAM3D_STRING MinimumValue("Minimum Value");

    const DREAM3D_STRING UnknownDistribution("Unknown Distribution");
    const DREAM3D_STRING DistributionType("Distribution Type");
    const DREAM3D_STRING BetaDistribution("Beta Distribution");
    const DREAM3D_STRING LogNormalDistribution("Log Normal Distribution");
    const DREAM3D_STRING PowerLawDistribution("Power Law Distribution");

    enum ColumnCount
    {
      BetaColumnCount = 2,       //!<
      LogNormalColumnCount = 2,  //!<
      PowerLawColumnCount = 2,   //!<
      UnknownColumCount = 0      //!<
    };
  }

  namespace PhaseType
  {
    const unsigned int PrimaryPhase = 0;              //!<
    const unsigned int PrecipitatePhase = 1;          //!<
    const unsigned int TransformationPhase = 2;       //!<
    const unsigned int MatrixPhase = 3;              //!<
    const unsigned int BoundaryPhase = 4;              //!<
    const unsigned int UnknownPhaseType = 999;    //!<

    const DREAM3D_STRING Primary("Primary");
    const DREAM3D_STRING Precipitate("Precipitate");
    const DREAM3D_STRING Transformation("Transformation");
    const DREAM3D_STRING Matrix("Matrix");
    const DREAM3D_STRING Boundary("Boundary");
  }

  namespace AlignmentMethod
  {
    const unsigned int OuterBoundary = 0;        //!<
    const unsigned int Misorientation = 1;       //!<
    const unsigned int MutualInformation = 2;    //!<
    const unsigned int Count = 3;                //!<
    const unsigned int UnknownAlignmentMethod = 999;    //!<
  }

  namespace StatisticsType
  {
    const unsigned int Grain_SizeVBoverA = 0;    //!<
    const unsigned int Grain_SizeVCoverA = 1;        //!<
    const unsigned int Grain_SizeVNeighbors = 2;     //!<
    const unsigned int Grain_SizeVOmega3 = 3;        //!<
    const unsigned int UnknownStatisticsGroup = 999;    //!<
  }

  namespace DistributionType
  {
    const unsigned int Beta = 0;         //!<
    const unsigned int LogNormal = 1;    //!<
    const unsigned int Power = 2;        //!<
    const unsigned int UnknownDistributionType = 3;    //!<
    const unsigned int Count = 3; //!<
  }

  namespace EulerAngleConversionType
  {
    const unsigned int DegreesToRadians = 0; //!<
    const unsigned int RadiansToDegrees = 1; //!<
  }

  namespace FlattenImageMethod
  {
    const unsigned int Lightness = 0; //!<
    const unsigned int Average = 1; //!<
    const unsigned int Luminosity = 2; //!<
  }

  namespace EulerFrameRotationAxis
  {
    const unsigned int RD = 0; //!<
    const unsigned int TD = 1; //!<
    const unsigned int ND = 2; //!<
    const unsigned int None = 3; //!<
  }

  namespace SampleFrameRotationAxis
  {
    const unsigned int X = 0; //!<
    const unsigned int Y = 1; //!<
    const unsigned int Z = 2; //!<
    const unsigned int None = 3; //!<
  }

  namespace RefFrameRotationAngle
  {
    const unsigned int Ninety = 0; //!<
    const unsigned int oneEighty = 1; //!<
    const unsigned int twoSeventy = 2; //!<
    const unsigned int Mirror = 3; //!<
    const unsigned int Zero = 4; //!<
  }

  namespace Overlap
  {
    const unsigned int Rigid = 0; //!<
    const unsigned int Progressive = 1; //!<
    const unsigned int UnknownOverlap = 999; //!<
  }

  namespace ShapeType
  {
    const unsigned int EllipsoidShape = 0; //!<
    const unsigned int SuperEllipsoidShape = 1; //!<
    const unsigned int CubeOctahedronShape = 2; //!<
    const unsigned int CylinderShape = 3; //!<
    const unsigned int UnknownShapeType = 999; //!<
  }

  namespace Precipitates
  {
    const unsigned int NoPrecipitates = 0; //!<
    const unsigned int BoundaryPrecipitates = 1; //!<
    const unsigned int BulkPrecipitates = 2; //!<
    const unsigned int UnknownPrecipitates = 999; //!<
  }

  namespace Reconstruction
  {
    /*    Reconstruction related */
    const DREAM3D_STRING H5VoxelFile("VoxelData.h5voxel");

    const DREAM3D_STRING VisualizationVizFile("Visualization.vtk");//11
    const DREAM3D_STRING DownSampledVizFile("DownSampled_Visualization.vtk");//11
    const DREAM3D_STRING HDF5GrainFile("Grains.h5grain");
  }

  namespace GrainData
  {
    const DREAM3D_STRING GrainID("Grain_ID");
    const DREAM3D_STRING PhaseID("Phase_ID");
    const DREAM3D_STRING Phi1("Phi1");
    const DREAM3D_STRING PHI("PHI");
    const DREAM3D_STRING Phi2("Phi2");
    const DREAM3D_STRING EquivDiam("Equiv_Diameter");
    const DREAM3D_STRING B_Over_A("b/a");
    const DREAM3D_STRING C_Over_A("c/a");
    const DREAM3D_STRING Omega3("Omega3");
    const DREAM3D_STRING SurfaceGrain("Surface_Grain");
    const DREAM3D_STRING OutsideBoundingBox("Outside_Bounding_Box");
    const DREAM3D_STRING NumNeighbors("No_Neighbors");
    const char Delimiter = ',';
  }

  namespace SyntheticBuilder
  {
    const DREAM3D_STRING GrainDataFile("GrainData.csv");
    const DREAM3D_STRING H5VoxelFile("VoxelData.h5voxel");

    const DREAM3D_STRING VisualizationVizFile("Visualization.vtk");
    const DREAM3D_STRING HDF5GrainFile("Grains.h5grain");

    const DREAM3D_STRING ErrorFile("Error.txt");
    const DREAM3D_STRING VtkFile("Test.vtk");
  }

  namespace MicroStats
  {
    const DREAM3D_STRING H5StatisticsFile("Results.h5stats");
    const DREAM3D_STRING GrainDataFile("GrainData.csv");//14
    const DREAM3D_STRING DeformationStatsFile("Deformation_Stats.txt");
    const DREAM3D_STRING IPFDeformVTKFile("IPF_DeformationData.vtk");
    const DREAM3D_STRING VoxelDataName("VoxelData");
  }

  /*   Surface Meshing Related   */
  namespace SurfaceMesh
  {
    namespace NodeType
    {
      const signed char Unused = 0;
      const signed char Default = 2;
      const signed char TriplePoint = 3;
      const signed char QuadPoint = 4;
      const signed char SurfaceDefault = 12;
      const signed char SurfaceTriplePoint = 13;
      const signed char SurfaceQuadPoint = 14;
    }
    namespace NodeId
    {
      const signed char Unused = -1;
    }
  }

  namespace SolidMeshing
  {
    /* Solid Meshing Related */
    const DREAM3D_STRING MeshFile("solid_mesh_v5_1.vtk");
    const DREAM3D_STRING MeshFile2("solid_mesh_v5_2.vtk");
    const DREAM3D_STRING ElementQualityFile("element_quality_measures_v5.txt");
    const DREAM3D_STRING VoxelsFile("voxels_v5.txt");
  }

  namespace Comparison
  {
    namespace Strings
    {
      const DREAM3D_STRING LessThan("<");
      const DREAM3D_STRING GreaterThan(">");
      const DREAM3D_STRING Equal("=");
    }
    enum Enumeration
    {
      Operator_LessThan = 0,
      Operator_GreaterThan,
      Operator_Equal,
      Operator_Unknown
    };

  }


}

#endif /* _DREAM3D_CONSTANTS_H_ */
