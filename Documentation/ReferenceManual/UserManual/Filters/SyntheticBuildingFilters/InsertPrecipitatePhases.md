Insert Precipitate Phases {#insertprecipitatephases}
======

## Group (Subgroup) ##
Synthetic Builder Filters (Packing)

## Description ##
If precipitate phases have been included in the _Statistics_ file used by the _Initialize Synthetic Volume_ Filter, _**Cells**_ are assigned based on the volume fraction of the precipitate phase.
 Periodic Boundary conditions are selected by the user to be active or inactive. 

## Parameters ##

| Name | Type |
|------|------|
| Periodic Boundary | Boolean (On or Off) |
| Write Goal Attributes | Boolean (On or Off) |
| Goal Attributes CSV File | Output File |


## Required DataContainers ##
Voxel

## Required Arrays ##

| Type | Default Name | Comment |
|------|--------------|---------|
| Cell | CellPhases |  |
| Cell | GrainIds |  |
| Cell | SurfaceVoxels |  |
| Ensemble | PhaseTypes |  |
| Ensemble | ShapeTypes |  |

## Created Arrays ##

| Type | Default Name | Comment |
|------|--------------|---------|
| Field | Active |  |

## Authors ##

**Copyright:** 2012 Michael A. Groeber (AFRL),2012 Michael A. Jackson (BlueQuartz Software)

**Contact Info:** dream3d@bluequartz.net

**Version:** 1.0.0

**License:**  See the License.txt file that came with DREAM3D.


