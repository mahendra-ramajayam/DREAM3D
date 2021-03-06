Merge Colonies {#mergecolonies}
======

## Group (Subgroup) ##
Reconstruction Filters (Grouping)

## Description ##
This Filter groups neighboring **Fields** that have a *"special"* misorientation that is associated with *alpha* variants that transformed from the same *beta* grain in titanium.  The algorithm for grouping the **Fields** is analogous to the algorithm for segmenting the **Fields** - only the average orientation of the **Fields** are used instead of the orientations of the individual **Cells** and the criterion for grouping is specific to the *alpha-beta transformation*.  The user can specify a tolerance on both the *axis* and the *angle* that defines the misorientation relationship (i.e. a tolerance of 1 degree for both tolerances would allow the neighboring **Fields** to be grouped if their misorientation was between 59-61 degrees about an axis within 1 degree of a2, as given by the 3rd *"special"* misorientation below).

The list of *"special"* misorientations can be found in the paper by Germain et al [1] and are listed here: 

| Angle | Axis |
|------|------|
| 0 | Identity |
| 10.529 | c = <0001> |
| 60 | a2 = <-12-10> |
| 60.832 | d1 at 80.97 degrees from c in the plane of (d3,c) |
| 63.262 | d2 at 72.73 degrees from c in the plane of (a2,c) |
| 90 | d3 at 5.26 degrees from a2 in the basal plane |

## Parameters ##

| Name | Type |
|------|------|
| Axis Tolerance | Double |
| Angle Tolerance | Double |

## Required DataContainers ##
Voxel

## Required Arrays ##

| Type | Default Name | Description | Comment | Filters Known to Create Data |
|------|--------------|-------------|---------|-----|
| Cell | GrainIds | Ids (ints) that specify to which **Field** each **Cell** belongs. | Values should be present from segmentation of experimental data or synthetic generation and cannot be determined by this filter. Not having these values will result in the filter to fail/not execute. | Segment Fields (Misorientation, C-Axis Misorientation, Scalar) (Reconstruction), Read Dx File (IO), Read Ph File (IO), Pack Primary Phases (SyntheticBuilding), Insert Precipitate Phases (SyntheticBuilding), Establish Matrix Phase (SyntheticBuilding) |
| Field | FieldPhases | Phase Id (int) specifying the phase of the **Field**| | Find Field Phases (Generic), Read Field Info File (IO), Pack Primary Phases (SyntheticBuilding), Insert Precipitate Phases (SyntheticBuilding), Establish Matrix Phase (SyntheticBuilding) |
| Field | AvgQuats | Five (5) values (floats) defining the average orientation of the **Field** in quaternion representation | Filter will calculate average quaternions for **Fields** if not already calculated. | Find Field Average Orientations (Statistics) |
| Ensemble | CrystalStructures | Enumeration (int) specifying the crystal structure of each Ensemble/phase (Hexagonal=0, Cubic=1, Orthorhombic=2) | Values should be present from experimental data or synthetic generation and cannot be determined by this filter. Not having these values will result in the filter to fail/not execute. | Read H5Ebsd File (IO), Read Ensemble Info File (IO), Initialize Synthetic Volume (SyntheticBuilding) |

## Created Arrays ##

| Type | Default Name | Description | Comment |
|------|--------------|-------------|---------|
| Field | Active | Boolean value specifying if the **Field** is still in the sample (1 if the **Field** is in the sample and 0 if it is not) | At the end of the filter, all **Fields** will be "Active" as the "Inactive" **Fields** will have been removed.  |

## Authors ##

**Copyright:** 2012 Michael A. Groeber (AFRL),2012 Michael A. Jackson (BlueQuartz Software)

**Contact Info:** dream3d@bluequartz.net

**Version:** 1.0.0

**License:**  See the License.txt file that came with DREAM3D.




See a bug? Does this documentation need updated with a citation? Send comments, corrections and additions to [The DREAM3D development team](mailto:dream3d@bluequartz.net?subject=Documentation%20Correction)

