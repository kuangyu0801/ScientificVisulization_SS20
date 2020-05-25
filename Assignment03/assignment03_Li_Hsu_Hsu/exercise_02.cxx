#include "exercise_02.h"

#include "vtkCellData.h"
#include "vtkDataObject.h"
#include "vtkDoubleArray.h"
#include "vtkFloatArray.h"
#include "vtkInformation.h"
#include "vtkInformationVector.h"
#include "vtkObjectFactory.h"
#include "vtkPointData.h"
#include "vtkPolyData.h"
#include "vtkRectilinearGrid.h"
#include "vtkSmartPointer.h"
#include "vtkStreamingDemandDrivenPipeline.h"

#include <array>

vtkStandardNewMacro(exercise_02);

exercise_02::exercise_02()
{
    this->SetNumberOfInputPorts(1);
    this->SetNumberOfOutputPorts(1);
}

int exercise_02::FillInputPortInformation(int port, vtkInformation* info)
{
    if (port == 0)
    {
        info->Set(vtkAlgorithm::INPUT_REQUIRED_DATA_TYPE(), "vtkPolyData");
        return 1;
    }

    return 0;
}

int exercise_02::RequestInformation(vtkInformation*, vtkInformationVector**, vtkInformationVector* output_vector)
{
    return 1;
}

int exercise_02::RequestData(vtkInformation*, vtkInformationVector** input_vector, vtkInformationVector* output_vector)
{
    // retrieve pointers to input and output data
    auto inInfo = input_vector[0]->GetInformationObject(0);
    auto input = vtkPolyData::SafeDownCast(inInfo->Get(vtkDataObject::DATA_OBJECT()));

    auto outInfo = output_vector->GetInformationObject(0);
    auto output = vtkRectilinearGrid::SafeDownCast(outInfo->Get(vtkDataObject::DATA_OBJECT()));

    // retrieve bounding box, order: (xmin, xmax, ymin, ymax, zmin, zmax)
    std::array<double, 6> boundingBox;
    input->GetBounds(boundingBox.data());

    // TODO Calculate the measurements of the grid cells for each dimension
    //-----------------------------------------------------------------
    std::array<double, 3> cellWidths;

    cellWidths[0] = (boundingBox[1]-boundingBox[0]) / GridResolution[0];
    cellWidths[1] = (boundingBox[3]-boundingBox[2]) / GridResolution[1];
    cellWidths[2] = (boundingBox[5]-boundingBox[4]) / GridResolution[2];





    //-----------------------------------------------------------------
    // END of todo section

    // set the extent of the output
    std::array<int, 6> extent = { 0, GridResolution[0], 0, GridResolution[1], 0, GridResolution[2] };
    output->SetExtent(extent.data());

    auto xCoords = vtkSmartPointer<vtkDoubleArray>::New();
    auto yCoords = vtkSmartPointer<vtkDoubleArray>::New();
    auto zCoords = vtkSmartPointer<vtkDoubleArray>::New();

    xCoords->SetNumberOfComponents(1);
    yCoords->SetNumberOfComponents(1);
    zCoords->SetNumberOfComponents(1);

    // this describes the amount of cell border vertices for each direction, so it always has to 
    // be GridResolution + 1
    xCoords->SetNumberOfTuples(GridResolution[0] + 1);
    yCoords->SetNumberOfTuples(GridResolution[1] + 1);
    zCoords->SetNumberOfTuples(GridResolution[2] + 1);

    // TODO set the coordinates of the points describing the cell border vertices for each dimension seperately
    // this can be done for each single value using the ->SetComponent(<index>, 0, <coordinate>) method of the three fields
    //-------------------------------------------------------------------------------------------
    for (int x = 0; x <= GridResolution[0]; ++x) {
        // TODO set x-coordinate for the x-th vertex in x-direction
        xCoords->SetComponent(x, 0, x * cellWidths[0]);

    }
    for (int y = 0; y <= GridResolution[1]; ++y) {
        // TODO set y-coordinate for the y-th vertex in y-direction
        yCoords->SetComponent(y, 0, y * cellWidths[1]);
        
    }
    for (int z = 0; z <= GridResolution[2]; ++z) {
        // TODO set z-coordinate for the z-th vertex in z-direction
        zCoords->SetComponent(z, 0, z * cellWidths[2]);
        
    }
    //-------------------------------------------------------------------------------------------
    // END of todo section

    output->SetXCoordinates(xCoords);
    output->SetYCoordinates(yCoords);
    output->SetZCoordinates(zCoords);
 
    // allocate storage for the cell values
    vtkSmartPointer<vtkFloatArray> splattedData = vtkSmartPointer<vtkFloatArray>::New();
    splattedData->Initialize();
    splattedData->SetName("Density");
    splattedData->SetNumberOfComponents(1);
    splattedData->SetNumberOfValues(GridResolution[0] * GridResolution[1] * GridResolution[2]);
    splattedData->FillValue(0.0f); // initialize the result array with zeros.

    // iterate over all input particles
    for (vtkIdType i = 0; i < input->GetNumberOfPoints(); ++i) {
        // retrieve the point position
        std::array<double, 3> point;
        input->GetPoint(i, point.data());

        auto xCoord = point[0];
        auto yCoord = point[1];
        auto zCoord = point[2];

        vtkIdType cellIdx;

        // TODO calculate the index of the currently viewed cell.
        // First, calculate the index for each dimension seperately, then retrieve the global vertex index value (cellIdx) from the result.
        // Finally, increment the value of the found cell in the splattedData field by 1. Hint: The methods "SetValue" and "GetValue" might be useful
        //-----------------------------------------------------------------------------------------------------------
        // index for each dimension
        
        if(point[0]/cellWidths[0]==int(point[0]/cellWidths[0]) && point[0]/cellWidths[0]!=0)
            xCoord = point[0] / cellWidths[0] -1;
        else
            xCoord = point[0] / cellWidths[0];

        if(point[1]/cellWidths[1]==int(point[1]/cellWidths[1]) && point[1]/cellWidths[1]!=0)
            yCoord = point[1] / cellWidths[1] -1;
        else
            yCoord = point[1] / cellWidths[1];

        if(point[2]/cellWidths[2]==int(point[2]/cellWidths[2]) && point[2]/cellWidths[2]!=0)
            zCoord = point[2] / cellWidths[2] -1;
        else
            zCoord = point[2] / cellWidths[2];	

        //global vertex index value
        cellIdx = xCoord + yCoord*(GridResolution[0]) + zCoord*(GridResolution[1])*(GridResolution[0]);

        //increment
        int64_t currentValue;
		currentValue = splattedData->GetValue(i);
		splattedData->SetValue(cellIdx, currentValue+1);

        

        //-----------------------------------------------------------------------------------------------------------
        // END of todo section
    }

    output->GetCellData()->AddArray(splattedData);
    return 1;
}
