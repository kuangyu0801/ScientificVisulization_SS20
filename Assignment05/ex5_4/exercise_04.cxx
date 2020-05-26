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

	//...

	// The following line accesses the data in the input object.
	// There are several ways to do this, the way below is very generic, and works for many VTK data objects and types.
	// Note that in this particular case, the data is stored as unsigned shorts.
	vtkSmartPointer<vtkUnsignedShortArray> scalarData = vtkUnsignedShortArray::SafeDownCast(input->GetPointData()->GetArray(0));

	// Step 2: Allocate Output Memory
	// Allocate an array to store gradient values, similar to last exercise. Use "Float" precision.

	//...

	// Step 3: Main Loop
	// Write the main loop going over all points of the input.
	// For each index, calculate the gradient using central differences, and store it in the array you created.
	// To do this, use the access funtions of the vtkUnsignedShortArray to get the data values.
	// The gradient array you allocated also provides similar functions to store the data.
	// Remember that you can simply set the boundary points' gradients to zero.
	
	//...

	// Step 4: Add Calculation Results to Output
	// Add the newly established gradient array to the point data of the output object, similar to last exercise.

	//...
}
