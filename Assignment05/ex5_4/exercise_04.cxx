#include "vtkObjectFactory.h"
#include "vtkSmartPointer.h"
#include "vtkUnsignedShortArray.h"
#include "vtkFloatArray.h"
#include "vtkPointData.h"
#include "vtkImageData.h"
#include "vtkMath.h"

#include "exercise_04.h"

vtkStandardNewMacro(exercise_04);

/// <summary>
/// Function executed by ParaView when requesting data
/// </summary>
/// <param name="input">Input image data</param>
/// <param name="output">Output image data</param>
void exercise_04::SimpleExecute(vtkImageData* input, vtkImageData* output)
{
	// Copy everything from input to output
	output->DeepCopy(input);

	// Step 1: Retrieve Information about the Data
	// Get the size of your regular input grid, so you know your loop constraints and identify boundaries
    // get the boundary xmin, xmax, ymin, ymax, zmin, zmax
    int *inExt = input->GetExtent();
    int xmin = inExt[0];
	int xmax = inExt[1];
	int ymin = inExt[2];
	int ymax = inExt[3];
	int zmin = inExt[4];
	int zmax = inExt[5];

	// get x, y, z dimensions
	int *dims = input->GetDimensions();
	int sliceSize = dims[0] * dims[1];
	//...

	// The following line accesses the data in the input object.
	// There are several ways to do this, the way below is very generic, and works for many VTK data objects and types.
	// Note that in this particular case, the data is stored as unsigned shorts.
	vtkSmartPointer<vtkUnsignedShortArray> scalarData = vtkUnsignedShortArray::SafeDownCast(input->GetPointData()->GetArray(0));

	// Step 2: Allocate Output Memory
	// Allocate an array to store gradient values, similar to last exercise. Use "Float" precision.
	vtkSmartPointer<vtkFloatArray> gradientVector = vtkSmartPointer<vtkFloatArray>::New();
    gradientVector->Initialize();
    gradientVector->SetName("Gradient");
    gradientVector->SetNumberOfComponents(3);
    gradientVector->SetNumberOfTuples(input->GetNumberOfPoints());
    gradientVector->FillValue(0.0f); // initialize the result array with zeros.
	//...

	// Step 3: Main Loop
	// Write the main loop going over all points of the input.
	// For each index, calculate the gradient using central differences, and store it in the array you created.
	// To do this, use the access funtions of the vtkUnsignedShortArray to get the data values.
	// The gradient array you allocated also provides similar functions to store the data.
	// Remember that you can simply set the boundary points' gradients to zero.

	// skip the boundaries in loop since all points are already initialized with zeros
    // Traverse input data and calculate gradient

    for (vtkIdType k = (zmin +1); k < zmax; k += 1) {
        int kOffset = (k - zmin) * sliceSize;

        for (vtkIdType j = (ymin + 1); j < ymax; j += 1) {
            int jOffset = (j - ymin) * dims[0];

            for (vtkIdType i = (xmin + 1); i < xmax; i += 1) {

                // i +/- 1, j +/- dims[0], k +/i dims[0]*dims[1]
                int diff[3] = {1, dims[0], sliceSize};
                int index = (i - xmin) + jOffset + kOffset;
                // getting f(i-1, j, k), f(i+1, j, k)
                for (int comIndex = 0; comIndex < 3; comIndex += 1) {
                    unsigned short int valuePlus = scalarData->GetValue(index + diff[comIndex]);
                    unsigned short int valueMinus = scalarData->GetValue(index - diff[comIndex]);
                    float gradient = (float) (valuePlus - valueMinus) / 2;
                    gradientVector->SetComponent(index, comIndex, gradient);
                }
            }
        }
	}

	//...

	// Step 4: Add Calculation Results to Output
	// Add the newly established gradient array to the point data of the output object, similar to last exercise.
    output->GetPointData()->AddArray(gradientVector);
	//...
}
